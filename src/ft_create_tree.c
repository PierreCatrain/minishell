/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_tree.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 02:02:25 by picatrai          #+#    #+#             */
/*   Updated: 2024/01/17 07:03:19 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char **ft_strdup_2d(char **str)
{
    char **new;
    int index;
    
    new = malloc((ft_strlen_2d(str) + 1) * sizeof(char));
    if (new == NULL)
        return (free_2d(str), NULL);
    index = -1;
    while (str[++index])
    {
        new[index] = ft_strdup(str[index]);
        if (new[index] == NULL)
            return (free_2d(str), ft_free_2d_index(new, index), NULL);
    }
    new[index] = NULL;
    return (free_2d(str), new);
}

t_tree  *ft_new_tree(char *cmd, char **args, int fd_in, int fd_out)
{
    t_tree *new;

    new = malloc(sizeof(t_tree));
    if (new == NULL)
        return (NULL);
    new->cmd = ft_strdup(cmd);
    if (new->cmd == NULL)
        return (free(new), NULL);
    new->args = ft_strdup_2d(args);
    if (new->args == NULL)
        return (free(new->cmd), free(new), NULL);
    new->fd_in = fd_in;
    new->fd_out = fd_out;
    return (new);
}

t_tree  *ft_tree_last(t_tree *tree)
{
    while (tree->next != NULL)
        tree = tree->next;
    return (tree);
}

int ft_tree_add_back(t_tree **tree, t_tree *new)
{
    if (new == NULL)
        return (ERROR_MALLOC);
    if (*tree == NULL)
    {
        *tree = new;
        return (SUCCESS);
    }
    new->prev = ft_tree_last(*tree);
    ft_tree_last(*tree)->next = new;
    return (SUCCESS);
}

int ft_nb_pipes(t_token *token)
{
    int count;

    count = 0;
    while (token != NULL)
    {
        if (token->type == PIPE)
            count++;
        token = token->next;
    }
    return (count);
}

int ft_create_tree(t_tree **tree, t_token *token)
{
    t_token *tmp;
    char *heredoc;
    int fd_in;
    int fd_out;
    char *cmd_tmp;
    char **args_tmp;
    int index_pipes;
    int **fd_pipes;
    int nb_pipes;

    printf("debut\n");
    nb_pipes = ft_nb_pipes(token);
    fd_pipes = malloc (nb_pipes * sizeof(int *));
    if (fd_pipes == NULL)
        return (ERROR_MALLOC);
    index_pipes = -1;
    while (++index_pipes <= nb_pipes)
    {
        fd_pipes[index_pipes] = malloc(2 * sizeof(int));
        if (fd_pipes[index_pipes] == NULL)
            return (ERROR_MALLOC);
        if (pipe(fd_pipes[index_pipes]) == -1)
            return (ERROR_PIPE);
    }
    index_pipes = 0;
    fd_in = 0;
    fd_out = 1;
    cmd_tmp = NULL;
    args_tmp = NULL;
    tmp = token;
    printf("fin\n");
    while (token != NULL)
    {
        if (token->type == INFILE)
        {
            if (fd_in != 0)
            {
                if (ft_tree_add_back(tree, ft_new_tree(cmd_tmp, args_tmp, fd_in, fd_out)) == ERROR_MALLOC)
                    return (ERROR_MALLOC);
                free(cmd_tmp);
                cmd_tmp = NULL;
                free_2d(args_tmp);
                args_tmp = NULL;
                fd_in = 0;
                fd_out = 1;
            }
            token = token->next;
            fd_in = open(token->str, O_RDONLY, 0644);
            if (fd_in < 0)
                return (ERROR_FILE);
            if (token->next != NULL)
                token = token->next;
        }
        else if (token->type == OUTFILE)
        {
            if (fd_out != 1)
            {
                if (ft_tree_add_back(tree, ft_new_tree(cmd_tmp, args_tmp, fd_in, fd_out)) == ERROR_MALLOC)
                    return (ERROR_MALLOC);
                free(cmd_tmp);
                cmd_tmp = NULL;
                free_2d(args_tmp);
                args_tmp = NULL;
                fd_in = 0;
                fd_out = 1;
            }
            token = token->next;
            fd_out = open(token->str, O_CREAT, O_WRONLY, O_TRUNC, 0644);
            if (fd_out < 0)
                return (ERROR_FILE);
            if (token->next != NULL)
                token = token->next;
        }
        else if (token->type == APPEND)
        {
            if (fd_out != 1)
            {
                if (ft_tree_add_back(tree, ft_new_tree(cmd_tmp, args_tmp, fd_in, fd_out)) == ERROR_MALLOC)
                    return (ERROR_MALLOC);
                free(cmd_tmp);
                cmd_tmp = NULL;
                free_2d(args_tmp);
                args_tmp = NULL;
                fd_in = 0;
                fd_out = 1;
            }
            token = token->next;
            fd_out = open(token->str, O_CREAT, O_WRONLY, O_APPEND, 0644);
            if (fd_out < 0)
                return (ERROR_FILE);
            if (token->next != NULL)
                token = token->next;
        }
        else if (token->type == HEREDOC)
        {
            if (fd_in != 1)
            {
                if (ft_tree_add_back(tree, ft_new_tree(cmd_tmp, args_tmp, fd_in, fd_out)) == ERROR_MALLOC)
                    return (ERROR_MALLOC);
                free(cmd_tmp);
                cmd_tmp = NULL;
                free_2d(args_tmp);
                args_tmp = NULL;
                fd_in = 0;
                fd_out = 1;
            }
            token = token->next;
            heredoc = ft_here_doc();
            if (heredoc == NULL)
                return (ERROR_FILE);
            fd_in = open(heredoc, O_CREAT, O_WRONLY, O_TRUNC, 0644);
            if (fd_in < 0)
                return (ERROR_FILE);
            ft_complete(fd_in, token);
            close(fd_in);
            fd_in = open(heredoc, O_RDONLY, 0644);
            if (fd_in < 0)
                return (ERROR_FILE);
            unlink(heredoc);
            free(heredoc);
            if (token->next != NULL)
                token = token->next;
        }
        else if (token->type == PIPE)
        {
            fd_out = fd_pipes[index_pipes][1];
            if (ft_tree_add_back(tree, ft_new_tree(cmd_tmp, args_tmp, fd_in, fd_out)) == ERROR_MALLOC)
                    return (ERROR_MALLOC);
            free(cmd_tmp);
            cmd_tmp = NULL;
            free_2d(args_tmp);
            args_tmp = NULL;
            fd_in = fd_pipes[index_pipes++][0];
            fd_out = 1;
        }
        else
        {
            if (cmd_tmp == NULL)
            {
                cmd_tmp = ft_strdup(token->str);
                if (cmd_tmp == NULL)
                    return (ERROR_MALLOC);
            }
            args_tmp = ft_join_2d(args_tmp, token->str);
            if (args_tmp == NULL)
                return (ERROR_MALLOC);
        }
        printf("tour\n");
        // on passe au suivant
        if (token->next == NULL)
            break;
        token = token->next;
    }
    printf("plus dans la boucle\n");
    if (ft_tree_add_back(tree, ft_new_tree(cmd_tmp, args_tmp, fd_in, fd_out)) == ERROR_MALLOC)
        return (ERROR_MALLOC);
    free(cmd_tmp);
    cmd_tmp = NULL;
    printf("plus dans la boucle\n");
    //free_2d(args_tmp);
    args_tmp = NULL;
    fd_in = 0;
    fd_out = 1;
    return (SUCCESS);
}
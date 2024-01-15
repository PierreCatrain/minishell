/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bac_a_sable.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 00:02:14 by picatrai          #+#    #+#             */
/*   Updated: 2024/01/15 00:02:57 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char *ft_str_isolate(char *str, int index_debut, int index_fin)
{
    char *new_str;
    int index_new_str;

    new_str = malloc((index_fin - index_debut + 1) * sizeof(char));
    if (new_str == NULL)
        return (NULL);
    index_new_str = 0;
    while (index_debut + index_new_str < index_fin)
    {
        new_str[index_new_str] = str[index_debut + index_new_str];
        index_new_str++;
    }
    new_str[index_new_str] = '\0';
    return (new_str);
}

char *ft_strjoin_two_malloc(char *new_str, char *str_tmp)
{
    char *join;
    int i;
    int j;
    
    join = malloc ((ft_strlen(new_str) + ft_strlen(str_tmp) + 1) * sizeof(char));
    if (join == NULL)
        return (free(new_str), free(str_tmp), NULL);
    i = -1;
    while (new_str[++i])
        join[i] = new_str[i];
    j = -1;
    while (str_tmp[++j])
        join[i + j] = str_tmp[j];
    join[i + j] = '\0';
    return (free(new_str), free(str_tmp), join);
}

char *ft_strjoin_one_malloc(char *new_str, char *str_tmp)
{
    char *join;
    int i;
    int j;
    
    if (str_tmp == NULL)
        return (new_str);
    join = malloc ((ft_strlen(new_str) + ft_strlen(str_tmp) + 1) * sizeof(char));
    if (join == NULL)
        return (free(new_str), NULL);
    i = -1;
    while (new_str[++i])
        join[i] = new_str[i];
    j = -1;
    while (str_tmp[++j])
        join[i + j] = str_tmp[j];
    join[i + j] = '\0';
    return (free(new_str), join);
}

char *ft_replace_dollars(char *str)
{
    char *new_str;
    char *str_tmp;
    int index;
    int index_tmp;
    int start_dollar;

    start_dollar = NOT_START_DOLLAR;
    if (str[0] == '$')
        start_dollar = START_DOLLAR;
    index = 0;
    new_str = malloc (sizeof(char));
    if (new_str == NULL)
        return (NULL);
    new_str[0] = '\0';
    while (str[index])
    {
        index_tmp = 0;
        while (str[index + index_tmp] && ft_occ("$\'", str[index + index_tmp] == 0)) // faire la liste des caracteres de fin de variable d'env
            index_tmp++;
        str_tmp = ft_str_isolate(str, index, index + index_tmp);
        if (str_tmp == NULL)
            return (NULL);
        if (start_dollar == NOT_START_DOLLAR && index == 0)
        {
            new_str = ft_strjoin_two_malloc(new_str, str_tmp);
            if (new_str == NULL)
                return (NULL);
        }
        else
        {
            new_str = ft_strjoin_one_malloc(new_str, getenv(str_tmp));
            if (new_str == NULL)
                return (free(str_tmp), NULL);
            free(str_tmp);
        }
        index += index_tmp;
        if (str[index])
            index++;
        //while (str[index] && ft_occ("~`", str[index]) != 0)
        //    index++;
    }
    if (str[ft_strlen(str) - 1] == '$')
    {
        new_str = ft_strjoin_one_malloc(new_str, "$");
        if (new_str == NULL)
            return (NULL);
    }
    return (new_str);
}

// on parcourt tout les tokens et on envoie que les mot et double quotes dans la transpho
int     ft_replace_env_variable(t_token **token)
{
    while (*token != NULL)
    {
        if ((*token)->type != SINGLE_QUOTES && ft_occ((*token)->str, '$') != 0)
        {
            (*token)->str = ft_replace_dollars((*token)->str);
            if ((*token)->str == NULL)
                return (ERROR_MALLOC);
        }
        if ((*token)->next == NULL)
            break;
        else
            *token = (*token)->next;
    }
    while ((*token)->prev != NULL)// pas forcement utils ca
        *token = (*token)->prev;
    return (SUCCESS);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_prompt.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 21:50:13 by picatrai          #+#    #+#             */
/*   Updated: 2024/01/12 01:45:02 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char    *ft_get_username(void)
{
    char *username;
    char *str;
    int index;

    str = getenv("USER");
    if (str == NULL)
        return (NULL);
    username = malloc ((ft_strlen(str) + 2) * sizeof(char));
    if (username == NULL)
        return (NULL);
    index = -1;
    while (str[++index])
        username[index] = str[index];
    username[index] = '@';
    username[++index] = '\0';
    return (username);
}

char *ft_add_device(char *prompt)
{
    char *device;
    char *str;
    int i;
    int j;

    str = getenv("SESSION_MANAGER");
    if (str == NULL)
        return (free(prompt), NULL);
    str += 6;
    i = 0;
    while (str[i] && str[i] != '.')
        i++;
    device = malloc ((i + 2) * sizeof(char));
    if (device == NULL)
        return (free(prompt), NULL);
    i = -1;
    while (prompt[++i])
        device[i] = prompt[i];
    j = 0;
    while (str[j] && str[j] != '.')
    {
        device[i + j] = str[j];
        j++;
    }
    device[i + j++] = ':';
    device[i + j] = '\0';
    return (free(prompt), device);
}

char *ft_get_start_prompt(void)
{
    char *prompt;
    
    prompt = ft_get_username();
    if (prompt == NULL)
        return (NULL);
    prompt = ft_add_device(prompt);
    if (prompt == NULL)
        return (NULL);
    return (prompt);
}

char *ft_at_home(char *start_prompt, char *str)
{
    char *prompt;
    int i;
    int j;
    
    prompt = malloc ((ft_strlen(start_prompt) + 8) * sizeof(char));
    if (prompt == NULL)
        return (NULL);
    i = -1;
    while (start_prompt[++i])
        prompt[i] = start_prompt[i];
    j = -1;
    while (++j <= 5)
        prompt[i + j] = str[j];
    prompt[i + j] = '$';
    prompt[i + ++j] = ' ';
    prompt[i + ++j] = '\0';
    return (prompt);
}

char *ft_at_user(char *start_prompt)
{
    char *prompt;
    int i;
    
    prompt = malloc ((ft_strlen(start_prompt) + 3) * sizeof(char));
    if (prompt == NULL)
        return (NULL);
    i = -1;
    while (start_prompt[++i])
        prompt[i] = start_prompt[i];
    prompt[i] = '$';
    prompt[++i] = ' ';
    prompt[++i] = '\0';
    return (prompt);
}

char *ft_at_else(char *start_prompt, char *str)
{
    char *prompt;
    int i;
    int j;
    int count;

    i = -1;
    count = 0;
    while (str[++i] && count < 3)
    {
        if (str[i] == '/')
            count++;
    }
    i--;
    prompt = malloc ((ft_strlen(start_prompt) + ft_strlen(str) - i + 4) * sizeof(char));
    if (prompt == NULL)
        return (NULL);
    j = -1;
    while (start_prompt[++j])
        prompt[j] = start_prompt[j];
    prompt[j++] = '~';
    while (str[i])
        prompt[j++] = str[i++];
    prompt[j++] = '$';
    prompt[j++] = ' ';
    prompt[j] = '\0';
    return (prompt);
}

char *ft_get_prompt(char *start_prompt)
{
    char *prompt;
    char *str;

    str = getenv("PWD");
    if (str == NULL)
        return (NULL);
    else if (ft_occ(str, '/') == 1)
    {
        prompt = ft_at_home(start_prompt, str);
        return (prompt);
    }
    else if (ft_occ(str, '/') == 1)
    {
        prompt = ft_at_user(start_prompt);
        return (prompt);
    }
    prompt = ft_at_else(start_prompt, str);
    return (prompt);
}

void    ft_put_prompt(char **envp)
{
    char *prompt;
    char *start_prompt;
    char *str;

    envp = (char **)envp;
    start_prompt = ft_get_start_prompt();
    if (start_prompt == NULL)
        return ;
    while (1)
    {
        prompt = ft_get_prompt(start_prompt);
        if (prompt == NULL)
           return (free(str), free(start_prompt)); // attention str est pas forcement alloue ici
        str = readline(prompt);
        if (ft_strncmp(str, "exit", 4) == 0 && ft_strlen(str) == 4)
            break;
        free(str);
        free(prompt);
    }
    free(str);
    free(prompt);
    return ;
}
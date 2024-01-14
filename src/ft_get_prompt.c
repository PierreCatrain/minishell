/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_prompt.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 21:50:13 by picatrai          #+#    #+#             */
/*   Updated: 2024/01/14 04:38:29 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char *ft_at_home(char *start_prompt, char *end_prompt, char *str)
{
    char *prompt;
    int i;
    int j;
    
    prompt = malloc ((ft_strlen(start_prompt) + ft_strlen(end_prompt) + 6) * sizeof(char));
    if (prompt == NULL)
        return (NULL);
    i = -1;
    while (start_prompt[++i])
        prompt[i] = start_prompt[i];
    j = -1;
    while (++j <= 5)
        prompt[i + j] = str[j];
    i += j;
    j = -1;
    while (end_prompt[++j])
        prompt[i + j] = end_prompt[j];
    prompt[i + j] = '\0';
    return (prompt);
}

char *ft_at_user(char *start_prompt, char *end_prompt)
{
    char *prompt;
    int i;

    prompt = malloc ((ft_strlen(start_prompt) + ft_strlen(end_prompt) + 2) * sizeof(char));
    if (prompt == NULL)
        return (NULL);
    i = -1;
    while (start_prompt[++i])
        prompt[i] = start_prompt[i];
    prompt[i] = '$';
    while (end_prompt[++i])
        prompt[i] = end_prompt[i];
    prompt[++i] = '\0';
    return (prompt);
}

char *ft_at_else(char *start_prompt, char *end_prompt, char *str)
{
    char *prompt;
    int i;
    int j;

    i = -1;
    j = 0;
    while (str[++i] && j < 3)
    {
        if (str[i] == '/')
            j++;
    }
    prompt = malloc ((ft_strlen(start_prompt) + ft_strlen(end_prompt) + ft_strlen(str) - i-- + 3) * sizeof(char));
    if (prompt == NULL)
        return (NULL);
    j = -1;
    while (start_prompt[++j])
        prompt[j] = start_prompt[j];
    prompt[j++] = '~';
    while (str[i])
        prompt[j++] = str[i++];
    i = -1;
    while (end_prompt[++i])
        prompt[j + i] = end_prompt[i];
    prompt[j + i] = '\0';
    return (prompt);
}

// on creer le prompt que l'on vas afficher
// le prompt est compose d'un debut et d'une fin qui entoure le WD
// on determine le WD en fonciton de si on est dans home dans user ou le rest
// example /home pour home et ~ pour user et ~/En travaux/minishell pour des enfants de user
char *ft_get_prompt(void)
{
    char *prompt;
    char *start_prompt;
    char *end_prompt;
    char wd[WD_BUFFER_SIZE];

    start_prompt = ft_get_str("\033[1;33m minishell \033[1;34mWD:(\033[1;31m");
    end_prompt = ft_get_str("\033[1;34m)\033[1;33m ~ \033[0m");
    if (getcwd(wd, WD_BUFFER_SIZE) == NULL)
        return (NULL);
    if (ft_occ(wd, '/') == 1)
    {
        prompt = ft_at_home(start_prompt, end_prompt, wd);
        return (prompt);
    }
    else if (ft_occ(wd, '/') == 2)
    {
        prompt = ft_at_user(start_prompt, end_prompt);
        return (prompt);
    }
    prompt = ft_at_else(start_prompt, end_prompt, wd);
    return (prompt);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 18:48:57 by picatrai          #+#    #+#             */
/*   Updated: 2024/02/12 07:23:56 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <sys/types.h>
# include <dirent.h>
# include <errno.h>
# include <limits.h>
# include <linux/limits.h>
# include <sys/wait.h>
# include <signal.h>

extern long long int g_exit_status;

# define SUCCESS 0
# define ERROR_ARGC_ENVP 1
# define ERROR_PROMPT 2
# define ERROR_MALLOC 3
# define ERROR_PIPE 4
# define ERROR_FILE 5
# define ERROR 6
# define GOOD_INPUT 0
# define WRONG_INPUT 1
# define WD_BUFFER_SIZE 5000
# define OPEN 0
# define CLOSE 1
# define WORD 1
# define SINGLE_QUOTES 2
# define DOUBLE_QUOTES 3
# define START_DOLLAR 0
# define NOT_START_DOLLAR 1
# define NOT_YET 0
# define YES 1
# define ADD 0
# define DONT_ADD 1

enum e_token_type
{
    TEXT = 0,
    PIPE,
    INFILE,
    OUTFILE,
    HEREDOC,
    APPEND,
    INFILE_TEXT,
    OUTFILE_TEXT,
    HEREDOC_TEXT,
    APPEND_TEXT,
    AND,
    OR,
    OPEN_PARENTHESIS,
    CLOSE_PARENTHESIS,
    CMD,
    ARGS,
};

enum e_tree_type
{
    EXEC_LIST = 0,
    OPPERATOR_AND,
    OPPERATOR_OR,
};

typedef struct s_lst_exec // suite d'execution // attention les fd peuvent etre -1 mais sont tous (sauf les -1) a fermer
{
    struct s_lst_exec *prev;
    struct s_lst_exec *next;
    char **args;
    int fd_in;
    int fd_out;
} t_lst_exec;

typedef struct s_tree // arbre binaire
{
    int type;
    struct s_tree *parent;
    struct s_tree *left_child;
    struct s_tree *right_child;
    t_lst_exec *lst_exec;
} t_tree;

typedef struct s_token
{
    char *str;
    int quotes;
    int type;
    struct s_token *prev;
    struct s_token *next;
}   t_token;

typedef struct s_data_parse
{
    t_token *token;
    int double_quote_open;
    int single_quote_open;
    int new_word;
    int index_str;
    int index;
    char *str;
    char *prompt;
    char *input;

    int index_new_str;

    char	*before;
	char	*after;
	int	i;
	int	part;

    char	*heredoc;
	int			fd_in;
	int			fd_out;
	char	**args_tmp;
	int			index_pipes;
	int		**fd_pipes;
	int			nb_pipes;

    int *array_here_doc;
    int index_here_doc;
}   t_data_parse;

typedef struct s_wildcard
{
    struct s_wildcard *prev;
    struct s_wildcard *next;
    char *str;
} t_wildcard;

enum bool
{
    FALSE = 0,
    TRUE
};

//ft_check_argc_envp.c
int ft_check_argc_envp(int argc, char **argv);

//ft_get_prompt.c
char *ft_get_prompt(void);

//signaux.c
int ft_set_sig(void);

//ft_parse.c
int ft_parse(t_tree **tree, t_data_parse *data_parse);

//ft_tokenisation.c
int ft_tokenisation(t_token **token, t_data_parse *data_parse);

//ft_token_part_1.c
int ft_token_part_1(t_data_parse *data_parse, t_token **token);

//ft_token_part_2.c
int ft_token_part_2(t_data_parse *data_parse, t_token **token);

//ft_isolate_operateur.c
int ft_isolate_operateur(t_token **token);

//ft_isolate_operateur_2.c
int ft_is_type_2(t_token **token, t_data_parse *data_parse);
int ft_insert_operateur_type_2(t_token **token, t_data_parse *data_parse);
int ft_is_type_1(t_token **token, t_data_parse *data_parse);
int ft_insert_operateur_type_1(t_token **token, t_data_parse *data_parse);

//ft_isolate_operateur_3.c
t_token	*ft_lstnew_no_malloc(char *str, int quotes, int type);
char	*ft_str_rev(char *str);
int	is_token_valid(char *str);
int ft_do_insert(t_token **token, t_data_parse *data_parse, char *opperator, int type);

// # ====================================================== #
// |														|
// |			FT_REPLACE_ENV_VARIABLE.C		            |
// |														|
// # ====================================================== #

int     ft_replace_env_variable(t_token **token);

//ft_replace_wildcard.c
int ft_replace_wildcard(t_token **token);

//ft_replace_wildcard_2.c
void	ft_complete_before_after(t_data_parse *data_parse, t_token **token);
int ft_insert_wildcard_before_after(t_wildcard *ls, t_data_parse *data_parse, t_token **token, int *find);
int	ft_wildcard_before_and_after(t_token **token, t_wildcard *ls, int *find);
int ft_wildcard_no_before_no_after(t_wildcard **ls, t_token **token, int *find);

//ft_replace_wildcard_3.c
void	ft_free_wildcard(t_wildcard **ls);
int	ft_strlen_before(char *str);
int	ft_strlen_after(char *str);
char	*ft_only_end_str(char *str, int size);
int	match_with_wildcard(char *before, char *after, char *str);

//ft_replace_wildcard_4.c
char	*ft_strjoin_1_malloc(char *str1, char *str2);
t_wildcard	*ft_lst_wildcard_new(char *str);
t_wildcard	*ft_lst_wildcard_last(t_wildcard *ls);
int	ft_lst_wildcard_add_back(t_wildcard **ls, t_wildcard *new);
int	set_ls(t_wildcard **ls);

//ft_set_all_grammaire.c
// # ====================================================== #
// |														|
// |			FT_SET_ALL_GRAMMAIRE.C				        |
// |														|
// # ====================================================== #

void ft_set_all_grammaire(t_token **token);
int ft_is_quote_close(char *input, int double_quote_open, int single_quote_open);

// # ====================================================== #
// |														|
// |			FT_CONDITION_GRAMMAIRE.C		        	|
// |														|
// # ====================================================== #
int ft_condition_grammaire(t_token *token);

// ft_condition_grammaire_2.c
int	ft_check_pipes(t_token *token);
int	is_redirection_well_followed(t_token *token);

// # ====================================================== #
// |														|
// |			    FT_CREATE_TREE,C    			        |
// |		        										|
// # ====================================================== #
int ft_create_tree(t_tree **tree, t_token *token, t_data_parse *data_parse);
int ft_lst_exec(t_token *token, t_lst_exec **lst_exec, t_data_parse *data_parse);

//ft_create_tree_2.c
int ft_complete_tree(t_tree **tree, t_token *token, t_data_parse *data_parse);

//ft_create_tree_3.c
char	**ft_strdup_2d(char **str);
t_lst_exec	*ft_new_lst_exec(char **args, int fd_in, int fd_out);
t_lst_exec	*ft_lst_exec_last(t_lst_exec *lst_exec);
int	ft_lst_exec_add_back(t_lst_exec **lst_exec, t_lst_exec *new);
int	ft_nb_pipes(t_token *token);

//ft_create_tree_4.c
void	ft_free_pipes(int **fd_pipes, int nb_pipes);
void	ft_pipes_fail(int **fd_pipes, int index_pipes);
int	ft_one_more_exec(t_data_parse *data_parse, t_lst_exec **lst_exec);
int	ft_set_exec(t_data_parse *data_parse, t_lst_exec **lst_exec, t_token *token);
int	ft_exec_token_type_1(t_data_parse *data_parse, t_lst_exec **lst_exec, t_token *token);

//ft_create_tree_5.c
void	ft_exec_token_type_2(t_data_parse *data_parse, t_token *token);
int	ft_exec_token_type_heredoc(t_data_parse *data_parse, t_token **token);
int	ft_exec_token_type_pipe(t_data_parse *data_parse, t_lst_exec **lst_exec);
int ft_is_token_type_1(t_token *token);
int ft_is_token_type_2(t_token *token);

//ft_create_tree_6.c
int	ft_add_left_child(t_tree **tree, t_tree *new);
int	ft_add_right_child(t_tree **tree, t_tree *new);
t_tree	*ft_tree_new(int type);
t_token	*before_token(t_token *token);
t_token	*after_token(t_token *token);

//ft_create_tree_7.c
int	ft_is_there_parenthesis(t_token *token);
t_token	*without_parenthesis(t_token *token);
t_tree	*ft_first_empty_child(t_tree *tree);
int	ft_add_tree_null(t_tree **tree, t_tree *new, t_token *token, t_data_parse *data_parse);
int	ft_add_tree_no_null(t_tree **tree, t_tree *new, t_token *token, t_data_parse *data_parse);

// # ====================================================== #
// |														|
// |					FT_HERE_DOC.C						|
// |														|
// # ====================================================== #

char *ft_here_doc(void);
void	ft_complete(int fd_in, t_token *token);

//ft_complete_here_doc.c
int ft_complete_here_doc(t_data_parse *data_parse, t_token *token);


// # ====================================================== #
// |														|
// |					FT_UTILS.C  						|
// |														|
// # ====================================================== #

void	ft_putstr_fd(char *s, int fd);
int ft_strlen(char *str);
int	ft_strncmp(char *s1, char *s2, int n);
int ft_occ(char *str, char c);
int ft_strchr(char *str, char *find);

// # ====================================================== #
// |														|
// |					FT_UTILS_2.C						|
// |														|
// # ====================================================== #

t_token    *ft_lstlast(t_token *token);
t_token *ft_lstnew(char *str, int quotes, int type);
int    ft_lst_add_back(t_token **token, t_token *new);
int ft_lst_insert(t_token **token, t_token *new);
void ft_lst_del(t_token **token);

// # ====================================================== #
// |														|
// |					FT_UTILS_3.C						|
// |														|
// # ====================================================== #

int	ft_lstsize(t_token *token);
void    ft_print_token(t_token **token);
int	ft_isalphanum(int c);
int ft_strcmp(char *str1, char *str2);
void	ft_printf_2d(char **str);

// # ====================================================== #
// |														|
// |	                FT_UTILS_4.C						|
// |														|
// # ====================================================== #

void    ft_free_2d_index(char **str, int index);
int ft_strlen_2d(char **str);
char **ft_join_2d_args_null(char *str, char **new);
char **ft_join_2d(char **args_cmd, char *str);
int is_input_only_whitespace(char *str);

// # ====================================================== #
// |														|
// |	                FT_UTILS_5.C						|
// |														|
// # ====================================================== #

char	**ft_split(char *s, char c);
char	*ft_strjoin_path(char *s1, char *s2);

//ft_utils_6.c
void    ft_print_tree(t_tree *tree);
void	ft_print_lst_exec(t_lst_exec *lst_exec);
char *ft_get_str(char *str);
int	ft_count_itoa(int n);
char	*ft_itoa(int n);

//ft_utils_7.c
void print_invalid_token(char *str);
char *ft_strdup(char *str);
void	ft_print_fd_pipe(int **fd_pipes, int nb_pipes);
char **new_args(char **args);

// # ====================================================== #
// |														|
// |					FREE.C								|
// |														|
// # ====================================================== #

void ft_free_token(t_token **token);
void free_tokenisation_1(char *input, t_token **token);
void free_tokenisation_2(t_token **token, t_data_parse *data_parse);
void    free_2d(char **str);
void ft_print_error_malloc(void);

//free_2.c
void    free_and_close_tree(t_tree *tree);


// # ====================================================== #
// |														|
// |					EXPORT								|
// |														|
// # ====================================================== #

void	free_tab_tab(char **tab);
void	print_tab_tab(char **tab);
void	clean_env_value(char ***new_env);
void	ft_print_env_ascii_order(char **env);
void	print_tab_tab_ascii_order(char **tab);
void	ft_add_export_value(char **export, char *str);
int		ft_is_ascii(char c);
int		ft_strlen(char *str);
int		ft_find_back_s(char *str);
int		ft_len_tab_tab(char **env);
int		equal_or_nothing(char *str);
int		check_after_equal(char *export);
int		value_start_equal(char *export);
int		ft_check_export_name(char *str);
int		ft_check_empty_export(char *export);
int		ft_strcmp_ascii_order(char *s1, char *s2);
int		ft_is_export_in_env(char **env, char *str);
int		ft_strncmp_exec(char *s1, char *s2, size_t size);
int		ft_find_export_index(char **env, char *str);
int		ft_export_name(char *str, char **export_name);
char	*add_null(char *export);
char	*ft_find_export_name(char *str);
char	*export_and_equal(char *export);
char	*export_and_empty(char *export);
char	*add_quote_to_value(char *export);
char	*add_equal_null_char(char *export);
char	*ft_str_dup_env(char *s1, char *s2);
char	*assign_export_empty_value(char *export);
char	**dup_env(char **env);
char	**dup_env_ascii_order(char **env);
char	**ft_change_export(char **env, char *str, char **new_env);

char	**ft_export(char **env, char *export_str);


// # ====================================================== #
// |														|
// |					UNSET								|
// |														|
// # ====================================================== #

int		ft_unset_is_in_env(char **env, char *unset_str);
int		ft_find_unset_index(char **env, char *unset_str);
char	**ft_copy_env_exept_unset(char **env, int unset_index);
char	**ft_unset(char **env, char *unset_str);

// # ====================================================== #
// |														|
// |					  CD								|
// |														|
// # ====================================================== #

char	**ft_cd(char **path_tab, char **env);
char	*ft_str_join_export_name_with_equal_value(char *s1, char *s2);
char	**ft_change_OLD_PWD(char **path_tab, char **env);

// # ====================================================== #
// |														|
// |					ECHO								|
// |														|
// # ====================================================== #

int		ft_echo(char **tab);

// # ====================================================== #
// |														|
// |					  PWD								|
// |														|
// # ====================================================== #

void	ft_pwd(char **tab);

// # ====================================================== #
// |														|
// |					EXIT								|
// |														|
// # ====================================================== #

int	ft_exit(char **arg);

// # ====================================================== #
// |														|
// |					  ENV								|
// |														|
// # ====================================================== #

void	ft_env(char **env);

// # ====================================================== #
// |														|
// |					  EXEC								|
// |														|
// # ====================================================== #

int 	ft_find_builtin(char *cmd, char **cmd_tab, char **env);
int 	ft_exec_cmd_fork(t_tree *tree, char **env);
void	find_cmd(char **env, char **cmd);
void	ft_tree_exec(t_tree *tree, char **env);



#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapaulin <dapaulin@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 15:47:13 by msilva-p          #+#    #+#             */
/*   Updated: 2023/05/25 22:52:49 by dapaulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

//  printf()

# include <stdio.h>

//  malloc()  free()  exit()  getenv()

# include <stdlib.h>

//  signal()  sigaction()  sigemptyset()  sigaddset()  kill()

# include <signal.h>

//  write()  access()  read() close()  fork()  getcwd()  chdir()  unlink()
//  execve()  dup()  dup2()  pipe()  isatty()  ttyname() ttyslot()

# include <unistd.h>

//  strerror()

# include <string.h>

//  perror()

# include <errno.h>

//  readline()  rl_clear_history()  rl_on_new_line()  rl_replace_line()
//  rl_redisplay()  add_history()

# include <readline/readline.h>
# include <readline/history.h>

//  open()  stat()  lstat()  fstat()

# include <fcntl.h>
# include <sys/stat.h>

//  wait()  waitpid()  wait3()  wait4()

# include <sys/wait.h> 

//  opendir()  readdir()  closedir()

# include <dirent.h>
# include <sys/types.h>

//  ioctl()

# include <sys/ioctl.h>

//  tcsetattr()  tcgetattr()

# include <termios.h>

//  tgetent()  tgetflag()  tgetnum()  tgetstr()  tgoto()  tputs()

# include <curses.h>
# include <term.h>

//  libft

# include "../libft/includes/libft.h"
# include "../libft/includes/ft_printf.h"

// COLORS DEFINES

# define L_RED "\033[0;31m"
# define L_REDB "\033[1;31m"
# define L_WHITE "\033[0;37m"
# define L_WHITEB "\033[1;37m"
# define L_YELLOW "\033[0;33m"
# define L_YELLOWB "\033[1;33m"
# define L_BLUE "\033[0;34m"
# define L_GREEN "\033[0;32m"
# define L_GREENB "\033[1;32m"

// PROMPT DEFINE

# define SHELLYNAME "Minishelly:"
# define PROPQUOTE "quote"
# define PROP "> "

# define SQUOTE 39
# define DQUOTE 34
# define NO_PRINT -1
# define CHAR_NULL 1
# define MORE_ONE_SPACE 2

// Number of functions in the exec array.
# define NUM_SYMBOLS 12
# define NUM_FUNCS 14

//############################ LABELS #############################//

# define HEREDOC_FILE ".heredoc"
# define LABEL_HEREDOC "heredoc> "
# define MSG_HEREDOC "\nwarning: here-document delimited by end-of-file \
 (wanted '%s')\n"

//######################## ERROR MESSAGES #########################//

// DEFINE ERRORS

typedef enum e_err
{
	NO_ERR = 0,
	ONLY_ENTER,
	ERR_QUOTES = 256,
	ERR_NOLINE
}	t_err;

//======== Define types ========\\/

typedef enum e_types
{
	OP_DEFAULT = 0,
	OP_OUTPUT = 1,
	OP_INPUT = 2,
	OP_UNTIL = 3,
	OP_APPEND = 4,
	OP_PIPE = 5,
	OP_CMD = 6,
	OP_EXIT = 7,
	OP_CD = 8,
	OP_ENV = 9,
	OP_UNSET = 10,
	OP_EXPORT = 11,
	OP_PWD = 12,
	OP_ECHO = 13
}	t_types;

typedef struct s_keyword_map
{
	char		*keyword;
	t_types		type;
}				t_keyword_map;

typedef struct s_token
{
	char			**token;
	t_types			type;
	struct s_token	*next;
}	t_token;

typedef enum e_first_or_end
{
	BFALSE,
	BTRUE
}			t_first_or_end;

typedef struct s_exec
{
	int				i;
	int				*pid;
	int				**fd;
	t_first_or_end	flag;
	void			*func;
}				t_exec;

typedef struct s_sys_config
{
	char	*str;
	char	**env;
	int		nlen_parser;
	char	*new_parser;
	t_token	*head;
	t_token	*tokens;
	char	**prompt;
	t_exec	*exec;
	char	**path;
}	t_sys_config;

typedef int					(*t_process_func)(t_sys_config *);
extern int					g_fd;

//############################# BUILTINS ##############################//
// BUILTIN CD												(cd)

int				special_cases(char ***token, char **env);
int				too_much_args(char **token);
void			update_pwd(char ***pwd, ssize_t pwd_index, char *key,
					char **value);
int				ft_cd(t_sys_config *mini);
// BUILTIN ECHO												(echo)

int				ft_echo(t_sys_config *mini);
// BUILTIN ENV												(env)

int				ft_env(t_sys_config *mini);
// BUILTIN EXIT												(exit)

int				ft_exit(t_sys_config *mini);
// BUILTIN EXPORT											(export)

int				check_existence(char **token, char **key, char **env, int i);
int				printf_export(char **token, char **env);
int				b_export(t_sys_config *mini);
// BUILTIN PWD												(pwd)

int				ft_pwd(t_sys_config *mini);
// BUILTIN UNSET											(unset)

int				b_unset(t_sys_config *mini);
//######################################################################//
//############################ ENVIRON #################################//
// CLOSE FDS
void			close_files_fds(void);
void			close_bkp_terms_fds(void);
void			close_terms_fds(void);
void			close_pipes_fds(t_sys_config *mini);

// ENVIRON UTILS											(envp_utils)

size_t			keylen(char *var_env);
char			**alloc_env(char **env, int slots);
int				env_empty(char ***env, char *key, char *value);
// EXIT FUNCTIONS											(exit_functions)

void			normal_exit(void (*f)(void *), int exit_code, \
				void *item);
void			sys_exit(void (*f)(t_sys_config *), int exit_code, \
				t_sys_config *mini);
void			sys_exit_err(void (*f)(t_sys_config *),
					t_sys_config *mini, char *msg);
// FREE														(frees)

void			clean_exec(t_exec **exec);
void			clean_data(t_sys_config *mini);
void			clean_sys(t_sys_config *mini);
void			clean_for_exec(t_sys_config *mini);
void			clean_no_exec(t_sys_config *ms);
void			clean_end_cmd(t_sys_config *ms);
// CRUD ENVIRON												(handle_env)

void			ft_unset(t_sys_config *mini, char *key);
void			ft_export(char ***env, char *key, char *value);
ssize_t			search_envp(char **envp, char *key);
int				edit_envp(char ***env, char *key, char *new_value);
void			get_envp(char **envp, t_sys_config *data);
// PATH CONTROL												(handle_path)

int				run_access(char *path, int flag);
char			**split_paths(char **env);
int				cmd_path_valid(char **token, char **path);
//######################################################################//
//###################### GETTERS AND SETTERS ###########################//
// STATUS CODE GET AND SET									(status_code)

int				*get_status_code(void);
void			set_status_code(int status_code);

// AMOUNT DE PIPES											(num_pipes)
int				*get_is_fork(void);
int				*get_num_pipes(void);
void			set_num_pipes(int num);
t_sys_config	**get_ms(void);

// FILE DESCRIPTORS											(file_descriptor)

int				*get_fd_in(void);
int				*get_fd_out(void);
int				*get_fd_bkp_out(void);
int				*get_fd_bkp_in(void);

// DUP FUNCTIONS
int				dup_fd_out(int fd);
int				dup_fd_in(int fd);
int				ft_exit_in_out_error(int status_code);

//######################################################################//
//######################### HANDLE INPUT ###############################//
// EXPAND DOLAR SIGN [$]									(expand)

ssize_t			find_key(char *line, char **env, int *i);
void			expand_symbol(int i, char **line, char **env, char **pieces);
int				check_single_quotes(char *line);
void			search_for_symbol(char **line, char c, char **env);
// FUNCTIONS FOR HANDLE TOKENS								(ft_tokens_utils)

void			ft_swap_token(t_token **head, t_token **current,
					t_token **dest);
t_token			*copy_token(t_token *bk, t_token **md, t_token *end);
char			**rm_first_item(char **array);
void			correct_puts(t_token *md, t_token *end);
char			*remove_quotes(char *str);
// FUNCTIONS FOR CREATE TOKENS								(ft_tokens)

t_token			*ft_token_new(char **cmds, int type);
t_token			*ft_token_last(t_token *node);
void			ft_token_add_end(t_token **node, t_token *new);
// PUT DATA IN TO TOKENS									(handle_tokens)

int				change_quotes(char *src, char quote, int *i, int schar);
char			*ft_token_repair(char *token);
t_token			*ft_create_tokens(t_sys_config *ms);
t_types			tag_token(char *cmd);
int				hash_func(char *cmd, t_keyword_map *keymap);
// UTILS FOR PARSER											(parser_utils)

int				insert_char_in_string(char *dst, int j, char c);
int				check_quotes(char *src, char quote, int jump);
int				jump_quotes(char *src, t_sys_config *mini, char quote, int *j);
// PARSER CREATE											(parser)

int				add_delimiters(char symbol, int *j, char *dst, char *c);
t_err			check_readline(char *src, t_sys_config *mini);
int				count_delimiter(char *str, int j);
// HANDLE OPERATORS AUX

char			**rm_first_item(char **array);
void			set_file_descriptor(t_token *t, t_token *aux);
int				ft_handle_operators(t_token **head, t_token *t);
t_token			*set_pipe(t_token **head, t_token *bk, t_token *end);
int				realloc_strings(t_token *back, t_token *end);
// HANDLE OPERATORS

t_token			*ft_handle_files(t_token *head, t_token *t, t_token *aux);
t_token			*handle_pipes(t_token **head, t_token *t);
void			prepare_commands(t_sys_config *ms);
//################ INTERFACES ################//

// MS
int				minishelly(int argc, char **argv, char **environ);

// SYS CONFIG
char			*cat_user(char **env);
t_sys_config	*start_sys(char **environ);
void			update_unbound_vars(char *key, t_sys_config *mini);

// PROCESS
void			exec(t_sys_config *mini);
int				exec_program(t_sys_config *mini);

// HASH
int				hash_func(char *cmd, t_keyword_map *keymap);

// Wait input

t_err			wait_input(t_sys_config *mini, int *prop, char *line);

// PROCESS INIT
int				turn_void(t_sys_config *mini);
t_exec			*init_exec(void);
t_process_func	*array_functions(void);

//################ OPERATORS ################//
// PIPE
void			choice_dup2(t_sys_config *ms);
int				ft_pipe(t_sys_config *mini);

// OUTPUT
int				ft_output(t_sys_config *ms);

// INPUT
int				ft_input(t_sys_config *ms);

// APPEND
int				ft_append(t_sys_config *ms);

//######################################################################//
//########################### OPERATORS ################################//
// HEREDOC
int				has_heredoc(t_token *t, char **env);
void			run_here_doc(t_token *t, char **env);
int				ft_heredoc(t_sys_config *ms);

void			ft_swap_token(t_token **head, t_token **current,
					t_token **dest);

// Signals
void			wait_signal_shield(void);
void			wait_signal(void);
void			wait_signal_heredoc(void);
int				ft_ctrl_d(t_sys_config *mini);
int				is_directory(char *path);
//######################################################################//
//############################# TOOLS ##################################//
// LEN FUNCTIONS											(ft_lenfunctions)

int				ft_listlen(char **list);
// FREE FUNCTIONS											(ft_free_functions)

void			ft_token_free(t_token **tokens);
void			free_node_only(t_token **node);
void			ft_node_free(t_token **node);
void			clean_strlist(char ***strs);
void			clean_lstitens(char **lst);
// CHECK FUNCTIONS											(ft_check_functions)

int				is_valid_char_for_var(char c);
int				ft_isspace(char c);
int				ft_is_allspace(char *str);
int				check_next_eq(char symbol, char *str);
int				check_is_a_valid_var(char *var);
// PRINT MESSAGES FUNCTIONS									(ft_print_msg)

void			ft_print_err(int status_code, char *msg);
void			ft_print_perr(int status_code, char *msg);
// JOIN FUNCTIONS											(ft_joinfunctions.c)

char			**ft_listjoin(char **ls, char **lsd);
#endif
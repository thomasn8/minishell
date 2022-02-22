/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnanchen <thomasnanchen@hotmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 17:54:46 by tnanchen          #+#    #+#             */
/*   Updated: 2022/02/22 15:28:22 by tnanchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* ********************* */
/*        LIBRARIES      */
/* ********************* */

# include "../libft/libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <errno.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>
# include <readline/history.h>
# include <readline/readline.h>

/* ********************* */
/*         MACROS        */
/* ********************* */

/* terminal colors */
# define RED "\033[0;31m"
# define GRE "\033[0;32m"
# define YEL "\033[0;33m"
# define BLU "\033[0;34m"
# define MAG "\033[0;35m"
# define CYA "\033[0;36m"
# define WHI "\033[0m"

/* no child process */
# define NO_CHILD_P -2

/* error status code */
# define NO_NAME 0
# define BUILTIN_FAILURE 2
# define REDIR_ERROR 3
# define PERMISSION_ERROR 126
# define CMD_NOT_EXECUTABLE 126
# define CMD_NOT_FOUND 127
# define FATAL_SIGNAL 128
# define INTERRUPTED_BY_SIG2 130
# define KILL_ERROR 254

/* config files */
// env
# define ENVS_FILE ".minishell_env"

/* execution */
// last cmd nbr
# define LAST 0

/* ********************* */
/*         GLOBAL        */
/* ********************* */

pid_t	g_child;

/* ********************* */
/*        STRUCTS        */
/* ********************* */

typedef struct s_t
{
	struct termios	termios_save;
	struct termios	termios_new;
}	t_t;

// liste chainée dans les listes chainées (redirections)
typedef struct s_ioredir
{
	int					order;
	int					type;
	char				*str;
	int					fd;
	struct s_ioredir	*next;
	struct s_ioredir	*prev;
}	t_ioredir;

// liste chainée principale (commandes)
typedef struct s_cmd
{
	int				order;
	char			*name;
	char			**args;
	t_ioredir		*first_in_redir;
	t_ioredir		*first_out_redir;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}	t_cmd;

// tmp (utils au parsing)
typedef struct s_redir
{
	char		*str;
	char		redir;
	int			order_in;
	int			order_out;
	int			type;
	char		*file_or_limiter;
	int			count_in;
	int			count_out;
	char		quote;
}	t_redir;
// tmp2 (utils au parsing)
typedef struct s_args
{
	int			args_count;
	char		*args_list;
	char		quote;
}	t_args;
// parse des components (utils au parsing)
typedef struct s_components
{
	int		i;
	char	quote;
	t_redir	tmp;
	t_args	tmp2;
}	t_components;
// expansion des env (utils au parsing)
typedef struct s_replace_env
{
	char	*tmp;
	char	*value;
	char	*before;
	char	*after;
	char	*new;
}	t_replace_env;

typedef struct s_exec
{
	char	**env;
	int		n;
	int		*status;
	int		stdin_fd;
	int		stdout_fd;
}	t_exec;

/* ********************* */
/*         FILES         */
/* ********************* */

/*** MAIN_UTILS ***/
// config
int			config(int ac, char **av, char **env, int *status);
char		*get_minishell_env(char *key);
int			check_config_file(char *dir, int *fd, int mask, char *filename);

// prompt
char		*get_cmd_line(int fd);
char		*prompt(void);
void		print_prompt(void);

// signals
void		init_signals(t_t *term);
void		ctrlc_signal(int sig);
void		ctrlslash_signal(int sig);
void		stop(int exit_code, t_t *term);

// free datas
int			free_cmds(t_cmd *cmd);

/*** PARSING ***/
t_cmd		*parsing(char *cmd, int *n, int *status);
int			parse_syntax(char *cmd, char **cmd_split);
t_cmd		*cmd_list_create(int n);
t_ioredir	*io_list_create(int n);
void		parse_redir(char *str, int *i, t_redir *tmp, t_cmd *cmd);
void		redir_list_create(char *str, t_redir *tmp, t_cmd *cmd);
void		parse_args(char *str, int *i, t_args *tmp2, t_cmd *cmd);
void		split_args_list(t_args *tmp2, t_cmd *cmd);
void		expansion(t_cmd *first_cmd, int *status);
char		*expansion_component(char *compo, int *status);
int			notblank_quotes(int c);
int			quotes(char a, char *quote);
void		remove_first(char **tab);

// print structs
void		print_all(t_cmd *first_cmd);

/*** BUILTINS ***/
int			is_builtin(t_cmd *current);
void		builtins(t_cmd *current, int fd);

// utils
int			first_nonempty_arg(char **args);

// pwd
int			pwd(void);

// cd
int			cd(t_cmd *cmd);
void		chdir_error_permission(char *dir);
void		chdir_error(char *dir);
int			print_absolute_path(char *cdpath_dir);
char		**explore_cdpath(char *dir);
char		*path_join(char *cdpath, char *dir);

// echo
int			echo(t_cmd *cmd);

// exit
int			exit_builtin(t_cmd *cmd);

// export, unset, env
int			export(t_cmd *cmd);
void		split_key_value(char *arg, int *fd, char *dir);
void		invalid_identifier(char *arg, int *error, int builtin);
int			unset(t_cmd *cmd);
int			env_builtin(t_cmd *cmd);

/*** EXECUTION ***/
void		execution(t_cmd *current, char **env, int n, int *status);
void		input_redirections(t_cmd *cmd, int stdin_fd);
void		simple_cmd(t_cmd *cmd, char **env);
int			output_redirections(t_cmd *cmd, int fd_read);
int			command_not_found(t_cmd *cmd);

#endif

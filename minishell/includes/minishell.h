/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gluisier <gluisier@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 14:59:31 by gluisier          #+#    #+#             */
/*   Updated: 2022/10/19 16:42:58 by scorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <libft.h>
# include <unistd.h>

# define PATH_MAX 256
# define SIGCTRLD 0
# define STDIN 0
# define STDOUT 1
# define STDERR 2
# define F_HEREDOC "/tmp/ms_heredoc.tmp"

enum e_bi {
	BI_ECHO,
	BI_CD,
	BI_PWD,
	BI_EXPORT,
	BI_UNSET,
	BI_ENV,
	BI_EXIT,
	BI_LAST,
	BI_UNKNOWN,
};

enum e_cmdt {
	CMDT_BI,
	CMDT_BO,
	CMDT_ENV,
	CMDT_LAST,
};

enum e_inst {
	INST_CMD,
	INST_PIPE,
	INST_ENV,
	INST_LAST,
};

union u_name {
	enum e_bi	index;
	char		*path;
};

typedef struct s_cmd
{
	union u_name	name;
	char			**args;
	t_dblst			*tmp_env;
	char			*f_read;
	char			*f_write;
	char			*heredoc;
	int				w_mode;
	enum e_cmdt		type;
}	t_cmd;

typedef struct s_pipe
{
	t_cmd	*cmd1;
	t_cmd	*cmd2;
}	t_pipe;

union u_inst {
	t_cmd	*cmd;
	t_dblst	*cmds;
};

typedef struct s_inst {
	union u_inst	data;
	enum e_inst		type;
}	t_inst;

typedef struct s_env
{
	t_dblst	*global;
	t_dblst	*local;
}	t_env;

typedef struct s_shell
{
	char	*prompt;
	t_env	*env;
}	t_shell;

size_t	bi_get_index(char *name);
int		ft_echo(t_shell *shell, char **args, char **env);
int		ft_cd(t_shell *shell, char **args, char **env);
int		ft_pwd(t_shell *shell, char **args, char **env);
int		ft_export(t_shell *shell, char **args, char **env);
int		ft_unset(t_shell *shell, char **args, char **env);
int		ft_env(t_shell *shell, char **args, char **env);
int		ft_exit(t_shell *shell, char **args, char **env);
static int (*const	g_bi[BI_LAST])(t_shell *shell, char **args, char **env)
	= {ft_echo,	ft_cd, ft_pwd, ft_export, ft_unset, ft_env, ft_exit};

void	cmd_destroy(t_cmd **cmd);
t_cmd	*cmd_create_env(t_dblst *tmp_env);
t_cmd	*cmd_create_bi(enum e_bi name, t_dblst *tmp_env);
t_cmd	*cmd_create_bo(char *path, t_dblst *tmp_env);

t_shell	*shell_create(char **envp);
void	shell_destroy(t_shell **shell);

void	inst_add_cmd(t_inst *inst, t_cmd *cmd);
t_inst	*inst_pipe_create(void);
t_inst	*inst_cmd_create(t_cmd *cmd);
t_inst	*inst_env_create(t_cmd *cmd);
void	inst_destroy(t_inst **inst);

char	*cmd_exist(t_cmd *cmd, t_env *env);
char	**get_cmd_env(t_cmd *cmd, t_shell *shell);
void	set_redirect_streams(t_cmd *cmd);
int		exec_cmd(t_cmd *cmd, t_shell *shell);
void	fork_cmd(t_cmd *cmd, t_shell *shell);
void	exec_pipes(t_dblst *cmds, t_shell *shell);

void	catch_ctrl(int signum, t_shell *shell);
void	init_signal_env(t_shell *shell);
void	update_underscore(t_env *env, char *line);
void	prompt_update(t_shell *shell);

t_env	*env_create(char **envp);
void	env_destroy(t_env **env);
int		env_new_var(t_env *env, char *str);
char	*env_get_value(t_env *env, char *name);
int		env_set_value(t_env *env, char *name, char *value);
int		env_export_value(t_env *env, char *name, char *value);
void	assign_env_var(t_env *env, t_dblst *new_vars);

int		ft_isspace(char c);
int		isspechar(char c);
int		isinstchar(char c);
int		token_is_redirect(char *token);
int		ft_strchrnb(const char *s, int c);
int		parse_token(const char **str, char **token, t_env *env);
t_inst	*inst_from_tokens(t_dblst **tokens);
t_cmd	*cmd_from_tokens(t_dblst **tokens);
t_inst	*parse_line(const char *line, t_env *env);

char	**bubble_sort(char **src);
int		ft_strncmp_mishell(const char *s1, const char *s2, size_t n);
char	*ft_strjoin_var(int count, ...);
void	free_array(char **ar);
int		ft_error(t_shell *shell, int code, int count, ...);
int		ft_strlen_2pts(char **str);
int		ft_strcmp(void *s1, void *s2);
char	*str_join_free(char *s1, char *s2);
int		ft_strlen_charset(const char *str, char c);
t_dblst	*env_lst_contains(t_dblst *lst, char *name);
void	cmd_print(t_cmd *cmd);
void	pipe_print(t_dblst *cmds);

void	sigint_heredoc(int signum);
void	reset_signal(int option);
int		signal_handler(int signum, void *ptr);
void	rl_replace_line(const char *text, int clear_undo);

#endif

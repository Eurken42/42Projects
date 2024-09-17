/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gluisier <gluisier@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 15:02:09 by gluisier          #+#    #+#             */
/*   Updated: 2022/10/25 18:13:20 by gluisier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>

t_shell	*shell_create(char **envp)
{
	t_shell			*shell;

	shell = ft_calloc(1, sizeof(*shell));
	if (!shell)
		return (NULL);
	shell->env = env_create(envp);
	if (!shell->env)
	{
		free(shell);
		return (NULL);
	}
	return (shell);
}

void	shell_destroy(t_shell **shell)
{
	t_shell	*s;

	if (!shell || !*shell)
		return ;
	s = *shell;
	env_destroy(&s->env);
	free(s);
	*shell = NULL;
}

int	signal_handler(int signum, void *ptr)
{
	static t_shell	*shell = NULL;

	if (shell == NULL)
		shell = ptr;
	if (signum == SIGINT || signum == SIGQUIT || signum == SIGCTRLD)
		catch_ctrl(signum, shell);
	return (0);
}

static void	handle_input(t_shell *shell)
{
	t_inst	*inst;
	char	*line;

	while (42)
	{
		prompt_update(shell);
		line = readline(shell->prompt);
		printf("\033[0m");
		free(shell->prompt);
		if (line == NULL)
			signal_handler(SIGCTRLD, shell);
		inst = parse_line(line, shell->env);
		if (*line && line)
			update_underscore(shell->env, line);
		free(line);
		if (inst && inst->type == INST_ENV)
			assign_env_var(shell->env, inst->data.cmd->tmp_env);
		else if (inst && inst->type == INST_CMD)
			fork_cmd(inst->data.cmd, shell);
		else if (inst && inst->type == INST_PIPE)
			exec_pipes(inst->data.cmds, shell);
		inst_destroy(&inst);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_shell	*shell;

	(void) ac;
	(void) av;
	setbuf(stdout, NULL);
	shell = shell_create(envp);
	if (!shell)
		return (1);
	init_signal_env(shell);
	system("clear");
	handle_input(shell);
	shell_destroy(&shell);
	return (0);
}

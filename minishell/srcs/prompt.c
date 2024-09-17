/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gluisier <gluisier@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 15:16:24 by gluisier          #+#    #+#             */
/*   Updated: 2022/10/25 18:41:26 by gluisier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	free_prompt_data(char *home, char *pwd, char *log)
{
	if (home)
		free(home);
	free(pwd);
	free(log);
}

void	prompt_update(t_shell *shell)
{
	char	*pwd;
	char	*home;
	char	*log;

	reset_signal(1);
	pwd = env_get_value(shell->env, "PWD");
	home = env_get_value(shell->env, "HOME");
	log = env_get_value(shell->env, "LOGNAME");
	if (!pwd)
		pwd = ft_strdup("");
	else
		pwd = str_join_free(pwd, ft_strdup(" "));
	if (!log)
		log = ft_strdup("minishell-1-0 : ");
	else
		log = str_join_free(log, ft_strdup("@minishell : "));
	if (home && !ft_strncmp(pwd, home, ft_strlen(home)))
		shell->prompt = ft_strjoin_var(5, "\033[1;32m", log,
				"\e[1;34m~", pwd + ft_strlen(home),
				"% \e[1;37m");
	else
		shell->prompt = ft_strjoin_var(5, "\033[1;32m", log,
				"\e[1;34m", pwd, "% \e[1;37m");
	free_prompt_data(home, pwd, log);
}

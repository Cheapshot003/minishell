/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohnatiuk <ohnatiuk@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 14:58:52 by ohnatiuk          #+#    #+#             */
/*   Updated: 2023/08/15 14:58:54 by ohnatiuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int received_signal;

void	int_handler(int sig, siginfo_t *info, void *context)
{
	(void) sig;
	(void) context;
	received_signal = info->si_code;
	if (info->si_code == 0)
	{
			// signal in prompt
		printf("\n"); // Move to a new line
		rl_on_new_line(); // Regenerate the prompt on a newline
		rl_replace_line("", 0); // Clear the previous text
		rl_redisplay();
	}
	return ;
}

void	chld_handler(int sig)
{
	received_signal = 0;
	//printf("\n\n");
	(void) sig;
}

void	handle_signal_by_child(int sig)
{
	(void) sig;
	ft_putstr_fd("Quit (core dumped)\n", 2);
	received_signal = 131;
	signal(SIGQUIT, SIG_IGN);
}

void	init_signals(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = int_handler;
	sigaction(SIGINT, &sa, NULL);
	signal(SIGCHLD, chld_handler);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddivaev <ddivaev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 19:38:46 by ddivaev           #+#    #+#             */
/*   Updated: 2025/09/06 19:38:53 by ddivaev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"

/**
 * @brief Signal handler for receiving messages from a client.
 *
 * Reconstructs characters sent bit by bit through SIGUSR1 and SIGUSR2 signals.
 * When a full character is received, it is printed to stdout.
 * If a null character is received, it signals the end of a message
 * and sends SIGUSR2 back to the client as an acknowledgment.
 *
 * @param sig      The signal received (SIGUSR1 or SIGUSR2).
 * @param info     Pointer to siginfo_t containing the client
 * PID and signal info.
 * @param context  Unused pointer (required by sigaction).
 *
 * @note
 * - SIGUSR1 encodes a binary `1`, SIGUSR2 encodes a binary `0`.
 * - Acknowledgments are sent back to the client with SIGUSR1 (for each bit)
 *   and SIGUSR2 (to confirm end of transmission).
 * - Uses static variables to accumulate bits and reconstruct characters.
 */
void	sig_usr(int sig, siginfo_t *info, void *context)
{
	static char	c = 0;
	static int	bit = -1;

	(void)context;
	if (kill(info->si_pid, 0) < 0)
	{
		ft_printf("ERROR : cant send sig to pid : %d\n", info->si_pid);
		exit(EXIT_FAILURE);
	}
	if (bit < 0 && !c)
		ft_printf("\nClient say : ");
	if (bit < 0)
		bit = __CHAR_BIT__ * sizeof(c) - 1;
	if (sig == SIGUSR1)
		c |= 1 << bit;
	else if (sig == SIGUSR2)
		c &= ~(1 << bit);
	if (!bit && c)
		ft_putchar_fd(c, 1);
	else if (!bit && !c)
		kill(info->si_pid, SIGUSR2);
	bit--;
	kill(info->si_pid, SIGUSR1);
}

/**
 * @brief Entry point of the server program.
 *
 * Sets up signal handlers for SIGUSR1 and SIGUSR2,
 * prints the server's PID, and enters an infinite loop
 * waiting for client messages.
 *
 * @return int Always returns 0 (program runs indefinitely).
 */
int	main(void)
{
	init_sig(SIGUSR1, &sig_usr);
	init_sig(SIGUSR2, &sig_usr);
	ft_printf("pid: %d", getpid());
	while (1)
		sleep(1);
}

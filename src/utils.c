/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddivaev <ddivaev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 19:33:28 by ddivaev           #+#    #+#             */
/*   Updated: 2025/09/06 20:08:21 by ddivaev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"

/**
 * @brief Initializes a signal handler.
 *
 * Sets up a sigaction structure for the given signal (SIGUSR1 or SIGUSR2)
 * and assigns the provided handler function.
 *
 * @param sig      The signal to handle (typically SIGUSR1 or SIGUSR2).
 * @param handler  Pointer to a signal handler function with the signature:
 *                 void handler(int, siginfo_t *, void *).
 *
 * @note The following flags are used:
 *       - SA_SIGINFO: allows passing extended signal information.
 *       - SA_RESTART: restarts interrupted system calls after the signal.
 *       - SA_NODEFER: does not block the signal during its own handling.
 */
void	init_sig(int sig, void (*handler)(int, siginfo_t *, void *))
{
	struct sigaction	susr;

	susr.sa_sigaction = handler;
	susr.sa_flags = SA_SIGINFO | SA_RESTART | SA_NODEFER;
	sigemptyset(&susr.sa_mask);
	if (sig == SIGUSR1)
		sigaction(SIGUSR1, &susr, 0);
	else if (sig == SIGUSR2)
		sigaction(SIGUSR2, &susr, 0);
}

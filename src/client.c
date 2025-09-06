/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddivaev <ddivaev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 19:38:21 by ddivaev           #+#    #+#             */
/*   Updated: 2025/09/06 19:45:52 by ddivaev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"

int	g_bit_control;

/**
 * @brief Sends a single character to the server process.
 *
 * Encodes the given character into binary and sends each bit to the server
 * using signals:
 * - SIGUSR1 encodes a binary `1`
 * - SIGUSR2 encodes a binary `0`
 *
 * After sending each bit, waits for an acknowledgment (SIGUSR1) from
 * the server before continuing. Exits if the target PID is invalid.
 *
 * @param c   Character to send.
 * @param pid PID of the server process.
 */
void	send_char(char c, pid_t pid)
{
	int	bit;

	bit = __CHAR_BIT__ * sizeof(c) - 1;
	while (bit >= 0)
	{
		if (kill(pid, 0) < 0)
		{
			ft_printf("ERROR : cant send sig to pid : %d\n", pid);
			exit(EXIT_FAILURE);
		}
		g_bit_control = 0;
		if (c & (1 << bit))
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		bit--;
		while (g_bit_control != 1)
			usleep(10);
	}
}

/**
 * @brief Sends a null-terminated string to the server process.
 *
 * Iterates through the string and sends each character using send_char().
 * At the end of the message, transmits a null character (`'\0'`) to indicate
 * the end of transmission.
 *
 * @param str The string to send.
 * @param pid PID of the server process.
 */
void	send_str(char *str, pid_t pid)
{
	int	cur;

	cur = 0;
	while (str[cur])
	{
		send_char(str[cur], pid);
		cur++;
	}
	send_char(0, pid);
}

/**
 * @brief Signal handler for client acknowledgments.
 *
 * Handles responses from the server:
 * - SIGUSR1: Confirms that a bit was received, allowing the client to send
 *   the next one.
 * - SIGUSR2: Confirms the entire message was received. Prints a message
 *   and exits successfully.
 *
 * @param sig The signal received (SIGUSR1 or SIGUSR2).
 */
void	sig_usr(int sig)
{
	if (sig == SIGUSR1)
		g_bit_control = 1;
	else if (sig == SIGUSR2)
	{
		ft_printf("Message received !\n");
		exit(EXIT_SUCCESS);
	}
}

/**
 * @brief Entry point of the client program.
 *
 * Validates arguments, sets up signal handlers, and sends a string to
 * the specified server process.
 *
 * Usage: ./client <pid> <string>
 *
 * @param argc Number of command-line arguments (must be 3).
 * @param argv Command-line arguments:
 *             - argv[1]: server PID
 *             - argv[2]: string to send
 *
 * @return Always returns 0 (program exits on SIGUSR2 or error).
 */
int	main(int argc, char **argv)
{
	pid_t	pid;

	if (argc != 3)
	{
		ft_printf("Usage : ./client <pid> <string to send>\n");
		exit(EXIT_FAILURE);
	}
	signal(SIGUSR1, &sig_usr);
	signal(SIGUSR2, &sig_usr);
	pid = ft_atoi(argv[1]);
	if (!pid)
	{
		ft_printf("%s is an invalid pid\n", argv[1]);
		exit(EXIT_FAILURE);
	}
	send_str(argv[2], pid);
	while (1)
		sleep(1);
}

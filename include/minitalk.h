/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddivaev <ddivaev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 20:10:51 by ddivaev           #+#    #+#             */
/*   Updated: 2025/09/06 20:11:19 by ddivaev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H
# include <sys/types.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include "../libft/libft.h"

void	init_sig(int sig, void (*handler)(int, siginfo_t *, void *));
#endif

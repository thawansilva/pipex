/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thaperei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 15:51:44 by thaperei          #+#    #+#             */
/*   Updated: 2025/10/19 07:55:44 by thawan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	if (argc - 1 != 4)
	{
		ft_putendl_fd("Usage: ./pipex file1 'cmd1' 'cmd2' file2", 2);
		return (1);
	}
	pipex(argv, envp);
	return (0);
}

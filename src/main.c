/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thaperei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 11:18:23 by thaperei          #+#    #+#             */
/*   Updated: 2025/10/14 07:34:57 by thawan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int main(int argc, char **argv)
{
	int	pipe_fd[2];
	int	pid;
//	int	fd;

	if (!argv)
		return (1);
	if (argc - 1 != 4)
		ft_putendl_fd("Usage: ./pipex file1 'cmd1' 'cmd2' file2", 2);
	if (pipe(pipe_fd) < 0)
		error_msg(strerror(errno));
	pid = fork();
	if (pid < 0)
		error_msg(strerror(errno));
	else if(pid == 0) // child
	{
	}
	else // parent
	{
//		fd = open(argv[1], O_RDONLY);
//		close(pipe_fd[READ]);
//		if (fd < 0)
//		{
//			close(fd);
//			error_msg(strerror(errno));
//		}
//		dup2(fd, STDIN);
//		write(pipe_fd[WRITE], "hello", 5);
//		close(fd);
	}
}

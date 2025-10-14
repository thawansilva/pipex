/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thaperei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 11:18:23 by thaperei          #+#    #+#             */
/* ************************************************************************** */

#include "pipex.h"

void	execute_command(char *cmd, char **envp)
{
//	char	*path;
	char	*env_variable;
//	char	**splited_variable;
	// Obter caminho do executável (path)
	(void)cmd;
	while (*envp != NULL)
	{
		if (ft_strncmp(*envp, "PATH=", 5) == 0)
		{
			env_variable = *envp;
			break ;
		}
		envp++;
	}
	if (*envp == NULL)
		return ;
	env_variable = env_variable + 5;
	printf("%s\n", env_variable);
//	splited_variable = ft_split(env_variable, ':');
	// Separar os argumentos se houver (args)
	// execve(path, args, envp)
}

int	open_input_file(char *filename, int *pipe_fd)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (!access(filename, R_OK) || fd < 0)
	{
		close(fd);
		close(pipe_fd[READ]);
		close(pipe_fd[WRITE]);
		return (-1);
	}
	return (fd);
}

void	child_treat_input(char **argv, char **envp, int *pipe_fd)
{
	int	fd;

	close(pipe_fd[READ]);
	fd = open_input_file(argv[1], pipe_fd);
	if (fd < 0)
		error_msg(strerror(errno));
	dup2(fd, STDIN);
	close(fd);
	dup2(pipe_fd[WRITE], STDOUT);
	close(pipe_fd[WRITE]);
	execute_command(argv[2], envp);
}

void	pipex(char **argv, char **envp)
{
	int		pipe_fd[2];
	int		pid_1;

	if (!envp && !argv)
		return ;
	if (pipe(pipe_fd) < 0)
		error_msg(strerror(errno));
	pid_1 = fork();
	if (pid_1 < 0)
		error_msg(strerror(errno));
	else if(pid_1 == 0) // child
		child_treat_input(argv, envp, pipe_fd);
	close(pipe_fd[WRITE]);
	close(pipe_fd[READ]);
	wait(NULL);
	return ;
}

int main(int argc, char **argv, char **envp)
{
	if (argc - 1 != 4)
		error_msg("Usage: ./pipex file1 'cmd1' 'cmd2' file2");
	if (access(argv[1], F_OK) < 0)
		error_msg(strerror(errno));
	pipex(argv, envp);
	return (0);
}

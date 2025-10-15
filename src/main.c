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

void	free_arr_str(char **arr_str)
{
	int	i;

	i = 0;
	while (arr_str[i] != NULL)
	{
		free(arr_str[i]);
		i++;
	}
	free(arr_str);
}

char	*get_path_env_variable(char **envp)
{
	while (*envp != NULL)
	{
		if (ft_strncmp(*envp, "PATH=", 5) == 0)
			return (*envp + 5);
		envp++;
	}
	return (NULL);
}

char	*get_command_path(char *full_cmd, char **envp)
{
	char	**splited_cmd;
	char	**arr_paths;
	char	*path;
	char	*aux;
	int		i;

	i = 0;
	splited_cmd = ft_split(full_cmd, ' ');
	arr_paths = ft_split(get_path_env_variable(envp), ':');
	path = NULL;
	while (arr_paths[i] != NULL)
	{
		free(path);
		aux = ft_strjoin(arr_paths[i], "/");
		path = ft_strjoin(aux, splited_cmd[0]);
		free(aux);
		if (access(path, F_OK | X_OK) == 0)
			break ;
		i++;
	}
	free_arr_str(arr_paths);
	free_arr_str(splited_cmd);
	return (path);
}

void	execute_command(char *full_cmd, char **envp)
{
	char	*path;
	char	**splited_cmd;

	if (*envp == NULL)
		return ;
	path = get_command_path(full_cmd, envp);
	splited_cmd = ft_split(full_cmd, ' ');
	if (execve(path, splited_cmd, envp) < 0)
	{
		ft_putendl_fd("pipex: command not found: ", 2);
		free(path);
		free_arr_str(splited_cmd);
		exit(1);
	}
	free(path);
	free_arr_str(splited_cmd);
}

int	open_input_file(char *filename, int *pipe_fd)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (access(filename, R_OK) != 0 || fd < 0)
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
	else if(pid_1 == 0)
		child_treat_input(argv, envp, pipe_fd);
	close(pipe_fd[WRITE]);
	close(pipe_fd[READ]);
	waitpid(pid_1, NULL, 0);
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

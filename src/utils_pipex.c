/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thaperei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 15:11:25 by thaperei          #+#    #+#             */
/*   Updated: 2025/10/18 14:42:48 by thaperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error_msg(char *str, int exit_code)
{
	perror(str);
	exit(exit_code);
}

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
	while (arr_paths[i] != NULL)
	{
		aux = ft_strjoin(arr_paths[i], "/");
		path = ft_strjoin(aux, splited_cmd[0]);
		free(aux);
		if (access(path, F_OK | X_OK) == 0)
		{
			free_arr_str(arr_paths);
			free_arr_str(splited_cmd);
			return (path);
		}
		i++;
		free(path);
	}
	free_arr_str(arr_paths);
	free_arr_str(splited_cmd);
	return (full_cmd);
}

void	execute_command(char *full_cmd, char **envp)
{
	char	*path;
	char	**splited_cmd;

	if (*envp == NULL)
		return ;
	path = get_command_path(full_cmd, envp);
	if (access(path, F_OK) != 0)
	{
		ft_putstr_fd("pipe: command not found: ", 2);
		ft_putendl_fd(path, 2);
		exit(1);
	}
	splited_cmd = ft_split(full_cmd, ' ');
	if (execve(path, splited_cmd, envp) < 0)
	{
		free_arr_str(splited_cmd);
		if (errno == EACCES)
			error_msg("exec", 126);
		else
			error_msg("exec", 127);
	}
}

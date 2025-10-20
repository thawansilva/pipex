/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thaperei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 19:45:39 by thaperei          #+#    #+#             */
/*   Updated: 2025/10/19 21:19:09 by thawan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	main(int argc, char **argv, char **envp)
{
	if (argc - 1 < 5)
		return (1);
	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
		printf("here_doc\n"); // Execute heredoc
	else
		handle_multiple_pipes(argc, argv, envp);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_literal_args_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thaperei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 11:25:25 by thaperei          #+#    #+#             */
/*   Updated: 2025/10/23 16:00:18 by thaperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static int	ft_count_words(char const *str, char c)
{
	int	in_word;
	int	in_literal;
	int	count;

	if (!*str)
		return (0);
	count = 0;
	in_word = 0;
	in_literal = 0;
	while (*str)
	{
		if (*str == '\'' || *str == '"')
			in_literal = !in_literal;
		else if (*str != c || in_literal)
		{
			if (!in_word && ++count)
				in_word = 1;
		}
		else
			in_word = 0;
		str++;
	}
	return (count);
}

static void	free_args(char **args)
{
	size_t	i;

	i = 0;
	if (!args)
		return ;
	while (args[i])
		free(args[i++]);
	free(args);
}

static char	*copy_arg(char const *str, char delimiter, int *start, int len)
{
	char	*result;
	char	quote;
	int		in_quotes;
	int		j;

	in_quotes = 0;
	quote = 0;
	j = 0;
	result = ft_calloc(len, sizeof(char));
	while (str[*start] && (str[*start] != delimiter || in_quotes))
	{
		if ((str[*start] == '\'' || str[*start] == '"') && !in_quotes)
		{
			quote = str[*start];
			in_quotes = 1;
		}
		else if (in_quotes && str[*start] == quote)
			in_quotes = 0;
		else
			result[j++] = str[*start];
		(*start)++;
	}
	return (result);
}

static char	*get_arg(char const *str, int *idx, char delimiter)
{
	char	*result;
	char	quote;
	char	in_quotes;
	int		start;
	int		len;

	len = 0;
	in_quotes = 0;
	start = *idx;
	while (str[start + len] && (str[start + len] != delimiter || in_quotes))
	{
		if ((str[start + len] == '\'' || str[start + len] == '"') && !in_quotes)
		{
			quote = str[start + len];
			in_quotes = 1;
		}
		else if (in_quotes && str[start + len] == quote)
			in_quotes = 0;
		len++;
	}
	result = copy_arg(str, delimiter, &start, len);
	*idx = start;
	return (result);
}

char	**split_literal_args(char const *str, char delimiter)
{
	char	**args;
	int		arg_idx;
	int		i;

	args = ft_calloc((ft_count_words(str, delimiter) + 1), sizeof(char *));
	if (!args)
		return (NULL);
	i = 0;
	arg_idx = 0;
	while (str[i])
	{
		while (str[i] == delimiter)
			i++;
		if (str[i] == '\0')
			break ;
		args[arg_idx] = get_arg(str, &i, delimiter);
		if (args[arg_idx] == NULL)
		{
			free_args(args);
			return (NULL);
		}
		arg_idx++;
	}
	return (args);
}

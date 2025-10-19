/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_literal.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thaperei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 11:25:25 by thaperei          #+#    #+#             */
/*   Updated: 2025/10/18 16:20:41 by thaperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_words(char const *str, char c, char literal)
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
		if (*str == literal)
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

static void	ft_free_arr(char **arr)
{
	size_t	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

static void	ft_insert_str(char **arr, const char *str, char c, char literal)
{
	size_t	i;
	size_t	j;
	size_t	start;
	int		in_literal;

	i = 0;
	j = 0;
	start = 0;
	in_literal = 0;
	while (str[i] != '\0')
	{
		if (str[i] == literal)
			in_literal = !in_literal;
		if (str[i] == c && !in_literal && i != start)
		{
			arr[j] = ft_substr(str, start, i - start);
			if (!arr[j++])
				return (ft_free_arr(arr));
			start = i + 1;
		}
		else if (str[i] == c && !in_literal && i == start)
			start = i + 1;
		i++;
	}
	if (i != start)
		arr[j] = ft_substr(str, start, i - start);
}

char	**ft_split_literal(char const *str, char c, char literal)
{
	char	**arr;

	arr = ft_calloc((ft_count_words(str, c, literal) + 1), sizeof(char *));
	if (!arr)
		return (NULL);
	ft_insert_str(arr, str, c, literal);
	return (arr);
}

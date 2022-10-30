/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srituit <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 16:21:20 by srituit           #+#    #+#             */
/*   Updated: 2022/10/30 16:21:35 by srituit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**ft_split(char const *s, char c)
{
	char	**tab;
	size_t	index;
	size_t	itab;
	int		isword;

	itab = ft_countword(s, c);
	tab = malloc(sizeof(char *) * itab + 1);
	if (!tab)
		return (NULL);
	itab = 0;
	index = 0;
	isword = -1;
	while (index <= ft_strlen(s))
	{
		if (s[index] != c && isword < 0)
			isword = index;
		else if ((s[index] == c || index == ft_strlen(s)) && (isword >= 0))
		{
			tab[itab++] = ft_putstr(s, isword, index);
			isword = -1;
		}
		index++;
	}
	tab[itab] = NULL;
	return (tab);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0')
	{
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	while (n)
	{
		if ((*s1 != *s2 && s1 && s2) || (*s1 == '\0' || *s2 == '\0'))
		{
			return ((unsigned char)*s1 - (unsigned char)*s2);
		}
		s1++;
		s2++;
		n--;
	}
	return (0);
}

void	ft_putendl_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (!s || fd < 0)
		return ;
	while (s[i] != '\0')
	{
		write(fd, &s[i], 1);
		i++;
	}
	write (fd, "\n", 1);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	c;
	size_t	n_len;
	char	*hay;

	i = 0;
	hay = (char *)haystack;
	n_len = ft_strlen(needle);
	if ((n_len == 0) || (haystack == needle && n_len == len))
		return (hay);
	while (hay[i] != '\0' && i < len)
	{
		c = 0;
		while (hay[i + c] != '\0' && needle[c] != '\0' \
				&& hay[i + c] == needle[c] && i + c < len)
			c++;
		if (c == n_len)
			return (hay + i);
		i++;
	}
	return (0);
}

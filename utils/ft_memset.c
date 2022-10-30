/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eturbat <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 15:48:33 by eturbat           #+#    #+#             */
/*   Updated: 2022/10/30 15:59:28 by eturbat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*ptr;

	ptr = (unsigned char *)b;
	while (len)
	{
		*ptr = (unsigned char)c;
		ptr++;
		len--;
	}
	return (b);
}

int	ft_countword(char const *s1, char del)
{
	int	i;
	int	word;

	i = 0;
	word = 0;
	while (*s1)
	{
		if (*s1 != del && word == 0)
		{
			word = 1;
			i++;
		}
		else if (*s1 == del)
			word = 0;
		s1++;
	}
	return (i);
}

char	*ft_putstr(char const *str, size_t start, size_t end)
{
	int			i2;
	char		*str1;

	i2 = 0;
	str1 = malloc(sizeof(char) * (end - start + 1));
	while (start < end)
		str1[i2++] = str[start++];
	str1[i2] = '\0';
	return (str1);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char			*res;
	size_t			i;
	unsigned int	length;

	if (!s1 || !s2)
		return (0);
	length = ft_strlen(s1) + ft_strlen(s2);
	res = (char *)malloc(sizeof(char) * (length + 1));
	if (!res)
		return (0);
	i = 0;
	while (*s1)
	{
		res[i] = *s1++;
		i++;
	}
	while (*s2)
	{
		res[i] = *s2++;
		i++;
	}
	res[i] = '\0';
	return (res);
}

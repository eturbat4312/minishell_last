/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_libft.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eturbat <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 12:05:12 by eturbat           #+#    #+#             */
/*   Updated: 2022/10/30 12:05:27 by eturbat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_get_len(int nbr)
{
	size_t		len;
	long long	nbr_long;

	len = 1;
	nbr_long = nbr;
	if (nbr_long < 0)
	{
		nbr_long = -nbr_long;
		len++;
	}
	while (nbr_long >= 10)
	{
		nbr_long /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int nbr)
{
	char		*result;
	size_t		len;
	long long	nbr_long;

	len = ft_get_len(nbr);
	result = (char *)malloc((len + 1) * sizeof (char));
	if (!result)
		return (0);
	result[len--] = '\0';
	nbr_long = nbr;
	if (!nbr)
		result[0] = '0';
	else if (nbr_long < 0)
	{
		nbr_long = -nbr_long;
		result[0] = '-';
	}
	while (nbr_long)
	{
		result[len] = nbr_long % 10 + '0';
		nbr_long /= 10;
		len--;
	}
	return (result);
}

char	*ft_substr(const char *s, unsigned int start_pos, size_t len)
{
	char	*res;
	size_t	i;

	if (!s)
		return (NULL);
	if (ft_strlen(s) < start_pos)
	{
		res = malloc(sizeof(char));
		if (!res)
			return (NULL);
		res[0] = '\0';
		return (res);
	}
	if (start_pos + len > ft_strlen(s))
		len = ft_strlen(s) - start_pos;
	res = malloc(sizeof(char) * (len + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (++i - 1 < len)
		*(res + i - 1) = *(s + start_pos + i - 1);
	*(res + i - 1) = '\0';
	return (res);
}

/*char	*strjoin(char const *s1, char const *s2)
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
}*/

char	*ft_strdup(const char *str)
{
	char			*res;
	unsigned int	len;
	unsigned int	i;

	len = ft_strlen (str);
	res = (char *)malloc (sizeof(char) * (len + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (len--)
	{
		res[i] = str[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

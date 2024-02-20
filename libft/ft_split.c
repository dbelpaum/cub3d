/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbelpaum <dbelpaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 23:02:17 by dbelpaum          #+#    #+#             */
/*   Updated: 2021/08/04 23:02:17 by dbelpaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	ft_countwords(const	char	*str, char c)
{
	int	i;
	int	n;

	n = 0;
	i = 0;
	while (str[i] == c && str[i])
		i++;
	while (str[i])
	{
		n++;
		while (str[i] != c && str[i])
			i++;
		while (str[i] == c && str[i])
			i++;
	}
	return (n);
}

char	*ft_get_words(const	char *str, char c)
{
	char	*ret;
	int		i;
	int		len;

	len = 0;
	i = 0;
	while ((str[len] != c) && str[len])
		len++;
	ret = malloc(sizeof(char) * (len + 1));
	if (!ret)
		return (0);
	while (i < len)
	{
		ret[i] = str[i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

char	**ft_split(char *s, char c)
{
	char	**tab;
	int		i;
	int		n;

	n = ft_countwords(s, c);
	i = 0;
	tab = malloc(sizeof(const char *) * (n + 1));
	if (!tab)
		return (0);
	tab[n] = 0;
	while (*s == c && *s)
		s++;
	while (*s)
	{
		tab[i] = ft_get_words(s, c);
		i++;
		while (*s != c && *s)
			s++;
		while (*s == c && *s)
			s++;
	}
	return (tab);
}

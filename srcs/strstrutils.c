/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstrutils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbelpaum <dbelpaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 12:01:59 by dbelpaum          #+#    #+#             */
/*   Updated: 2022/08/19 12:10:41 by dbelpaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

void	free_strstr(char **str)
{
	int	i;

	i = -1;
	while (str[++i])
		free(str[i]);
	free(str);
}

int	ft_strstrlen(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	**ft_strstrdup(char **env)
{
	char	**new;
	int		i;

	if (!env || !*env)
		return (NULL);
	new = (char **)malloc(sizeof(char *) * (ft_strstrlen(env) + 1));
	if (!new)
		return (NULL);
	i = -1;
	while (env[++i])
	{
		new[i] = ft_strdup(env[i]);
		if (!new[i])
			return (NULL);
	}
	new[i] = NULL;
	return (new);
}

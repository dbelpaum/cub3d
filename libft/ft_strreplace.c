/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strreplace.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbelpaum <dbelpaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 20:18:44 by dbelpaum          #+#    #+#             */
/*   Updated: 2022/08/22 20:19:30 by dbelpaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_strreplace(char *str, char old, char new)
{
	if (!str)
		return ;
	while (*str)
	{
		if (*str == old)
			*str = new;
		str++;
	}
}

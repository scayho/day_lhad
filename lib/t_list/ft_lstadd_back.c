/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchahid <hchahid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 16:58:55 by hchahid           #+#    #+#             */
/*   Updated: 2022/09/22 11:49:50 by hchahid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_lstadd_back(t_env **lst, t_env *new)
{
	t_env	*iter;

	iter = *lst;
	if (!new)
		return (1);
	if (*lst == NULL)
		*lst = new;
	else
	{
		ft_lstlast(iter)->next = new;
	}
	return (0);
}

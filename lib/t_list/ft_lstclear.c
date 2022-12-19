/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchahid <hchahid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 17:54:44 by hchahid           #+#    #+#             */
/*   Updated: 2022/07/24 17:02:13 by hchahid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*this;
	t_list	*another_one;

	if (!*lst || !del)
		return ;
	this = *lst;
	while (this)
	{
		another_one = this -> next;
		del(this -> content);
		free(this);
		this = another_one;
	}
	*lst = 0;
}

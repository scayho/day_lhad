/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_arg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchahid <hchahid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 17:31:15 by hchahid           #+#    #+#             */
/*   Updated: 2022/09/25 18:32:16 by hchahid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "lib/libft.h"

// t_arg	*new_arg(char *arg, char type)
// {
// 	t_arg	*new;
// 	char	*tmp;
// 	char	holder;
// 	int		i;

// 	i = 0;
// 	new = malloc (sizeof(t_arg));
// 	if (!new)
// 		perror(new);
// 	if (type == '"' || type == 's')
// 		new->expand = true;
// 	else
// 		new->expand = false;
// 	if (type == '\'')
// 		i = closing_quote(arg, 0);
// 	else if (type == '"')
// 		i = closing_d_quote(arg, 0);
// 	else
// 		i = end_of_arg(arg, 0);
// 	holder = arg[i];
// 	arg[i - 1] = '\0';
// 	new->arg = ft_strdup(arg);
// 	arg[i] = holder;
// 	if (arg[i + 1] && !is_space(arg[i + 1]))
// 		new->linked = 1;
// 	else
// 		new->linked = 0;
// 	return (new);
// }

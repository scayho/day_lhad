/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_env_shape.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchahid <hchahid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 15:35:24 by hchahid           #+#    #+#             */
/*   Updated: 2022/08/26 20:38:47 by hchahid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_env
{
	char			*e_name;
	char			*e_value;
	struct s_env	*next;
} t_env;

// char	*get_e_var_name(char *s)
// {
// 	char	*ret;
// 	int		i;

// 	i = 0;
// 	while (s[i] && s[i] != '=')
// 		i++;
// 	ret = malloc (i);
// 	if (!ret)
// 	{
// 		printf("Unable to preform operation due to allocation issues\n");
// 		return (NULL);
// 	}
// 	i = 0;
// 	while (s[i] && s[i] != '=')
// 	{
// 		ret[i] = s[i];
// 		i++;
// 	}
// 	ret[i] = '\0';
// 	return (ret);
// }

// char	*get_e_var_value(char *value)
// {
// 	char	*ret;
// 	int		start_value;
// 	int		len;

// 	start_value = 0;
// 	while (value[start_value] && value[start_value] != '=')
// 		start_value++;
// 	start_value++;
// 	len = start_value;
// 	while (value[len])
// 		len++;
// 	ret = malloc (len);
// 	if (!ret)
// 	{
// 		printf("Unable to preform operation due to allocation issues\n");
// 		return (NULL);
// 	}
// 	len = 0;
// 	while (value[start_value])
// 	{
// 		ret[len] = value[start_value];
// 		len++;
// 		start_value++;
// 	}
// 	ret[len] = '\0';
// 	return (ret);
// }



// void	set_env_vars(char **envp, t_env **env_p)
// {
// 	int	i;

// 	i = 0;
// 	while (envp[i])
// 		ft_lstadd_back(env_p, ft_lstnew(envp[i++]));
// }

void	ft_putstr(char *s)
{
	int	i = 0;

	while (s[i])
		write(1, &s[i++], 1);
}
// void	display(t_env *p)
// {
// 	while (p)
// 	{
// 		ft_putstr(p->e_name);
// 		ft_putstr("=");
// 		ft_putstr(p->e_value);
// 		ft_putstr("\n");
// 		p = p->next;
// 	}
// }

int	main(int ac, char **av, char **envp)
{
	t_env	*env;

	env = NULL;
	set_env_vars(envp, &env);
	display(env);
	return (0);
}
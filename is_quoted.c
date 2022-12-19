

#include "minishell.h"


char	*ft_strchr(const char *s, int c);

// int is_quoted(char *s, char *mark)
// {
//     char    quote;
//     int     i;

//     i = 0;
//     while (s[i])
//     {
//         if ((s[i] == '"' || s[i] == '\'') && (s + i) > mark)
//             return (0);
//         else if (s[i] == '"' || s[i] == '\'')
//         {
//             quote = s[i++];
//             while (s[i] && s[i] != quote)
//             {
//                 if ((s + i) == mark)
//                     return (1);
//                 i++;
//             }
//         }
//         i++;
//     }
//     return (0);
// }

// int unclosed(char *s)
// {
// 	char	quote;
// 	int		fail;
// 	int		i;

// 	fail = 0;
// 	i = 0;
// 	while (s[i])
// 	{
// 		if (s[i] == '"' || s[i] == '\'')
// 	{
// 	quote = s[i++];
// 	fail = 1;
// 	while (s[i] && s[i] != quote)
// 		i++;
// 	if (s[i] == quote)
// 	fail = 0;
// 	}
// 	i++;
// 	}
// 	return (fail);
// }

// int main()
// {
//     char s[] = "   echo   \"eyooo guys how are you doing\"    arigato  '''  ssuup ''";
//     char *p;

// //    p = ft_strchr(s, '|');
//    printf("%d\n", unclosed(s));
// }
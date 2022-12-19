NAME =    libft.a
CC = gcc
CFLAGS = -Wall -Wextra -Werror

RM = rm -f
SRC = lib/ft_isalnum.c \
	lib/ft_itoa.c \
	lib/ft_memcmp.c	\
	lib/ft_strlcat.c \
	lib/ft_strtrim.c \
	lib/ft_isprint.c \
	lib/ft_substr.c \
	lib/ft_memset.c	\
	lib/ft_strjoin.c	\
	lib/ft_strnstr.c	\
	lib/ft_toupper.c	\
	lib/ft_atoi.c		\
	lib/ft_isalpha.c	\
	lib/ft_memchr.c		\
	lib/ft_split.c		\
	lib/ft_strlcpy.c	\
	lib/ft_strrchr.c	\
	lib/ft_bzero.c		\
	lib/ft_isascii.c	\
	lib/ft_memcpy.c	\
	lib/ft_strchr.c	\
	lib/ft_strlen.c	\
	lib/ft_calloc.c	\
	lib/ft_isdigit.c	\
	lib/ft_memmove.c	\
	lib/ft_strdup.c	\
	lib/ft_strncmp.c	\
	lib/ft_tolower.c \
	lib/ft_strmapi.c 	\
	lib/ft_striteri.c	\
	lib/ft_putchar_fd.c	\
	lib/ft_putstr_fd.c	\
	lib/ft_putendl_fd.c	\
	lib/ft_putnbr_fd.c

BNS = t_list/ft_lstadd_back.c \
	t_list/ft_lstdelone.c \
	t_list/ft_lstnew.c \
	t_list/ft_lstlast.c \
	t_list/ft_lstsize.c 


LST = t_list/ft_lstdelone.c \
	t_list/ft_lstclear.c \
	t_list/ft_lstiter.c \
	t_list/ft_lstmap.c \
	t_list/ft_lstadd_front.c 

BOBJ = $(BNS:.c=.o)
OBJ = $(SRC:.c=.o)
$(NAME): $(OBJ) libft.h
	ar rc $(NAME) $(OBJ)
%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

all: $(NAME)

bonus: $(BOBJ) $(BNS)
	ar rc $(NAME) $(BOBJ) $(BNS)

clean:
	$(RM) $(OBJ) $(BOBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: clean fclean


## export/env with spaces
## export with var without value / it should export it
## cd - / it should go to OLDPWD
## exit status / always your program should exit woth last exit status/ set var in your struct named (exit_status) and everytime you wanna exit it should exit with it (var in your struct)
## execute minishell without env (env -i) / #include "path.h" _PATH_STDPATH
## herdoc / when Del was $USER
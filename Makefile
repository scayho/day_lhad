NAME = minishell

HEADER = minishell.h

LIB_ARCHIVE = libft.a

LIB_HEADER= lib/libft.h

CC = gcc

FLAGS = -Wall -Wextra -Werror

RM = rm -f

RDFLAGS =  -lreadline 
# RDFLAGS =  -lreadline -L ~/.brew/opt/readline/lib -I ~/.brew/opt/readline/include

# RDFLAGS = -I /Users/hchahid/Desktop/mnsh/readline/include -L /Users/hchahid/Desktop/mnsh/readline/lib   -lreadline

# RDFLAGS = -L readline -I readline -l readline 


# RDFLAGS = -l readline

# $(wildecard lib/*.c)

SRC = minishell.c env_variables.c env_vars1.c built_ins.c echo.c   \
	 redirection.c update_pwd_vars.c \
	davidof.c \
	updates_for_env_after_export.c \
	attributes.c \
	parsing.c \
	ft_strcmp.c \
	replace_env_buf.c \
	if_directory.c \
	parse.c \
	syntax.c \
	wild_card.c \
	split_by_args.c \
	join_free.c \
	nested_dirs.c \
	pipe.c \
	custom_split.c \
	is_quoted.c \
	pipe_utils.c \
	redirection_split.c	\
	cd.c \
	cd1.c \
	j.c \
	remove_qoutes.c \
	last_red_in.c \
	env_handling.c	\
	signals.c

LIB = lib/ft_isalnum.c	 \
	lib/ft_itoa.c		 \
	lib/ft_memcmp.c		\
	lib/ft_strlcat.c 	\
	lib/ft_strtrim.c	\
	lib/ft_isprint.c	\
	lib/ft_substr.c 	\
	lib/ft_memset.c		\
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
	lib/ft_memcpy.c		\
	lib/ft_strchr.c		\
	lib/ft_strlen.c		\
	lib/ft_calloc.c		\
	lib/ft_isdigit.c	\
	lib/ft_memmove.c	\
	lib/ft_strdup.c		\
	lib/ft_strncmp.c	\
	lib/ft_tolower.c	\
	lib/ft_strmapi.c 	\
	lib/ft_striteri.c	\
	lib/ft_putchar_fd.c	\
	lib/ft_putstr_fd.c	\
	lib/ft_putendl_fd.c	\
	lib/ft_putnbr_fd.c	\
	lib/t_list/ft_lstadd_back.c \
	lib/t_list/ft_lstdelone.c \
	lib/t_list/ft_lstnew.c \
	lib/t_list/ft_lstlast.c \
	lib/t_list/ft_lstsize.c 

LIB_OBJ = $(LIB:.c=.o)

OBJ = $(SRC:.c=.o)

$(NAME): $(OBJ) $(HEADER) $(LIB_ARCHIVE)
	$(CC) $(FLAGS) $(OBJ) $(LIB_ARCHIVE) $(RDFLAGS) -o $(NAME)

$(LIB_ARCHIVE): $(LIB_OBJ) $(LIB_HEADER)
	ar rc $(LIB_ARCHIVE) $(LIB_OBJ)

%.o: %.c minishell.h
	$(CC) $(FLAGS) -o $@ -c $<


all: $(NAME)

clean:
	$(RM) $(OBJ)
	$(RM) $(LIB_OBJ)

fclean: clean
	$(RM) $(NAME)
	$(RM) $(LIB_ARCHIVE)

re: fclean all

.PHONY: all clean fclean re

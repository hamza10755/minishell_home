CC = cc

CFLAGS = -Wall -Wextra -Werror

NAME = libft.a

SRCS = ft_isalpha.c ft_isalnum.c ft_isascii.c ft_isdigit.c ft_isprint.c ft_strlen.c ft_memset.c \
ft_strchr.c ft_atoi.c ft_toupper.c ft_tolower.c ft_bzero.c ft_strlcpy.c ft_strlcat.c ft_strrchr.c \
ft_strncmp.c ft_memcpy.c ft_memchr.c ft_memcmp.c ft_strdup.c ft_calloc.c ft_strnstr.c ft_substr.c \
ft_strjoin.c ft_memmove.c ft_putstr_fd.c ft_putendl_fd.c ft_putchar_fd.c ft_putnbr_fd.c ft_strtrim.c \
ft_itoa.c ft_strmapi.c ft_split.c ft_striteri.c get_next_line.c ft_strtok.c

BONUS_SRCS = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c \
ft_lstclear.c ft_lstiter.c ft_lstmap.c

BONUS_OBJS = $(BONUS_SRCS:.c=.o)

OBJS = $(SRCS:.c=.o)

all : $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -c -o $@ $<

$(NAME) : $(OBJS)
	@ar rcs $(NAME) $(OBJS) 

bonus: $(OBJS) $(BONUS_OBJS)
	@ar rcs $(NAME) $(OBJS) $(BONUS_OBJS)

clean :
	@rm -rf $(OBJS) $(BONUS_OBJS)
fclean : clean
	@rm -rf $(NAME)

re: fclean all

.PHONY: fclean clean all


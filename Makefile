NAME= pipex
FLAGS= -Werror -Wall -Wextra
SRCS= pipex.c
OBJS= $(SRCS:.c=.o)
LIBFT= libft/libft.a

all: libft $(NAME)

libft:
	@make -C ./libft -j

$(NAME): $(LIBFT) $(OBJS)
	@gcc $(LIBFT) $(OBJS) -o $(NAME)
	@echo
	@echo "---------- \033[1;36mSuccessfully generated pipex\033[0m ----------"
	@echo

%.o: %.c
	@gcc -g -c $< -o $@

clean:
	@make clean -C ./libft
	@rm -f *.o

fclean: clean
	@make fclean -C ./libft
	@rm -f $(NAME)
	@echo
	@echo "---------- \033[1;36mSuccessfully deleted pipex\033[0m ----------"
	@echo

re: fclean all

.PHONY: libft
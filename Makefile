SRCS_ALGO	=	srcs/draw.c								\
				srcs/hook.c								\
				srcs/iso.c								\
				srcs/main.c								\
				srcs/parsing.c							\

INCLUDES	=	-Iincludes								\
				-Ilibft/includes						\
				-Imlx


SRCS		=	$(SRCS_ALGO)
OBJS		=	$(SRCS:.c=.o)

CC			=	@cc
RM			=	@rm -f
NAME		=	fdf

LD_FLAGS	=	-Lmlx -lbsd -lmlx -lXext -lX11
FLAGS		=	-Wall -Werror -Wextra $(INCLUDES) -fsanitize=address -g

LIBFT			=	libft/libft.a
MLX				=	mlx/libmlx_Linux.a

.c.o:
				@$(CC) -c $< -o $(<:.c=.o) $(FLAGS)

$(NAME):		$(LIBFT) start_message $(OBJS)
				@if [ "$?" = "start_message" ]; then echo -n "\033[1A\033[30C\033[0;33mAlready done\033[15D\033[1B\033[1A\033[2D\033[1;32m✓\033[26D\033[1B\033[0m";else echo -n "\033[1A\033[25C\033[1;32m✓\033[26D\033[1B\033[0m"; fi
				$(CC) $(LD_FLAGS) $(FLAGS) $(OBJS) $(LIBFT) $(MLX) -o $(NAME)

$(LIBFT):
				@make -s -C libft -f Makefile

all:			$(NAME)

bonus:			re

clean:
				@make -s -C libft -f Makefile clean
				@echo "\033[0;33mCleaning \033[1;31m$(NAME)\033[0;33m's objects\033[0m"
				$(RM) $(OBJS)

fclean:			clean
				@make -s -C libft -f Makefile fclean
				@echo "\033[0;33mRemoving \033[1;31m$(NAME)\033[0;33m.\033[0m"
				$(RM) $(NAME)

start_message:
				@echo "\033[0;33mMaking \033[1;31m$(NAME)\033[0;33m\t\t\033[1;30m[\033[1;31mX\033[1;30m]\033[0m"

re:				fclean $(NAME)
				$(CC) $(LD_FLAGS) $(FLAGS) $(OBJS) $(LIBFT) $(MLX) -o $(NAME)

.PHONY:			all clean fclean re
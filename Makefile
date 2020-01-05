SRCS			=	main.c
OBJS			= $(SRCS:.c=.o)

CC				= gcc
RM				= rm -f
CFLAGS			= -O3 -Wall -Wextra -Werror -I.
LIBS			= -lmlx -lXext -lX11
MLX				= libmlx.a

NAME			= cub3D

all:			$(NAME)

$(NAME):		$(MLX) $(OBJS)
					gcc ${CFLAGS} -o ${NAME} ${OBJS} ${LIBS}

$(MLX):
					@$(MAKE) -C mlx
									@mv mlx/$(MLX) .

clean:
					@$(MAKE) -C mlx clean
									$(RM) $(OBJS) $(BONUS_OBJS)

fclean:			clean
					$(RM) $(NAME) $(MLX)

re:				fclean $(NAME)

.PHONY:			all clean fclean re

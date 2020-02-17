# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: darodrig <darodrig@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/12/09 13:22:42 by darodrig          #+#    #+#              #
#    Updated: 2020/02/13 15:00:21 by darodrig         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS			=	ft_cub3d.c get_next_line.c get_next_line_utils.c map.c \
					libft.c logic.c array.c utils.c put.c put2.c raycasting.c \
					free.c limits.c textures.c keys.c minimap.c map2.c \
					sprites.c libft2.c screenshot.c raycasting2.c limits2.c
OBJS			= $(SRCS:.c=.o)

CC				= gcc
RM				= rm -f
CFLAGS			= -O3 -Wall -Wextra -Werror -I.
LIBS			= -Lmlx -lmlx -framework OpenGL -framework AppKit -lm
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

debug:		$(MLX) $(OBJS)
				gcc -g ${CFLAGS} -o ${NAME} ${OBJS} ${LIBS}
				
test:		$(MLX) $(OBJS)
				gcc ${CFLAGS} -o ${NAME} ${OBJS} ${LIBS}
				make clean
				./$(NAME) 1.cub


.PHONY:			all clean fclean re

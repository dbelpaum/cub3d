CC			=	gcc

FLAGS		=	-Wall -Werror -Wextra -g3

RM			=	rm -f

SRCS		=	srcs/main.c						\
				srcs/map_parsing.c				\
				srcs/parsingnorm.c				\
				srcs/map_content_checker.c		\
				srcs/map_map_checker.c			\
				srcs/strutils.c					\
				srcs/strstrutils.c				\
				srcs/data_utils.c				\
				srcs/hooks.c					\
				srcs/hooks2.c					\
				srcs/gnl.c						\
				srcs/my_free.c					\
				srcs/debug.c					\
				srcs/minimap.c					\
				srcs/minimapnorm.c				\
				srcs/game_loop.c				\
				srcs/game_loop2.c				\


OBJS		=	${SRCS:.c=.o}

LIBFT		=	libft/libft.a

MLX			=	minilibx-linux/libmlx_Linux.a

MLXFLAGS	=	-lX11 -lXext

NAME		=	cub3D

all			:	${NAME}

${NAME}		:	${LIBFT} inc/cub3D.h ${OBJS}
				${CC} ${FLAGS} ${OBJS} ${LIBFT} -Iinc/cub3D.h -o ${NAME} ${MLX} ${MLXFLAGS}

${LIBFT}	:
				make -C libft/ bonus

.c.o		:
				$(CC) $(FLAGS) -I/usr/include -Iminilibx-linux -c $< -o $@

clean		:
				${RM} ${OBJS}
				make -C libft/ clean

fclean		:	clean
				${RM} ${NAME}
				make -C libft/ fclean

re			:	fclean	all

.PHONY		:	all clean fclean re libft bonus

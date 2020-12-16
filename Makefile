SRC_DIR		= ./srcs/

SRC 		= ${SRC_DIR}screen.c ${SRC_DIR}ft_strdup.c ${SRC_DIR}start.c ${SRC_DIR}parse.c ${SRC_DIR}utils.c ${SRC_DIR}ft_split.c ${SRC_DIR}ft_atoi.c ${SRC_DIR}parse_rgb.c ${SRC_DIR}parse_map.c ${SRC_DIR}ft_strcmp.c ${SRC_DIR}close.c ${SRC_DIR}ft_putstr_fd.c ${SRC_DIR}get_next_line.c ${SRC_DIR}ft_strjoin.c
OBJS 		= ${SRC:.c=.o}

NAME 		= Cub3D

CC 			= clang

CFLAGS 		= -Wall -Wextra -Werror

${NAME}: 	${OBJS}
		 	${CC} ${OBJS} -o ${NAME}

all: 		${NAME}

clean:
	   		rm -f ${OBJS} ${BONUS_OBJS}

fclean:		clean
			rm -f ${NAME}

re:			fclean all

bonus:		${OBJS}
		 	${CC} -o ${NAME} ${OBJS} -lmlx -L/usr/lib -lXext -lX11 -lm -lbsd 

.PHONY:		all clean fclean re bonus

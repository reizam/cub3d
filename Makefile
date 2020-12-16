SRC_DIR		= ./srcs/

SRC 		= ${SRC_DIR}start.c ${SRC_DIR}parse.c ${SRC_DIR}utils.c ${SRC_DIR}ft_split.c ${SRC_DIR}ft_atoi.c ${SRC_DIR}parse_rgb.c ${SRC_DIR}parse_map.c ${SRC_DIR}ft_strcmp.c ${SRC_DIR}close.c ${SRC_DIR}ft_putstr_fd.c ${SRC_DIR}get_next_line.c ${SRC_DIR}ft_strjoin.c
OBJS 		= ${SRC:.c=.o}

NAME 		= Cub3D

CC 			= gcc

CFLAGS 		= -Wall -Wextra -Werror

.c.o:		
			${CC} ${CFLAGS} -c -I./includes/ $< -o ${<:.c=.o}

${NAME}: 	${OBJS}
		 	${CC} ${NAME} ${OBJS} -o ${NAME}

all: 		${NAME}

clean:
	   		rm -f ${OBJS} ${BONUS_OBJS}

fclean:		clean
			rm -f ${NAME}

re:			fclean all

bonus:		${OBJS}
		 	${CC} ${NAME} ${OBJS} -o ${NAME}

.PHONY:		all clean fclean re bonus

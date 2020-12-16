SRC_DIR		= ./srcs/

SRC 		= ${SRC_DIR}start.c ${SRC_DIR}parse.c ${SRC_DIR}utils.c ${SRC_DIR}ft_split.c
OBJS 		= ${SRC:.c=.o}

NAME 		= Cub3D

CC 			= gcc

CFLAGS 		= -Wall -Wextra -Werror

.c.o:		
			${CC} ${CFLAGS} -c -I./includes/ $< -o ${<:.c=.o}

${NAME}: 	${OBJS}
		 	${AR} ${NAME} ${OBJS}

all: 		${NAME}

clean:
	   		rm -f ${OBJS} ${BONUS_OBJS}

fclean:		clean
			rm -f ${NAME}

re:			fclean all

bonus:		${OBJS} ${BONUS_OBJS}
			${AR} ${NAME} ${OBJS} ${BONUS_OBJS}

.PHONY:		all clean fclean re bonus

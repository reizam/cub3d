SRC_DIR		= ./srcs/

SRC 		= ${SRC_DIR}screen.c ${SRC_DIR}ft_strdup.c ${SRC_DIR}start.c ${SRC_DIR}parse.c ${SRC_DIR}utils.c ${SRC_DIR}ft_split.c ${SRC_DIR}ft_atoi.c ${SRC_DIR}parse_rgb.c ${SRC_DIR}parse_map.c ${SRC_DIR}ft_strcmp.c ${SRC_DIR}close.c ${SRC_DIR}ft_putstr_fd.c ${SRC_DIR}get_next_line.c ${SRC_DIR}ft_strjoin.c
OBJS 		= ${SRC:.c=.o}

NAME 		= Cub3D

CC 			= clang

CFLAGS 		= -Wall -Wextra -Werror

.c.o:		
			${CC} ${CFLAGS} -I/usr/include/ -03 -I.. -I./includes/ -c $< -o ${<:.c=.o}

${NAME}: 	${OBJS}
		 	${CC} -o ${NAME} ${OBJS} -L.. -lmlx -L/usr/include/../lib -lXext -lX11 -lm -lbsd 

all: 		${NAME}

clean:
	   		rm -f ${OBJS} ${BONUS_OBJS}

fclean:		clean
			rm -f ${NAME}

re:			fclean all

.PHONY:		all clean fclean re bonus

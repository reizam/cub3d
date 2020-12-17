SRC_DIR		= ./srcs/
UTILS_DIR	= ./utils/

SRC 		= ${SRC_DIR}screen.c ${UTILS_DIR}ft_strdup.c ${SRC_DIR}start.c ${SRC_DIR}parse.c ${UTILS_DIR}utils.c ${UTILS_DIR}ft_split.c ${UTILS_DIR}ft_atoi.c ${SRC_DIR}parse_rgb.c ${SRC_DIR}parse_map.c ${UTILS_DIR}ft_strcmp.c ${SRC_DIR}close.c ${UTILS_DIR}ft_putstr_fd.c ${UTILS_DIR}get_next_line.c ${UTILS_DIR}ft_strjoin.c
OBJS 		= ${SRC:.c=.o}

NAME 		= Cub3D

CC 			= clang

CFLAGS 		= -Wall -Wextra -Werror

.c.o:		
			${CC} ${CFLAGS} -I/usr/include/ -I.. -I./includes/ -c $< -o ${<:.c=.o}

${NAME}: 	${OBJS}
		 	${CC} -o ${NAME} ${OBJS} -L.. -lmlx -L/usr/include/../lib -lXext -lX11 -lm -lbsd 

all: 		${NAME}

clean:
	   		rm -f ${OBJS} ${BONUS_OBJS}

fclean:		clean
			rm -f ${NAME}

re:			fclean all

.PHONY:		all clean fclean re bonus

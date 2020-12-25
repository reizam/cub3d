MAIN_DIR	= ./main/
UTILS_DIR	= ./utils/
PARSING_DIR = ./parsing/
IMAGE_DIR = ./image/
CONTROLS_DIR = ./controls/

SRC 		= ${IMAGE_DIR}others.c ${IMAGE_DIR}sprite.c ${UTILS_DIR}sprite_utils.c ${IMAGE_DIR}bitmap.c ${PARSING_DIR}parse_check_map.c ${IMAGE_DIR}wall.c ${IMAGE_DIR}texture.c ${PARSING_DIR}parse_texture.c ${CONTROLS_DIR}controls.c ${IMAGE_DIR}draw.c ${IMAGE_DIR}screen.c ${UTILS_DIR}ft_strlen.c ${UTILS_DIR}ft_strdup.c ${MAIN_DIR}start.c ${PARSING_DIR}parse.c ${UTILS_DIR}utils.c ${UTILS_DIR}ft_split.c ${UTILS_DIR}ft_atoi.c ${PARSING_DIR}parse_rgb.c ${PARSING_DIR}parse_map.c ${UTILS_DIR}ft_strcmp.c ${MAIN_DIR}close.c ${UTILS_DIR}ft_putstr_fd.c ${UTILS_DIR}get_next_line.c ${UTILS_DIR}ft_strjoin.c
OBJS 		= ${SRC:.c=.o}

NAME 		= cub3D

CC 			= clang

CFLAGS 		= -Wall -Wextra -Werror 

.c.o:		
			${CC} ${CFLAGS} -I/usr/include/ -I.. -I./includes/ -c $< -o ${<:.c=.o}

${NAME}: 	${OBJS}
		 	${CC} -o ${NAME} ${OBJS} -L.. -lmlx -L/usr/include/../lib -lXext -lX11 -lm -lbsd 

all: 		${NAME}

clean:
	   		rm -f ${OBJS}

fclean:		clean
			rm -f ${NAME}

re:			fclean all

.PHONY:		all clean fclean re bonus

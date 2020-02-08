# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: lperron <lperron@student.le-101.f>         +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2019/05/09 12:30:59 by lperron      #+#   ##    ##    #+#        #
#    Updated: 2020/02/04 18:34:24 by mtaquet     ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

CC= gcc
SRCDIR= ./srcs/
FILES= point.c vector.c vector2.c rotate.c input.c fast_dda.c raycaster.c event.c main.c init.c controls.c utils.c threads.c init_button.c get_pack_info.c get_pack_check.c get_pack_check2.c utils2.c utils3.c utils4.c menu.c menu_control.c menu_pack.c button.c key_event.c img_utils.c free.c
SRC= $(addprefix $(SRCDIR),$(FILES))
OBJ= $(SRC:.c=.o)
INC= ./includes/wolf.h
ifeq ($(shell uname -s),Linux)
	INCFLAG= -I ./libft/includes/ -I ./minilibx/ -I ./includes/
endif
ifeq ($(shell uname -s),Darwin)
	INCFLAG= -I ./libft/includes/ -I ./minilibx_macos/ -I ./includes/
endif

all: libs wolf3d

libs:
	make -C ./libft/
	cp ./libft/libft.a ./libft.a
ifeq ($(shell uname -s),Linux)
	make -C ./minilibx/
	cp ./minilibx/libmlx_Linux.a ./libmlx.a
endif
ifeq ($(shell uname -s),Darwin)
	make -C ./minilibx_macos/
	cp ./minilibx_macos/libmlx.a ./libmlx.a
endif

%.o: %.c $(INC)
	$(CC) -c -o $@ $< $(INCFLAG)  -Wextra -Wall -pthread -O3 -march=native
	
wolf3d: $(OBJ) $(INC)
ifeq ($(shell uname -s),Linux)
	$(CC) -o wolf3d $(OBJ) -L.. -lmlx -L/usr/include/../lib -lXext -lX11 -lm -L . -lft -lm -L/usr/X11/lib -lX11 -lmlx -lXext -Wall -Wextra -pthread
endif
ifeq ($(shell uname -s),Darwin)
	$(CC) -o wolf3d $(OBJ) -L . -lft -lm -framework OpenGl -framework Appkit -lmlx -Wall -Wextra -Werror
endif

clean: 
	make -C ./libft/ clean
	make -C ./minilibx/ clean
	make -C ./minilibx_macos/ clean
	rm -f ./srcs/*.o

fclean: clean
	make -C ./libft/ fclean
	make -C ./minilibx/ clean
	make -C ./minilibx_macos/ clean
	rm -f ./libmlx.a
	rm -f ./libft.a
	rm -f ./wolf3d


re: fclean all

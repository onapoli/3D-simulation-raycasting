NAME = cub3D

CUB3D_SRC =	cub3d.c \
			main_function_utilities.c \
			main_function_utilities_2.c \
			main_function_utilities_3.c \
			utilities.c \
			movement.c \
			rotation.c \
			map_interpreter.c \
			raycaster.c \
			raycaster_utilities.c \
			raycaster_wall_utilities.c \
			sprites.c \
			sprites_utilities.c \
			view.c \
			view_utilities.c \
			draw_sprite.c \
			reader.c \
			reader_utils.c \
			process_file_data.c \
			add_file_data.c \
			add_file_data_utilities.c \
			map_processor.c \
			generate_map.c \
			validate_map.c \
			validate_map_first_last_lines.c \
			validate_line_utilities.c \
			get_next_line.c \
			get_next_line_utils.c \
			create_bmp.c \
			time.c

OBJ = $(CUB3D_SRC:.c=.o)

CC = gcc
# QUITAR -g AL ENTREGAR. -g ES PARA gdb DEBUGGING
CFLAGS = -g -Wall -Wextra -Werror
# ESTAS FLAGS HAY QUE CAMBIARLAS EN MAC
IFLAG = -I /usr/local/include
LFLAG = -L /usr/local/lib -lmlx -lXext -lX11
# ESTO AÑADE LIBRERÍAS COMO math.h. CREO QUE EN MAC NO HACE FALTA
LIBS = -lm

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(IFLAG) -o $(NAME) $(OBJ) $(LFLAG) $(LIBS)

%.o: %.c
	@$(CC) $(CFLAGS) $(IFLAG) -c $< -o $@

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

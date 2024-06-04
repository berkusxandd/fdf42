NAME = fdf
SRCS = ./srcs/main.c ./srcs/mlx_data_operations.c ./srcs/key_menu_handle.c ./srcs/vector_operations.c ./srcs/draw_line_utils.c ./srcs/map_parse.c ./srcs/draw_line.c ./srcs/free_tabs.c ./srcs/error_handling.c ./srcs/map_parse_utils.c ./srcs/map_parse_utils2.c
OBJS = $(SRCS:.c=.o)
LIBFT = ./Libft/libft.a
RM = rm -rf
all: $(NAME)

%.o: %.c
	$(CC) -Wall -Wextra -Werror -I/usr/include -Imlx_linux -O3 -c $< -o $@

$(NAME): $(OBJS)
	make -C ./Libft
	$(CC) $(OBJS) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz $(LIBFT) -o $(NAME)

clean:
	$(RM) $(OBJS)
	@make clean -C ./Libft

fclean: clean
	$(RM) $(NAME)
	@make fclean -C ./Libft

re: fclean all

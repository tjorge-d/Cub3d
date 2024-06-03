NAME= cub3D

CC= cc
CFLAGS= -Wall -Werror -Wextra -Ofast -g

SRC_MA= $(addprefix sources/main/, $(SOURCES_MAIN))
SOURCES_MAIN=		cub_utils.c			\
					main.c				\
					initializer.c		\
					load_cub.c			\
					hooks.c

SRC_PA= $(addprefix sources/parser/, $(SOURCES_PARSER))
SOURCES_PARSER=		parser.c			\
					colors.c			\
					map_creator.c		\
					map_elements.c		\
					map_validator.c

SRC_DI= $(addprefix sources/display/, $(SOURCES_DISPLAY))
SOURCES_DISPLAY=	frame.c				\
					minimap.c			\
					painting_tools.c	\
					mlx_window.c		\
					drawer.c

SRC_PH= $(addprefix sources/physics/, $(SOURCES_PHYSICS))
SOURCES_PHYSICS=	dda_basic.c			\
					dda_combo.c			\
					dda_utils.c			\
					movement.c
		
OBJ_DIR= objects
OBJ=	$(addprefix $(OBJ_DIR)/, $(SRC_MA:sources/main/%.c=%.o)) \
		$(addprefix $(OBJ_DIR)/, $(SRC_PA:sources/parser/%.c=%.o)) \
		$(addprefix $(OBJ_DIR)/, $(SRC_DI:sources/display/%.c=%.o)) \
		$(addprefix $(OBJ_DIR)/, $(SRC_PH:sources/physics/%.c=%.o))

MLX_DIR= ./.mlx
MLX= $(MLX_DIR)/libmlx_Linux.a -lXext -lX11 -lm -lz

LIBFT_DIR= ./libft
LIBFT= $(LIBFT_DIR)/libft.a

all: $(NAME)

$(NAME): $(OBJ) $(MLX) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) -o $@ $(MLX) $(LIBFT)

$(OBJ_DIR)/%.o: sources/main/%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: sources/parser/%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: sources/display/%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: sources/physics/%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(MLX):
	$(MAKE) -C $(MLX_DIR)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

clean:
	rm -rf $(OBJ_DIR)
	$(MAKE) -C $(MLX_DIR) clean
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

run: re
	clear && ./Cub3D

.PHONY: all fclean clean re run
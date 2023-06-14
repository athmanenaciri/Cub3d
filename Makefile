
CC = cc -g

CFLAGS = -Wall -Werror -Wextra -g
DBUILD = build
FILES = get_next_line getnext_utils parsing parsing_utils main draw about_lines \
	cast_rays2 ft_split map_content events2 wall_projection ft_atoi images parsing_texture\
	init draw2

	
OBJS = $(addprefix $(DBUILD)/, $(FILES:=.o))

NAME = cub3d

all: $(NAME)

# $(NAME): $(OBJS)
# 	$(CC) $^ -o $@ -Lmlx -lmlx -L/usr/lib -Imlx -lXext -lX11 -lm -lz 
#
# $(DBUILD)/%.o: %.c cub3D.h
# 	@mkdir -p $(@D)
# 	$(CC) $(CFLAGS) -I/usr/include -Imlx -c $< -o $@ # -I ./mlx

$(NAME): $(OBJS)
	$(CC) $^ -o $@  -lmlx -framework OpenGL -framework AppKit #-fsanitize=address

$(DBUILD)/%.o: %.c cub3D.h
	@mkdir -p $(DBUILD)
	$(CC) -c $< -o $@ -Imlx


clean:
	@rm -rf $(OBJ) $(DBUILD)
fclean: clean
	@rm -f $(NAME)

re: fclean all

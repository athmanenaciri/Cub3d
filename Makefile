
NAME = cub3D

B_NAME = cub3D_bonus

CC = cc -g

CFLAGS = -Wall -Werror -Wextra -Ofast

DBUILD = build/M_CUB3D

B_BUILD = build/B_CUB3D

FILES = get_next_line getnext_utils parsing parsing_utils main draw about_lines \
	cast_rays ft_split map_content events2 wall_projection ft_atoi images parsing_texture\
	init 

OBJS = $(addprefix $(DBUILD)/, $(FILES:=.o))

B_OBJS = $(addprefix $(B_BUILD)/, $(FILES:=.o))

all: $(NAME)

bonus : $(B_NAME)

$(NAME): $(OBJS)
	$(CC) $^ -o $@  -lmlx -framework OpenGL -framework AppKit

$(B_NAME): $(B_OBJS)
	$(CC) $^ -o $@ -lmlx -framework OpenGL -framework AppKit

$(DBUILD)/%.o: M_CUB3D/%.c M_CUB3D/cub3D.h
	@mkdir -p $(DBUILD)
	$(CC) -c $< -o $@ -Imlx

$(B_BUILD)/%.o: B_CUB3D/%.c B_CUB3D/cub3D_bonus.h
	@mkdir -p $(B_BUILD)
	$(CC) -c $< -o $@ -Imlx

clean:
	@rm -rf build
fclean: clean
	@rm -f $(NAME)
	@rm -f $(B_NAME)

re: fclean all

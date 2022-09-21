# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: lsinke <lsinke@student.codam.nl>             +#+                      #
#                                                    +#+                       #
#    Created: 2022/09/11 19:43:19 by lsinke        #+#    #+#                  #
#    Updated: 2022/09/14 17:27:08 by rvan-mee      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME := miniRT

CC := gcc

CFLAGS += -Wall -Werror -Wextra
CFLAGS += -g
INCLUDE += -I $(INCD)

# SOURCE FILES
SRCD := src/
SRCS := main.c										\
		\
		mlx/create_mlx.c							\
		mlx/hooks.c									\
		mlx/bmp.c									\
		\
		parse/parse.c								\
		parse/parse_scene.c							\
		parse/parse_object.c						\
		parse/parse_utils.c							\
		parse/objects/parse_ambient.c				\
		parse/objects/parse_camera.c				\
		parse/objects/parse_cylinder.c				\
		parse/objects/parse_plane.c					\
		parse/objects/parse_sphere.c				\
		parse/objects/parse_light.c					\
		parse/attributes/parse_float.c				\
		parse/attributes/parse_rgb.c				\
		parse/attributes/parse_vector.c				\
		parse/normalize/normalize.c					\
		parse/normalize/normalize_coords.c			\
		parse/normalize/normalize_orientation.c		\
		\
		math/product.c								\
		math/matrix.c								\
		math/normalize_vector.c						\
		\
		render/render.c								\
		render/cast_primary_rays.c

SRCP := $(addprefix $(SRCD), $(SRCS))

# OBJECT FILES
OBJD := obj/
OBJS := $(SRCS:.c=.o)
OBJP := $(addprefix $(OBJD), $(OBJS))

# HEADER FILES
INCD := include/
INCS := minirt.h									\
		parse.h										\
		mlx.h										\
		bmp.h										\
		ft_math.h									\
		render.h
INCP := $(addprefix $(INCD), $(INCS))

HEADERS += $(INCP)

# LIBRARIES

LIBD = lib/

#		LIBFT
LIBFT_D := $(LIBD)libft/
LIBFT_N := libft.a
LIBFT_H := libft.h								\
		   get_next_line.h						\
		   dynarr.h
LIBFT_I := $(addprefix $(LIBFT_D), $(INCD))
LIBFT_L := $(addprefix $(LIBFT_D), $(LIBFT_N))

INCLUDE += -I $(LIBFT_I)
LIBS += $(LIBFT_L)

#		MLX42
MLX42_D := $(LIBD)MLX42/
MLX42_N := libmlx42.a
MLX42_I := $(addprefix $(MLX42_D), $(INCD))
MLX42_L := $(addprefix $(MLX42_D), $(MLX42_N))

LINKER_FLAGS += -lglfw
LINKER_FLAGS += -lm
INCLUDE += -I $(MLX42_I)
LIBS += $(MLX42_L)

ifeq ($(shell uname -s), Darwin)
	GLFW := $(shell brew --prefix glfw)/lib
	LINKER_FLAGS += -L $(GLFW)
else
	LINKER_FLAGS += -ldl
endif

#		RANDOM THINGS
COMPILE := @$(CC) $(INCLUDE) $(CFLAGS)

# TEST

TEST_DIR := test/
TEST_LIB := $(addprefix $(TEST_DIR), $(addsuffix _test.a, $(NAME)))
TEST_LIB_OBJS := $(filter-out $(OBJD)main.o, $(OBJP))

TESTS := parse.sh
TEST_P := $(addprefix $(TEST_DIR), $(TESTS))

# RECIPES
all: $(NAME) $(TEST_LIB)

$(NAME): $(LIBS) $(OBJP)
	@echo "Compiling main executable!"
	$(COMPILE) $(OBJP) $(LIBS) $(LINKER_FLAGS) -o $(NAME)

$(OBJD)%.o: $(SRCD)%.c $(HEADERS)
	@mkdir -p $(@D)
	@echo "Compiling: $<"
	$(COMPILE) -c -o $@ $<

$(LIBFT_L):
	@$(MAKE) -C $(LIBFT_D)

$(MLX42_L):
	@$(MAKE) -C $(MLX42_D)

clean: cleantest
	@rm -rf $(OBJD)
	@echo "Done cleaning $(CURDIR)/$(OBJD)"
	@$(MAKE) -C $(LIBFT_D) clean
	@$(MAKE) -C $(MLX42_D) clean

fclean:
	@rm -f $(NAME)
	@$(MAKE) clean
	@$(MAKE) -C $(LIBFT_D) fclean
	@$(MAKE) -C $(MLX42_D) fclean

re: fclean
	@$(MAKE)

$(TEST_LIB): $(TEST_LIB_OBJS)
	@ar -cr $(TEST_LIB) $(TEST_LIB_OBJS)
	@echo "Done creating archive $(TEST_LIB)"

cleantest:
	@rm -f $(TEST_LIB)

.PHONY: all clean fclean re cleantest

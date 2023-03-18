# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: lsinke <lsinke@student.codam.nl>             +#+                      #
#                                                    +#+                       #
#    Created: 2022/09/11 19:43:19 by lsinke        #+#    #+#                  #
#    Updated: 2023/03/06 12:14:44 by lsinke        ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME := miniRT

CC = gcc

CFLAGS += -Wall -Werror -Wextra
CFLAGS += -march=native -O3 -pthread
CFLAGS += -g #-fsanitize=address
INCLUDE += -I $(INCD)

# SOURCE FILES
SRCD := src/
SRCS := main.c										\
		\
		mlx/create_mlx.c							\
		mlx/hooks.c									\
		mlx/bmp.c									\
		mlx/reload_scene.c							\
		mlx/adjust_camera.c							\
		\
		parse/parse.c								\
		parse/parse_scene.c							\
		parse/parse_object.c						\
		parse/parse_utils.c							\
		parse/parse_data.c							\
		parse/destroy_scene.c						\
		parse/objects/parse_ambient.c				\
		parse/objects/parse_camera.c				\
		parse/objects/parse_cylinder.c				\
		parse/objects/parse_plane.c					\
		parse/objects/parse_sphere.c				\
		parse/objects/parse_light.c					\
		parse/objects/parse_triangle.c				\
		parse/objects/parse_obj_vec.c				\
		parse/objects/parse_face.c					\
		parse/objects/parse_exposure.c				\
		parse/attributes/parse_float.c				\
		parse/attributes/parse_float_rgb.c			\
		parse/attributes/parse_rgb.c				\
		parse/attributes/parse_vector.c				\
		parse/attributes/parse_mtl_map.c			\
		parse/mtl/parse_bmp.c						\
		parse/mtl/parse_mtl_d.c						\
		parse/mtl/parse_mtl_illum.c					\
		parse/mtl/parse_mtl_ka.c					\
		parse/mtl/parse_mtl_kd.c					\
		parse/mtl/parse_mtl_ke.c					\
		parse/mtl/parse_mtl_ks.c					\
		parse/mtl/parse_mtl_ni.c					\
		parse/mtl/parse_mtl_ns.c					\
		parse/mtl/parse_mtl_tf.c					\
		parse/mtl/parse_mtl_tr.c					\
		parse/mtl/parse_mtl_map_ka.c				\
		parse/mtl/parse_mtl_map_kd.c				\
		parse/mtl/parse_mtl_map_ks.c				\
		parse/mtl/parse_mtl_name.c					\
		parse/mtl/parse_newmtl.c					\
		parse/mtl/parse_usemtl.c					\
		parse/obj/parse_objfile.c					\
		parse/obj/parse_usemesh.c					\
		parse/obj/meshdata.c						\
		parse/obj/mesh.c							\
		parse/obj/add_mesh.c						\
		\
		math/product.c								\
		math/matrix.c								\
		math/quadratic.c							\
		math/normalize_vector.c						\
		math/vector_utils.c							\
		math/reflect.c								\
		\
		render/render.c								\
		render/trace.c								\
		render/intersect/intersect.c				\
		render/intersect/intersect_sphere.c			\
		render/intersect/intersect_plane.c			\
		render/intersect/intersect_cylinder.c		\
		render/intersect/intersect_triangle.c		\
		render/intersect/intersect_face.c			\
		render/calculate_normal.c					\
		render/get_cam_ray.c						\
		render/shading/shading.c					\
		render/shading/phong.c						\
		render/shading/fresnel.c					\
		render/shading/get_ray_bias.c				\
		render/texture/get_uv_colour.c				\
		render/texture/get_texture_sphere.c			\
		render/texture/get_texture_plane.c			\
		render/texture/get_texture_cyl.c			\
		render/texture/get_texture_triangle.c		\
		render/texture/get_texture_face.c			\
		\
		bvh/new_bvh.c								\
		bvh/morton.c								\
		bvh/cluster.c								\
		bvh/aac_merge.c								\
		bvh/intersect_bvh.c							\
		bvh/get_scene_scale.c						\
		\
		aabb/aabb_combine.c							\
		aabb/aabb_sa.c								\
		aabb/aabb_intersect.c						\
		aabb/calc_bounds.c							\
		\
		threading/threads.c							\
		threading/work.c							\
		threading/work_utils.c						\
		threading/add_job_node.c					\
		threading/reset_work.c						\
		threading/create_render_queue.c

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
		render.h									\
		bvh.h										\
		texture.h									\
		thread.h									
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
	CORE_COUNT = $(shell sysctl -n hw.ncpu)
else
	LINKER_FLAGS += -ldl
	CORE_COUNT = $(shell grep '^processor' /proc/cpuinfo | wc -l)
endif

DEFINES := -D THREAD_C=$(CORE_COUNT)
#		RANDOM THINGS
COMPILE := @$(CC) $(INCLUDE) $(CFLAGS) $(DEFINES)


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

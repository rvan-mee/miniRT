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
CFLAGS += #-fsanitize=address
CFLAGS += $(OFLAGS)
OFLAGS += -march=native -O3 -flto=auto -fuse-linker-plugin -fno-math-errno \
		  -freciprocal-math -fno-signed-zeros -fno-trapping-math -fsingle-precision-constant
INCLUDE += -I $(INCD)

ifdef DEBUG
	CFLAGS += -g
endif

# SOURCE FILES
SRCD := src/
SRCS := main.c										\
		headless.c									\
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
		parse/file_utils.c							\
		parse/parse_data.c							\
		parse/destroy_scene.c						\
		parse/parse_resolution.c					\
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
		parse/mtl/parse_mtlfile.c					\
		parse/obj/parse_objfile.c					\
		parse/obj/parse_usemesh.c					\
		parse/obj/parse_smoothing.c					\
		parse/obj/meshdata.c						\
		parse/obj/mesh.c							\
		parse/obj/add_mesh.c						\
		\
		math/product.c								\
		math/matrix.c								\
		math/quadratic.c							\
		math/normalize_vector.c						\
		math/reflect.c								\
		math/refract.c								\
		math/exp.c									\
		math/minmax.c								\
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
		render/shading/reflect_ray.c				\
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
		bvh/prio_queue.c							\
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
		parse_obj.h									\
		parse_mtl.h									\
		scene.h										\
		mlx.h										\
		bmp.h										\
		ft_math.h									\
		render.h									\
		bvh.h										\
		texture.h									\
		thread.h									\
		headless.h
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

LINKER_FLAGS += -pthread
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

DEFINES := -DTHREAD_C=$(CORE_COUNT) $(OPTIONS)
#		RANDOM THINGS
COMPILE := @$(CC) $(INCLUDE) $(CFLAGS) $(DEFINES)

RES_ARCHIVE = resources.tar.gz
RES_PARTS = resources.tar.gz.part-aa		\
			resources.tar.gz.part-ab

RESOURCES = scenes/models/bmw.obj			\
			scenes/materials/bmw.mtl		\
			\
			scenes/models/buddha.obj		\
			scenes/materials/buddha.mtl		\
			\
			scenes/models/conference.obj	\
			scenes/materials/conference.mtl	\
			\
			scenes/models/female02.obj		\
			scenes/materials/female02.mtl	\
			scenes/textures/female2.bmp		\
			scenes/textures/female3.bmp		\
			scenes/models/male02.obj		\
			scenes/materials/male02.mtl		\
			scenes/textures/male2.bmp		\
			scenes/textures/male3.bmp		\
			scenes/textures/hair.bmp		\
			\
			scenes/models/FireHydrantMesh.obj					\
			scenes/materials/FireHydrantMesh.mtl				\
			scenes/textures/fire_hydrant_Base_Color.bmp			\
			scenes/textures/fire_hydrant_Metallic.bmp			\
			scenes/textures/fire_hydrant_MetallicRoughness.bmp	\
			scenes/textures/fire_hydrant_Mixed_AO.bmp			\
			scenes/textures/fire_hydrant_Normal_OpenGL.bmp		\
			scenes/textures/fire_hydrant_Roughness.bmp			\
			\
			scenes/models/hand.obj			\
			scenes/materials/hand.mtl		\
			scenes/textures/handDiffuse.bmp	\
			\
			scenes/models/raptor.obj	\
			scenes/materials/Raptor.mtl	\
			scenes/textures/raptor.bmp	\
			\
			scenes/models/san-miguel.obj	\
			scenes/materials/san-miguel.mtl	\
			\
			scenes/models/sportsCar.obj		\
			scenes/materials/sportsCar.mtl	\
			\
			scenes/models/sub.obj			\
			scenes/textures/sub_texture.bmp	\
			\
			scenes/models/dragon.obj		\
			scenes/materials/Ceramic.mtl

# RECIPES
all: $(NAME) $(TEST_LIB)

$(NAME): $(LIBS) $(OBJP) $(RESOURCES)
	@echo "Compiling main executable!"
	$(COMPILE) $(OBJP) $(LIBS) $(LINKER_FLAGS) -o $(NAME)

$(OBJD)%.o: $(SRCD)%.c $(HEADERS)
	@mkdir -p $(@D)
	@echo "Compiling: $<"
	$(COMPILE) -c -o $@ $<

$(LIBFT_L):
	@$(MAKE) -C $(LIBFT_D) OFLAGS="$(OFLAGS)"

$(MLX42_L):
	@$(MAKE) -C $(MLX42_D)

clean:
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

$(RESOURCES) &: $(RES_PARTS)
	@test -f $(RES_ARCHIVE) || (cat "$(RES_ARCHIVE).part"* > $(RES_ARCHIVE))
	@echo "Decompressing $(@) from $(RES_ARCHIVE)"
	@tar xzvmf $(RES_ARCHIVE)
	@rm -f $(RES_ARCHIVE)

get_resources: $(RESOURCES)

clean_resoures:
	@rm -f $(RES_ARCHIVE)
	@rm -f $(RESOURCES)

store_resources:
	@echo "Compressing resources into $(RES_ARCHIVE)"
	@tar czvf $(RES_ARCHIVE) $(RESOURCES)
	@echo "Splitting $(RES_ARCHIVE) into 100MB chunks"
	@split -b 100m $(RES_ARCHIVE) "$(RES_ARCHIVE).part-"
	@rm -f $(RES_ARCHIVE)

.PHONY: all clean fclean re get_resources clean_resources store_resources

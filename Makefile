# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: lsinke <lsinke@student.codam.nl>             +#+                      #
#                                                    +#+                       #
#    Created: 2022/09/11 19:43:19 by lsinke        #+#    #+#                  #
#    Updated: 2022/09/11 19:43:19 by lsinke        ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME := miniRT

CC := gcc

CFLAGS += -Wall -Werror -Wextra
INCLUDE += -I $(INCD)

# SOURCE FILES
SRCD := src/
SRCS := main.c
SRCP := $(addprefix $(SRCD), $(SRCS))

# OBJECT FILES
OBJD := obj/
OBJS := $(SRCS:.c=.o)
OBJP := $(addprefix $(OBJD), $(OBJS))

# HEADER FILES
INCD := include/
INCS := miniRT.h
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

LIBS += -lglfw
INCLUDE += -I $(MLX42_I)
LIBS += $(MLX42_L)

ifeq ($(shell uname -s), Darwin)
	GLFW := $(shell brew --prefix glfw)/lib
	CFLAGS += -L $(GLFW)
else
	MLX_ARG = -ldl
endif

#		RANDOM THINGS
COMPILE := @$(CC) $(CFLAGS) $(INCLUDE)

# RECIPES
all: $(NAME)

$(NAME): $(LIBS) $(OBJP)
	@echo "Compiling main executable!"
	$(COMPILE) $(OBJP) $(LIBS) -o $(NAME)

$(OBJD)%.o: $(SRCD)%.c $(HEADERS)
	@mkdir -p $(@D)
	@echo "Compiling: $<"
	$(COMPILE) -c -o $@ $<

$(LIBFT_L):
	@$(MAKE) -C $(LIBFT_D)

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

.PHONY: all clean fclean re -lglfw

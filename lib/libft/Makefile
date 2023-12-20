# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:      :+:    :+:    #
#                                                      +:+                     #
#    By: lsinke <lsinke@student.codam.nl>             +#+                      #
#                                                    +#+                       #
#    Created: 2022/04/20 12:19:17 by lsinke        #+#    #+#                  #
#    Updated: 2023/12/20 16:06:55 by rvan-mee         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

OBJ_DIR = obj/
SRC_DIR = src/
INC_DIR = include/

SRCS = mem/ft_bzero.c				mem/ft_calloc.c				mem/ft_free_mult.c			mem/ft_memchr.c\
	   mem/ft_memcmp.c				mem/ft_memcpy.c				mem/ft_memmove.c			mem/ft_memset.c\
	   mem/ft_realloc.c\
	   str/ft_split.c				str/ft_strchr.c				str/ft_striteri.c			str/ft_strlcat.c\
	   str/ft_strlen.c				str/ft_strmod.c				str/ft_strnstr.c			str/ft_strtrim.c\
	   str/ft_split_map.c			str/ft_strdup.c				str/ft_strjoin.c			str/ft_strlcpy.c\
	   str/ft_strmapi.c				str/ft_strncmp.c			str/ft_strrchr.c			str/ft_substr.c\
	   str/strcontains.c\
	   arr/dynarr_create.c			arr/dynarr_delete.c			arr/dynarr_finalize.c		arr/dynarr_grow.c\
	   arr/dynarr_foreach.c			arr/dynarr_add.c			arr/dynarr_get.c			arr/dynarr_set.c\
	   arr/dynarr_pop.c\
	   lst/ft_lstadd_back.c			lst/ft_lstclear.c			lst/ft_lstdelone.c			lst/ft_lstlast.c\
	   lst/ft_lstnew.c				lst/ft_lstadd_front.c		lst/ft_lstdelelem.c			lst/ft_lstiter.c\
	   lst/ft_lstmap.c				lst/ft_lstsize.c\
	   put/ft_putchar_fd.c			put/ft_putendl_fd.c			put/ft_putnbr_fd.c			put/ft_putstr_fd.c\
	   ascii/ft_isalnum.c			ascii/ft_isalpha.c			ascii/ft_isascii.c			ascii/ft_isdigit.c\
	   ascii/ft_isprint.c			ascii/ft_isspace.c			ascii/ft_tolower.c			ascii/ft_toupper.c\
	   conversion/ft_atoi.c			conversion/ft_hextoui.c		conversion/ft_itoa.c		conversion/ft_strtof.c\
	   math/ft_interpolate.c		math/ft_simple_math.c\
	   printf/ft_printf.c			printf/nbr_to_str_utils.c	printf/parse_flags.c		printf/parse_options.c\
	   printf/printf_printchar.c	printf/printf_printhex.c	printf/printf_printnbr.c	printf/printf_printstr.c\
	   printf/printf_utils.c\
	   gnl/get_next_line.c			gnl/get_next_line_utils.c\
	   binary_search.c\
	   sort/quicksort.c				sort/squicksort.c			sort/insertion_sort.c

HEADERS = include/libft.h			\
		  include/get_next_line.h	\
 		  include/ft_printf.h		include/ft_printf_internal.h	\
 		  include/dynarr.h			include/sort.h

OBJS = $(SRCS:.c=.o)
OBJS_PREFIXED = $(addprefix $(OBJ_DIR), $(OBJS))

CC = gcc
CFLAGS = -Wall -Werror -Wextra -Wno-unused-result  $(OFLAGS)
ifdef DEBUG
	CFLAGS += -g
endif

ifeq ($(shell uname -s), Darwin)
	AR=ar
else
	AR=gcc-ar
endif

all: $(NAME)

$(NAME): $(OBJS_PREFIXED)
	@$(AR) rc $(NAME) $?
	@echo "Done creating archive $(NAME)"

$(OBJS_PREFIXED): $(OBJ_DIR)%.o: $(SRC_DIR)%.c $(HEADERS)
	@mkdir -p $(@D)
	@echo "Compiling: $<"
	@$(CC) $(CFLAGS) -I $(INC_DIR) -c -o $@ $<

clean:
	@rm -rf $(OBJ_DIR)
	@echo "Done cleaning $(CURDIR)/$(OBJ_DIR)"

fclean: clean
	@rm -f $(NAME)
	@echo "Done cleaning archive $(CURDIR)/$(NAME)"

re: fclean
	@$(MAKE)

.PHONY: all clean fclean re

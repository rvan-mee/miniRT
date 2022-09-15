INCLUDE="-I../include -I../lib/libft/include -I../lib/MLX42/include"
LIBS="./miniRT_test.a ../lib/libft/libft.a"
LINK_FLAGS="-lm"

gcc ./parse/main.c $INCLUDE $LIBS $LINK_FLAGS -o ./parse_test
INCLUDE="-I../include -I../lib/libft/include -I../lib/MLX42/include"
LIBS="./miniRT_test.a ../lib/libft/libft.a"


gcc ./parse/main.c $INCLUDE $LIBS -o ./parse_test
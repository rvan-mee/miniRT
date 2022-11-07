CFLAGS="-march=native -O3"
INCLUDE="-I../include -I../lib/libft/include -I../lib/MLX42/include"
LIBS="./miniRT_test.a ../lib/libft/libft.a"
LINK="-lm"

gcc costs/main.c $INCLUDE $CFLAGS $LIBS $LINK -o ./cost.test
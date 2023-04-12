NUM_TESTS=100
NUM_VALUES=10000

exe="./test"
libft_dir="../.."
libft_a="$libft_dir/libft.a"

if [[ ! -f $exe ]]; then
   [[ -f $libft_a ]] || make -C $libft_dir || exit 1
   gcc main.c $libft_a "-I$libft_dir/include" -o $exe || exit 1
fi

orig="orig.txt"
out="out.txt"

seq $NUM_VALUES | sort -d > $orig

for ((i=$NUM_TESTS;i>0;i--)); do
   $exe $(< $orig sort -R) > $out
   diff -q $orig $out || exit 1
done

rm -f $orig $out $exe
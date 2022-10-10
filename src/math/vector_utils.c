#include <minirt.h>

int	compare_points(const t_fvec a, const t_fvec b, const uint8_t axis)
{
	uint8_t	ax;

	ax = axis;
	while (true)
	{
		if (a[ax] > b[ax])
			return (1);
		if (a[ax] < b[ax])
			return (-1);
		ax = (ax + 1) % 3;
		if (ax == axis)
			return (0);
	}
}

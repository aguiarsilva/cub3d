#include "cub3d.h"

void	ft_set_image_pixel(t_img_data *image, int x, int y, int color_val)
{
	int	pixel;

	pixel = y * (image->size_line / 4) + x;
	image->addr[pixel] = color_val;
}

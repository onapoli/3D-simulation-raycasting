/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_bmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onapoli- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 14:06:58 by onapoli-          #+#    #+#             */
/*   Updated: 2020/09/07 11:21:32 by onapoli-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "reader.h"

static void		free_headers_pixels(t_bmp_file_header *file_header,
t_bmp_info_header *info_header, unsigned char *pixels)
{
	if (file_header)
		free(file_header);
	if (info_header)
		free(info_header);
	if (pixels)
		free(pixels);
}

static int		write_file(t_bmp_file_header *file_header,
t_bmp_info_header *info_header, unsigned char *pixels, int image_size)
{
	int fd;

	if ((fd = open("rendered_image.bmp", O_RDWR | O_CREAT, 0666)) == -1)
		return (-1);
	write(fd, &file_header->signature, 2);
	write(fd, &file_header->file_size, 4);
	write(fd, &file_header->reserved_1, 2);
	write(fd, &file_header->reserved_2, 2);
	write(fd, &file_header->offset, 4);
	write(fd, &info_header->info_header_size, 4);
	write(fd, &info_header->image_width, 4);
	write(fd, &info_header->image_height, 4);
	write(fd, &info_header->color_planes, 2);
	write(fd, &info_header->bpp, 2);
	write(fd, &info_header->compression, 4);
	write(fd, &info_header->image_size, 4);
	write(fd, &info_header->x_pixels_per_meter, 4);
	write(fd, &info_header->y_pixels_per_meter, 4);
	write(fd, &info_header->colors_used, 4);
	write(fd, &info_header->important_colors, 4);
	write(fd, pixels, image_size);
	free_headers_pixels(file_header, info_header, pixels);
	close(fd);
	return (0);
}

static int		create_bmp_pixels(unsigned char *pixels, char *image_data,
int width, int height)
{
	int	i;
	int	j;
	int	p;

	j = 0;
	while (j < height)
	{
		i = 0;
		while (i < width)
		{
			p = (j * width + i) * 4;
			pixels[p + 0] = image_data[p + 0];
			pixels[p + 1] = image_data[p + 1];
			pixels[p + 2] = image_data[p + 2];
			pixels[p + 3] = image_data[p + 3];
			i++;
		}
		j++;
	}
	return (0);
}

static void		add_rest_info_values(t_bmp_info_header *bmp_info_header,
int img_bpp, int size)
{
	bmp_info_header->color_planes = 1;
	bmp_info_header->bpp = img_bpp;
	bmp_info_header->compression = 0;
	bmp_info_header->image_size = size;
	bmp_info_header->x_pixels_per_meter = 0;
	bmp_info_header->y_pixels_per_meter = 0;
	bmp_info_header->colors_used = 0;
	bmp_info_header->important_colors = 0;
}

int				create_bmp(int img_width, int img_height, int img_bpp,
char *img_data)
{
	t_bmp_file_header	*bmp_file_header;
	t_bmp_info_header	*bmp_info_header;
	unsigned char		*pixels;
	int					size;

	size = img_width * img_height * 4;
	if (!(bmp_file_header = malloc(sizeof(t_bmp_file_header))))
		return (-1);
	bmp_file_header->signature = 0x4D42;
	bmp_file_header->file_size = 54 + size;
	bmp_file_header->reserved_1 = 0;
	bmp_file_header->reserved_2 = 0;
	bmp_file_header->offset = 54;
	if (!(bmp_info_header = malloc(sizeof(t_bmp_info_header))))
		return (-1);
	bmp_info_header->info_header_size = 40;
	bmp_info_header->image_width = img_width;
	bmp_info_header->image_height = img_height * (-1);
	add_rest_info_values(bmp_info_header, img_bpp, size);
	if (!(pixels = malloc(sizeof(unsigned char) * size)))
		return (-1);
	create_bmp_pixels(pixels, img_data, img_width, img_height);
	write_file(bmp_file_header, bmp_info_header, pixels, size);
	return (0);
}

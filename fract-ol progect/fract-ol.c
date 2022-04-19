/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fract-ol.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mskerba <mskerba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 08:22:02 by mskerba           #+#    #+#             */
/*   Updated: 2022/04/19 05:47:40 by mskerba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract-ol.h"

void my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char *dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void puissance(t_equ *z, double x, double y)
{
	z->a = (z->a * z->a) - (z->b * z->b) + x;
	z->b = (2 * z->a * z->b) + y;
}

int mandelbrot_calcule(double x, double y, double iter)
{
	double a;
	double b;
	double aa;

	a = 0;
	b = 0;
	int i = 0;
	while (i < iter && ((a * a) + (b * b)) < 4)
	{
		aa = ((a * a) - (b * b)) + x;
		b = (2 * a * b) + y;
		a = aa;
		i++;
	}
	return (i);
}

int julia_calcule(double x, double y, double iter, t_data *img)
{
	double a;
	double b;
	double aa;

	a = x;
	b = y;
	int i = 0;
	while (i < iter && ((a * a) + (b * b)) < 4)
	{
		aa = ((a * a) - (b * b)) + img->julia_x;
		b = (2 * a * b) - img->julia_y;
		a = aa;
		i++;
	}
	return (i);
}

void mandelbrot(t_data *img)
{
	int j;
	int x = 0;
	int y = 0;

	for (x = 0; x < 1000; x++)
	{
		for (y = 0; y < 1000; y++)
			my_mlx_pixel_put(img, x, y, 0x00000000);
	}
	for (x = 0; x < 1000; x++)
	{
		int color;
		color = 0x00000000;
		for (y = 0; y < 1000; y++)
		{
			j = mandelbrot_calcule((x * img->k) + img->real, img->imagin - (y * img->k), img->iter);
			if (j == img->iter)
				my_mlx_pixel_put(img, x, y, color);
			else if (j >img->iter - 10)
				my_mlx_pixel_put(img, x, y, color + 200);
			else if (j >img->iter - 20)
				my_mlx_pixel_put(img, x, y, color + 400);
			else if (j >img->iter - 30)
				my_mlx_pixel_put(img, x, y, color + 600);
			else if (j >img->iter - 40)
				my_mlx_pixel_put(img, x, y, color + 800);
			else if (j >img->iter - 50)
				my_mlx_pixel_put(img, x, y, color + 900);
			else if (j >img->iter - 60)
				my_mlx_pixel_put(img, x, y, color + 1100);
			else if (j > 0)
				my_mlx_pixel_put(img, x, y, color + 1000);
		}
	}
	mlx_put_image_to_window(img->mlx, img->win, img->img, 0, 0);
}

void julia(t_data *img)
{
	int j;
	int x = 0;
	int y = 0;

	for (x = 0; x < 1000; x++)
	{
		for (y = 0; y < 1000; y++)
			my_mlx_pixel_put(img, x, y, 0x00000000);
	}
	for (x = 0; x < 1000; x++)
	{
		for (y = 0; y < 1000; y++)
		{
			j = julia_calcule((x * img->k) + img->real, img->imagin - (y * img->k), img->iter, img);
			if (j == img->iter)
				my_mlx_pixel_put(img, x, y, 0x00ffff00);
		}
	}
	mlx_put_image_to_window(img->mlx, img->win, img->img, 0, 0);
}

int mouse(int keycode, int a, int b, t_data *img)
{
	if (keycode == 4)
	{
		img->k /= 2;
		img->real += (a * img->k);
		img->imagin -= (b * img->k);
		img->iter += 10;
	}
	else if (keycode == 5)
	{
		img->real -= (a * img->k);
		img->imagin += (b * img->k);
		img->k *= 2;
		img->iter -= 10;
	}
	if (img->key_num == 0)
		julia(img);
	else
		mandelbrot(img);
	return (0);
}

int ft_strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1[i] != '\0' && s2[i] == s1[i])
	{
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

void help()
{
	exit(1);
}

void julia_type(t_data *img, int n)
{
	if (n == 1)
	{
		img->julia_x = -0.4;
		img->julia_y = 0.6;
	}
	else if (n == 2)
	{
		img->julia_x = 0.285;
		img->julia_y = 0;
	}
	else if (n == 3)
	{
		img->julia_x = 0.285;
		img->julia_y = 0.01;
	}
	else if (n == 4)
	{
		img->julia_x = 0.45;
		img->julia_y = 0.1428;
	}
	else if (n == 5)
	{
		img->julia_x = -0.70176;
		img->julia_y = -0.3842;
	}
	else if (n == 6)
	{
		img->julia_x = -0.835;
		img->julia_y = -0.2321;
	}
	else if (n == 7)
	{
		img->julia_x = -0.8;
		img->julia_y = 0.156;
	}
	else if (n == 8)
	{
		img->julia_x = -0.7269;
		img->julia_y = 0.1889;
	}
	else if (n == 9)
	{
		img->julia_x = 0;
		img->julia_y = -0.8;
	}
	else if (n == 0)
	{
		img->julia_x = 1 - (1 + sqrt(5)) / 2;
		img->julia_y = 0;
	}
	julia(img);
}

int keabord(int keycode, t_data *img)
{
	if (keycode == 69)
		img->iter += 10;
	else if (keycode == 123)
		img->real += 0.1;
	else if (keycode == 124)
		img->real -= 0.1;
	else if (keycode == 126)
		img->imagin -= 0.1;
	else if (keycode == 125)
		img->imagin += 0.1;
	else if (keycode == 50)
	{
		img->key_num = 1;
		mandelbrot(img);
	}
	if (keycode == 53)
	{
		img->key_num = 0;
		mlx_clear_window(img->mlx, img->win);
		exit(1);
	}
	else if (keycode == 78)
		img->iter -= 10;
	else if (keycode == 18)
	{
		img->key_num = 0;
		julia_type(img, 1);
	}
	else if (keycode == 19)
	{
		img->key_num = 0;
		julia_type(img, 2);
	}
	else if (keycode == 20)
	{
		img->key_num = 0;
		julia_type(img, 3);
	}
	else if (keycode == 21)
	{
		img->key_num = 0;
		julia_type(img, 4);
	}
	else if (keycode == 23)
	{
		img->key_num = 0;
		julia_type(img, 5);
	}
	else if (keycode == 22)
	{
		img->key_num = 0;
		julia_type(img, 6);
	}
	else if (keycode == 26)
	{
		img->key_num = 0;
		julia_type(img, 7);
	}
	else if (keycode == 28)
	{
		img->key_num = 0;
		julia_type(img, 8);
	}
	else if (keycode == 25)
	{
		img->key_num = 0;
		julia_type(img, 9);
	}
	else if (keycode == 29)
	{
		img->key_num = 0;
		julia_type(img, 0);
	}
	if (img->key_num == 0)
		julia(img);
	else
		mandelbrot(img);
	// printf("%d\n", keycode);
	// printf("%f   %f\n",img->imagin,img->real);
	return (0);
}

int exit_now(t_data *img)
{
	mlx_destroy_image(img->mlx, img->img);
	mlx_destroy_window(img->mlx, img->win);
	exit(1);
	return (0);
}

int main(int c, char **v)
{
	t_data img;

	(void)c;
	img.real = -2;
	img.imagin = 2;
	img.k = 0.004;
	img.iter = 60;
	img.mlx = mlx_init();
	img.win = mlx_new_window(img.mlx, 1000, 1000, "Fract-ol");
	img.img = mlx_new_image(img.mlx, 1000, 1000);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	if (c == 1 || c > 3)
		help();
	else if (!ft_strcmp(v[1], "julia") && c == 3)
	{
		img.key_num = 0;
		julia_type(&img, ft_atoi(v[2]));
	}
	else if (!ft_strcmp(v[1], "julia"))
	{
		img.key_num = 0;
		julia_type(&img, 0);
	}
	else if (!ft_strcmp(v[1], "mandelbrot"))
	{
		img.key_num = 1;
		mandelbrot(&img);
	}
	else
		help();
	mlx_hook(img.win, 4, 0L, mouse, &img);
	mlx_hook(img.win, 2, 0L, keabord, &img);
	mlx_hook(img.win, 17, 0L, exit_now, &img);
	mlx_loop(img.mlx);
}
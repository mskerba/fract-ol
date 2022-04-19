/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fract-ol.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mskerba <mskerba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 08:18:59 by mskerba           #+#    #+#             */
/*   Updated: 2022/04/18 11:12:37 by mskerba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACT_OL_H
# define FRACT_OL_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <mlx.h>
# include <math.h>

typedef struct s_data
{
	void *img;
	void *win;
	int l;
	void *mlx;
	double k;
	int key_num;
	double julia_x;
	double julia_y;
	double iter;
	double real;
	double iter_key;
	double imagin;
	char *addr;
	int bits_per_pixel;
	int line_length;
	int endian;
} t_data;

typedef struct s_equ
{
	double a;
	double b;
} t_equ;

void my_mlx_pixel_put(t_data *data, int x, int y, int color);
int	ft_atoi(const char	*str);
void puissance(t_equ *z, double x, double y);
int mandelbrot_calcule(double x, double y, double iter);
int julia_calcule(double x, double y, double iter, t_data *img);
void mandelbrot(t_data *img);
void julia(t_data *img);
int mouse(int keycode, int a, int b, t_data *img);
int ft_strcmp(char *s1, char *s2);
void help();
void julia_type(t_data *img, int n);
int keabord(int keycode, t_data *img);
#endif
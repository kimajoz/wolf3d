/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   w_cast_rays.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbillett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/06 21:05:19 by pbillett          #+#    #+#             */
/*   Updated: 2017/07/21 16:01:01 by pbillett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int				getcolor(t_img *img, int x, int y)
{
	int			color;
	int			c;

	/*if (w->w.sprnumb)
	{
		ft_putendl("start getcolor spr");
		ft_putstr("sizeline");
		ft_putnbr(img->size_line);
		ft_putchar('\n');
		printf("sizeline: %d\n", img->size_line);
		//printf("sizeline: %d, bpp:%d\n", img->size_line, img->bpp);
	}*/
	c = y * img->size_line + (x * (img->bpp / 8));
	color = img->pxl_ptr[c];
	if (color == -120 && img->pxl_ptr[c + 1] == 0 && img->pxl_ptr[c + 2] == -104)
		return (256 * 256 * 256 + 256 * 256 + 256);
	color += img->pxl_ptr[c + 1] * 256;
	color += img->pxl_ptr[c + 2] * 256 * 256;
	return (color);
}

void		ft_int_to_rgb(t_wind *w, int x, int y, int color)
{
	char	b;
	char	g;
	char	r;
	int		i;

	if (color == 256 * 256 * 256 + 256 * 256 + 256)
		return ;
	i = ((w->img.size_line * y) + (x * (w->img.bpp / 8)));
	b = color % 256;
	g = (color / 256) % 256;
	r = (color / 256 / 256) % 256;
	printf("r:%d, g:%d, b:%d, i:%d\n", r, g, b, i);
}

void				w_draw_the_wall(t_wind *w, int i)
{
	double			projsliceh;
	t_point			p;
	t_point			pd;
	int				y;
	int				h;
	int				col;

	projsliceh = (CUBESIZE * FOV) / w->w.dist;
	p = (t_point){(i * w->w.slicew), (w->height / 2) - (projsliceh / 2), 0};
	pd = (t_point){p.x, p.y + projsliceh, 0};
	p.x += w->w.marginw;
	pd.x += w->w.marginw;
	if (w->w.info.texture)
	{
		h = 0;
		y = p.y;
		while(y < pd.y)
		{
			h++;
			w->w.texY = (TEXHEIGHT / projsliceh) * h;
			if (w->w.sprnumb)
			{
				//ft_putendl("sprnumb before");
				//printf("sprnumb: %d\n", w->w.sprnumb);
				//col = mlx_get_color_value(w->mlx, w->w.sprite[w->w.sprnumb - 1]);
				col = getcolor(&w->w.sprite[w->w.sprnumb - 1], w->w.texX, w->w.texY);
				//ft_putendl("sprnumb after");
			}
			else
				col = getcolor(&w->w.text[w->w.textnumb], w->w.texX, w->w.texY);

			if (mlibx_dot_in_window(w, rint(p.x), y))
				mlibx_draw_dot(w, (int)p.x, y, col);
			y++;
		}
	}
	else
		mlibx_draw_pixel_line_int(p, pd, w, w->w.color);
}

void			w_verticales_lines_check(t_wind *w, double ray_angle,
		double right)
{
	t_dpoint	d;
	t_dpoint	p;
	t_dpoint	wall;
	t_dpoint	dist;

	w->w.slope = sin(ray_angle) / cos(ray_angle);
	d.x = right ? 1 : -1;
	d.y = (w->w.slope < 360) ? d.x * w->w.slope : 0;
	p.x = right ? ceil(w->cam.pos.x) : floor(w->cam.pos.x);
	p.y = (w->cam.pos.z) + (p.x - w->cam.pos.x) * w->w.slope;
	while (p.x >= 0 && p.x < w->b.nbr_elem_line[0] && p.y >= 0 && p.y < w->b.nbrtot_of_line)
	{
		wall = (t_dpoint){floor(p.x + (right ? 0 : -1)), floor(p.y), 0};
		if (wall.x < 0 || wall.y < 0)
			break ;
		if ((w->w.tab_int_spr[(int)wall.y][(int)wall.x] > 0) || (w->b.tab_int[(int)wall.y][(int)wall.x] > 0))
		{
			dist = (t_dpoint){(p.x * MMS) - (w->cam.pos.x * MMS), (p.y * MMS) - (w->cam.pos.z * MMS), 0};
			w->w.dist = sqrt(pow(dist.x, 2) + pow(dist.y, 2));
			w->w.hit = p;
			w->w.texX = fmod(p.y, 1) * TEXWIDTH; // keep the float number after coma.
			if (!right) w->w.texX = TEXWIDTH - w->w.texX; // if we're looking to the left side of the map, the texture should be reversed
			w->w.textnumb = w->b.tab_int[(int)wall.y][(int)wall.x] - 1;
			w->w.sprnumb = w->w.tab_int_spr[(int)wall.y][(int)wall.x];
			w->w.color = (p.x < w->cam.pos.x) ? IC_FGREEN : IC_FBLUE;
			w->w.side = 1; // Verticales lines
			break ;
		}
		p.x += d.x;
		p.y += d.y;
	}
}

void			w_horizontales_lines_check(t_wind *w, double ray_angle,
		double up)
{
	t_dpoint	d;
	t_dpoint	p;
	t_dpoint	wall;
	t_dpoint	dist;

	w->w.slope = cos(ray_angle) / sin(ray_angle);
	d.y = up ? -1 : 1;
	d.x = (w->w.slope < 360) ? (d.y * w->w.slope) : 0;
	p.y = up ? floor(w->cam.pos.z) : ceil(w->cam.pos.z);
	p.x = w->cam.pos.x + (p.y - w->cam.pos.z) * w->w.slope;
	while (p.x >= 0 && p.x < w->b.nbr_elem_line[0] && p.y >= 0 && p.y < w->b.nbrtot_of_line)
	{
		wall = (t_dpoint){floor(p.x), floor(p.y + (up ? -1 : 0)), 0};
		if (wall.x < 0 || wall.y < 0)
			break ;
		if ((w->w.tab_int_spr[(int)wall.y][(int)wall.x] > 0) || (w->b.tab_int[(int)wall.y][(int)wall.x] > 0))
		{
			dist = (t_dpoint){(p.x * MMS) - (w->cam.pos.x * MMS), (p.y * MMS) - (w->cam.pos.z * MMS), 0};
			w->w.block_dist = sqrt(pow(dist.x, 2) + pow(dist.y, 2));
			if (!w->w.dist || w->w.block_dist < w->w.dist)
			{
				w->w.dist = w->w.block_dist;
				w->w.hit = p;
				w->w.texX = fmod(p.x, 1) * TEXWIDTH; // keep the float number after coma.
				if (!up) w->w.texX = TEXWIDTH - w->w.texX; // if we're looking to the left side of the map, the texture should be reversed
				w->w.textnumb = w->b.tab_int[(int)wall.y][(int)wall.x] - 1;
				w->w.sprnumb = w->w.tab_int_spr[(int)wall.y][(int)wall.x];
				w->w.color = p.y < w->cam.pos.z ? IC_FYELLOW : IC_FPURPLE;
				w->w.side = 0; // Horizontales lines
				break ;
			}
		}
		p.x += d.x;
		p.y += d.y;
	}
}

void			w_cast_single_ray(t_wind *w, double ray_angle, int raynumb)
{
	double		right;
	double		up;

	w->w.dist = 0;
	w->w.hit = (t_dpoint){0, 0, 0};
	ray_angle = ft_degreetorad(ray_angle);
	ray_angle = fmod(ray_angle, TWOPI);
	right = (ray_angle > TWOPI * 0.75 || ray_angle < TWOPI * 0.25);
	up = (ray_angle < 0 || ray_angle > M_PI);
	w_verticales_lines_check(w, ray_angle, right);
	w_horizontales_lines_check(w, ray_angle, up);
	if (w->w.dist)
	{
		if (w->w.info.ray_minimap)
			w_print_radar_ray_hitwall(w, w->w.hit.x, w->w.hit.y, "0x00FF00");
		w->w.dist = w->w.dist * cos(ft_degreetorad(w->w.correct_fisheyes));
		w_draw_the_wall(w, raynumb);
	}
}

void			w_cast_rays(t_wind *w)
{
	int			i;
	double		angle;

	w->cam.vp.dist = (w->cam.vp.w / 2) / tan(ft_degreetorad(FOV / 2));
	w->cam.anglebetrays = (double)FOV / (double)w->w.info.raynumb;
	w->w.slicew = w->cam.vp.w / w->w.info.raynumb;
	angle = w->cam.rot.y - (FOV / 2);
	w->w.correct_fisheyes = FOV / 2;
	i = 0;
	while (i < w->w.info.raynumb)
	{
		w->w.correct_fisheyes -= w->cam.anglebetrays;
		w_cast_single_ray(w, angle, i);
		angle += w->cam.anglebetrays;
		i++;
	}
}

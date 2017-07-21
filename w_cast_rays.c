/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   w_cast_rays.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbillett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/06 21:05:19 by pbillett          #+#    #+#             */
/*   Updated: 2017/07/06 23:17:33 by pbillett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

#define MARGINW 200

void			w_draw_the_wall(t_wind *w, int i)
{
	double		projsliceh;
	t_point		p;
	t_point		pd;
	int			y;
	int			d;
	//t_rgbcolor	color;
	int			*col;
	char		hex[9];
	char		*colhexa;

	// http://lodev.org/cgtutor/raycasting.html

	// Standard filling
	projsliceh = (CUBESIZE * FOV) / w->w.dist;
	p = (t_point){(i * w->w.slicew), (w->height / 2) - (projsliceh / 2), 0};
	pd = (t_point){p.x, p.y + projsliceh, 0};
	p.x += MARGINW;
	pd.x += MARGINW;
	w->w.lineheight = w->height / w->w.dist;
	//printf("rayon: %d\n", i);
	//printf("p.x: %d, p.y: %d, pd.y: %d\n", p.x, p.y, pd.y);
	
	if (w->w.info.texture)
	{
		y = p.y;
		while(y < pd.y)
		{
			d = y * 256 - w->height * 128 + w->w.lineheight * 128;  //256 and 128 factors to avoid floats
			w->w.texY = ((d * texHeight) / w->w.lineheight) / 256;
			//w->w.color = w->w.text[w->w.textnumb][w->w.texY][w->w.texX];

			printf("y: %d\n", y);
			printf("texX: %d\n", w->w.texX);
			printf("texY: %d\n", w->w.texY);
			printf("w->w.textw: %d\n", w->w.textw);
			printf("w->w.texth: %d\n", w->w.texth);
			printf("bpp/8: %d\n",  w->w.bpp[w->w.textnumb]/8);
			printf("w->w.sline %d\n", w->w.sline[w->w.textnumb]);
			printf("w->w.textnumb %d\n", w->w.textnumb);
			//printf("texY * texth: %d\n", (w->w.texY * w->w.texth));
			printf("texX * bpp/8: %d\n",  (w->w.texX * (w->w.bpp[w->w.textnumb]/8)));
			col = (w->w.text[w->w.textnumb] + (w->w.texY * w->w.sline[w->w.textnumb]) + (w->w.texX * (w->w.bpp[w->w.textnumb])));
			printf("color%d\n", (int)col);
			printf("color hex:\n");
			sprintf(hex, "%x", *col);
			//w->w.color = ft_inttohex_comp(col);
			//puts(w->w.color);
			//printf("colorhexa%s\n", hex);
			colhexa = ft_strnew(10);
			colhexa[0] = '0';
			colhexa[1] = 'x';
			ft_strcpy(&colhexa[2], hex);
			//printf("colorhexa mod%s\n", colhexa);
			//color.g = (int)(w->w.text[w->w.textnumb] + (w->w.texY * w->w.texth) + (w->w.texX * (w->w.bpp[w->w.textnumb]/8)) + 1);
			//color.b = (int)(w->w.text[w->w.textnumb] + (w->w.texY * w->w.texth) + (w->w.texX * (w->w.bpp[w->w.textnumb]/8)) + 2);
			//printf("color.r:%d, g:%d, b:%d\n", color.r, color.g, color.b);
			/*color.g = *(w->w.text[w->w.textnumb] + (w->w.texY * w->w.texth) + (w->w.texX * (w->w.bpp/8)) + 1);
			color.b = *(w->w.text[w->w.textnumb] + (w->w.texY * w->w.texth) + (w->w.texX * (w->w.bpp/8)) + 2);*/
			mlibx_draw_pixel(w, (int)p.x, y, colhexa);
			//make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
			//if(side == 1) color = (color >> 1) & 8355711;
				//buffer[y][x] = color;
			y++;
		}
	}
	else
		mlibx_draw_pixel_line(p, pd, w, w->w.color);
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
	while (p.x >= 0 && p.x < MAPLEN && p.y >= 0 && p.y < MAPLEN)
	{
		wall = (t_dpoint){floor(p.x + (right ? 0 : -1)), floor(p.y), 0};
		if (wall.x < 0 || wall.y < 0)
			break ;
		if (w->b.tab_int[(int)wall.y][(int)wall.x] > 0)
		{
			dist = (t_dpoint){(p.x * MMS) - (w->cam.pos.x * MMS), (p.y * MMS) - (w->cam.pos.z * MMS), 0};
			w->w.dist = sqrt(pow(dist.x, 2) + pow(dist.y, 2));
			w->w.hit = p;
			w->w.dir = d; //for textures
			w->w.textnumb = w->b.tab_int[(int)wall.y][(int)wall.x] - 1;
			w->w.color = (p.x < w->cam.pos.x) ? "0x00FF00" : "0x0000FF";
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
	while (p.x >= 0 && p.x < MAPLEN && p.y >= 0 && p.y < MAPLEN)
	{
		wall = (t_dpoint){floor(p.x), floor(p.y + (up ? -1 : 0)), 0};
		if (wall.x < 0 || wall.y < 0)
			break ;
		if (w->b.tab_int[(int)wall.y][(int)wall.x] > 0)
		{
			dist = (t_dpoint){(p.x * MMS) - (w->cam.pos.x * MMS), (p.y * MMS) - (w->cam.pos.z * MMS), 0};
			w->w.block_dist = sqrt(pow(dist.x, 2) + pow(dist.y, 2));
			if (!w->w.dist || w->w.block_dist < w->w.dist)
			{
				w->w.dist = w->w.block_dist;
				w->w.hit = p;
				w->w.dir = d; //for textures
				w->w.textnumb = w->b.tab_int[(int)wall.y][(int)wall.x] - 1;
				w->w.color = p.y < w->cam.pos.z ? "0xFFFF00" : "0xFF00FF";
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
	double		wallX;

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
		
		//ft_putstr("test\n");
		w->w.dist = w->w.dist * cos(ft_degreetorad(w->w.correct_fisheyes));
		//where exactly the wall was hit
		if (w->w.side == 0)
			wallX = w->w.hit.y + w->w.dist * w->w.dir.y;
		else
			wallX = w->w.hit.x + w->w.dist * w->w.dir.x;
		wallX -= floor((wallX));

		printf("wallX: %.3f\n", wallX);
		printf("w->w.textw: %d\n", w->w.textw);
		//x coordinate on the texture
		w->w.texX = (int)(wallX * (double)w->w.textw);
		printf("w->w.texX: %d\n", w->w.texX);
		//if((w->w.side == 0 && w->w.dir.x > 0) || (w->w.side == 1 && w->w.dir.y < 0))
			//w->w.texX = w->w.textw - w->w.texX - 1;
		printf("w->w.texX after: %d\n", w->w.texX);


		w_draw_the_wall(w, raynumb);
	}
	//printf("fin single ray\n");
}

void			w_cast_rays(t_wind *w)
{
	int			i;
	double		angle;

	w->cam.vp.dist = (w->cam.vp.w / 2) / tan(ft_degreetorad(FOV / 2));
	w->cam.anglebetrays = (double)FOV / (double)w->w.info.raynumb;
	w->w.slicew = w->cam.vp.w / w->w.info.raynumb;
	//printf("slicew:  %.3f\n", w->w.slicew);
	//printf("vp.dist:  %.3f\n", w->cam.vp.dist);
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
	//printf("fin cast ray\n");
}

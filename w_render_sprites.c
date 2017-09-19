#include "wolf3d.h"

void		w_clear_vis_sprites(t_wind *w)
{
	int		y;
	int		x;

	y = 0;
	while (y < w->b.nbrtot_of_line)
	{
		//w->w.tab_int_spr[y] = malloc(w->b.nbr_elem_line[3] * sizeof(t_sprite));
		x = 0;
		while (x < w->b.nbr_elem_line[3])
			w->w.tab_int_spr[y][x++].vis = 0;
		y++;
	}
}

void		w_set_pxl_spr(int bx, int by, int size, t_wind *w)
{
	int		x;
	int		y;
	double	percx;
	double	percy;

	y = 0;
	while ((by + y) < (by + size))
	{
		//x = w->w.xtextp;
		x = 0;
		while ((bx + x) < (bx + size))
		{
			// We set color due to pos on spr texture
			//ft_putstr("i");
			//printf("w->w.sprnumb: %d\n", w->w.sprnumb);
			percx = (double)x / (double)size;
			percy = (double)y / (double)size;
			//printf("sprite perc x: %.3f, y: %.3f, valuex: %d, valuey: %d\n", percx, percy, (int)(percx * 64), (int)(percy * 64));
			//We get color for each pixel
			w->w.color = getcolor(&w->w.sprite[w->w.sprnumb - 1].img, percx * 64, percy * 64);
			// We set color in img to show on screen
			if (mlibx_dot_in_window(w, bx + x, by + y) && w->w.color != 0)
			{
				//mlibx_draw_dot(w, bx + x, by + y, w->w.color);
				if (w->w.dist < w->screen[by + y][bx + x].zdepth && !ft_fiszero(w->w.dist))
				{
					w->screen[by + y][bx + x].zdepth = w->w.dist;
					w->screen[by + y][bx + x].color = w->w.color;
				}
			}
			x++;
		}
		y++;
	}
}

void			w_calc_render_spr(t_wind *w)
{
	double		sprite_angle;
	int			size;
	//double		xtextp;
	//double		s_xleft; // pos x text on screen
	double		s_ytop; // pos x text on screen

	// http://permadi.com/1996/05/ray-casting-tutorial-5/
	// https://dev.opera.com/articles/3d-games-with-canvas-and-raycasting-part-2/
	printf("Sprites:\n");
	printf("w->w.memdistspr.x: %.3f, w->w.memdistspr.y: %.3f\n",  w->w.memdistspr.x,  w->w.memdistspr.y);
	printf("rot player in radian %.3f\n", ft_degreetorad(w->cam.rot.y));
	sprite_angle = atan2(w->w.memdistspr.y, w->w.memdistspr.x) - ft_degreetorad(w->cam.rot.y);
	printf("sprite_angle %.3f\n", sprite_angle);
	printf("sprite_angle degree %.3f\n", ft_radtodegree(sprite_angle));
	size = w->cam.vp.dist / (cos(sprite_angle) * w->w.block_distsprreal);
	printf("w->cam.vp.dist %.3f\n", w->cam.vp.dist);
	printf("w->w.block_distsprreal %.3f\n", w->w.block_distsprreal);
	// Define X pos of text on the screen
	w->w.xtextp = tan(sprite_angle) * w->cam.vp.dist;
	printf("xtextp %.3f\n", w->w.xtextp);
	w->w.s_xleft = ((w->width) / 2) + w->w.xtextp - (size / 2);
	//s_xleft = ((w->width - w->w.marginw) / 2) + xtextp - (size / 2) + w->w.marginw;
	// Define Y pos of text on the screen
	s_ytop = (w->height - size) / 2;
	printf("textx: %.3f, texty: %.3f size: %d\n", w->w.s_xleft, s_ytop, size);
	w_set_pxl_spr(w->w.s_xleft, s_ytop, size, w);
}

void		w_render_sprites(t_wind *w)
{
	int		y;
	int		x;

	y = 0;
	//printf("-----------------------------------------------\n");
	while (y < w->b.nbrtot_of_line)
	{
		x = 0;
		while (x < w->b.nbr_elem_line[3])
		{
			//printf("%d", w->w.tab_int_spr[y][x].vis);
			//printf("%d", w->w.tab_int_spr[y][x].num);
			if (w->w.tab_int_spr[y][x].vis == 1)
				w_calc_render_spr(w);
			x++;
		}
		//printf("\n");
		y++;
	}

}

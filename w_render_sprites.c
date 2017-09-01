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
/*
void		w_clear_vis_sprites(t_wind *w)
{
	int		x;

	x = 0;
	while (x < w->w.sprnbvis)
	{
		w->w.spr_visible[x].vis = 0;
		x++;
	}
	free(w->w.spr_visible);
	w->w.sprnbvis = 0;
}*/

void		w_set_pxl_spr(int bx, int by, int size, t_wind *w)
{
	int		x;
	int		y;

	printf("sprite draw y start: %d, end: %d\n", by, (by + size));
	printf("sprite draw x start: %d, end: %d\n", bx, (bx + size));
	y = 0;
	while ((by + y) < (by + size))
	{
		x = 0;
		while ((bx + x) < (bx + size))
		{
			// We set color due to pos on spr texture
			//printf("w->w.sprnumb: %d\n", w->w.sprnumb);
			w->w.color = getcolor(&w->w.sprite[w->w.sprnumb - 1].img, x, y);
			// We set color in img to show on screen
			if (mlibx_dot_in_window(w, bx + x, by + y))
				mlibx_draw_dot(w, bx + x, by + y, w->w.color);
			x++;
		}
		y++;
	}
}

void			w_calc_render_spr(int z, int x, t_wind *w)
{
	t_dpoint	dist;
	double	sprite_angle;
	int		size;
	double	xtextp;
	double	s_xleft; // pos x text on screen
	double	s_ytop; // pos x text on screen
	//double	dbx;
	//double	dbz;
	//double	distaftrot;
	//double	zindex;

	printf("render spr posx: %d, posz: %d\n", x, z);
	// Translate position to viewer sprite
	dist = (t_dpoint){((x + 0.5) * MMS) - (w->cam.pos.x * MMS), 0, ((z + 0.5) * MMS) - (w->cam.pos.z * MMS)};

	// Distance to sprite
	w->w.block_distspr = sqrt(pow(dist.x, 2) + pow(dist.z, 2));
	printf("dist to sprites: %.3f\n", w->w.block_distspr);

	if (!w->w.distspr || w->w.block_distspr < w->w.distspr)
	{
		printf("check dist viez spr: %.3f\n", w->w.distspr);
		w->w.distspr = w->w.block_distspr;
		// Sprite angle relative to viewing angle
		sprite_angle = atan2(dist.z, dist.x) - ft_degreetorad(w->cam.rot.y);
		printf("atan angle: %.3f\n",  atan2(dist.z, dist.x));
		printf("sprites angle: %.3f\n", sprite_angle);
		// Size of the sprite
		size = w->cam.vp.dist / (cos(sprite_angle) * w->w.distspr);
		printf("size sprites: %d\n", size);

		// Define X pos of text on the screen
		xtextp = tan(ft_degreetorad(sprite_angle)) * w->cam.vp.dist;
		printf("width/2: %d\n", (w->width / 2));
		printf("tan(ft_degreetorad(sprite_angle)) : %.3f\n", tan(ft_degreetorad(sprite_angle)));
		printf("w->cam.vp.dist: %.3f\n", w->cam.vp.dist);
		printf("xtextp: %.3f\n", xtextp);
		printf("size/2: %d\n", (size / 2));
		s_xleft = (w->width / 2) + xtextp - (size / 2);

		// Define Y pos of text on the screen
		// Y is constant since we keep sprites at the same height and vertical position
		s_ytop = (w->height - size) / 2;

		//Calculate zindex with real dist after rotation angle.(to keep plane always faces the player)
		//dbx = x - w->cam.pos.x;
		//dbz = z - w->cam.pos.z;
		//distaftrot = pow(dbx, 2) + pow(dbz, 2);
		//zindex = -floor(distaftrot * 1000);

		printf("render spr preend\n");
		printf("sprites textx: %.3f, texty: %.3f\n", s_xleft, s_ytop);

		w_set_pxl_spr(s_xleft, s_ytop, size, w);
		printf("render spr lastend\n");
	}
}
/*
   void		w_render_sprites(t_wind *w)
   {
   int		x;

   printf("-----------------------------------------------\n");
   x = 0;
   printf("nb sprites visibles: %d - ", w->w.sprnbvis);
   printf("sprites visibles: ");
   while (x < w->w.sprnbvis)
   {
   printf("%d", w->w.spr_visible[x].num);
//if (w->w.tab_int_spr[y][x].vis == 1)
//w_calc_render_spr(y, x, w);
x++;
}
printf("\n");
}*/

void		w_render_sprites(t_wind *w)
{
	int		y;
	int		x;

	y = 0;
	printf("-----------------------------------------------\n");
	while (y < w->b.nbrtot_of_line)
	{
		x = 0;
		while (x < w->b.nbr_elem_line[3])
		{
			//printf("%d", w->w.tab_int_spr[y][x].vis);
			printf("%d", w->w.tab_int_spr[y][x].num);
			/*if (w->w.tab_int_spr[y][x].vis == 1)
			 *				w_calc_render_spr(y, x, w);*/
			x++;
		}
		printf("\n");
		y++;
	}

}

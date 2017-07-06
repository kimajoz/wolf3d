
#include "wolf3d.h"

# define MARGINW 200

void			w_draw_the_wall(t_wind *w, int i, double ray_angle)
{
	double		projsliceh;
	t_point		p;
	t_point		pd;

	// https://dev.opera.com/articles/3d-games-with-canvas-and-raycasting-part-1/
	printf("ray_angle: %.3f\n", ray_angle);
	printf("ray_angle in degree: %.3f\n", ft_radtodegree(ray_angle));
	printf("dist before: %.3f\n", w->w.dist);
	// FISHEYES CORRECT DISTORTION distorted_dist = correct_dist / cos(relative_angle_of_ray)
	w->w.dist = w->w.dist * cos(ft_degreetorad(w->w.correct_fisheyes));
	printf("dist after: %.3f\n", w->w.dist);
	printf("w->cam.vp.h: %.3f\n", w->cam.vp.h);
	printf("w->cam.vp.dist: %.3f\n", w->cam.vp.dist);
	projsliceh = (CUBESIZE / w->w.dist) * w->cam.vp.dist;
	printf("projsliceh: %.3f\n", projsliceh);
	p = (t_point){(int)((double)i * w->w.slicew), (w->height/2) - (projsliceh/2), 0};
	pd = (t_point){(int)p.x, p.y + projsliceh, 0};
	p.x += MARGINW;
	pd.x += MARGINW;
	//printf("p .x : %d, y: %d | pd.x: %d, y: %d\n", p.x, p.y, pd.x, pd.y);
	mlibx_draw_pixel_line(p, pd, w, w->w.color);
}

void				w_verticales_lines_check(t_wind *w, double ray_angle, double right)
{
	t_dpoint		d;
	t_dpoint		p;
	t_dpoint		wall;
	t_dpoint		dist;

	w->w.slope = sin(ray_angle) / cos(ray_angle);
	d.x = right ? 1 : -1;
	d.y = (w->w.slope < 360) ? d.x * w->w.slope : 0;
	p.x = right ? ceil(w->cam.pos.x) : floor(w->cam.pos.x);
	p.y = (w->cam.pos.z) + (p.x - w->cam.pos.x) * w->w.slope;
	while (p.x >= 0 && p.x < MAPLEN && p.y >= 0 && p.y < MAPLEN) {
		wall.x = floor(p.x + (right ? 0 : -1));
		wall.y = floor(p.y);
		if (wall.x < 0 || wall.y < 0) break;
		if (w->b.tab_int[(int)wall.y][(int)wall.x] > 0) {
			dist = (t_dpoint){(p.x * MINIMAPSCALE) - (w->cam.pos.x * MINIMAPSCALE), (p.y * MINIMAPSCALE) - (w->cam.pos.z * MINIMAPSCALE), 0};
			w->w.dist = sqrt(pow(dist.x, 2) + pow(dist.y, 2));
			w->w.hit = p;
			w->w.color = (p.x < w->cam.pos.x) ? "0x00FF00" : "0x0000FF";
			break;
		}
		p.x += d.x;
		p.y += d.y;
	}
}

void				w_horizontales_lines_check(t_wind *w, double ray_angle, double up)
{
	t_dpoint		d;
	t_dpoint		p;
	t_dpoint		wall;
	t_dpoint		dist;
	
	w->w.slope = cos(ray_angle) / sin(ray_angle);
	d.y = up ? -1 : 1;
	d.x = (w->w.slope < 360) ? (d.y * w->w.slope) : 0;
	p.y = up ? floor(w->cam.pos.z) : ceil(w->cam.pos.z);
	p.x = w->cam.pos.x + (p.y - w->cam.pos.z) * w->w.slope;
	while (p.x >= 0 && p.x < MAPLEN && p.y >= 0 && p.y < MAPLEN) {
		wall = (t_dpoint){floor(p.x), floor(p.y + (up ? -1 : 0)), 0};
		if (wall.x < 0 || wall.y < 0) break;
		if (w->b.tab_int[(int)wall.y][(int)wall.x] > 0) {
			dist = (t_dpoint){(p.x * MINIMAPSCALE) - (w->cam.pos.x * MINIMAPSCALE), (p.y * MINIMAPSCALE) - (w->cam.pos.z * MINIMAPSCALE), 0};
			w->w.block_dist = sqrt(dist.x*dist.x + dist.y*dist.y);
			if (!w->w.dist || w->w.block_dist < w->w.dist)
			{
				w->w.dist = w->w.block_dist;
				w->w.hit = p;
				w->w.color = p.y < w->cam.pos.z ? "0xFFFF00" : "0xFF00FF";
			}
			break;
		}
		p.x += d.x;
		p.y += d.y;
	}
}

void		w_cast_single_ray(t_wind *w, double ray_angle, int raynumb)
{
	double			right;
	double			up;
	int				showrayminimap;

	w->w.dist = 0;
	w->w.hit = (t_dpoint){0, 0, 0};
	ray_angle = ft_degreetorad(ray_angle);
	ray_angle = fmod(ray_angle, TWOPI); // like modulo for double
	right = (ray_angle > TWOPI * 0.75 || ray_angle < TWOPI * 0.25);
	up = (ray_angle < 0 || ray_angle > M_PI);
	w_verticales_lines_check(w, ray_angle, right);
	w_horizontales_lines_check(w, ray_angle, up);
	showrayminimap = 0;
	if (w->w.dist)
	{
		if (showrayminimap)
			w_print_radar_ray_hitwall(w, w->w.hit.x, w->w.hit.y, "0x00FF00");
		w_draw_the_wall(w, raynumb, ray_angle);
	}
}

void			w_cast_rays(t_wind *w)
{
	int			i;
	double		angle;

	w->cam.vp.dist = (RAYNUMB/2) / tan(ft_degreetorad(FOV/2));
	w->cam.anglebetrays = (double)FOV / (double)RAYNUMB;
	w->w.slicew = w->cam.vp.w / RAYNUMB;
	angle = w->cam.rot.y - (FOV/2);
	w->w.correct_fisheyes = FOV/2;
	i = 0;
	while (i < RAYNUMB)
	{
		w->w.correct_fisheyes -= w->cam.anglebetrays;
		printf("anglebetrays: %.3f\n", w->cam.anglebetrays);
		printf("correct_fisheyes: %.3f\n", w->w.correct_fisheyes);
		printf("w->cam.pos.x: %.3f\n", w->cam.pos.x);
		w_cast_single_ray(w, angle, i);
		angle += w->cam.anglebetrays;
		i++;
	}
}



#include "wolf3d.h"

void			w_print_radar_ray_hitwall(t_wind *w, double cx, double cy, char *color)
{
	t_point		p;
	t_point		pd;
	//double		ra;

	//ra = ft_degreetorad(angle + (w->cam.rayangle/MAPSIZE));
	p = (t_point){w->cam.pos.x * MINIMAPSCALE, w->cam.pos.z * MINIMAPSCALE, 0};
	//pd = (t_point){cos(ra) * RADARL + cx, sin(ra) * RADARL + cy, 0};
	pd = (t_point){cx * MINIMAPSCALE, cy * MINIMAPSCALE, 0};
	//printf("print line hitwall x: %d, y %d, destx: %d, y:%d\n", p.x, p.y, pd.x, pd.y);
	mlibx_draw_pixel_line(p, pd, w, color);
}

void			w_print_radar_ray(t_wind *w, int cx, int cy, int angle, char *color)
{
	t_point		p;
	t_point		pd;

	p = (t_point){cx, cy, 0};
	pd = (t_point){cos(ft_degreetorad(angle)) * RADARL + p.x, sin(ft_degreetorad(angle)) * RADARL + p.y, 0};
	mlibx_draw_pixel_line(p, pd, w, color);
}

void			w_print_radar_fov(t_wind *w, int cx, int cy, int angle, char *color)
{
	t_point		p;
	t_point		pd;

	p = (t_point){cx, cy, 0};
	pd = (t_point){cos(ft_degreetorad(angle - (FOV/2))) * RADARL + p.x, sin(ft_degreetorad(angle - (FOV/2))) * RADARL + p.y, 0};
	mlibx_draw_pixel_line(p, pd, w, color);
	pd = (t_point){cos(ft_degreetorad(angle + (FOV/2))) * RADARL + p.x, sin(ft_degreetorad(angle + (FOV/2))) * RADARL + p.y, 0};
	mlibx_draw_pixel_line(p, pd, w, color);
}

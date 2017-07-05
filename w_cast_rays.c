
#include "wolf3d.h"

void			w_draw_the_wall(t_wind *w, int i, double ray_angle)
{
	double		projsliceh;
	int			marginw;
	t_point		p;
	t_point		pd;

	marginw = 200;
	//perpendicular dist to adjust fish eye
	if (ray_angle < w->cam.pos.y)
		w->w.dist = w->w.dist * cos(ray_angle - ft_degreetorad(w->cam.pos.y + 30));
	else
		w->w.dist = w->w.dist * cos(ray_angle - ft_degreetorad(w->cam.pos.y - 30));
	projsliceh = (CUBESIZE / w->w.dist) * w->cam.vp.dist;
	// We draw the vertical strip centered in the middle
	p = (t_point){(int)((double)i * w->w.slicew), (w->cam.vp.h/2) - (projsliceh/2), 0};
	pd = (t_point){(int)p.x, p.y + projsliceh, 0};
	p.x += marginw;
	pd.x += marginw;
	//printf("p .x : %d, y: %d | pd.x: %d, y: %d\n", p.x, p.y, pd.x, pd.y);
	mlibx_draw_pixel_line(p, pd, w, w->w.color);
}

void		w_verticales_lines_check(t_wind *w, double ray_angle, double right)
{
	double			xHit;
	double			yHit;
	double			dX;
	double			dY;
	double			x;
	double			y;
	int				wallX;
	int				wallY;
	double			distX;
	double			distY;

	// Vertical lines check
	w->w.slope = sin(ray_angle) / cos(ray_angle);
	dX = right ? 1 : -1; // We move either 1 map unit to the left or right
	// How much to move up or down
	dY = (w->w.slope < 360) ? dX * w->w.slope : 0;
	x = right ? ceil(w->cam.pos.x) : floor(w->cam.pos.x);
	y = (w->cam.pos.z) + (x - w->cam.pos.x) * w->w.slope;
	while (x >= 0 && x < MAPLEN && y >= 0 && y < MAPLEN) {
		wallX = floor(x + (right ? 0 : -1));
		wallY = floor(y);
		if (wallX < 0 || wallY < 0)//avoid segfault
			break;
		// Is this point inside a wall block?
		if (w->b.tab_int[wallY][wallX] > 0) {
			distX = x - w->cam.pos.x;
			distY = y - w->cam.pos.z;
			w->w.dist = (pow(distX, 2)) + (pow(distY, 2));
			xHit = x; //save hitpoint for minimap
			yHit = y;
			w->w.color = (x < w->cam.pos.x) ? "0x00FF00" : "0x0000FF"; // green or blue
			break;
			}
		x += dX;
		y += dY;
	}
}

void		w_horizontales_lines_check(t_wind *w, double ray_angle, double right, double up)
{
	double			xHit;
	double			yHit;
	double			dX;
	double			dY;
	double			x;
	double			y;
	int				wallX;
	int				wallY;
	double			distX;
	double			distY;

	// now check against horizontal lines. It's basically the same, just "turned around".
	w->w.slope = cos(ray_angle) / sin(ray_angle);
	dY = up ? -1 : 1;
	dX = (w->w.slope < 360) ? (dY * w->w.slope) : 0;
	y = up ? floor(w->cam.pos.z) : ceil(w->cam.pos.z);
	x = w->cam.pos.x + (y - w->cam.pos.z) * w->w.slope;

	while (x >= 0 && x < MAPLEN && y >= 0 && y < MAPLEN) {
		wallY = floor(y + (up ? -1 : 0));
		wallX = floor(x);
		if (wallX < 0 || wallY < 0)//avoid segfault
			break;
		// Is this point inside a wall block?
		if (w->b.tab_int[wallY][wallX] > 0) {
			distX = x - w->cam.pos.x;
			distY = y - w->cam.pos.z;
			w->w.block_dist = distX*distX + distY*distY;
			if (!w->w.dist || w->w.block_dist < w->w.dist)
			{
				w->w.dist = w->w.block_dist;
				//xHit = x;
				//yHit = y;
				w->w.color = y < w->cam.pos.z ? "0xFFFF00" : "0xFF00FF"; // yellow or purple
			}
			break;
		}
		x += dX;
		y += dY;
	}
}

void		w_cast_single_ray(t_wind *w, double ray_angle, int raynumb)
{
	double			right;
	double			up;

	w->w.dist = 0;
	ray_angle = ft_degreetorad(ray_angle);
	ray_angle = fmod(ray_angle, TWOPI); // like modulo for double
	right = (ray_angle > TWOPI * 0.75 || ray_angle < TWOPI * 0.25);
	up = (ray_angle < 0 || ray_angle > M_PI);
	//xHit = 0;//x/y coord where the ray hit the block
	//yHit = 0;

	w_verticales_lines_check(w, ray_angle, right);
	w_horizontales_lines_check(w, ray_angle, right, up);
	if (w->w.dist)
	{
		//w_print_radar_ray_hitwall(w, xHit, yHit, "0x00FF00");
		w_draw_the_wall(w, raynumb, ray_angle);
	}
}

void			w_cast_rays(t_wind *w)
{
	int			i;
	double		angle;
	//double		rayScreenPos;

	w->cam.vp.dist = (RAYNUMB/2) / tan(ft_degreetorad(FOV/2));
	w->cam.anglebetrays = (double)FOV / (double)RAYNUMB;
	w->w.slicew = w->cam.vp.w / RAYNUMB;
	angle = w->cam.rot.y - (FOV/2);
	i = 0;
	while (i < RAYNUMB)
	{
		//rayScreenPos = (-RAYNUMB/2 + i) * stripwidth;
		//w->cam.vp.distpix = pow(rayScreenPos, 2) / pow(w->cam.vp.dist, 2);
		w_cast_single_ray(w, angle, i);
		angle += w->cam.anglebetrays;
		i++;
	}
}


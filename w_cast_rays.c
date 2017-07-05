
#include "wolf3d.h"
/*
double			get_doubleangle_3points(t_wind *w, )
{
	double		res;
	

	return (res);
}*/

void			w_draw_the_wall(t_wind *w, int i)
{
	double		projsliceh;
	int			marginw;
	//int			marginh;
	t_point		p;
	t_point		pd;

	marginw = 200;
	//marginh = 100;
	//http://permadi.com/1996/05/ray-casting-tutorial-9/
	projsliceh = ( CUBESIZE / w->dist) * w->cam.vp.dist;
	//printf("projsliceh : %.3f\n", projsliceh);

	// We draw the vertical strip centered in the middle
	p = (t_point){i, (w->cam.vp.h/2) - (projsliceh/2), 0};
	pd = (t_point){p.x, p.y + projsliceh, 0};

	p.x += marginw;
	pd.x += marginw;
	//printf("p .x : %d, y: %d | pd.x: %d, y: %d\n", p.x, p.y, pd.x, pd.y);
	mlibx_draw_pixel_line(p, pd, w, "0xFFFFFF");
}

void		w_cast_single_ray(t_wind *w, double ray_angle, int raynumb)
{
	double	right;
	double	up;
	double	block_dist;
	double	xHit;
	double	yHit;
	double	slope;
	double	dX;
	double	dY;
	double	x;
	double	y;
	int		wallX;
	int		wallY;
	double	distX;
	double	distY;
	int		hitblockn;

	w->dist = 0;
	//printf("ray_angle : %.3f\n", ray_angle);
	ray_angle = ft_degreetorad(ray_angle);
	ray_angle = fmod(ray_angle, TWOPI); // like modulo for double
	ft_putendl("--------------------------------------");
	ft_putstr("raynumb: ");
	ft_putnbr(raynumb);
	ft_putchar('\n');
	printf("ray_angle : %.3f\n", ray_angle);
	right = (ray_angle > TWOPI * 0.75 || ray_angle < TWOPI * 0.25);
	up = (ray_angle < 0 || ray_angle > M_PI);
	//dist = 0;// the distance to the block we hit
	xHit = 0;// the	x and y coord of where the ray hit the block
	yHit = 0;
	// First check against the vertical map/wall lines
	slope = sin(ray_angle) / cos(ray_angle);
	dX = right ? 1 : -1; // We move either 1 map unit to the left or right
	if (slope < 360)
		dY = dX * slope; // How much to move up or down
	else
		dY = 0;
	x = right ? ceil(w->cam.pos.x) : floor(w->cam.pos.x);
	y = (w->cam.pos.z) + (x - w->cam.pos.x) * slope;
	if (w->p.comments)
	{
		printf("VERTICAL CHECK\n");
		printf("cam.pos.x : %.3f, z: %.3f\n", w->cam.pos.x, w->cam.pos.z);
		printf("pos x : %.3f, y: %.3f\n", x, y);
		printf("right : %.3f\n", right);
		printf("up : %.3f\n", up);
		printf("slope : %.3f\n", slope);
		printf("dX : %.3f\n", dX);
		printf("dY : %.3f\n", dY);
	}
	while (x >= 0 && x < MAPLEN && y >= 0 && y < MAPLEN) {
		wallX = floor(x + (right ? 0 : -1));
		wallY = floor(y);
		if (w->p.comments)
			printf("wallX : %d, wallY: %d\n", wallX, wallY);
		if (wallX < 0 || wallY < 0)//avoid segfault
			break;
		// Is this point inside a wall block?
		if (w->b.tab_int[wallY][wallX] > 0) {
			distX = x - w->cam.pos.x;
			distY = y - w->cam.pos.z;
			w->dist = (pow(distX, 2)) + (pow(distY, 2));
			if (w->p.comments)
			{
				printf("distX : %.3f\n", distX);
				printf("distY : %.3f\n", distY);
				// The distance from the player to this point, squared
				printf("pow of distX : %.3f\n", pow(distX, 2));
				printf("pow of distY : %.3f\n", pow(distY, 2));
				printf("pow of distX + 2: %.3f\n", pow(distX, 2) + 2);
				printf("dist : %.3f\n", w->dist);
			}
			// Save the coordinates of the hit. We only really
			// use these to draw the rays on minimap
			xHit = x;
			yHit = y;
			printf("first yHit: %.3f xHit: %.3f\n", yHit, xHit);
			hitblockn = 1;
			//print_radar_ray_hitwall(w, xHit, yHit, "0x00FF00");
			break;
			}
		x += dX;
		y += dY;
	}

	// now check against horizontal lines. It's basically the same, just "turned around".
	slope = cos(ray_angle) / sin(ray_angle);
	dY = up ? -1 : 1;
	if (slope < 360)
		dX = dY * slope;
	else
		dX = 0;
	y = up ? floor(w->cam.pos.z) : ceil(w->cam.pos.z);
	x = w->cam.pos.x + (y - w->cam.pos.z) * slope;

	if (w->p.comments)
	{
		printf("HORIZONTAL CHECK\n");
		printf("cam.pos.x : %.3f, z: %.3f\n", w->cam.pos.x, w->cam.pos.z);
		printf("pos x : %.3f, y: %.3f\n", x, y);
		printf("right : %.3f\n", right);
		printf("up : %.3f\n", up);
		printf("slope : %.3f\n", slope);
		printf("dX : %.3f\n", dX);
		printf("dY : %.3f\n", dY);
	}
	while (x >= 0 && x < MAPLEN && y >= 0 && y < MAPLEN) {
		wallY = floor(y + (up ? -1 : 0));
		wallX = floor(x);
		if (wallX < 0 || wallY < 0)//avoid segfault
			break;
		// Is this point inside a wall block?
		if (w->b.tab_int[wallY][wallX] > 0) {
			distX = x - w->cam.pos.x;
			distY = y - w->cam.pos.z;
			block_dist = distX*distX + distY*distY;
			if (w->p.comments)
				printf("presupposed block_dist : %.3f\n", block_dist);
			if (!w->dist || block_dist < w->dist)
			{
				if (w->p.comments)
				{
					//printf("pos x : %.3f, y: %.3f\n", x, y);
					//printf("wallX : %d, wallY: %d\n", wallX, wallY);
					//printf("block_dist : %.3f\n", block_dist);
				}
				w->dist = block_dist;
				xHit = x;
				yHit = y;
				printf("second yHit: %.3f xHit: %.3f\n", yHit, xHit);
				hitblockn = 2;
			}
			break;
		}
		x += dX;
		y += dY;
	}
	if (w->dist)
	{
		if (hitblockn == 2 || hitblockn == 1)
		{
			printf("w->dist : %.3f\n", w->dist);
			printf("yHit : %.3f, xHit: %.3f\n", yHit, xHit);
			//printf("pos x : %.3f, y: %.3f\n", x, y);
			w_print_radar_ray_hitwall(w, xHit, yHit, "0x00FF00");
			//w_draw_the_wall(w, raynumb);
		}
	}
}

void			w_cast_rays(t_wind *w)
{
	int			i;
	double		angle;
	//double		rayScreenPos;
	//int			stripwidth;

	//stripwidth = w->cam.vp.w / RAYNUMB;
	w->cam.vp.dist = (w->cam.vp.w/2) / tan(ft_degreetorad(FOV/2));
	angle = w->cam.rot.y - (FOV/2);
	//printf("angle of start : %.3f\n", angle);
	w->cam.anglebetrays = (double)FOV / (double)RAYNUMB;
	i = 0;
	ft_putendl("|||||||||||||||||||||||||||||||||||||||||||||");
	ft_putendl("--------------------------------------");
	while (i < RAYNUMB)
	{
		//rayScreenPos = (-RAYNUMB/2 + i) * stripwidth;
		//w->cam.vp.distpix = pow(rayScreenPos, 2) / pow(w->cam.vp.dist, 2);
		w_cast_single_ray(w, angle, i);
		angle += w->cam.anglebetrays;
		i++;
	}
	//printf("anglebetrays : %.3f\n", w->cam.anglebetrays);
	//printf("angle of end : %.3f\n", angle);
}


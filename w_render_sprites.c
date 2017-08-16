#include "wolf3d.h"

void		w_render_sprites(t_wind *w)
{
	double	dx;
	double	dy;
	double	dist;
	double	sprite_angle;
	double	size;

	// Translate position to viewer sprite
	dx = w->w.tab_int_spr[][] + 0.5 - w->cam.pos.x;
	dy = w->w.tab_int_spr[][] + 0.5 - w->cam.pos.z;
	
	// Distance to sprite
	dist = sqrt(dx * dx + dy * dy);

	// Sprite angle relative to viewing angle
	sprite_angle = atan2(dy, dx) - w->cam.rot.y;
	
	// Size of the sprite
	size = w->cam.vp.dist / (cos(ft_degreetorad(sprite_angle)) * dist);
}

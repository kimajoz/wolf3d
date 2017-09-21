/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbillett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 14:52:45 by pbillett          #+#    #+#             */
/*   Updated: 2017/09/21 18:29:13 by pbillett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

#define LEFTM 4
#define ROW 20
#define BL 6

static void			put_string(char *s, int l, int c, t_wind *w)
{
	mlx_string_put(w->mlx, w->win, 3 + c * 10, l * 20, 0xFFFFFF, s);
}

void				put_info_cam(t_wind *w, int leftm, int row, int bl)
{
	row = w->b.nbrtot_of_line  / 1.5;
	put_string("player.speed :", row, 1, w);
	put_string(ft_itoa((int)w->w.player.speed), row, leftm + bl + 5, w);
	row++;
	put_string("player.dir :", row, 1, w);
	put_string(ft_itoa((int)w->w.player.dir), row, leftm + bl + 5, w);
	row++;
	put_string("Camera :", row, 1, w);
	row++;
	put_string("pos.x:", row, leftm, w);
	put_string(ft_itoa((int)w->cam.pos.x), row, leftm + bl, w);
	put_string("y: ", row, leftm + bl + 4, w);
	put_string(ft_itoa((int)w->cam.pos.y), row, leftm + bl + 6, w);
	put_string("z: ", row, leftm + bl + 10, w);
	put_string(ft_itoa((int)w->cam.pos.z), row, leftm + bl + 12, w);
	row++;
	put_string("rot.x:", row, leftm, w);
	put_string(ft_itoa((int)w->cam.rot.x), row, leftm + bl, w);
	put_string("y: ", row, leftm + bl + 4, w);
	put_string(ft_itoa((int)w->cam.rot.y), row, leftm + bl + 6, w);
	put_string("z: ", row, leftm + bl + 10, w);
	put_string(ft_itoa((int)w->cam.rot.z), row, leftm + bl + 12, w);
	row++;
	/*put_string("fire: ", row, leftm + bl + 10, w);
	put_string(ft_itoa((int)w->w.player.fire), row, leftm + bl + 12, w);
	row++;
	put_string("firetmp: ", row, leftm + bl + 10, w);
	put_string(ft_itoa((int)w->w.tmpgun), row, leftm + bl + 12, w);*/
}

void				put_info_timeout(t_wind *w, int rightm, int bl)
{
	put_string("Time:", 1, rightm, w);
	put_string(ft_itoa((int)w->w.player.timeout), 1, rightm + bl, w);
}

void				put_info_game(t_wind *w, int row, int bl)
{
	int				rightm;
	int				midm;

	rightm = 71;
	midm = 25;
	put_info_timeout(w, rightm, bl);
	row = w->b.nbrtot_of_line + 4;
	put_string("Health:", row, midm, w);
	put_string(ft_itoa((int)w->w.player.health), row, midm + 7, w);
	put_string("Ammunition:", row, midm + 12, w);
	put_string(ft_itoa((int)w->w.player.ammunition), row, midm + 24, w);
	put_string("Objects:", row, midm + 27, w);
	put_string(w->w.player.object, row, midm + bl + 29, w);
	put_string("Score:", row, rightm, w);
	put_string(ft_itoa((int)w->w.player.totalscore), row, rightm + bl + 1, w);
	row++;
	if (w->w.player.gameover)
		mlx_string_put(w->mlx, w->win, ((w->width / 3) * 2) - 15, (w->height / 2), 0xFFFFFF, "GAME OVER");
	else if (w->w.player.win)
	{
		mlx_string_put(w->mlx, w->win, ((w->width / 3) * 2) - 50, (w->height / 2) - 200, 0xFFFFFF, "YOU WIN !");
		mlx_string_put(w->mlx, w->win, ((w->width / 3) * 2) - 50, (w->height / 2) - 150, 0xFFFFFF, "LEVEL 1");
		mlx_string_put(w->mlx, w->win, ((w->width / 3) * 2) - 50, (w->height / 2) - 100, 0xFFFFFF, "Points: ");
		mlx_string_put(w->mlx, w->win, ((w->width / 3) * 2) + rightm - 50, (w->height / 2) - 100, 0xFFFFFF, ft_itoa((int)w->w.player.points));
		mlx_string_put(w->mlx, w->win, ((w->width / 3) * 2) - 50, (w->height / 2) - 80, 0xFFFFFF, "Kills: ");
		mlx_string_put(w->mlx, w->win, ((w->width / 3) * 2) + rightm - 50, (w->height / 2) - 80, 0xFFFFFF, ft_itoa((int)w->w.player.kills));
		mlx_string_put(w->mlx, w->win, ((w->width / 3) * 2) - 50, (w->height / 2) - 60, 0xFFFFFF, "Health: ");
		mlx_string_put(w->mlx, w->win, ((w->width / 3) * 2) + rightm - 50, (w->height / 2) - 60, 0xFFFFFF, ft_itoa((int)w->w.player.health));
		mlx_string_put(w->mlx, w->win, ((w->width / 3) * 2) - 50, (w->height / 2) - 40, 0xFFFFFF, "Bonus Time: ");
		mlx_string_put(w->mlx, w->win, ((w->width / 3) * 2) + rightm, (w->height / 2) - 40, 0xFFFFFF, ft_itoa(TIMEOUT_GAME - (int)w->w.player.timeout));
		mlx_string_put(w->mlx, w->win, ((w->width / 3) * 2) - 50, (w->height / 2) + 20, 0xFFFFFF, "Total: ");
		mlx_string_put(w->mlx, w->win, ((w->width / 3) * 2) + rightm - 50, (w->height / 2) + 20, 0xFFFFFF, ft_itoa((int)w->w.player.points + w->w.player.kills + w->w.player.health + (TIMEOUT_GAME - (int)w->w.player.timeout)));
	}
}

void				put_info(t_wind *w)
{
	int				row;
	int				column;
	int				margin;

	column = 17;
	row = 14;
	margin = 2;
	put_info_cam(w, LEFTM, row, BL);
	row = 22;
	put_string("1/4: Rays min/max", row, 1, w);
	row = 23;
	put_string("2/3: Rays -/+", row, 1, w);
	put_string(ft_itoa((int)w->w.info.raynumb), row, column, w);
	row = 25;
	put_string("Toogles:", row, margin, w);
	row = 26;
	put_string("5: Minimap rays", row, margin, w);
	put_string(ft_itoa((int)w->w.info.ray_minimap), row, column, w);
	row = 27;
	put_string("6: Background", row, margin, w);
	put_string(ft_itoa((int)w->w.info.bg), row, column, w);
	row = 28;
	put_string("7: Textures", row, margin, w);
	put_string(ft_itoa((int)w->w.info.texture), row, column, w);
	row = 29;
	put_string("8: Sound", row, margin, w);
	put_string(ft_itoa((int)w->w.info.sound), row, column, w);
	put_info_game(w, row, BL);
}

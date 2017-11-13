/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbillett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 14:52:45 by pbillett          #+#    #+#             */
/*   Updated: 2017/11/09 18:46:30 by pbillett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

#define LEFTM 4
#define ROW 20
#define BL 6
#define WH 0xFFFFFF
#define COLUMN 17
#define MARGIN 2

void				put_info_cam(t_wind *w, int leftm, int row, int bl)
{
	row = w->b.nbrtot_of_line / 1.75;
	mlibx_putstring("player.speed :", row, 1, w);
	w_mlibx_putint(w->w.player.speed, row, leftm + bl + 5, w);
	row++;
	mlibx_putstring("player.dir :", row, 1, w);
	w_mlibx_putint(w->w.player.dir, row, leftm + bl + 5, w);
	row++;
	mlibx_putstring("Camera :", row, 1, w);
	row++;
	mlibx_putstring("pos.x:", row, leftm, w);
	mlibx_putstring(w->w.legend[13], row, leftm + bl, w);
	mlibx_putstring("y: ", row, leftm + bl + 4, w);
	w_mlibx_putint(w->cam.pos.y, row, leftm + bl + 6, w);
	mlibx_putstring("z: ", row, leftm + bl + 10, w);
	w_mlibx_putint(w->cam.pos.z, row, leftm + bl + 12, w);
	row++;
	mlibx_putstring("rot.x:", row, leftm, w);
	w_mlibx_putint(w->cam.rot.x, row, leftm + bl, w);
	mlibx_putstring("y: ", row, leftm + bl + 4, w);
	w_mlibx_putint(w->cam.rot.y, row, leftm + bl + 6, w);
	mlibx_putstring("z: ", row, leftm + bl + 10, w);
	w_mlibx_putint(w->cam.rot.z, row, leftm + bl + 12, w);
	row++;
}

void				put_info_timeout(t_wind *w, int rightm, int bl)
{
	mlibx_putstring("Time:", 1, rightm, w);
	w_mlibx_putint(w->w.player.timeout, 1, rightm + bl, w);
}

void				put_info_win(t_wind *w, int rightm)
{
	int				marg;
	int				hh;

	marg = ((w->width / 3) * 2);
	hh = w->height / 2;
	mlx_string_put(w->mlx, w->win, marg - 50, hh - 200, WH, "YOU WIN !");
	mlx_string_put(w->mlx, w->win, marg - 50, hh - 150, WH, "LEVEL 1");
	mlx_string_put(w->mlx, w->win, marg - 50, hh - 100, WH, "Points: ");
	mlx_string_put(w->mlx, w->win, marg + rightm - 50, hh - 100, WH,
			w->w.legend[8]);
	mlx_string_put(w->mlx, w->win, marg - 50, hh - 80, WH, "Kills: ");
	mlx_string_put(w->mlx, w->win, marg + rightm - 50, hh - 80, WH,
			w->w.legend[9]);
	mlx_string_put(w->mlx, w->win, marg - 50, hh - 60, WH, "Health: ");
	mlx_string_put(w->mlx, w->win, marg + rightm - 50, hh - 60, WH,
			w->w.legend[10]);
	mlx_string_put(w->mlx, w->win, marg - 50, hh - 40, WH, "Bonus Time: ");
	mlx_string_put(w->mlx, w->win, marg + rightm, hh - 40, WH,
			w->w.legend[11]);
	mlx_string_put(w->mlx, w->win, marg - 50, hh + 20, WH, "Total: ");
	mlx_string_put(w->mlx, w->win, marg + rightm - 50, hh + 20, WH,
			w->w.legend[12]);
	mlx_string_put(w->mlx, w->win, marg - 50, hh + 40, WH,
			"PRESS ENTER - TO GO TO THE NEXT LEVEL");
}

void				put_info_game(t_wind *w, int row, int bl)
{
	int				rightm;
	int				midm;

	row = 29;
	mlibx_putstring("8: Sound", row, MARGIN, w);
	w_mlibx_putint(w->w.info.sound, row, COLUMN, w);
	rightm = 71;
	midm = 25;
	put_info_timeout(w, rightm, bl);
	row = (w->height - 50) / 20;
	mlibx_putstring("Health:", row, midm, w);
	mlibx_putstring(w->w.legend[0], row, midm + 7, w);
	mlibx_putstring("Ammunition:", row, midm + 12, w);
	mlibx_putstring(w->w.legend[1], row, midm + 24, w);
	mlibx_putstring("Objects:", row, midm + 27, w);
	mlibx_putstring(w->w.legend[2], row, midm + bl + 29, w);
	mlibx_putstring("Score:", row, rightm, w);
	mlibx_putstring(w->w.legend[3], row, rightm + bl + 1,
		w);
	row++;
	if (w->w.player.gameover)
		mlx_string_put(w->mlx, w->win, ((w->width / 3) * 2) - 15,
			w->height / 2, WH, "GAME OVER");
	else if (w->w.player.win)
		put_info_win(w, rightm);
}

void				put_info(t_wind *w)
{
	int				row;

	legend(w);
	row = 14;
	put_info_cam(w, LEFTM, row, BL);
	row = 19;
	mlibx_putstring("Ctrl(right): fire | r: reload", row++, 1, w);
	mlibx_putstring("Space: open doors", row, 1, w);
	row = 22;
	mlibx_putstring("1/4: Rays min/max", row++, 1, w);
	mlibx_putstring("2/3: Rays -/+", row, 1, w);
	mlibx_putstring(w->w.legend[7], row, COLUMN, w);
	row = 25;
	mlibx_putstring("Toogles:", row, MARGIN, w);
	row = 26;
	mlibx_putstring("5: Minimap rays", row, MARGIN, w);
	mlibx_putstring(w->w.legend[4], row, COLUMN, w);
	row = 27;
	mlibx_putstring("6: Background", row, MARGIN, w);
	mlibx_putstring(w->w.legend[5], row, COLUMN, w);
	row = 28;
	mlibx_putstring("7: Textures", row, MARGIN, w);
	mlibx_putstring(w->w.legend[6], row, COLUMN, w);
	put_info_game(w, row, BL);
	free_legend(w);
}

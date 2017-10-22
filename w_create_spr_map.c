

#include "wolf3d.h"

void		create_spr_map(t_wind *w)
{
	int		y;
	int		x;

	w->w.tab_int_spr = malloc(w->b.nbrtot_of_line * sizeof(t_sprite *));
	y = 0;
	while (y < w->b.nbrtot_of_line)
	{
		w->w.tab_int_spr[y] = malloc(w->b.nbr_elem_line[3] * sizeof(t_sprite));
		x = 0;
		while (x < w->b.nbr_elem_line[3])
		{
			w->w.tab_int_spr[y][x].num = 0;
			w->w.tab_int_spr[y][x].posx = x;
			w->w.tab_int_spr[y][x].posy = y;
			w->w.tab_int_spr[y][x].vis = 0;
			w->w.tab_int_spr[y][x].block = 0;
			x++;
		}
		y++;
	}
}

void		set_spr_to_prog(int fd, t_wind *w)
{
	char	*line;
	char	**tab;
	int		x;

	init_sprites(w);
	w->w.sprnbvis = 0;
	create_spr_map(w);
	w->w.nbtotsprprog = 0;
	while (get_next_line(fd, &line))
	{
		tab = ft_strsplit(line, ';');
		ft_strdel(&line);
		x = 0;
		if (tab[x][0] != '#')
		{
			w->w.tab_int_spr[ft_atoi(tab[2])][ft_atoi(tab[1])].num =
				ft_atoi(tab[0]);
			w->w.tab_int_spr[ft_atoi(tab[2])][ft_atoi(tab[1])].block =
				w->w.sprite[ft_atoi(tab[0])].block;
			while (tab[x])
				ft_strdel(&tab[x++]);
			w->w.nbtotsprprog++;
		}
		ft_putendl("before free init_sprites");
		//free(tab);
		ft_putendl("after free init_sprites");
	}
	w->w.visiblespr = malloc(w->w.nbtotsprprog * sizeof(t_sprite));
	ft_putendl("after free init_sprites 2");
}

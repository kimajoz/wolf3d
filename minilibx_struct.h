/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minilibx_struct.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbillett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/06 21:06:50 by pbillett          #+#    #+#             */
/*   Updated: 2017/07/06 23:31:37 by pbillett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINILIBX_STRUCT_H
# define MINILIBX_STRUCT_H

typedef struct		s_rgbcolorf
{
	float			r;
	float			g;
	float			b;
}					t_rgbcolorf;

typedef struct		s_point
{
	int				x;
	int				y;
	int				z;
}					t_point;

typedef struct		s_rgbcolor
{
	int				r;
	int				g;
	int				b;
}					t_rgbcolor;

typedef struct		s_colorpalette
{
	char			*hexa_bot;
	char			*hexa_mid;
	char			*hexa_top;
	char			*hexa_default;
	int				hexa_bool;
	int				z;
	int				zd;
	int				min;
	int				max;
}					t_colorpalette;

typedef struct		s_mouse
{
	int				button1;
	int				button2;
	int				button3;
	int				memm_x;
	int				memm_y;
	int				mem_rotx;
	int				mem_rotz;
	int				mem_spacing_x;
	int				mem_zaccentuation;
	int				mem_posx;
	int				mem_posy;
	int				mem_gizx;
	int				mem_gizy;
}					t_mouse;

typedef struct		s_line
{
	float			x;
	float			y;
	float			z;
	int				xdest;
	int				ydest;
	int				zdest;
	int				sign_x;
	int				sign_y;
	int				sign_z;
	float			bigdiff;
	float			diff_x;
	float			diff_y;
	float			diff_z;
	int				midx;
	int				midy;
}					t_line;

typedef struct		s_dpoint
{
	double			x;
	double			y;
	double			z;
}					t_dpoint;

typedef struct		s_vec
{
	t_dpoint		dir;
	float			len;
}					t_vec;

typedef struct		s_viewplane
{
	float			w;
	float			h;
	float			aspect_r;
	float			dist;
	float			distpix;
	t_vec			dot_upleft;
	t_vec			rightvec;
	t_vec			upvec;
}					t_viewplane;

typedef struct		s_camera
{
	t_viewplane		vp;
	t_dpoint		pos;
	t_point			rot;
	t_vec			dir;
	t_vec			right;
	t_vec			left;
	double			fov;
	double			anglebetrays;
	double			rayangle;
}					t_camera;

typedef struct				s_listp_path
{
	t_point					*p;
	struct s_listp_path		*next;
}							t_listp_path;

typedef struct				s_listofnodes
{
	t_listp_path			*lstp;
	struct s_listofnodes	*next;
}							t_listofnodes;

typedef struct		s_fillsquare
{
	int				bol;
	int				bolfill;
	t_listp_path	*path;
	t_listp_path	*beginpath;
	t_listofnodes	*lstnodes;
	t_listofnodes	*lstnodesbeg;
	int				i;
	t_point			p;
	t_point			pr;
	t_point			pd;
	t_point			pdi;
	int				row_min;
	int				row_max;
}					t_fillsquare;

typedef struct		s_sortlistp
{
	int				mem_x;
	int				mem_z;
}					t_sortlistp;

typedef struct		s_matrice_rot
{
	double			a;
	double			b;
	double			c;
	double			d;
	double			e;
	double			f;
	double			ad;
	double			bd;
	float			mat[16];
	t_dpoint		p_r;
}					t_matrice_rot;

typedef struct		s_browsefile
{
	char			*filename;
	int				x;
	int				y;
	int				**tab_int;
	char			**tab_char;
	int				nbrtot_of_line;
	int				nbr_of_line;
	int				*nbr_elem_line;
}					t_browsefile;

typedef struct		s_img
{
	void			*ptr_img;
	int				x;
	int				y;
	int				start_x;
	int				start_y;
	int				width;
	int				height;
	int				x_centerpoint;
	int				y_centerpoint;
	int				z_centerpoint;
	char			*pxl_ptr;
	int				bits_per_pixel;
	int				size_line;
	int				octet_per_pixel;
	int				endian_type;
	t_point			point;
	t_point			pointd;
	t_point			r_point;
	t_point			r_pointd;
	int				margin;
}					t_img;

typedef struct		s_params
{
	int				zaccentuation;
	int				zhighest;
	int				zlowest;
	int				zmid;
	int				x_spacing;
	int				y_spacing;
	int				z_spacing;
	t_point			t;
	t_point			rot;
	t_dpoint		r_rot;
	int				graphic_mode;
	int				view_mode;
	int				dot;
	int				insert;
	int				space_mousemove;
	int				help;
	int				comments;
	int				comments2;
	t_colorpalette	color;
	int				turntable;
	t_mouse			m;
	int				paint;
	int				cubesize;
}					t_params;

typedef struct		s_movegizmo
{
	t_point			t;
	t_point			p_x;
	t_point			pd_x;
	t_point			p_y;
	t_point			pd_y;
	t_point			p_z;
	t_point			pd_z;
}					t_movegizmo;

typedef struct		s_rot_tra_scale
{
	int				r;
	int				t;
	int				s;
}					t_rot_tra_scale;

typedef struct		s_obj
{
	t_movegizmo		gizt;
	t_point			center_rgiz;
	t_rot_tra_scale	showgiz;
	t_fillsquare	f;
}					t_obj;

typedef struct		s_info
{
	int				bg;
	int				ray_minimap;
	int				raynumb;
	int				texture;
	int				sound;

}					t_info;

typedef struct		s_wolf
{
	double			dist;
	double			dist_correct;
	double			slicew;
	double			slope;
	t_dpoint		hit;
	double			block_dist;
	char			*color;
	char			*color_mfov;
	char			*color_mray;
	double			correct_fisheyes;
	t_info			info;
}					t_wolf;

typedef struct		s_wind
{
	void			*mlx;
	void			*win;
	char			*title;
	int				width;
	int				height;
	t_camera		cam;
	t_point			point;
	t_img			img;
	t_browsefile	b;
	t_params		p;
	t_obj			obj;
	t_matrice_rot	mr;
	t_wolf			w;
}					t_wind;

#endif

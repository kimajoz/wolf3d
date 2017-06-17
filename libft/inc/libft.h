/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ../inc/libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbillett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/23 12:11:15 by pbillett          #+#    #+#             */
/*   Updated: 2017/04/12 13:44:57 by pbillett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <string.h>
# include <math.h>
# include "../../minilibx_struct.h"

void				*ft_memset(void *b, int c, size_t len);
void				ft_bzero(void *s, size_t n);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memccpy(void *dst, const void *src, int c, size_t n);
void				*ft_memmove(void *dst, const void *src, size_t len);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
size_t				ft_strlen(char const *str);
char				*ft_strdup(const char *s1);
char				*ft_strcpy(char *dst, const char *src);
char				*ft_strncpy(char *dst, const char *src, size_t n);
char				*ft_strcat(char *s1, char *s2);
char				*ft_strncat(char *s1, char *s2, size_t n);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
char				*ft_strstr(const char *s1, const char *s2);
char				*ft_strnstr(const char *s1, const char *s2, size_t n);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					ft_atoi(const char *str);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_tolower(int c);
int					ft_toupper(int c);
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_is_prime(int n);
int					ft_add_prime_sum(int nbr);
char				*ft_strrev(char *str);

void				ft_putchar(char c);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr(char const *s);
void				ft_putstr_fd(char const *s, int fd);
void				ft_putnbr(int n);
void				ft_putnbr_fd(int n, int fd);
void				ft_putendl(char const *s);
void				ft_putendl_fd(char const *s, int fd);
char				*ft_itoa(int n);
void				ft_putlstnbr(int *lstnbr, int numbelem);

void				*ft_memalloc(size_t size);
void				ft_memdel(void **ap);
char				*ft_strnew(size_t size);
void				ft_strdel(char **as);
void				ft_strclr(char *s);
void				ft_striter(char *s, void (*f)(char *));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				*ft_strmap(char const *s, char (*f)(char));
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int					ft_strequ(char const *s1, char const *s2);
int					ft_strnequ(char const *s1, char const *s2, size_t n);
char				*ft_strsub(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s);
char				**ft_strsplit(char const *s, char c);

typedef struct		s_list
{
	void			*data;
	size_t			data_size;
	struct s_list	*next;
}					t_list;

t_list				*ft_lstnew(void const *content, size_t content_size);
void				ft_lstdelone(t_list **alst, void (*del)(void*, size_t));
void				ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void				ft_lstadd(t_list **alst, t_list *new);
void				ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list				*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
t_list				*ft_sort_list(t_list *lst, int (*cmp)(int, int));

float				ft_squared(float n);
float				ft_pythagore(float a, float b);
double				ft_degreetorad(int degrees);
float				ft_radian_to_degree(float radians);
char				*ft_rgbtohexa(t_rgbcolor rgbcolor);
char				*ft_rgbftohexa(t_rgbcolorf rgbcolorf);
t_rgbcolor			ft_hexatorgb(char *hexcolor);
int					ft_hextoint(char *s);
char				*ft_inttohex(int n);
t_listofnodes		ft_listofnodes_init(t_listp_path *tmp);
void				ft_listofnodes_free(t_listofnodes *lstnodes);
t_point				*ft_pointnew(int x, int y, int z);
t_listp_path		*ft_pathinit(t_line v);
t_listp_path		*ft_pathadd(t_listp_path *list, t_listp_path *elem);
t_listp_path		*ft_freepath(t_listp_path *list);
void				ft_sort_listofnodes_foreach_nodes(t_listofnodes *lstnodes);
t_wind				mlibx_create_new_window(char *title, int width, int height);
int					mlibx_dot_in_window(t_wind *w, int x, int y);
void				mlibx_draw_circle(t_wind *w, t_point centp, int rayon, char *hexcol);
void				mlibx_draw_circlef(t_wind *w, t_point centp, int rayon, char *hexcol);
void				mlibx_draw_pixel(t_wind *w, int x, int y, char *hexacolor);
void				mlibx_draw_pixel_line(t_point point, t_point pointd, t_wind *w);
t_line				ft_set_parameters_tline(t_line v);
int					ft_get_sign(int first, int second);
int					ft_get_diff(int first, int second);
double				ft_fabs(double x);
int					ft_nbrlen(int n);

#endif

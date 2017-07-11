/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keymacro.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbillett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 14:44:56 by pbillett          #+#    #+#             */
/*   Updated: 2017/07/06 23:21:34 by pbillett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEYMACRO_H
# define KEYMACRO_H

# if MACROKEY == 1
#  define EXIT 53
#  define KEY_W 13
#  define KEY_S 1
#  define KEY_E 14
#  define KEY_R 15
#  define KEY_T 17
#  define KEY_P 35
#  define L_ARROW 123
#  define R_ARROW 124
#  define U_ARROW 126
#  define D_ARROW 125
#  define BACKSLASH 44
#  define EXCLAMMARK 47
#  define INSERT 117
#  define NUM_U 91
#  define NUM_D 84
#  define NUM_R 88
#  define NUM_L 86
#  define NUM_1 83
#  define NUM_3 85
#  define ZOOM_P 69
#  define ZOOM_M 78
#  define PAGE_U 116
#  define PAGE_D 121
#  define KEY_1 18
#  define KEY_2 19
#  define KEY_3 20
#  define KEY_4 21
#  define KEY_5 23
#  define KEY_6 22
#  define KEY_7 232
#  define KEY_8 95
#  define KEY_I 34
#  define F1 23
#  define F2 22
#  define F3 26
#  define SPACE 49
# else
#  define EXIT 65307
#  define KEY_S 115
#  define KEY_W 119
#  define KEY_E 101
#  define KEY_R 114
#  define KEY_T 116
#  define KEY_P 112
#  define L_ARROW 65361
#  define R_ARROW 65363
#  define U_ARROW 65362
#  define D_ARROW 65364
#  define BACKSLASH 33
#  define EXCLAMMARK 58
#  define INSERT 65379
#  define NUM_U 65431
#  define NUM_D 65433
#  define NUM_R 65432
#  define NUM_L 65430
#  define NUM_1 65436
#  define NUM_3 65435
#  define ZOOM_P 65451
#  define ZOOM_M 65453
#  define PAGE_U 65365
#  define PAGE_D 65366
#  define KEY_1 38
#  define KEY_2 233
#  define KEY_3 34
#  define KEY_4 39
#  define KEY_5 40
#  define KEY_6 45
#  define KEY_7 232
#  define KEY_8 95
#  define KEY_I 105
#  define F1 65470
#  define F2 65471
#  define F3 65472
#  define SPACE 32
# endif
#endif

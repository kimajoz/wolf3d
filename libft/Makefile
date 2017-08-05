# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pbillett <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/11/26 14:11:23 by pbillett          #+#    #+#              #
#    Updated: 2017/07/06 18:46:47 by pbillett         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME= libft.a
SRC= src/ft_lstiter.c \
	src/ft_putendl.c \
	src/ft_strequ.c \
	src/ft_strnstr.c \
	src/ft_lstmap.c \
	src/ft_putendl_fd.c \
	src/ft_striter.c \
	src/ft_strrchr.c \
	src/ft_strrev.c \
	src/ft_atoi.c \
	src/ft_lstnew.c \
	src/ft_putnbr.c \
	src/ft_putlstnbr.c \
	src/ft_striteri.c \
	src/ft_strsplit.c \
	src/ft_bzero.c \
	src/ft_memalloc.c \
	src/ft_putnbr_fd.c \
	src/ft_strjoin.c \
	src/ft_strstr.c \
	src/ft_isalnum.c \
	src/ft_memccpy.c \
	src/ft_putstr.c \
	src/ft_strlcat.c \
	src/ft_strsub.c \
	src/ft_isalpha.c \
	src/ft_memchr.c \
	src/ft_putstr_fd.c \
	src/ft_strlen.c \
	src/ft_nbrlen.c \
	src/ft_strtrim.c \
	src/ft_isascii.c \
	src/ft_memcmp.c \
	src/ft_strcat.c \
	src/ft_strmap.c \
	src/ft_tolower.c \
	src/ft_isdigit.c \
	src/ft_memcpy.c \
	src/ft_strchr.c \
	src/ft_strmapi.c \
	src/ft_toupper.c \
	src/ft_isprint.c \
	src/ft_memdel.c \
	src/ft_strclr.c \
	src/ft_strncat.c \
	src/ft_itoa.c \
	src/ft_memmove.c \
	src/ft_strcmp.c \
	src/ft_strncmp.c \
	src/ft_lstadd.c \
	src/ft_memset.c \
	src/ft_strcpy.c \
	src/ft_strncpy.c \
	src/ft_lstdel.c \
	src/ft_putchar.c \
	src/ft_strdel.c \
	src/ft_strnequ.c \
	src/ft_lstdelone.c \
	src/ft_putchar_fd.c \
	src/ft_strdup.c \
	src/ft_strnew.c \
	src/ft_squared.c \
	src/ft_inttohex.c \
	src/ft_pythagore.c \
	src/ft_hexatorgb.c \
	src/ft_rgbtohexa.c \
	src/ft_rgbftohexa.c \
	src/ft_degreetorad.c \
	src/ft_radtodegree.c \
	src/ft_fabs.c \
	src/mlibx_draw_pixel.c \
	src/mlibx_draw_pixel_line.c \
	src/mlibx_draw_pixel_line_float.c \
	src/mlibx_dot_in_window.c \
	src/mlibx_draw_dot.c \
	src/ft_hextoint.c \
	src/get_next_line.c \
	src/ft_check_fd.c \
	src/ft_rot_fabs.c
CFLAGS= -Wall -Werror -Wextra
SRCDIR= src
OBJDIR= obj
OBJ := $(SRC:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
CC= gcc

all:	$(NAME)

$(OBJ): $(OBJDIR)/%.o : $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)
	@echo "Compiled $(NAME) successfully!"

clean:
	@rm -rf $(OBJ)
	@echo "Fclean done successfully!"

fclean: clean
	@rm -f $(NAME)
	@echo "Clean done successfully!"

re: fclean all

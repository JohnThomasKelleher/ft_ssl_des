#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jkellehe <jkellehe@student.42.us.org>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/08/14 21:44:46 by jkellehe          #+#    #+#              #
#    Updated: 2018/11/27 19:18:25 by jkellehe         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = ft_ssl

SRC = main.c sha256.c sha512.c append.c init.c make_sk.c md5.c misc.c padders.c parse.c printers.c sub_parse.c sub_sha.c base64.c main_des.c acc_des.c pbkdf.c s_box.c s_box_init1.c s_box_init2.c pkcs7pad.c  handles.c des_printers.c acc_des2.c sliders.c des_keys.c base64_flippers.c base64_print.c handles2.c init2.c main2.c

LIB = libft

all:  $(NAME)

$(NAME):
	@make -C $(LIB)
	@gcc -Wextra -Werror -Wall -g -o $(NAME) $(SRC) libft/libft.a

clean:
	@make clean -C $(LIB)

fclean: clean
	@rm -f $(NAME)
	@make fclean -C $(LIB)

re: fclean all

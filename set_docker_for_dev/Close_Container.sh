# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Close_Container.sh                                 :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mdoquocb <mdoquocb@student.42quebec.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/02 19:49:40 by mdoquocb          #+#    #+#              #
#    Updated: 2023/04/02 19:53:26 by mdoquocb         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#!/bin/bash

make finish

rm /usr/local/bin/webserv
rm -rf /usr/local/bin/webserv; \
rm -rf /usr/local/etc/webserv; \
rm -rf/usr/local/var/www;
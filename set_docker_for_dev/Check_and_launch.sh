# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Check_and_launch.sh                                    :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mdoquocb <mdoquocb@student.42quebec.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/02 19:49:40 by mdoquocb          #+#    #+#              #
#    Updated: 2023/04/02 19:53:26 by mdoquocb         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#!/bin/bash

# Aller dans le répertoire du code source
cd webserv

# Récupérer les dernières modifications depuis la branche distante
git fetch origin

# Fusionner les modifications locales avec les dernières modifications de la branche distante
git merge origin/main

#compile project
make

#set file server
mv /Bin/webserv /usr/local/bin/; \
mv /for_etc/* /usr/local/etc/; \
mv /for_var/* /usr/local/var/; \

webserv

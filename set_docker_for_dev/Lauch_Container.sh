# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Launch_Container.sh                                :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mdoquocb <mdoquocb@student.42quebec.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/02 19:49:40 by mdoquocb          #+#    #+#              #
#    Updated: 2023/04/02 19:53:26 by mdoquocb         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#!/bin/bash

while true; do
    read -p "Enter path of local work directory : " directory
    if [ -z "${directory}" ] ; then
        echo "directory empty"
    else
        break
    fi
done

if docker images | grep -q websev:latest ; then \
  echo "Image already pull"
else
  echo "load image webserv:latest"
  ./Build_Container.sh
fi

docker container run --name webserv_dev -v ${directory}:/webserv webserv:latest

alias webserv_start="docker container start webserv"
alias webserv_stop="docker container stop webserv"
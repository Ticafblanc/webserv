# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    update_dockerhub.sh                                 :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mdoquocb <mdoquocb@student.42quebec.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/02 19:49:40 by mdoquocb          #+#    #+#              #
#    Updated: 2023/04/02 19:53:26 by mdoquocb         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#!/bin/bash

if docker images | grep -q ubuntu:latest ; then \
  echo "Image already pull"
else
  echo "load image webserv:latest"
  docker pull ticafblanc/webserv:latest
fi

while true; do
    read -p "Enter number of old version : " version
    if [ -z "${version}" ] ; then
        echo " need old version "
    else
        docker tag ticafblanc/webserv:latest ticafblanc/webserv:${version}
        docker push ticafblanc/webserv:${version}
        break
    fi
done

docker build -t ticafblanc/webserv:latest .

# update docker hub
docker push ticafblanc/webserv:latest

docker rmi ticafblanc/webserv:${version}
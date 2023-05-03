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

while true; do
    read -p "Enter your repo : " repo
    if git ls-remote "$repo" &> /dev/null; then
        break
    else
        echo "Invalide repo : $repo"
    fi
done

if docker images | grep -q ubuntu:latest ; then \
  echo "Image already pull"
else
  echo "load image ubunut:latest"
  docker pull ubuntu:latest
fi

read -p "Enter path of config content servre directory : " config
if [ -z "${config}" ] ; then
  docker build --build-arg repo_git=${repo} \
  -t webserv:latest .
else
  docker build --build-arg repo_git=${repo} \
    --build-arg path_to_config_content_sever=${config} \
    -t webserv:latest .
fi


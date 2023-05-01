# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Build_Container.sh                                 :+:      :+:    :+:    #
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
  echo "load image ubunut:latest"
  docker pull ubuntu:latest
fi

docker build -d webserv:latest .


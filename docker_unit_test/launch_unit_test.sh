# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    lanch_unit_test.sh                                 :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mdoquocb <mdoquocb@student.42quebec.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/02 19:49:40 by mdoquocb          #+#    #+#              #
#    Updated: 2023/04/02 19:53:26 by mdoquocb         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#!/bin/bash

#Check if the Ubuntu image exist
if docker images | grep -q ubuntu:latest ; then \
  echo "Image already pull"
else
  echo "load image ubunut:latest"
  docker pull ubuntu:latest
fi

#find path of dockerfile
SCRIPT_DIR="$(dirname "$(readlink -f "$0")")"

SOURCE_CODE_DIR="$(dirname "$(dirname "$(readlink -f "$0")")")"

#build image
docker build -t webserv_unit_test -f ${SCRIPT_DIR}/Dockerfile ${SOURCE_CODE_DIR}

#run write error and remove container
docker run --rm -it webserv_unit_test

#remove image after test
docker rmi webserv_unit_test
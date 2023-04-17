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

echo "write a represetory you want to load in your container"
read REPO
if [ -z "${REPO}"] ; then
  REPO="https://github.com/Ticafblanc/webserv.git"
fi

echo "name of container"
read NAME
if [ -z "${NAME}"] ; then
  NAME="webserv"
fi

echo "path of work directory"
read WORKDIR
if [ -z "${WORKDIR}"] ; then
  WORKDIR=$PWD
fi

if docker images | grep -q ubuntu:latest ; then
  echo "Image already pull"
else
  echo "load image ubuntu:latest"
  docker pull ubuntu:latest
fi

docker build -t webserv:latest -f webserv/set_docker/Dockerfile ${REPO}


#docker build -t clion/remote-cpp-env:0.5 .

alias dr='docker run --name ${NAME} -v ${WORKDIR}:/webserv_container/webserv webserv:latest'
alias webserv='docker exec -it ${NAME} /bin/bash'

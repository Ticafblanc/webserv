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
if docker images | grep -q ticafblanc/webserv-env-dev:latest ; then \
  echo "Image already pull"
else
  echo "load image ticafblanc/webserv-env-dev:latest"
  docker pull ticafblanc/webserv-env-dev:latest
fi

while true; do
    read -p "Enter number of old version : " version
    if [ -z "${version}" ] ; then
        echo " need old version "
    else
        docker tag ticafblanc/webserv-env-dev:latest ticafblanc/webserv-env-dev:${version}
        docker push ticafblanc/webserv-env-dev:${version}
        break
    fi
done

#find path of dockerfile
SCRIPT_DIR="$(dirname "$(readlink -f "$0")")"

SOURCE_CODE_DIR="$(dirname "${SCRIPT_DIR}")"

#build image update the number for each update
docker build -t ticafblanc/webserv-env-dev:latest -f ${SCRIPT_DIR}/Dockerfile ${SOURCE_CODE_DIR}

# update docker hub
docker push ticafblanc/webserv-env-dev:latest

docker rmi ticafblanc/webserv-env-dev:${version}



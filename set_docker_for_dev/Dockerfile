# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Dockerfile                                         :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mdoquocb <mdoquocb@student.42quebec.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/02 19:43:18 by mdoquocb          #+#    #+#              #
#    Updated: 2023/04/02 20:08:04 by mdoquocb         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# set image release  Ubuntu 20.04 LTS
FROM ubuntu:latest

#set macro of repo path and path to contant web site
ARG repo_git
ARG path_to_config_content_sever=config_content_server


# set a new docker
RUN apt-get update \
    && apt-get install -y \
    build-essential \
    gcc\
    g++\
    gdb\
    clang\
    cmake \
    rsync \
    tar \
    python3 \
    && apt-get clean

#define wrorkdir
WORKDIR /webserv

#copy repo
COPY . /webserv

#compile project
RUN cd /webserv \
    && cmake -S . -B build \
    && cmake --build build  \
    && cd build  \
    && ctest

# Exposition of port 80
EXPOSE 80

## Command to do at start
CMD [ "webserv" ]
#see at the end if need to share content

# Commande to update and launch the container
ENTRYPOINT ["/webserv/set_docker_for_dev/Check_and_launch.sh"]
# Command to do at close
CMD ["bash", "-c", "trap EXIT; ./webserv/set_docker_for_dev/Close_Container.sh"]


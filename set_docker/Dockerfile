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
    git \
    rsync \
    tar \
    python3 \
    && apt-get clean

#define wrorkdir
WORKDIR webserv

#clone repo
RUN git clone ${repo_git} .

#compile project
RUN cd /webserv \
    && make \
    && mv Bin/webserv /usr/local/bin/webserv \
    && mv ${path_to_config_content_sever}/for_etc/* /usr/local/etc/ \
    && mv ${path_to_config_content_sever}/for_var/* /usr/local/var/


# Exposition of port 80
EXPOSE 80

## Command to do at close
CMD [ "webserv" ]


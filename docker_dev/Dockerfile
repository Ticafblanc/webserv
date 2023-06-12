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

# set a new docker
RUN apt-get update \
    && apt-get install -y \
    sudo \
    build-essential \
    gcc\
    g++\
    gdb\
    clang\
    cmake \
    rsync \
    tar \
    python3 \
    valgrind \
    net-tools \
    curl \
    && apt-get clean \
    && useradd -m Ticablanc  \
    && echo 'Ticablanc ALL=(ALL) NOPASSWD:ALL' >> /etc/sudoers
#    && usermod -aG sudo Ticafblanc

USER Ticafblanc

EXPOSE 80 8080 8081
#-p 0.0.0.0:80:80

#set the webserv config content
COPY ../etc/ /usr/local/etc/

COPY ../var/ /usr/local/var/

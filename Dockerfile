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
FROM ubuntu:latest as baseUbuntu

# set env for compiler
ENV COMPILING_IN_CONTAINER=1

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

#define wrorkdir
WORKDIR /webserv

#copy repo
COPY . /webserv/
COPY /Docker_build/etc /usr/local/etc/
COPY /Docker_build/var /usr/local/var/

#compile project
RUN make && mv Bin/webserv /usr/local/bin/webserv

#allowed ports 1024 => 49151
EXPOSE 8080 8081 4242

CMD ["/bin/bash"]


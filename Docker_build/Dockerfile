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
    && apt-get clean

#define wrorkdir
WORKDIR /webserv

#copy repo
COPY .. /webserv/
COPY etc /usr/local/etc/
COPY var /usr/local/var/

#compile project
RUN make && mv Bin/webserv /usr/local/bin/webserv

FROM alpine:3.18

RUN	apk update && apk upgrade && apk add --no-cache

COPY etc /usr/local/etc/
COPY var /usr/local/var/

COPY --from=baseUbuntu /usr/local/bin/webserv /usr/local/bin/webserv


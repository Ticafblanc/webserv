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
RUN apt-get update  \
    && apt-get install -y ssh\
    build-essential \
    gcc\
    g++\
    gdb\
    clang\
    cmake \
    git \
    libboost-all-dev \
    libcurl4-openssl-dev \
    libssl-dev\
    rsync \
    tar \
    python \
    && apt-get clean

#creates a user for ide to use
RUN useradd -m user && yes password | passwd user



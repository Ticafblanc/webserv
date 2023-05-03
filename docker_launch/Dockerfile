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
COPY ../ /webserv/

#compile project
RUN make && mv Bin/webserv /usr/local/bin/webserv \
    && mv /webserv/config_content_server/for_etc/* /usr/local/etc/ \
    && mv config_content_server/for_var/* /usr/local/var/


# Exposition of port 80
EXPOSE 80

#launch test
CMD ["webserv"]



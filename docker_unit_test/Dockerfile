# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Dockerfile                                         :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jrossign <jrossign@student.42quebec.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/02 19:43:18 by mdoquocb          #+#    #+#              #
#    Updated: 2023/05/09 12:50:48 by jrossign         ###   ########.fr        #
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
RUN cmake -S . -B build \
    && cmake --build build


#launch test
CMD ["sh", "-c", "cd build && ctest --verbose --timeout 10"]
#CMD ["bash"]



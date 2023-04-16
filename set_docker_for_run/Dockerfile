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
FROM ubuntu:20.04

# set a new docker
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    git \
    libboost-all-dev \
    libcurl4-openssl-dev \
    libssl-dev

# clone project
RUN git clone https://github.com/Ticafblanc/webserv.git



# Compilation du projet Webserv
WORKDIR webserv
COPY . webserv
RUN make run

# Exposition du port 80
EXPOSE 80

# Commande pour démarrer le serveur
CMD ["./webserv", "webserv.conf"]#expand shell and of command
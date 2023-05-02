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
ARG repo_git=https://github.com/Ticafblanc/webserv.git


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
    install neovim \
    install zsh \
    && apt-get clean \
    && chsh -s /usr/bin/zsh \
    && git clone --depth 1 https://github.com/AstroNvim/AstroNvim ~/.config/nvim \

#creates a user for ide to use
RUN useradd -m user && yes password | passwd user

#set workdir
WORRKDIR webserv

#clone repo
RUN git clone repo_git .

# Exposition of port 80
EXPOSE 80

# Commande to update and launch the container
ENTRYPOINT ["/webserv/set_docker_for_dev/Check_and_launch.sh"]
# Command to do at close
CMD ["bash", "-c", "trap EXIT; ./webserv/set_docker_for_dev/Close_Container.sh"]


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
ARG path_to_config_content_sever=/config_content_server


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

#set at end of project and remove the close container and add monunt volume to link local path>>>

#compile project
#cd webserv
#RUN make

#set file server
#RUN mv /Bin/webserv /usr/local/bin/webserv; \
#RUN mv $TEST_DIRECTORY_CONTENT/for_etc/* /usr/local/etc/; \
#RUN mv $TEST_DIRECTORY_CONTENT/for_var/* /usr/local/var/; \


# Exposition of port 80
EXPOSE 80

# Commande to update and launch the container
ENTRYPOINT ["/webserv/set_docker/Check_and_launch.sh"]
# Command to do at close
CMD ["bash", "-c", "trap EXIT; ./webserv/set_docker/Close_Container.sh"]

#<<<

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserv.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoquocb <mdoquocb@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 16:23:33 by mdoquocb          #+#    #+#             */
/*   Updated: 2023/03/02 16:23:37 by mdoquocb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

extern char** environ;


#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>
//#include <sys/sendfile.h>
#include <sys/stat.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <sys/poll.h>

#define MAX_CLIENTS 100
#define PORT 8080

#ifndef WEBSERV_HPP
# define WEBSERV_HPP

#endif //WEBSERV_HPP
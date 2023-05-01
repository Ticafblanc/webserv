/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UTmain.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoquocb <mdoquocb@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 18:57:53 by mdoquocb          #+#    #+#             */
/*   Updated: 2023/03/02 18:57:57 by mdoquocb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/unit_test.hpp"
#include <sys/socket.h>

int unitTestInit()
{
    try {
        init("../../config_content_server/for_etc/webserv/nginx.conf");
    } catch (const std::exception & e) {
        e.what();
        return (TEST_FAIL);
    }
    return (TEST_PASS);
}

int unitTestGetter()
{
    std::string ip = "127.0.0.1";
    try {
		int port = 8081;
		std::vector<server> server_vec = init("../../config_content_server/for_etc/webserv/nginx.conf");
		std::vector<server>::iterator server_it = server_vec.begin();
		for(int i = 0; server_it != server_vec.end(); server_it++, i++, port++)
		{
            TEST_EQ(server_it->getDataServer().getIdServer(), i);
            TEST_EQ(server_it->getDataServer().getIpAddress(), ip);
            TEST_EQ(server_it->getDataServer().getPort(), port);
            TEST_EQ(server_it->getDataServer().getDomain(), AF_INET);
            TEST_EQ(server_it->getDataServer().getType(), SOCK_STREAM);
            TEST_EQ(server_it->getDataServer().getProtocol(), 0);
            TEST_EQ(server_it->getDataServer().getBacklog(), 10);
            TEST_EQ(server_it->getDataServer().getAddress().sin_family, server_it->getDataServer().getDomain());
            TEST_EQ(server_it->getDataServer().getAddress().sin_addr.s_addr, inet_addr(ip.c_str()));
            TEST_EQ(server_it->getDataServer().getAddress().sin_port, htons(port));
            TEST_EQ(server_it->getDataServer().getLevel(), SOL_SOCKET);
            TEST_EQ(server_it->getDataServer().getOptionName(), SO_REUSEADDR);
            TEST_EQ(server_it->getDataServer().getOptionVal(), 1);
		}
    }
    catch (const std::exception & e) {
        e.what();
        return (TEST_FAIL);
    }
    return (TEST_PASS);
}

int main() {
    TEST_EQ(unitTestInit(), TEST_PASS);
    TEST_EQ(unitTestGetter(), TEST_PASS);
    return (TEST_PASS);
}

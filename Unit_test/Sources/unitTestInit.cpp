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
        init("../config_content_server/for_etc/webserv/webserv.conf");
    } catch (const std::exception & e) {
        cerr << e.what() << endl;
        return (TEST_FAIL);
    }
    return (TEST_PASS);
}

int unitTestGetter()
{
    std::string ip = "127.0.0.1";
    try {
		int port = 8081;
		std::vector<server> server_vec = init("../config_content_server/for_etc/webserv/webserv.conf");
		std::vector<server>::iterator server_it = server_vec.begin();
		for(int i = 0; server_it != server_vec.end(); server_it++, i++, port++)
		{
            TEST_EQ(server_it->getDataServer().getIdServer(), i);
            vector<std::pair<string, int> > vecip = server_it->getDataServer().getHostPort();
            TEST_EQ(vecip[0].first, ip);
            TEST_EQ(vecip[0].second, port);
            TEST_EQ(server_it->getDataServer().getDomain(), AF_INET);
            TEST_EQ(server_it->getDataServer().getType(), SOCK_STREAM);
            TEST_EQ(server_it->getDataServer().getProtocol(), 0);
            TEST_EQ(server_it->getDataServer().getBacklog(), 10);
            TEST_EQ(server_it->getDataServer().getLevel(), SOL_SOCKET);
            TEST_EQ(server_it->getDataServer().getOptionName(), SO_REUSEADDR);
            TEST_EQ(server_it->getDataServer().getOptionVal(), 1);
		}
    }
    catch (const std::exception & e) {
        cerr << e.what() << endl;
        return (TEST_FAIL);
    }
    return (TEST_PASS);
}

int unitTestNServ() {
    try {
        Parser parser("../config_content_server/for_etc/webserv/testconfig2.conf");
        TEST_EQ(parser.getNServ(), 3);
    }
    catch (const std::exception& e) {
        cerr << e.what() << endl;
        return (TEST_FAIL);
    }
    return (TEST_PASS);
}

int unitTestParser() {
    try {
        Parser parser("../config_content_server/for_etc/webserv/testconfig.conf");
        vector<data_server> dataVec = parser.get_data();
        data_server data = dataVec.at(0);
        vector<std::pair<string, int> > hostPort = data.getHostPort();
        TEST_EQ(hostPort.size(), 1);
        TEST_EQ(hostPort.at(0).first, "127.0.0.1");
        TEST_EQ(hostPort.at(0).second, 8081);
        cout << "Unit Test hostPort passed" << endl;

        TEST_EQ(data.getServerName().size(), 1);
        TEST_EQ(data.getServerName().at(0), "Cyborgab");
        cout << "Unit Test servername passed" << endl;

        TEST_EQ(data.getMaxBodySize(), 80);
        cout << "Unit Test bodySize passed" << endl;

        vector<std::pair<vector<int>, string> > errors = data.getErrorPages();
        TEST_EQ(errors.size(), 3);
        TEST_EQ(errors.at(0).first.size(), 1);
        TEST_EQ(errors.at(1).first.size(), 1);
        TEST_EQ(errors.at(2).first.size(), 1);
        cout << "Unit Test errors size passed" << endl;

        TEST_EQ(errors.at(0).first.at(0), 404);
        TEST_EQ(errors.at(1).first.at(0), 413);
        TEST_EQ(errors.at(2).first.at(0), 420);
        cout << "Unit Test errors code passed" << endl;

        TEST_EQ(errors.at(0).second, "./resources/error/error404.html");
        TEST_EQ(errors.at(1).second, "./resources/error/error413.html");
        TEST_EQ(errors.at(2).second, "./resources/error/error420.html");
        cout << "Unit Test error url passed" << endl;
    }
    catch (const std::exception& e) {
        cerr << e.what() << endl;
        return (TEST_FAIL);
    }
    return (TEST_PASS);
}

int main() {
    TEST_EQ(unitTestInit(), TEST_PASS);
    cout << "Unit Test init passed" << endl;
    TEST_EQ(unitTestGetter(), TEST_PASS);
    cout << "Unit Test Getter passed" << endl;
    TEST_EQ(unitTestNServ(), TEST_PASS);
    cout << "Unit Test NServ passed" << endl;
    TEST_EQ(unitTestParser(), TEST_PASS);
    cout << "Unit Test Parser passed" << endl;

    return (TEST_PASS);
}

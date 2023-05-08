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

		vector<Route> routes = data.getRoutes();
		TEST_EQ(routes.at(0).getPrefix(), "/upload");
		TEST_EQ(routes.at(0).getRoot(), "./resources");
		cout << "Unit Test prefix & root passed" << endl;
		vector<std::pair<string, string> > cgi = routes.at(0).getCGI();
		TEST_EQ(cgi.at(0).first, ".php");
		TEST_EQ(cgi.at(0).second, "/usr/bin/php");
		TEST_EQ(cgi.at(1).first, ".py");
		TEST_EQ(cgi.at(1).second, "/usr/bin/python");
		TEST_EQ(cgi.at(2).first, ".pl");
		TEST_EQ(cgi.at(2).second, "/usr/bin/perl");
		cout << "Unit Test cgi passed" << endl;
		TEST_EQ(routes.at(0).getDirectoryListing(), true);
		TEST_EQ(routes.at(0).getUploadDir(), "./resources/upload/");
		cout << "Unit Test autoindex & upload passed" << endl;
		vector<string> allowed_methods = routes.at(0).getAllowedMethods();
		TEST_EQ(allowed_methods.size(), 3);
		TEST_EQ(allowed_methods.at(0), "GET");
		TEST_EQ(allowed_methods.at(1), "POST");
		TEST_EQ(allowed_methods.at(2),"DELETE");
		cout << "Unit Test route 1 passed" << endl;

		TEST_EQ(routes.at(1).getPrefix(), "/redirection");
		TEST_EQ(routes.at(1).getHttpRedir().first, "301");
		TEST_EQ(routes.at(1).getHttpRedir().second, "/");
		cout << "Unit Test route 2 passed" << endl;

		TEST_EQ(routes.at(2).getPrefix(), "/");
		TEST_EQ(routes.at(2).getRoot(), "./Cyborgab");
		TEST_EQ(routes.at(2).getIndex().size(), 1);
		TEST_EQ(routes.at(2).getIndex().at(0), "index.html");
		cout << "Unit Test route 3 passed" << endl;

		data = dataVec.at(1);
		hostPort = data.getHostPort();
		TEST_EQ(hostPort.size(), 1);
		TEST_EQ(hostPort.at(0).first, "127.0.0.1");
		TEST_EQ(hostPort.at(0).second, 4242);
		cout << "Unit Test hostPort passed" << endl;

		TEST_EQ(data.getServerName().size(), 1);
		TEST_EQ(data.getServerName().at(0), "website2");
		cout << "Unit Test servername passed" << endl;

		TEST_EQ(data.getMaxBodySize(), 500);
		cout << "Unit Test bodySize passed" << endl;

		errors = data.getErrorPages();
		TEST_EQ(errors.size(), 1);
		TEST_EQ(errors.at(0).first.size(), 1);
		cout << "Unit Test errors size passed" << endl;

		TEST_EQ(errors.at(0).first.at(0), 404);
		cout << "Unit Test errors code passed" << endl;

		TEST_EQ(errors.at(0).second, "./resources/error/error404.html");
		cout << "Unit Test error url passed" << endl;

		routes = data.getRoutes();
		TEST_EQ(routes.at(0).getPrefix(), "/");
		TEST_EQ(routes.at(0).getRoot(), "./resources");
		cout << "Unit Test prefix & root passed" << endl;
		TEST_EQ(routes.at(0).getIndex().size(), 1);
		TEST_EQ(routes.at(0).getIndex().at(0), "index2.html");
		cout << "Unit Test index passed" << endl;
		cgi = routes.at(0).getCGI();
		TEST_EQ(cgi.at(0).first, ".py");
		TEST_EQ(cgi.at(0).second, "/usr/bin/python");
		TEST_EQ(cgi.at(1).first, ".php");
		TEST_EQ(cgi.at(1).second, "/usr/bin/php");
		TEST_EQ(cgi.at(2).first, ".pl");
		TEST_EQ(cgi.at(2).second, "/usr/bin/perl");
		cout << "Unit Test cgi passed" << endl;
		TEST_EQ(routes.at(0).getDirectoryListing(), false);
		cout << "Unit Test autoindex passed" << endl;
		cout << "Unit Test route 1 passed" << endl;
		cout << "Unit Test server1 passed" << endl;

		data = dataVec.at(2);
		hostPort = data.getHostPort();
		TEST_EQ(hostPort.size(), 1);
		TEST_EQ(hostPort.at(0).first, "127.0.0.1");
		TEST_EQ(hostPort.at(0).second, 8081);
		cout << "Unit Test hostPort passed" << endl;

		TEST_EQ(data.getServerName().size(), 1);
		TEST_EQ(data.getServerName().at(0), "website3");
		cout << "Unit Test servername passed" << endl;

		TEST_EQ(data.getMaxBodySize(), 500);
		cout << "Unit Test bodySize passed" << endl;

		errors = data.getErrorPages();
		TEST_EQ(errors.size(), 1);
		TEST_EQ(errors.at(0).first.size(), 1);
		cout << "Unit Test errors size passed" << endl;

		TEST_EQ(errors.at(0).first.at(0), 404);
		cout << "Unit Test errors code passed" << endl;

		TEST_EQ(errors.at(0).second, "./resources/error/error404.html");
		cout << "Unit Test error url passed" << endl;

		routes = data.getRoutes();
		TEST_EQ(routes.at(0).getPrefix(), "/playa");
		TEST_EQ(routes.at(0).getRoot(), "./resources");
		TEST_EQ(routes.at(0).getIndex().size(), 1);
		TEST_EQ(routes.at(0).getIndex().at(0), "index.html");
		cout << "Unit Test route 1 passed" << endl;

		cgi = routes.at(0).getCGI();
		TEST_EQ(cgi.empty(), true);
		cout << "Unit Test cgi passed" << endl;
		TEST_EQ(routes.at(0).getDirectoryListing(), false);
		cout << "Unit Test autoindex passed" << endl;
		cout << "Unit Test route 1 passed" << endl;

		TEST_EQ(routes.at(1).getPrefix(), "/");
		TEST_EQ(routes.at(1).getRoot(), "./resources");
		cout << "Unit Test route 2 passed" << endl;
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

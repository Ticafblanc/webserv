/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Unit_test.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoquocb <mdoquocb@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 16:23:33 by mdoquocb          #+#    #+#             */
/*   Updated: 2023/03/02 16:23:37 by mdoquocb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/webserv.hpp"
#include "../../Include/data_server.class.hpp"

#ifndef UNIT_TEST_UNIT_TEST_HPP
# define UNIT_TEST_UNIT_TEST_HPP

#define TEST_FAIL -1
#define TEST_PASS 0

#define TEST int main()

#define TEST_EQ(x, y)		\
	if (x != y)				\
		return (TEST_FAIL);	\

#define TEST_NE(x, y)		\
	if (x == y)				\
		return (TEST_FAIL);	\

#define TEST_THROW(statement, exception_type) \
{										\
	try {								\
		statement();					\
	} catch (const exception_type& e) {	\
	}									\
}
#endif 

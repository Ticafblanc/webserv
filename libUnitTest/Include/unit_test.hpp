/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unit_test.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrossign <jrossign@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 16:23:33 by jrossign          #+#    #+#             */
/*   Updated: 2023/05/17 15:06:05 by jrossign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/webserv.hpp"
#include "../../Include/config_webserv.class.hpp"

#ifndef UNIT_TEST_UNIT_TEST_HPP
# define UNIT_TEST_UNIT_TEST_HPP

#define TEST_FAIL -1
#define TEST_PASS 0

#define TEST_EQ(x, y)								\
	if (x != y)										\
		return (TEST_FAIL);							\

#define TEST_NEQ(x, y)								\
	if (x == y)										\
		return (TEST_FAIL); 						\

#define EXPECT_THROW(statment, expected_exception)	\
	try {											\
		statment;									\
	}												\
	catch (const expected_exception & e) {			\
		return TEST_PASS;							\
	}												\
	catch (const std::exception & e) {				\
		return TEST_FAIL;							\
}													\
	return TEST_FAIL;								\

#endif 

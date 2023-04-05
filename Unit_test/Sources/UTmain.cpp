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

int main() {
    std::cout <<"====================[ Unit test ]===============================\n" <<std::endl;
    enum{constructor,}; // add enum for name of test
    int nbr = 1;//add number for each function
    int (*funcTester[nbr])(void);
    funcTester[constructor] = &construcor;
    std::cout <<"====================[ Start test ]==============================\n" <<std::endl;
    for (int i = 0; i < nbr; ++i) {
        if((*funcTester[i])() == -1){
            std::cout <<"===========[ Unit_test | Crash | test nbr "
            << nbr << " ]===================" <<std::endl;
            exit(EXIT_FAILURE);
        }
    }
    std::cout <<"\n================[ Unit_test | Success ]=========================" <<std::endl;
    exit(EXIT_SUCCESS);
}

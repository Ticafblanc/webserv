/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoquocb <mdoquocb@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 18:57:53 by mdoquocb          #+#    #+#             */
/*   Updated: 2023/03/02 18:57:57 by mdoquocb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/webserv.hpp"



int main(int argc, char **argv, char **envp){
    init(argv[]);
    if (argc == 1)
        minishell_loop(&envp);
    else if (argc > 1 && ft_strncmp(argv[1], "-c", 2) == 0)
        exit(execute(ft_strdup(argv[2]), &envp));

    exit(0);
}
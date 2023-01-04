/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   upper_bound.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: englot <englot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 20:19:38 by mleblanc          #+#    #+#             */
/*   Updated: 2023/01/04 17:55:46 by englot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map_prelude.hpp"

int main()
{
    SETUP;

    NAMESPACE::map<int, int> data;

    for (std::size_t i = 0; i < MAXSIZE / 2; ++i) {
        data.insert(NAMESPACE::make_pair(rand(), rand()));
    }

    timer t;

    for (int i = 0; i < 10000000; ++i) {
        NAMESPACE::map<int, int>::iterator it = data.upper_bound(rand());
        if (it != data.end()) {
            it->second = 64;
        }
    }

    PRINT_TIME(t);
}

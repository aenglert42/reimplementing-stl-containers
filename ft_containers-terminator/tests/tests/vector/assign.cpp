/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: englot <englot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 18:47:35 by mleblanc          #+#    #+#             */
/*   Updated: 2022/12/31 11:15:14 by englot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector_prelude.hpp"

void vec_test_assign()
{
    {
        charvector v;

        v.assign(0, 'c');

        CHECK_AND_PRINT_ALL(v);

        v.assign(64, 'A');

        CHECK_AND_PRINT_ALL(v);

        v.assign(32, '5');

        CHECK_AND_PRINT_ALL(v);

        v.assign(49, '8');

        CHECK_AND_PRINT_ALL(v);

        v.assign(77, '2');

        CHECK_AND_PRINT_ALL(v);
    }

    {
        strvector v;

        v.assign(0, "");

        CHECK_AND_PRINT_ALL(v);

        v.assign(64, "vector-string");

        CHECK_AND_PRINT_ALL(v);
    }
}

MAIN(vec_test_assign)

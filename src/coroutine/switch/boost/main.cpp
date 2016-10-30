/*!The Benchmark Testing Box 
 * 
 * Benchbox is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2.1 of the License, or
 * (at your option) any later version.
 * 
 * Benchbox is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public License
 * along with Benchbox; 
 * If not, see <a href="http://www.gnu.org/licenses/"> http://www.gnu.org/licenses/</a>
 * 
 * Copyright (C) 2016-2020, ruki All rights reserved.
 *
 * @author      ruki
 * @file        main.c
 *
 */

/* //////////////////////////////////////////////////////////////////////////////////////
 * includes
 */
#include "tbox/tbox.h"
#include <boost/coroutine/coroutine.hpp>

/* //////////////////////////////////////////////////////////////////////////////////////
 * macros
 */

// the switch count
#define COUNT       (10000000)

/* //////////////////////////////////////////////////////////////////////////////////////
 * types
 */

// the coroutine type
typedef boost::coroutines::symmetric_coroutine<tb_size_t>::call_type coroutine_t;

/* //////////////////////////////////////////////////////////////////////////////////////
 * implementaiton
 */
static tb_void_t switchtask(boost::coroutines::symmetric_coroutine<tb_size_t>::yield_type& yield)
{
    tb_size_t count = yield.get();
    while (count--) 
        yield(); 
}

/* //////////////////////////////////////////////////////////////////////////////////////
 * main
 */
tb_int_t main(tb_int_t argc, tb_char_t** argv)
{
    // init tbox
    if (!tb_init(tb_null, tb_null)) return -1;

    // get coroutine count
    tb_size_t cocount = argv[1]? tb_atoi(argv[1]) : 2;
    tb_assert_and_check_return_val(cocount > 1, -1);

    // make coroutines
    coroutine_t* coroutines = tb_nalloc0_type(cocount, coroutine_t);
    tb_assert_and_check_return_val(coroutines, -1);

    // init coroutines
    tb_size_t i = 0;
    for (i = 0; i < cocount; i++)
        new (coroutines + i) coroutine_t (switchtask);

    // init duration
    tb_hong_t duration = tb_mclock();

    // scheduling
    tb_size_t j = 0;
    tb_size_t n = COUNT / cocount;
    for (i = 0; i < n; i++)
        for (j = 0; j < cocount; j++)
            coroutines[j](n);

    // computing time
    duration = tb_mclock() - duration;

    // trace
    tb_trace_i("switch[%lu]: boost: %d switches in %lld ms, %lld switches per second", cocount, COUNT, duration, (((tb_hong_t)1000 * COUNT) / duration));

    // exit coroutines
    for (i = 0; i < cocount; i++)
        (coroutines + i)->~coroutine_t();
    tb_free(coroutines);

    // exit tbox
    tb_exit();

    // ok
    return 0;
}

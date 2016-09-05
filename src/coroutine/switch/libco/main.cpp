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
#include "libco/libco.h"

/* //////////////////////////////////////////////////////////////////////////////////////
 * macros
 */

// the switch count
#define COUNT       (10000000)

/* //////////////////////////////////////////////////////////////////////////////////////
 * implementaiton
 */
static tb_pointer_t switchtask(tb_pointer_t priv)
{
    // loop
    tb_size_t* pcount = (tb_size_t*)priv;
    while ((*pcount)--) co_yield_ct();
    return 0;
}

/* //////////////////////////////////////////////////////////////////////////////////////
 * main
 */
tb_int_t main(tb_int_t argc, tb_char_t** argv)
{
    // init tbox
    if (!tb_init(tb_null, tb_null)) return -1;

    // create coroutine
    stCoRoutine_t*  co1 = tb_null;
    stCoRoutine_t*  co2 = tb_null;
    tb_size_t       count1 = COUNT >> 1;
    tb_size_t       count2 = COUNT >> 1;
    co_create(&co1, tb_null, switchtask, &count1);
    co_create(&co2, tb_null, switchtask, &count2);

    // init duration
    tb_hong_t duration = tb_mclock();

    // scheduling
    while (count1 && count2)
    {
        co_resume(co1);
        co_resume(co2);
    }

    // computing time
    duration = tb_mclock() - duration;

    // trace
    tb_trace_i("switch: libco: %d switches in %lld ms, %lld switches per second", COUNT, duration, (((tb_hong_t)1000 * COUNT) / duration));

    // exit coroutine
    co_release(co1);
    co_release(co2);

    // exit tbox
    tb_exit();

    // ok
    return 0;
}

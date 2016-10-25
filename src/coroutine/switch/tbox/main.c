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

/* //////////////////////////////////////////////////////////////////////////////////////
 * macros
 */

// the switch count
#define COUNT       (10000000)

/* //////////////////////////////////////////////////////////////////////////////////////
 * implementaiton
 */
static tb_void_t switchtask(tb_cpointer_t priv)
{
    // loop
    tb_size_t count = (tb_size_t)priv;
    while (count--)
    {
        // yield
        tb_coroutine_yield();
    }
}

/* //////////////////////////////////////////////////////////////////////////////////////
 * main
 */
tb_int_t main(tb_int_t argc, tb_char_t** argv)
{
    // init tbox
    if (!tb_init(tb_null, tb_null)) return -1;

    // init scheduler
    tb_co_scheduler_ref_t scheduler = tb_co_scheduler_init();
    if (scheduler)
    {
        // start coroutine
        tb_coroutine_start(scheduler, switchtask, (tb_cpointer_t)(COUNT >> 1), 0);
        tb_coroutine_start(scheduler, switchtask, (tb_cpointer_t)(COUNT >> 1), 0);

        // init the start time
        tb_hong_t startime = tb_mclock();

        // run scheduler
        tb_co_scheduler_loop(scheduler, tb_true);

        // computing time
        tb_hong_t duration = tb_mclock() - startime;

        // trace
        tb_trace_i("switch: tbox: %d switches in %lld ms, %lld switches per second", COUNT, duration, (((tb_hong_t)1000 * COUNT) / duration));

        // exit scheduler
        tb_co_scheduler_exit(scheduler);
    }

    // exit tbox
    tb_exit();

    // ok
    return 0;
}

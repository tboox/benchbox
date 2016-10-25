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
#include "coroutine/coroutine.h"

/* //////////////////////////////////////////////////////////////////////////////////////
 * macros
 */

// the switch count
#define COUNT       (10000000)

/* //////////////////////////////////////////////////////////////////////////////////////
 * implementaiton
 */
static tb_void_t switchtask(struct schedule* scheduler, tb_pointer_t priv)
{
    // loop
    tb_size_t count = (tb_size_t)priv;
    while (count--) coroutine_yield(scheduler);
}

/* //////////////////////////////////////////////////////////////////////////////////////
 * main
 */
tb_int_t main(tb_int_t argc, tb_char_t** argv)
{
    // init tbox
    if (!tb_init(tb_null, tb_null)) return -1;

    // init schedule
    struct schedule* scheduler = coroutine_open();
    if (scheduler)
    {
        // init coroutine
        tb_int_t co1 = coroutine_new(scheduler, switchtask, (tb_pointer_t)(COUNT >> 1));
        tb_int_t co2 = coroutine_new(scheduler, switchtask, (tb_pointer_t)(COUNT >> 1));

        // init duration
        tb_hong_t duration = tb_mclock();

        // run scheduler
        while (coroutine_status(scheduler, co1) && coroutine_status(scheduler, co2))
        {
            coroutine_resume(scheduler, co1);
            coroutine_resume(scheduler, co2);
        }

        // computing time
        duration = tb_mclock() - duration;

        // trace
        tb_trace_i("switch: coroutine(cloudwu): %d switches in %lld ms, %lld switches per second", COUNT, duration, (((tb_hong_t)1000 * COUNT) / duration));

        // exit scheduler
        coroutine_close(scheduler);
    }

    // exit tbox
    tb_exit();

    // ok
    return 0;
}

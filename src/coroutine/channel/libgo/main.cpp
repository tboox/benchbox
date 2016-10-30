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
 * @file        main.cpp
 *
 */

/* //////////////////////////////////////////////////////////////////////////////////////
 * includes
 */
#include "tbox/tbox.h"
#include "libgo/libgo.h"

/* //////////////////////////////////////////////////////////////////////////////////////
 * macros
 */

// the channel count
#define COUNT       (10000000)

/* //////////////////////////////////////////////////////////////////////////////////////
 * implementaiton
 */
static tb_void_t channeltask_recv(co_chan<tb_size_t>& channel)
{
    // loop
    tb_size_t value;
    while (1) 
    {
        channel >> value;
        if (!value) break;
    }
}
static tb_void_t channeltask_send(co_chan<tb_size_t>& channel)
{
    // loop
    tb_size_t count = COUNT;
    while (count--) channel << count;
}

/* //////////////////////////////////////////////////////////////////////////////////////
 * main
 */
tb_int_t main(tb_int_t argc, tb_char_t** argv)
{
    // init tbox
    if (!tb_init(tb_null, tb_null)) return -1;

    // get channel buffer size
    tb_size_t size = argv[1]? tb_atoi(argv[1]) : 0;

    // init channel
    co_chan<tb_size_t> channel(size);

    // init duration
    tb_hong_t duration = tb_mclock();
   
    // scheduling
    go [&]{ channeltask_recv(channel); };
    go [&]{ channeltask_send(channel); };
    co_sched.RunUntilNoTask();

    // computing time
    duration = tb_mclock() - duration;

    // trace
    tb_trace_i("channel[%lu]: libgo(boost): %d passes in %lld ms, %lld passes per second", size, COUNT, duration, (((tb_hong_t)1000 * COUNT) / duration));

    // exit tbox
    tb_exit();

    // ok
    return 0;
}

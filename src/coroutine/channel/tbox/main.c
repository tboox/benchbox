/*!The Benchmark Testing Box 
 *
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 * 
 * Copyright (C) 2015 - 2017, TBOOX Open Source Group.
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

// the channel count
#define COUNT       (10000000)

/* //////////////////////////////////////////////////////////////////////////////////////
 * implementaiton
 */
static tb_void_t channeltask_send(tb_cpointer_t priv)
{
    // check
    tb_co_channel_ref_t channel = (tb_co_channel_ref_t)priv;

    // loop
    tb_size_t count = COUNT;
    while (count--) tb_co_channel_send(channel, (tb_cpointer_t)count);
}
static tb_void_t channeltask_recv(tb_cpointer_t priv)
{
    // check
    tb_co_channel_ref_t channel = (tb_co_channel_ref_t)priv;

    // loop
    tb_size_t count = COUNT;
    while (count--) tb_co_channel_recv(channel);
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

    // init scheduler
    tb_co_scheduler_ref_t scheduler = tb_co_scheduler_init();
    if (scheduler)
    {
        // init channel
        tb_co_channel_ref_t channel = tb_co_channel_init(size, tb_null, tb_null);
        tb_assert(channel);

        // start coroutine
        tb_coroutine_start(scheduler, channeltask_send, channel, 0);
        tb_coroutine_start(scheduler, channeltask_recv, channel, 0);

        // init the start time
        tb_hong_t startime = tb_mclock();

        // run scheduler
        tb_co_scheduler_loop(scheduler, tb_true);

        // computing time
        tb_hong_t duration = tb_mclock() - startime;

        // exit channel 
        tb_co_channel_exit(channel);

        // trace
        tb_trace_i("channel[%lu]: tbox: %d passes in %lld ms, %lld passes per second", size, COUNT, duration, (((tb_hong_t)1000 * COUNT) / duration));

        // exit scheduler
        tb_co_scheduler_exit(scheduler);
    }

    // exit tbox
    tb_exit();

    // ok
    return 0;
}

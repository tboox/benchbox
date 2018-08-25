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
 * @file        main.cpp
 *
 */

/* //////////////////////////////////////////////////////////////////////////////////////
 * includes
 */
#include "tbox/tbox.h"
#include "libgo/libgo.h"
#include <atomic>

/* //////////////////////////////////////////////////////////////////////////////////////
 * macros
 */

// the channel count
#define COUNT       (10000000)

/* //////////////////////////////////////////////////////////////////////////////////////
 * implementaiton
 */
std::atomic<int> gDone{0};

static tb_void_t channeltask_recv(co_chan<tb_size_t>& channel)
{
    // loop
    tb_size_t value;
    while (1) 
    {
        channel >> value;
        if (!value) break;
    }
    if (++gDone == 2) {
        co_sched.Stop();
    }
}
static tb_void_t channeltask_send(co_chan<tb_size_t>& channel)
{
    // loop
    tb_size_t count = COUNT;
    while (count--) channel << count;
    if (++gDone == 2) {
        co_sched.Stop();
    }
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
    co_sched.Start();

    // computing time
    duration = tb_mclock() - duration;

    // trace
    tb_trace_i("channel[%lu]: libgo(boost): %d passes in %lld ms, %lld passes per second", size, COUNT, duration, (((tb_hong_t)1000 * COUNT) / duration));

    // exit tbox
    tb_exit();

    // ok
    return 0;
}

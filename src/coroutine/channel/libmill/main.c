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
#ifndef asm
#   define asm __tb_asm__
#endif
#include "libmill.h"

/* //////////////////////////////////////////////////////////////////////////////////////
 * macros
 */

// the channel count
#define COUNT       (10000000)

/* //////////////////////////////////////////////////////////////////////////////////////
 * implementaiton
 */
static coroutine tb_void_t channeltask(chan channel)
{
    // loop
    tb_size_t value;
    while (1) value = chr(channel, tb_size_t);
    tb_used(&value);
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

    // make input and output passes
    chan channel = chmake(tb_size_t, size);

    // init duration
    tb_hong_t duration = tb_mclock();

    // create task
    tb_size_t count = COUNT;
    go(channeltask(channel));

    // scheduling
    while (count--) chs(channel, tb_size_t, count);

    // computing time
    duration = tb_mclock() - duration;

    // trace
    tb_trace_i("channel[%lu]: libmill: %d passes in %lld ms, %lld passes per second", size, COUNT, duration, (((tb_hong_t)1000 * COUNT) / duration));

    // exit tbox
    tb_exit();

    // ok
    return 0;
}

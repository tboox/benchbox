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

// the switch count
#define COUNT       (10000000)

/* //////////////////////////////////////////////////////////////////////////////////////
 * implementaiton
 */
static coroutine tb_void_t switchtask(tb_size_t count)
{
    // loop
    while (count--) yield();
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

    // init duration
    tb_hong_t duration = tb_mclock();

    // create task
    tb_size_t i = 0;
    for (i = 0; i < cocount - 1; i++)
        go(switchtask(COUNT / cocount));

    // scheduling
    switchtask(COUNT / cocount);

    // computing time
    duration = tb_mclock() - duration;

    // trace
    tb_trace_i("switch[%lu]: libmill: %d switches in %lld ms, %lld switches per second", cocount, COUNT, duration, (((tb_hong_t)1000 * COUNT) / duration));

    // exit tbox
    tb_exit();

    // ok
    return 0;
}

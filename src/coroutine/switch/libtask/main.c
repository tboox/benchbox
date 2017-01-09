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
#include "task.h"

/* //////////////////////////////////////////////////////////////////////////////////////
 * macros
 */

// the task stack size
#define STACK       (32768)

// the switch count
#define COUNT       (10000000)

/* //////////////////////////////////////////////////////////////////////////////////////
 * globals
 */

// the start time
static tb_hong_t g_startime = 0;

// the coroutine count
static tb_size_t g_cocount = 0;

/* //////////////////////////////////////////////////////////////////////////////////////
 * implementaiton
 */
static tb_void_t switchtask(tb_pointer_t priv)
{
    // loop
    tb_size_t count = (tb_size_t)priv;
    while (count--) taskyield();

    // computing time
    tb_hong_t duration = tb_mclock() - g_startime;

    // trace
    tb_trace_i("switch[%lu]: libtask: %d switches in %lld ms, %lld switches per second", g_cocount, COUNT, duration, (((tb_hong_t)1000 * COUNT) / duration));

    // exit all tasks
    taskexitall(0);

    // exit tbox
    tb_exit();
}

/* //////////////////////////////////////////////////////////////////////////////////////
 * main
 */
tb_void_t taskmain(tb_int_t argc, tb_char_t** argv)
{
    // init tbox
    if (!tb_init(tb_null, tb_null)) return ;

    // get coroutine count
    g_cocount = argv[1]? tb_atoi(argv[1]) : 2;
    tb_assert_and_check_return(g_cocount > 1);

    // create task
    tb_size_t i = 0;
    for (i = 0; i < g_cocount; i++)
        taskcreate(switchtask, (tb_pointer_t)(COUNT / g_cocount), STACK);

    // init start time
    g_startime = tb_mclock();
}

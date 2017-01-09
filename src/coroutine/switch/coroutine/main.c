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

    // get coroutine count
    tb_size_t cocount = argv[1]? tb_atoi(argv[1]) : 2;
    tb_assert_and_check_return_val(cocount > 1, -1);

    // init coroutines
    tb_int_t* coroutines = tb_nalloc0_type(cocount, tb_int_t);

    // init schedule
    struct schedule* scheduler = coroutine_open();
    if (scheduler && coroutines)
    {
        // init coroutines
        tb_size_t i = 0;
        for (i = 0; i < cocount; i++)
            coroutines[i] = coroutine_new(scheduler, switchtask, (tb_pointer_t)(COUNT / cocount));

        // init duration
        tb_hong_t duration = tb_mclock();

        // run scheduler
        tb_size_t count = COUNT / cocount;
        while (count--)
        {
            for (i = 0; i < cocount; i++)
                coroutine_resume(scheduler, coroutines[i]);
        }

        // computing time
        duration = tb_mclock() - duration;

        // trace
        tb_trace_i("switch[%lu]: coroutine(cloudwu): %d switches in %lld ms, %lld switches per second", cocount, COUNT, duration, (((tb_hong_t)1000 * COUNT) / duration));

        // exit scheduler
        coroutine_close(scheduler);
    }

    // exit coroutines
    if (coroutines) tb_free(coroutines);
    coroutines = tb_null;

    // exit tbox
    tb_exit();

    // ok
    return 0;
}

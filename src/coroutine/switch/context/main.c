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
static tb_void_t switchtask1(tb_context_from_t from)
{
    // check
    tb_context_ref_t* contexts = (tb_context_ref_t*)from.priv;
    tb_assert_and_check_return(contexts);

    // save main context
    contexts[0] = from.context;

    // jump to context2
    from.context = contexts[2];

    // loop
    __tb_volatile__ tb_size_t count = COUNT >> 1;
    while (count--)
    {
        // switch to the func2
        from = tb_context_jump(from.context, contexts);
    }

    // switch to the main function
    tb_context_jump(contexts[0], tb_null);
}
static tb_void_t switchtask2(tb_context_from_t from)
{
    // check
    tb_context_ref_t* contexts = (tb_context_ref_t*)from.priv;
    tb_assert_and_check_return(contexts);

    // loop
    __tb_volatile__ tb_size_t count = COUNT >> 1;
    while (count--)
    {
        // switch to the func1
        from = tb_context_jump(from.context, contexts);
    }

    // switch to the main function
    tb_context_jump(contexts[0], tb_null);
}

/* //////////////////////////////////////////////////////////////////////////////////////
 * main
 */
tb_int_t main(tb_int_t argc, tb_char_t** argv)
{
    // init tbox
    if (!tb_init(tb_null, tb_null)) return -1;

    // the stacks
    static tb_context_ref_t contexts[3];
    static tb_byte_t        stacks1[8192];
    static tb_byte_t        stacks2[8192];

    // make context1
    contexts[1] = tb_context_make(stacks1, sizeof(stacks1), switchtask1);

    // make context2
    contexts[2] = tb_context_make(stacks2, sizeof(stacks2), switchtask2);

    // init start time
    tb_hong_t startime = tb_mclock();

    // switch to func1
    tb_context_jump(contexts[1], contexts);

    // computing time
    tb_hong_t duration = tb_mclock() - startime;

    // trace
    tb_trace_i("switch: context(tbox): %d switches in %lld ms, %lld switches per second", COUNT, duration, (((tb_hong_t)1000 * COUNT) / duration));

    // exit tbox
    tb_exit();

    // ok
    return 0;
}

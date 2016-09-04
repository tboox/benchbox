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
#include "libfiber/libfiber.h"

/* //////////////////////////////////////////////////////////////////////////////////////
 * macros
 */

// the task stack size
#define STACK       (32768)

// the channel count
#define COUNT       (10000000)

/* //////////////////////////////////////////////////////////////////////////////////////
 * implementaiton
 */
static tb_void_t channeltask_recv(ACL_FIBER* fiber, tb_pointer_t priv)
{
    // loop
    ACL_CHANNEL* channel = (ACL_CHANNEL*)priv;
    while (1) acl_channel_recvul(channel);
}
static tb_void_t channeltask_send(ACL_FIBER* fiber, tb_pointer_t priv)
{
    // loop
    ACL_CHANNEL*    channel = (ACL_CHANNEL*)priv;
    tb_size_t       count = COUNT;
    while (count--) acl_channel_sendul(channel, count);
}

/* //////////////////////////////////////////////////////////////////////////////////////
 * main
 */
tb_int_t main(tb_int_t argc, tb_char_t** argv)
{
    // init tbox
    if (!tb_init(tb_null, tb_null)) return -1;

    // init channel
    ACL_CHANNEL* channel = acl_channel_create(sizeof(tb_size_t), 0);

    // create task
    acl_fiber_create(channeltask_recv, channel, STACK);
    acl_fiber_create(channeltask_send, channel, STACK);

    // init duration
    tb_hong_t duration = tb_mclock();
   
    // scheduling
    acl_fiber_schedule();

    // computing time
    duration = tb_mclock() - duration;

    // trace
    tb_trace_i("channel: libfiber: %d passes in %lld ms, %lld passes per second", COUNT, duration, (((tb_hong_t)1000 * COUNT) / duration));

    // exit channel
    acl_channel_free(channel);

    // exit tbox
    tb_exit();

    // ok
    return 0;
}

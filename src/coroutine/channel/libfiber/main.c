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
#include "acl/lib_fiber.h"

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

    // get channel buffer size
    tb_size_t size = argv[1]? tb_atoi(argv[1]) : 0;

    // init channel
    ACL_CHANNEL* channel = acl_channel_create(sizeof(tb_size_t), size);

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
    tb_trace_i("channel[%lu]: libfiber(acl): %d passes in %lld ms, %lld passes per second", size, COUNT, duration, (((tb_hong_t)1000 * COUNT) / duration));

    // exit channel
    acl_channel_free(channel);

    // exit tbox
    tb_exit();

    // ok
    return 0;
}

/* app_sim_scattered.c
 *
 * Test bare-metal boot-led-on application
 *
 * Copyright (C) 2014-2025 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#include "target.h"

#include "wolfboot/wolfboot.h"

#ifdef TARGET_sim


__attribute__((section(".r3text")))
int do_cmd(const char *cmd)
{
    /* Do nothing */
    return 0;
}

__attribute__((section(".r2text")))
int do_exec_cmd(char *name)
{
    return do_cmd(name);
}

__attribute__((section(".r1text")))
int main(int argc, char *argv[]) {
    do_exec_cmd((void *)0);
    return 0;
}
#endif /** TARGET_sim **/

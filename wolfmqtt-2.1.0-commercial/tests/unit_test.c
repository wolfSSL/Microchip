/* unit_test.c
 *
 * Copyright (C) 2006-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfMQTT.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

/* Main unit test runner for wolfMQTT */

#ifdef HAVE_CONFIG_H
    #include <config.h>
#endif

/* Define UNIT_TEST_IMPLEMENTATION to provide storage for global counters */
#define UNIT_TEST_IMPLEMENTATION
#include "tests/unit_test.h"

/* Declare test suite runners */
extern void run_framework_tests(void);
extern void run_mqtt_packet_tests(void);
extern void run_mqtt_client_tests(void);

int main(int argc, char** argv)
{
    (void)argc;
    (void)argv;

    TEST_RUNNER_BEGIN();

    run_framework_tests();
    run_mqtt_packet_tests();
    run_mqtt_client_tests();

    TEST_RUNNER_END();
}

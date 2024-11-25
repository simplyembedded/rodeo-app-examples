/**
 * \file main.c
 * \brief Rodeo IoT environmental sensor example application.
 *
 * \copyright Copyright (c) 2024 Simply Embedded Inc. All Rights Reserved.
 * 
 * This software is licensed under terms that can be found in the 
 * LICENSE file in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 */

#include "rodeo.h"
#include "sensor_message.h"
#include "drivers/bme688_driver.h"
#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>
#include <fcntl.h>
#include <inttypes.h>

LOG_LEVEL_INIT(LOG_LEVEL_INFO);

static void send_env_data(void);

int app_main(int argc, const char *argv[])
{
    (void)argc;
    (void)argv;

    /* Initialize the Rodeo subsystem */
    rodeo_init(ORG_NAME);

    /* Initialize the environmental sensor */
    bme688_init();
    
    while (1) {
        send_env_data();
        INFO("Example log %lld\n", (long long int) time(0));
        sleep(30);
    }

    return 0;
}

static void send_env_data(void)
{
    bme688_measurements_t env;
    bme688_get_measurements(&env);
    float envdata[4] = { env.gas_resistance, env.humidity, env.pressure, env.temperature};
    send_sensor_msg_float_array_by_id(SENSOR_ID_ENV, envdata, 4);
}

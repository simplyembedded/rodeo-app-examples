/**
 * \file main.c
 * \brief Rodeo IoT IR sensor example application.
 *
 * \copyright Copyright (c) 2024 Simply Embedded Inc. All Rights Reserved.
 * 
 * This software is licensed under terms that can be found in the 
 * LICENSE file in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 */

#include "rodeo.h"
#include "sensor_message.h"
#include "drivers/sths34pf80_driver.h"
#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>
#include <fcntl.h>
#include <inttypes.h>

LOG_LEVEL_INIT(LOG_LEVEL_INFO);

int app_main(int argc, const char *argv[])
{
    (void)argc;
    (void)argv;

    /* Initialize the Rodeo subsystem */
    rodeo_init(ORG_NAME);

    /* Initialize the environmental sensor */
    sths34pf80_init();
    
    while (1) {
        bool presence = false;
        if (sths34pf80_get_presence(&presence) == 0) {
            printf("Object detected\n");
        }
        sleep(1);
    }

    return 0;
}


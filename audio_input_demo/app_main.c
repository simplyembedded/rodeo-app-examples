/**
 * \file main.c
 * \brief Rodeo IoT audio input example application.
 *
 * \copyright Copyright (c) 2024 Simply Embedded Inc. All Rights Reserved.
 * 
 * This software is licensed under terms that can be found in the 
 * LICENSE file in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 */

#include "rodeo.h"
#include "sensor_message.h"
#include "drivers/sai_driver.h"
#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>
#include <fcntl.h>
#include <inttypes.h>

LOG_LEVEL_INIT(LOG_LEVEL_INFO);

static uint8_t _samples[4096];

int app_main(int argc, const char *argv[])
{
    (void)argc;
    (void)argv;

    /* Initialize the Rodeo subsystem */
    rodeo_init(ORG_NAME);

    /* Initialize the audio driver */
    sai_init();
    
    while (1) {
        if (sai_input(_samples, sizeof(_samples)) == 0) {
            /* TODO run an FFT on the samples to obtain the amplitude */
        }
    }

    return 0;
}

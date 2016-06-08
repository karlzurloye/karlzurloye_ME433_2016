#ifndef _IMU_H
#define _IMU_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include "system_config.h"
#include "system_definitions.h"
#include "mouse.h"

void initIMU();
void readIMU(char regstr, unsigned char* data, char length);

#endif
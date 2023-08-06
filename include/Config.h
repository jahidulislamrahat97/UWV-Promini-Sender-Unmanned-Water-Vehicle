#ifndef CONFIG_H
#define CONFIG_H

#include<Arduino.h>


#define DEBUG                                   1
#define CODE_UPLOAD                             1
#define NRF_ID                                  "2209110000" //Year-Month-Date-ID

#define JOYSTICK_X_SPEED_PIN                    A0
#define JOYSTICK_Y_RUDDER_PIN                   A1
#define ARM_SWITCH_PIN                          3
#define MODE_SWITCH_PIN                         2

#define MAX_RUDDER_ANGLE_LEFT                   120
#define MAX_RUDDER_ANGLE_RIGHT                  90
#define RUDDER_ANGLE_CENTER                     105
#define MIN_UWV_SPEED                           12
#define MAX_UWV_SPEED                           35




#endif // !CONFIG_H
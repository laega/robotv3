#ifndef EVENT_H
#define EVENT_H

#include "robot.h"

typedef struct {
    SensorsState sensorState;
    Speed speed;
} Event;

#endif /* EVENT_H */

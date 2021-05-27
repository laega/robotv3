#include "logger.h"
#include <string.h>

static void Logger_appendEvent (Logger* this) {
    if (this->eventsCounter == MAX_NB_OF_EVENTS) PProseError("Out of bounds exception");

    Event* event = (Event*) malloc(sizeof(Event));
    if(event == NULL) PProseError("Cannot allocate memory");

    event->sensorState = Robot_getSensorsState(this->robot);
    event->speed = Robot_getRobotSpeed(this->robot);

    this->events[this->eventsCounter++] = event;
}

Logger* Logger_new(Robot* robot) {
    Logger* this = (Logger*) malloc(sizeof(Logger));

	if (this == NULL) PProseError("Cannot initiate pilot");
    this->eventsCounter = 0;
    this->robot = robot;
    this->watchdog = Watchdog_new(0, 250000000, (WatchdogCallback)Logger_appendEvent, this);

	return this;
}

void Logger_free(Logger* this) {
    Logger_clearEvents(this);
    Watchdog_free(this->watchdog);
    free(this);
}

void Logger_startPolling(Logger* this) {
    Watchdog_start(this->watchdog);
}
void Logger_stopPolling(Logger* this) {
    Watchdog_cancel(this->watchdog);
}

Event** Logger_getEvents(Logger* this, int from, int to) {
    if (to > this->eventsCounter || to < from)
        PProseError("Illegal argument value");

    size_t size = sizeof(Event*) * (to - from);
    Event** returnPnt = (Event**) malloc(size + 1);
    if (returnPnt == NULL) PProseError("Cannot allocate memory");
    memcpy(returnPnt, &this->events[from], size);
    returnPnt[size] = NULL;
    return returnPnt;
}
int Logger_getEventsCount(Logger* this) {
    return this->eventsCounter;
}
void Logger_clearEvents(Logger* this) {
    while (this->eventsCounter > 0) {
        free(this->events[--this->eventsCounter]);
    }
}

void Logger_signalES(Logger* this, _Bool signalVal) {
    // TODO
}

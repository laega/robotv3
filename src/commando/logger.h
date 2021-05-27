#ifndef LOGGER_H
#define LOGGER_H

#include "event.h"

#define MAX_NB_OF_EVENTS 999

typedef struct {
    Event*[MAX_NB_OF_EVENTS] events;
    int eventsCounter;
    Robot* robot;
    Watchdog* watchdog;
} Logger;

extern Logger* Logger_new(Robot*);

extern void Logger_free(Logger*);

extern void Logger_startPolling(Logger*);
extern void Logger_stopPolling(Logger*);
extern Event** Logger_getEvents(Logger*, int, int);
extern int Logger_getEventsCount(Logger*);
extern void Logger_clearEvents(Logger*);
extern void Logger_signalES(Logger*, _Bool);

#endif /* LOGGER_H */

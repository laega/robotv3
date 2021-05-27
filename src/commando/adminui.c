
#include "adminui.h"

typedef enum {
    MAIN_SCREEN,
    LOG_SCREEN
} Screen;

static void AdminUI_displayScreen(AdminUI* this, Screen id) {
    Event* event;
    char hasBumpedStr[] = "yes";
    char noBumpStr[] = "no";
    switch (id) {
        case MAIN_SCREEN:
            printf("Main screen\n");
            // TODO
        break;

        case LOG_SCREEN:
            printf("Log screen\n");
            for(int i = 0; this->events[i] != NULL; i++) {
                event = this->events[i];
                printf("Robot speed: %d, luminosity: %f, collision: %s\n", event->speed, event->sensorState.luminosity, event->sensorState.collision == BUMPED ? hasBumpedStr : noBumpStr);
            }
        break;

        default:
        PProseError("Illegal invocation");
    }
}
static void AdminUI_updateEvents(AdminUI* this) {
    this->currentEventNumber = Logger_getEventsCount(this->logger);

    if (this->events != NULL) free(this->events);
    this->events = Logger_getEvents(this->logger, this->previousEventNumber,this->currentEventNumber);

    this->previousEventNumber = this->currentEventNumber;
}

static void AdminUI_logScreen(AdminUI* this) {
    Watchdog_start(this->watchdog);
    AdminUI_updateEvents(this);
    AdminUI_displayScreen(this, LOG_SCREEN);
}

AdminUI* AdminUI_new(Logger* logger, Pilot* pilot) {
    AdminUI* this = (AdminUI*) malloc(sizeof(AdminUI));
	if (this == NULL) PProseError("Cannot initiate AdminUI");

    this->previousEventNumber = this->currentEventNumber = 0;
    this->events = NULL;
    this->logger = logger;
    this->pilot = pilot;
    this->watchdog = Watchdog_new(1, 0, (WatchdogCallback)AdminUI_logScreen, this);

	return this;
}
void AdminUI_free(AdminUI* this) {
    if (this->events != NULL) free(this->events);
    Watchdog_free(this->watchdog);
    free(this);
}

void AdminUI_start(AdminUI* this) {
    this->previousEventNumber = this->currentEventNumber = 0;

    AdminUI_displayScreen(this, MAIN_SCREEN);
}
void AdminUI_stop(AdminUI* this) {
    AdminUI_quit(this);
}
void AdminUI_quit(AdminUI* this) {
    Logger_stopPolling(this->logger);
    Watchdog_cancel(this->watchdog);
}
void AdminUI_toggleEmergencyStop(AdminUI* this) {
    Pilot_toggleES(this->pilot);
}
void AdminUI_clearLog(AdminUI* this) {
    Logger_clearEvents(this->logger);
    if (this->events != NULL) {
        free(this->events);
        this->events = NULL;
    }
    this->previousEventNumber = this->currentEventNumber = 0;
}
void AdminUI_goScreenLog(AdminUI* this) {
    AdminUI_logScreen(this);
}
void AdminUI_backMainSreen(AdminUI* this) {
    AdminUI_displayScreen(this, MAIN_SCREEN);
}


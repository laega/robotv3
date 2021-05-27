
#include "adminui.h"

typedef enum {
    MAIN_SCREEN,
    LOG_SCREEN
} Screen;

static void AdminUI_displayScreen(AdminUI* this, Screen id) {
    // TODO
}
static void AdminUI_updateEvents(AdminUI* this) {
    this->currentEventNumber = Logger_getEventsCount(this->logger);
    this->events = Logger_getEvents(this->logger, this->previousEventNumber,this->currentEventNumber);
    this->previousEventNumber = this->currentEventNumber;
}

static void AdminUI_logScreen() {
    AdminUI_updateEvents(this);
    AdminUI_displayScreen(this, LOG_SCREEN);
}

extern AdminUI* AdminUI_new(Pilot* pilot, Logger* logger) {
    AdminUI* this = (AdminUI*) malloc(sizeof(AdminUI));
	if (this == NULL) PProseError("Cannot initiate AdminUI");

    this->previousEventNumber = this->currentEventNumber = 0;
    this->pilot = pilot;
    this->logger = logger;
    this->watchdog = Watchdog_new(1, 0, (WatchdogCallback)AdminUI_logScreen, this);

	return this;
}
extern void AdminUI_free(AdminUI*) {
    free(this);
}

extern void AdminUI_start(AdminUI*);
extern void AdminUI_stop(AdminUI*);
extern void AdminUI_quit(AdminUI*);
extern void AdminUI_toggleEmergencyStop(AdminUI*) {
    Pilot_toggleES(this->pilot);
}
extern void AdminUI_clearLog(AdminUI*);
extern void AdminUI_goScreenLog(AdminUI*);
extern void AdminUI_backMainSreen(AdminUI*);

#endif /* ADMINUI_H */


#ifndef ADMINUI_H
#define ADMINUI_H

typedef struct {
    int currentEventNumber;
    int previousEventNumber;
    Event*[] events;

    Pilot* pilot;
    Logger* logger;
    Watchdog* watchdog;
} AdminUI;


extern AdminUI* AdminUI_new(Pilot*, Logger*);
extern void AdminUI_free(AdminUI*);
extern void AdminUI_start(AdminUI*);
extern void AdminUI_stop(AdminUI*);
extern void AdminUI_quit(AdminUI*);
extern void AdminUI_toggleEmergencyStop(AdminUI*);
extern void AdminUI_clearLog(AdminUI*);
extern void AdminUI_goScreenLog(AdminUI*);
extern void AdminUI_backMainSreen(AdminUI*);

#endif /* ADMINUI_H */

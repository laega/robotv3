#include "adminui.h"
#include "logger.h"
#include "pilot.h"
#include "robot.h"

/**
 * Fonction Main de Robot_Commando
 *
 * @brief Initialise et démarre le serveur
 */
int main (int argc, char *argv[])
{
	Robot* robot = Robot_new();
	Logger* logger = Logger_new(robot);
	Pilot* pilot = Pilot_new(logger, robot);
	AdminUI* adminUI = AdminUI_new(logger, pilot);

	AdminUI_free(adminUI);
	Pilot_free(pilot);
	Logger_free(logger);
	Robot_free(robot);
	return 0;
}

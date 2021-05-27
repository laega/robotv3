#include "server.h"
#include "pilot.h"

/**
 * Fonction Main de Robot_Commando
 *
 * @brief Initialise et démarre le serveur
 */
int main (int argc, char *argv[])
{
    Server* server = Server_new(Pilot_new());
	Server_start(server);
	Server_stop(server);
	Server_free(server);
	return 0;
}

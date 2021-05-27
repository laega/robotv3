#ifndef SERVER_H
#define SERVER_H

#include <sys/types.h>
#include <sys/socket.h>

#include "commun.h"
#include "pilot.h"

typedef struct
{
    int socket;
    Pilot* pilot;

} Server;

/**
 * Fontion New Server
 *
 * @brief Initialise l'objet Server en mémoire
 */
extern Server* Server_new (Pilot*);

/**
 * Fontion Start Server
 *
 * @brief Démarre Server
 */
extern void Server_start (Server*);

/**
 * Fontion Stop Server
 *
 * @brief Arrête Server
 */
extern void Server_stop (Server*);

/**
 * Fontion Free Server
 *
 * @brief Détruit l'objet Server de la mémoire
 */
extern void Server_free (Server*);

#endif /* SERVER_H */




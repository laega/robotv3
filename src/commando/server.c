#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>
#include <netinet/in.h>
#include "server.h"

#define MAX_CONNECTION 3


static struct sockaddr_in address;

/**
 * Fonction New Server
 *
 * @brief Initialise l'object Server en mémoire
 */
Server* Server_new (Pilot* pilot) {
    Server* this = (Server *) malloc(sizeof(Server));

    address.sin_family = AF_INET; 
    address.sin_addr.s_addr = INADDR_ANY; 
    address.sin_port = htons( PORT );

    this->pilot=pilot;

    return this;
}

/**
 * Fonction Free Server
 *
 * @brief Détruit l'object Server de la mémoire
 */
void Server_free (Server *this) {
    free(this);
}

/**
 * Fonction Start Server
 *
 * @brief Démarre le Server 
 */
void Server_start (Server *this) {
   if ((this->socket = socket (AF_INET, SOCK_STREAM, 0)) == 0){
       PProseError("Socket creation failed");
   }

    if (bind(this->socket, (struct sockaddr *)&address, sizeof(address))<0) {
        PProseError("Failed to bind");
    }                                

    if (listen(this->socket, MAX_CONNECTION) < 0){
        PProseError("Cannot listen (max connection exceeded?)");
    }
}

/**
 * Fonction Stop Server
 *
 * @brief Arrête le Server 
 */
void Server_stop(Server* this) {
    if(close(this->socket) != 0){
        PProseError("Failed to close the connection");
    }
}

/**
 * Fontion Send Message Server
 *
 * @brief Renvoie l'état du pilot au client
 */
ssize_t Server_sendMsg(Server* this, PilotState msg) {
    return send(this->socket , &msg , sizeof(msg) , 0 );
}

/**
 * Fontion Read Message Server
 *
 * @brief Reçoit un message de client et agit en fonction de ce qu'on lui demande
 */
void Server_readMsg (Server* this, Message* msg) {
    int new_socket;
    if ((new_socket = accept(this->socket, NULL, 0))<0){
        PProseError("Cannot accept");
    }
    if (read(new_socket, msg, sizeof(Message))==-1){
        PProseError("there is no message");
    }
    switch (msg->event){
        case CHECK:
            Pilot_check(this->pilot);
            Server_sendMsg(this, Pilot_getState(this->pilot));
            break;
        case SET_VEL:
            Pilot_setVelocity(this->pilot, msg->vel);
            break;
        default:
            break;
    }
}

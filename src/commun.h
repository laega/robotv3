#ifndef COMMUN_H
#define COMMUN_H

#define PORT (12345)

/**
 * Définition des évenements possibles
 *
 * @brief énumération des différents évenements possible
 */
// typedef enum {START, SET_VEL, CHECK, STOP_PILOT, FREE} Event;
typedef enum {LEFT=0, RIGHT, FORWARD, BACKWARD, STOP} Direction;
/**
 * Structure du Velocity Vectir
 *
 * @brief Définition de Velocity
 */
typedef struct
{
    Direction dir;
    int power;
} VelocityVector;

/**
 * Structure du Pilotage
 *
 * @brief Définition de PilotState
 */
typedef struct
{
    int speed;
    _Bool collision;
    float luminosity;
} PilotState;

/**
 * Structure de Message
 *
 * @brief Le message a transmettre peut être un Event ou un VelocityVector
 */
typedef struct
{
  // Event event;
  VelocityVector vel;
} Message;

#endif /* __COMMON_H */
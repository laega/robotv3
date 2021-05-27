/* -*- mode: c; c-basic-offset: 4; indent-tabs-mode: nil -*- */  

#include "pilot.h"

#include <stdlib.h>
#include <stdio.h>

/**
 * Fonction sendMvt Pilot
 *
 * @brief Met à jour velocity en fonction de la direction demandée
 *
 * @return _Bool
 */
static void Pilot_sendMvt(Pilot* this)
{
	switch (this->vel.dir)
	{
		case (LEFT) :
			Robot_setWheelsVelocity(this->robot, 0, this->vel.power);
			break;
		case (RIGHT) :
			Robot_setWheelsVelocity(this->robot, this->vel.power, 0);
			break;
		case (FORWARD) :
			Robot_setWheelsVelocity(this->robot, this->vel.power, this->vel.power);
			break;
		case (BACKWARD) :
			Robot_setWheelsVelocity(this->robot, this->vel.power, this->vel.power);
			break;
		default :
			Robot_setWheelsVelocity(this->robot, 0, 0);
	}
}

/**
 * Fonction Start Pilot
 *
 * @brief Démarre le robot et le pilotage
 */
static void Pilot_start(Pilot* this){
	this->etat = NORMAL_IDLE;
	this->vel = (VelocityVector) {STOP,0};

	/*Initialisation robot*/
	Pilot_sendMvt(this);
}

/**
 * Fonction HasBumped Pilot
 *
 * @brief Met à jour l'état des capteurs et renvoie "true" s'il a rencontré un obstacle
 *
 * @return _Bool
 */
static _Bool Pilot_hasBumped(Pilot* this)
{
	return Robot_getSensorsState(this->robot).collision;
}

static void Pilot_choice(Pilot* this) {
	if (Pilot_hasBumped(this)) {
		this->etat = NORMAL_IDLE;
		this->vel.dir = STOP;
		Pilot_sendMvt(this);
	} else {
		Watchdog_start(this->watchdog);
	}
}

/**
 * Fonction New Pilot
 *
 * @brief Initialise l'objet Pilot en mémoire
 */
Pilot* Pilot_new(Logger* logger, Robot* robot){
	Pilot* this = (Pilot*) malloc(sizeof(Pilot));

	if (this == NULL) PProseError("Cannot initiate pilot");

	this->logger = logger;
	this->robot = robot;
	this->watchdog = Watchdog_new(1, 0, (WatchdogCallback) Pilot_choice, this);

	Pilot_start(this);

	return this;
}

/**
 * Fonction Free Pilot
 *
 * @brief Détruit l'objet Pilot de la mémoire
 */
void Pilot_free(Pilot* this){
	Watchdog_free(this->watchdog);
	free(this);
}

/**
 * Mutateur setVelocity Pilot
 *
 * @brief Change velocity
 * @param vel
 */
void Pilot_setVelocity(Pilot* this, VelocityVector vel)
{
	switch (this->etat) {
		case NORMAL_IDLE:
			this->etat = NORMAL_RUNNING;
			this->vel = vel;
			Pilot_sendMvt(this);
			Watchdog_start(this->watchdog);
		break;

		case NORMAL_RUNNING:
			this->vel = vel;
			Pilot_sendMvt(this);
			if (vel.dir == STOP) {
				this->etat = NORMAL_IDLE;
				Watchdog_cancel(this->watchdog);
			}

		default: 
			PProseError("Illegal invocation");
	}
}

void Pilot_toggleES(Pilot* this) {
	switch (this->etat) {
		case NORMAL_RUNNING:
			Watchdog_cancel(this->watchdog);
		case NORMAL_IDLE:
			this->etat = EMERGENCY;
			Logger_signalES(this->logger, TRUE);
			this->vel.dir = STOP;
			Pilot_sendMvt(this);
		break;

		case EMERGENCY:
			this->etat = NORMAL_IDLE;
			Logger_signalES(this->logger, FALSE);
		break;

		default: PProseError("Illegal invocation");
	}
}

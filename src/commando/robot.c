/* -*- mode: c; c-basic-offset: 4; indent-tabs-mode: nil -*- */  

#include "robot.h"

/**
 * Fonction New Robot
 *
 * @brief Initialise l'object Robot en mémoire
 */
Robot* Robot_new(){
	return (Robot *) malloc(sizeof(Robot));
}

/**
 * Fonction Free Robot
 *
 * @brief Détruit l'object Robot de la mémoire
 */
void Robot_free(Robot* rbt){
	free(rbt);
}

/**
 * Fonction Start Robot
 *
 * @brief Démarre le robot (initialise la communication et ouvre le port)
 */
void Robot_start(Robot* rbt){
	/* Initialisation des moteurs. */
	rbt-> mD = Motor_open(MA);
	if (rbt-> mD == NULL) PProseError("Problème d'ouverture du moteur droit (port MA)");

	rbt->mG = Motor_open(MD);
	if (rbt-> mG == NULL) PProseError("Problème d'ouverture du moteur gauche (port MD)");

	/*Initialisation des capteurs. */
	rbt -> sensorLight = LightSensor_open(S1);
	if (rbt-> sensorLight == NULL) PProseError("Problème d'ouverture du capteur de lumiere (port S1)");

	rbt -> sensorFront = ContactSensor_open(S3);
	if (rbt-> sensorFront == NULL) PProseError("Problème d'ouverture du capteur de sensorFront (port S3)");

	rbt -> sensorFloor = ContactSensor_open(S2);
	if (rbt-> sensorFloor == NULL) PProseError("Problème d'ouverture du capteur de sensorFloor (port S2)");

}

/**
 * Fonction Stop Robot
 *
 * @brief Arrête le robot (arrête la communication et ferme le port)
 */
void Robot_stop(Robot* rbt){
	/* fermeture des ports des moteurs. */

	if (Motor_close(rbt->mD) == -1) PProseError("Problème de fermeture du moteur droit (port MA)");

	if (Motor_close(rbt->mG) == -1) PProseError("Problème de fermeture du moteur gauche (port MD)");

	/*fermeture des ports des capteurs. */
	if (LightSensor_close(rbt -> sensorLight) == -1) PProseError("Problème de fermeture du capteur de lumiere (port S1)");

	if (ContactSensor_close(rbt -> sensorFront) == -1) PProseError("Problème de fermeture du capteur de sensorFront (port S3)");

	if (ContactSensor_close(rbt -> sensorFloor) == -1) PProseError("Problème de fermeture du capteur de sensorFloor (port S2)");
}

/**
 * Accesseur getRobotSpeed Robot
 *
 * @brief retourne la vitesse du robot (moyenne positive de la puissance instantannée de la roue droite et de la gauche)
 *
 * @return vitesse du robot (valeur entre 0 et 100)
 */
int Robot_getRobotSpeed(Robot* rbt){
	/*moteur droit*/
	Cmd CmdD = Motor_getCmd(rbt -> mD);
	if (CmdD == E_GCMD){
		PProseError("Problème lors de la récupération de la vitesse du Moteur Droit");
		CmdD = 0;
	}
	/*moteur gauche*/
	Cmd CmdG = Motor_getCmd(rbt -> mG);
	if (CmdG == E_GCMD){
		PProseError("Problème lors de la récupération de la vitesse du Moteur Gauche");
		CmdG = 0;
	}
	/*valeur absolue de la moyenne pour obtenir une valeur positive*/
	return abs((CmdD+CmdG)/2);
}

/**
 * Accesseur getSensorState Robot
 *
 * @brief Retourne l'état des capteurs Frontal, Au sol et de Lumière
 *
 * @return SensorsState
 */
SensorsState Robot_getSensorsState(Robot* rbt){
	Collision col;
	if ( ContactSensor_getStatus(rbt-> sensorFront) == (PRESSED || ERROR) || ContactSensor_getStatus(rbt -> sensorFloor) == (PRESSED || ERROR))
		col = BUMPED;
	else
		col = 0;
	SensorsState sensor = {col,(float) LightSensor_getStatus(rbt -> sensorLight)};
	return sensor;
}

/**
 * Mutateur setWheelsVelocity Robot
 *
 * @brief Change la puissance des roues du Robot
 *
 * @param int: puissance envoyée au moteur droit , valeur comprise entre (-100, 100).
 * @param int: puissance envoyée au moteur gauche, valeur comprise entre (-100, 100).
 */
void Robot_setWheelsVelocity(Robot* rbt, int mr, int ml){
	if (Motor_setCmd(rbt -> mD, mr)==-1)
		PProseError("Problème lors de la transmission de la commande au mD");
	if (Motor_setCmd(rbt -> mG, ml)==-1)
		PProseError("Problème lors de la transmission de la commande au mG");

}

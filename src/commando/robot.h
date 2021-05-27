/* -*- mode: c; c-basic-offset: 4; indent-tabs-mode: nil -*- */  
/**
 * @file  robot.h
 *
 * @brief  description
 *
 * @author Jerome Delatour
 * @date 17-04-2016
 * @version version
 * @section License
 *
 * The MIT License
 *
 * Copyright (c) 2016, Jerome Delatour
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 * 
 */


#ifndef ROBOT_H
#define ROBOT_H


#include "prose.h"

#include <stdlib.h>
#include <stdio.h>

#define LEFT_MOTOR MD
#define RIGHT_MOTOR MA

#define LIGHT_SENSOR S1
#define FRONT_BUMPER S3
#define FLOOR_SENSOR S2

typedef int Speed;
typedef enum {NO_BUMP=0, BUMPED} Collision;

/**
 * Structure du Robot
 *
 * @brief Définitions des Etats des capteurs (Collision et Luminosité)
 */
typedef struct
{
    Collision collision;
    float luminosity;
} SensorsState;

/**
 * Structure du Robot
 *
 * @brief Définitions des capteurs (Collision frontale, Collision au sol et Luminosité)
 */
typedef struct
{
	Motor * mD;
	Motor * mG;

	LightSensor * sensorLight;
	ContactSensor * sensorFront;
	ContactSensor * sensorFloor;

} Robot;

/**
 * Fonction New Robot
 *
 * @brief Initialise l'object Robot en mémoire
 */
extern Robot* Robot_new();


/**
 * Fonction Free Robot
 *
 * @brief Détruit l'object Robot de la mémoire
 */
extern void Robot_free(Robot*);

/**
 * Accesseur getRobotSpeed Robot
 *
 * @brief retourne la vitesse du robot (moyenne positive de la puissance instantannée de la roue droite et de la gauche)
 *
 * @return vitesse du robot (valeur entre 0 et 100)
 */
extern Speed Robot_getRobotSpeed(Robot*);

/**
 * Accesseur getSensorState Robot
 *
 * @brief Retourne l'état des capteurs Frontal, Au sol et de Lumière
 *
 * @return SensorsState
 */
extern SensorsState Robot_getSensorsState(Robot*);

/**
 * Mutateur setWheelsVelocity Robot
 *
 * @brief Change la puissance des roues du Robot
 *
 * @param Speed: puissance envoyée au moteur droit , valeur comprise entre (-100, 100).
 * @param Speed: puissance envoyée au moteur gauche, valeur comprise entre (-100, 100).
 */
extern void Robot_setWheelsVelocity(Robot*, Speed, Speed);

#endif /* ROBOT_H */


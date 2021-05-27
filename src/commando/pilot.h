/* -*- mode: c; c-basic-offset: 4; indent-tabs-mode: nil -*- */  
/**
 * @file  pilot.h
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

#ifndef PILOT_H
#define PILOT_H

#include "commun.h"
#include "logger.h"
#include "robot.h"
#include "watchdog.h"

/**
 * Structure du Pilotage
 *
 * @brief Directions, Etats et Evenements
 */
typedef enum {
    NORMAL_IDLE = 0,
    NORMAL_RUNNING,
    EMERGENCY,
    ETAT_LENGTH
} Etat;

/**
 * Structure du Pilot
 *
 * @brief Définition de Pilot
 */
typedef struct
{
    VelocityVector vel;
    Etat etat;
    Logger* logger;
    Robot* robot;
    Watchdog* watchdog;
} Pilot;

/**
 * Fonction New Pilot
 *
 * @brief Initialise l'objet Pilot en mémoire
 */
extern Pilot* Pilot_new(Logger*, Robot*);


/**
 * Fonction Free Pilot
 *
 * @brief Détruit l'objet Pilot de la mémoire
 */
extern void Pilot_free(Pilot*);

/**
 * Mutateur setVelocity Pilot
 *
 * @brief Change velocity
 * @param vel
 */
extern void Pilot_setVelocity(Pilot*, VelocityVector vel);

/**
 * @brief Active ou désactive l'état d'urgence
 */
extern void Pilot_toggleES(Pilot*);


#endif /* PILOT_H */


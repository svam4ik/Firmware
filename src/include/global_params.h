#ifndef GLOBAL_PARAMS_H
#define GLOBAL_PARAMS_H

#include <math.h>


/*
 * Output PWM channels mapping
 */

// supplementary thrusters:
#define	THRST_1		(0)
#define	THRST_2		(2)
#define	THRST_3		(4)

// main rotor:
#define	MAIN_ROTOR_ENGINE		(7)
#define	MAIN_ROTOR_ENGINE_2		(6)


/*
 * Main engine control signal params:
 * ENGINE_SET- value, when engine is recognized by controllers
 * ENGINE_MIN - value, when engine starts to rotate on min speed
 * ENGINE_MAX - value, when engine rotates on max speed
 */
#define ENGINE_SET 1000
#define ENGINE_MIN 1030//1476
#define ENGINE_MIN_ROT 1520
#define ENGINE_MAX 1905

#define HEIGHT_MAX 10
#define HEIGHT_MIN 0

#define FAN_SET 1500
#define FAN_MIN 1210
#define FAN_MAX 1450

#define HEIGHT_LEVEL 4

const float discrete_time 	= 0.004;

#endif

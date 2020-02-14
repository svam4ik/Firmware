/**
 * @file rc_work.h
 * RC related definitions.
 */
#ifndef RC_WORK
#define RC_WORK

#include <stdint.h>
#include "../uORB.h"

#define RC_ON_HESTERESIS_PWM_VALUE 		(1250)
#define RC_THROTLE_CUT_PWM_VALUE		(1000)
#define RC_MIN_PWM_VALUE 				(1099)
#define RC_MAX_PWM_VALUE 				(1901)

/* Total number of RC channels */
#define RC_CHANNEL_COUNT	(8)		// ..since we use the receiver with eight channels

/* RC values for the 3-state mode ("FLAP/GYRO") switch */
#define RC_MODE_MANUAL_PWM_VALUE		(1901)
#define RC_MODE_AUTOMATIC_PWM_VALUE		(1500)
#define RC_MODE_TESTING_PWM_VALUE		(1099)
#define RC_MODE_TESTING_PWM_VALUE		(1099)

/* Mapping between RC channels and their functions */
#define RC_CHANNEL_X		(0)
#define RC_CHANNEL_Y		(1)
#define RC_CHANNEL_THRO		(2)
#define RC_CHANNEL_RUD		(3)
#define RC_CHANNEL_MODE		(4)
#define RC_CHANNEL_AUX		(6)


typedef enum RC_STATES {
	RC_STATE_OFF = 0,
	RC_STATE_ON,
} RC_STATES;

/* RC control modes */
typedef enum RC_MODES {
	RC_MODE_MANUAL = 0,
	RC_MODE_AUTOMATIC,
	RC_MODE_TESTING,
	RC_MODE_INACTIVE,
} RC_MODES;

/* Automatic flight submodes */
typedef enum AUTO_FLIGHT_MODES {
	AUTO_FLIGHT_MODE_INACTIVE = 0,
	AUTO_FLIGHT_MODE_MISSION,
	AUTO_FLIGHT_MODE_STANDBY,
} AUTO_FLIGHT_MODES;

struct rc_work_s {
	RC_MODES	mode;
	RC_STATES 	turn;
	RC_STATES 	throttle_work;
	AUTO_FLIGHT_MODES	auto_flight_mode;
	bool should_land;
	bool signal_lost;
};

ORB_DECLARE(rc_work);

#endif

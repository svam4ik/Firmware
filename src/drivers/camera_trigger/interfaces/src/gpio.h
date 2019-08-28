/**
 * @file relay.h
 *
 * Interface with cameras via FMU auxiliary pins.
 *
 */
#pragma once

#ifdef __PX4_NUTTX

#include <board_config.h>

#include "camera_interface.h"

class CameraInterfaceGPIO : public CameraInterface
{
public:
	CameraInterfaceGPIO();
	virtual ~CameraInterfaceGPIO() = default;

	void trigger(bool trigger_on_true);

	void info();

private:

	void setup();

	param_t _p_polarity;

	bool _trigger_invert;

	static constexpr uint32_t _gpios[] = {
		GPIO_GPIO0_OUTPUT,
		GPIO_GPIO1_OUTPUT,
		GPIO_GPIO2_OUTPUT,
		GPIO_GPIO3_OUTPUT,
		GPIO_GPIO4_OUTPUT,
#if defined(GPIO_GPIO5_OUTPUT)
		GPIO_GPIO5_OUTPUT
#endif
	};
	static constexpr int ngpios = sizeof(_gpios) / sizeof(_gpios[0]);

	uint32_t _triggers[ngpios];
};

#endif /* ifdef __PX4_NUTTX */

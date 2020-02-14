/****************************************************************************
 *
 *   Copyright (c) 2018 PX4 Development Team. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name PX4 nor the names of its contributors may be
 *    used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 ****************************************************************************/

#include "counter.h"

#include <px4_getopt.h>
#include <px4_log.h>
#include <px4_posix.h>

#include <uORB/topics/counter.h>
#include <uORB/topics/parameter_update.h>

int counter::print_usage(const char *reason)
{
	if (reason) {
		PX4_WARN("%s\n", reason);
	}

	PRINT_MODULE_DESCRIPTION(
		R"DESCR_STR(
### Description
Section that describes the provided module functionality.
This is an attempt to develop own publishing task.
### Implementation
Section describing the high-level implementation of this module.
### Examples
CLI usage example:
$ module start -s 0 -l 1000
)DESCR_STR");

	PRINT_MODULE_USAGE_NAME("counter", "modules");
	PRINT_MODULE_USAGE_COMMAND("start");
	PRINT_MODULE_USAGE_PARAM_INT('s', 0, 0, 10000, "Start counter from s", true);
	PRINT_MODULE_USAGE_DEFAULT_COMMANDS();

	return 0;
}

int counter::print_status()
{
	PX4_INFO("Running");
	// TODO: print additional runtime information about the state of the module

	return 0;
}

int counter::custom_command(int argc, char *argv[])
{
	/*
	if (!is_running()) {
		print_usage("not running");
		return 1;
	}
	// additional custom commands can be handled like this:
	if (!strcmp(argv[0], "do-something")) {
		get_instance()->do_something();
		return 0;
	}
	 */

	return print_usage("unknown command");
}


int counter::task_spawn(int argc, char *argv[])
{
	_task_id = px4_task_spawn_cmd("counter",
				      SCHED_DEFAULT,
				      SCHED_PRIORITY_DEFAULT,
				      1024,
				      (px4_main_t)&run_trampoline,
				      (char *const *)argv);

	if (_task_id < 0) {
		_task_id = -1;
		return -errno;
	}

	return 0;
}

counter *counter::instantiate(int argc, char *argv[])
{
	int start_param = 0;
	int last_param = 1000;
	bool error_flag = false;

	int myoptind = 1;
	int ch;
	const char *myoptarg = nullptr;

	// parse CLI arguments
	while ((ch = px4_getopt(argc, argv, "s:l:", &myoptind, &myoptarg)) != EOF) {
		switch (ch) {
		case 's':
			PX4_INFO("changing start value to %s", myoptarg);
			start_param = (int)atoi(myoptarg);
			break;
		case 'l':
			PX4_INFO("changing last value to %s", myoptarg);
			last_param = (int)atoi(myoptarg);
			break;

		case '?':
			error_flag = true;
			break;

		default:
			PX4_WARN("unrecognized flag");
			error_flag = true;
			break;
		}
	}

	if (error_flag) {
		return nullptr;
	}

	counter *instance = new counter(start_param, last_param);

	if (instance == nullptr) {
		PX4_ERR("alloc failed");
	}

	return instance;
}

counter::counter(int start_param = 0, int last_param = 1000)
	: ModuleParams(nullptr),
	  _counter(start_param),
	  _start(start_param),
	  _last(last_param)
{
	PX4_INFO("_start = %d", _start);
	PX4_INFO("_last = %d", _last);
}

void counter::run()
{
	// Example: run the loop synchronized to the sensor_combined topic publication
	orb_id_t counter_id = ORB_ID(counter);
	struct counter_s counter1;
	counter1.value = _counter;
	orb_advert_t counter_pub = orb_advertise(counter_id, &counter1);

	// initialize parameters
	int parameter_update_sub = orb_subscribe(ORB_ID(parameter_update));
	parameters_update(parameter_update_sub, true);

	while (!should_exit()) {

		if (++_counter > _last) {
			_counter = _start;
		}
		counter1.value = _counter;
		orb_publish(counter_id, counter_pub, &counter1);
		parameters_update(parameter_update_sub);
		usleep(50000);
	}

	orb_unsubscribe(parameter_update_sub);
	orb_unadvertise(counter_pub);
}

void counter::parameters_update(int parameter_update_sub, bool force)
{
	bool updated;
	struct parameter_update_s param_upd;

	orb_check(parameter_update_sub, &updated);

	if (updated) {
		orb_copy(ORB_ID(parameter_update), parameter_update_sub, &param_upd);
	}

//	if (force || updated) {
//		updateParams();
//	}
}


int counter_main(int argc, char *argv[])
{
	return counter::main(argc, argv);
}

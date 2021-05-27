/**
 * @file compute_pi.c
 *
 * @author team FORMATO, ESEO
 *
 * @section License
 *
 * The MIT License
 *
 * Copyright (c) 2016, Jonathan ILIAS-PILLET (ESEO)
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
 */
#include "watchdog.h"
#include "pmu_tools.h"
#include <malloc.h>
#include <signal.h>
#include <time.h>

struct Watchdog_t
{
	timer_t timerid; //timer id creation
	uint32_t secDelay; /**< configured delay in seconds */
	long nanoDelay; /**< configured delay in nanoseconds */
	WatchdogCallback myCallback; // function to be called at delay expiration
	void* arg; // Argument passed to the called function
};

/**
 * Calls the watchdog callback when the delay of the timer expires
 *
 * @param handlerParam must be the watchdog reference
 */
static void mainHandler (union sigval sv)
{
	Watchdog *theWatchdog = sv.sival_ptr;

	theWatchdog->myCallback (theWatchdog->arg);
}

Watchdog *Watchdog_new (uint32_t thisDelay, long nanoDelay, WatchdogCallback callback, void* arg)
{
	Watchdog *result;
	int error_code;
	struct sigevent sev = {0};

	// allocates and initializes the watchdog's attributes
	result = (Watchdog *)malloc (sizeof(Watchdog));
	if (result == NULL) PProseError("Cannot allocate memory");

	result->secDelay = thisDelay;
	result->nanoDelay = nanoDelay;
	result->myCallback = callback;
	result->arg = arg;

	//creates the POSIX timer
	sev.sigev_notify = SIGEV_THREAD;
	sev.sigev_notify_function = mainHandler;
	sev.sigev_value.sival_ptr = result;

	error_code = timer_create(CLOCK_REALTIME, &sev, &(result->timerid));
	if(error_code == -1) PProseError("Unexpected error code");
	
	return result;
}

void Watchdog_start (Watchdog *this)
{
	int error_code;
	struct itimerspec trigger = {0};
	trigger.it_value.tv_sec = this->secDelay;
	trigger.it_value.tv_nsec = this->nanoDelay;
	error_code = timer_settime(this->timerid, 0, &trigger, NULL);
	if(error_code == -1) PProseError("Unexpected error code");
}

void Watchdog_cancel (Watchdog *this)
{
	int error_code;
	struct itimerspec trigger = {0}; //lorsque tout est à 0, le timer est désarmé
	error_code = timer_settime(this->timerid, 0, &trigger, NULL);
	if(error_code == -1) PProseError("Unexpected error code");
}

void Watchdog_destroy (Watchdog *this)
{
	int error_code;

	Watchdog_cancel(this);
	error_code = timer_delete(this->timerid);
	if(error_code == -1) PProseError("Unexpected error code");
	
	// then we can free memory
	free (this);
}

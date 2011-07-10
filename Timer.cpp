#include <stdint.h>
#include <ctime>
#include "Timer.hpp"

Timer::Timer() {
	clock_gettime(CLOCK_THREAD_CPUTIME_ID, &ts1);
}

double Timer::ns() {
	struct timespec ts2;
	clock_gettime(CLOCK_THREAD_CPUTIME_ID, &ts2);
	return ((uint64_t)ts2.tv_sec - ts1.tv_sec) * 1000000000ll + ts2.tv_nsec - ts1.tv_nsec;
}

double Timer::us() {
	return ns() / 1000;
}

double Timer::ms() {
	return ns() / 1000000;
}

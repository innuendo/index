#include <stdint.h>
#include <ctime>

class Timer {
	struct timespec ts1;
public:
	Timer();
	double ns();
	double us();
	double ms();
};

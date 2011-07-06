#include <string>
//#include <sstream>
//#include <boost/iostreams/filter/zlib.hpp>

class zstring {
	std::string z;
public:
	zstring(std::string s): z(s) {};
	operator std::string () {
		return z;
	}
};




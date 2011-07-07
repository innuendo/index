#include <stdint.h>
#include <vector>
#include <string>
#include "rawxml.hpp"

typedef uint64_t pmid_t;

struct MLCitation {
	pmid_t				pmid;
	char				*journal;
	char				*date;
	std::vector<std::string>	meshtags;
};

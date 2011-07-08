#ifndef _MLCITATION_H_
#define _MLCITATION_H_

#include <stdint.h>
#include <vector>
#include <string>

typedef uint64_t pmid_t;

struct MLCitation {
	pmid_t				pmid;
	std::string			journal;
	std::string			date;
	std::vector<char*>	meshtags;
};

#endif

#ifndef __MLCITATION_H
#define __MLCITATION_H

#include <stdint.h>
#include <set>
#include <string>

typedef uint64_t pmid_t;

struct mesh_cmp {
    bool operator() (char const* a, char const* b) {
        return strcmp(a, b) < 0;
    }
};

typedef std::set<char*, mesh_cmp> mesh_set_t;

struct MLCitation {
	pmid_t				pmid;
	std::string			journal;
	std::string			date;
	mesh_set_t          meshtags;
};

#endif
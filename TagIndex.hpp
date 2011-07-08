#ifndef _TAGINDEX_H_
#define _TAGINDEX_H_

#include <vector>
#include <boost/unordered_map.hpp>
#include "MLCitation.hpp"

typedef std::vector<pmid_t> mlcvect;
typedef boost::unordered_map<std::string, mlcvect> mlcmap;

class TagIndex {
	mlcmap	journal;
	mlcmap	date;
	mlcmap	mesh;
public:
	void insert(const MLCitation&);
	void sort();

	const mlcvect& query_journal(const std::string) const;
	const mlcvect& query_date(const std::string) const ;
	const mlcvect& query_mesh(const std::string) const ;
};

#endif

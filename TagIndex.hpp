#include <utility>
#include <vector>
#include <boost/unordered_map.hpp>
#include "MLCitation.hpp"

typedef boost::unordered_multimap<std::string, pmid_t> mimap;

class TagIndex {
	mimap	journal;
	mimap	date;
public:
	std::vector<pmid_t> query_journal(std::string);
	std::vector<pmid_t> query_date(std::string);

	void insert(MLCitation&);
};


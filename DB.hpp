#include <utility>
#include <vector>
#include <boost/intrusive/unordered_set.hpp>

#include "MLCitation.hpp"

class DB {
	struct DBNode {
		MLCitation	citation;
	};
	boost::intrusive::unordered_set<uint64_t, DBNode*>		pmid_map;
	boost::intrusive::unordered_multiset<std::string, DBNode*>	title_map;
	boost::intrusive::unordered_multiset<std::string, DBNode*>	journal_map;

public:
	MLCitation*		 query_pmid(uint64_t);
	std::vector<MLCitation*> query_title(std::string);
	std::vector<MLCitation*> query_journal(std::string);

	void insert(MLCitation&);
};


#include <utility>
#include <vector>
#include <boost/unordered_map.hpp>
#include "MLCitation.hpp"

class DB {
	boost::unordered_map<uint64_t, MLCitation*>		pmid;
	boost::unordered_multimap<std::string, MLCitation*>	title;
	boost::unordered_multimap<std::string, MLCitation*>	abstract;
	boost::unordered_multimap<std::string, MLCitation*>	journal;
	boost::unordered_multimap<std::string, MLCitation*>	date;

public:
	MLCitation*		 query_pmid(uint64_t);
	std::vector<MLCitation*> query_title(std::string);
	std::vector<MLCitation*> query_abstract(std::string);
	std::vector<MLCitation*> query_journal(std::string);
	std::vector<MLCitation*> query_date(std::string);

	void insert(MLCitation&);
};


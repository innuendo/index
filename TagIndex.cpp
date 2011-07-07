#include "TagIndex.hpp"
using namespace std;
using namespace boost;

void TagIndex::insert(MLCitation& cit) {
	journal.insert(make_pair(cit.journal, cit.pmid));
	date.insert(make_pair(cit.date, cit.pmid));
}

static inline vector<pmid_t> do_query(mimap &m, string s) {
	vector<pmid_t> ret;
	pair<mimap::iterator, mimap::iterator> range = m.equal_range(s);
	for (mimap::iterator i = range.first; i != range.second; ++i)
		ret.push_back(i->second);
	return ret;
}

vector<pmid_t> TagIndex::query_journal(string s) {
	return do_query(journal, s);
}

vector<pmid_t> TagIndex::query_date(string s) {
	return do_query(date, s);
}

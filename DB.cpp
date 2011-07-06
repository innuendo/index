#include "DB.hpp"
using namespace std;
using namespace boost;

void DB::insert(MLCitation& cit) {
	pmid.insert(make_pair(cit.pmid, &cit));
	title.insert(make_pair(cit.title, &cit));
	abstract.insert(make_pair(cit.abstract, &cit));
	journal.insert(make_pair(cit.journal, &cit));
	date.insert(make_pair(cit.date, &cit));
}

MLCitation* DB::query_pmid(uint64_t id) {
	return pmid[id];
}

vector<MLCitation*> DB::query_title(string s) {
	vector<MLCitation*> ret;
	pair<unordered_multimap<string, MLCitation*>::iterator, unordered_multimap<string, MLCitation*>::iterator> range = title.equal_range(s);
	for (unordered_multimap<string, MLCitation*>::iterator i = range.first; i != range.second; ++i)
		ret.push_back(i->second);
	return ret;
}

vector<MLCitation*> DB::query_abstract(string s) {
	vector<MLCitation*> ret;
	pair<unordered_multimap<string, MLCitation*>::iterator, unordered_multimap<string, MLCitation*>::iterator> range = abstract.equal_range(s);
	for (unordered_multimap<string, MLCitation*>::iterator i = range.first; i != range.second; ++i)
		ret.push_back(i->second);
	return ret;
}

vector<MLCitation*> DB::query_journal(string s) {
	vector<MLCitation*> ret;
	pair<unordered_multimap<string, MLCitation*>::iterator, unordered_multimap<string, MLCitation*>::iterator> range = journal.equal_range(s);
	for (unordered_multimap<string, MLCitation*>::iterator i = range.first; i != range.second; ++i)
		ret.push_back(i->second);
	return ret;
}

vector<MLCitation*> DB::query_date(string s) {
	vector<MLCitation*> ret;
	pair<unordered_multimap<string, MLCitation*>::iterator, unordered_multimap<string, MLCitation*>::iterator> range = date.equal_range(s);
	for (unordered_multimap<string, MLCitation*>::iterator i = range.first; i != range.second; ++i)
		ret.push_back(i->second);
	return ret;
}

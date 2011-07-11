#include <algorithm>
#include "TagIndex.hpp"
using namespace std;
using namespace boost;

void TagIndex::insert(const MLCitation& cit) {
	journal[cit.journal].push_back(cit.pmid);
	date[cit.date].push_back(cit.pmid);
	for (vector<char*>::const_iterator i = cit.meshtags.begin(); i != cit.meshtags.end(); ++i)
		mesh[*i].push_back(cit.pmid);
}

void TagIndex::postprocess() {
	for (mlcmap::iterator i = journal.begin(); i != journal.end(); ++i)
		std::sort(i->second.begin(), i->second.end());
	for (mlcmap::iterator i = date.begin(); i != date.end(); ++i)
		std::sort(i->second.begin(), i->second.end());
	for (mlcmap::iterator i = mesh.begin(); i != mesh.end(); ++i)
		std::sort(i->second.begin(), i->second.end());
}

static inline const mlcvect& do_query(const mlcmap& m, const string s) {
	static const mlcvect empty;
	mlcmap::const_iterator i = m.find(s);
	if (i != m.end())
		return i->second;
	else
		return empty;
}

const mlcvect& TagIndex::query_journal(const string s) const {
	return do_query(journal, s);
}

const mlcvect& TagIndex::query_date(const string s) const {
	return do_query(date, s);
}

const mlcvect& TagIndex::query_mesh(const string s) const {
	return do_query(mesh, s);
}

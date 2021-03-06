#include <iostream>
#include <cstring>
#include "TagIndex.hpp"
#include "XMLStore.hpp"
#include "Parser.hpp"
#include "Timer.hpp"
#include "DB.hpp"
using namespace std;

void print(const vector<pmid_t>& v) {
	for (vector<pmid_t>::const_iterator i = v.begin(); i != v.end(); ++i)
		cout << *i << endl;
}

int main(int argc, char *argv[]) {
	TagIndex index;
	XMLStore store(argv[1]);
	for (XMLStore::iterator i = store.begin(); i != store.end(); ++i) {
		//cerr << "Processing PMID " << *i <<endl;
		char *xml = store.get_xml(*i);
		//cerr << xml <<endl;
		Parser parser(xml);
		//cerr << "Parser loaded, parsing... ";
		MLCitation cit = parser.parse();
		//cerr << "done." <<endl;
		//if (cit.meshtags.size())
		//	cerr << cit.meshtags[0] << ' '<< cit.meshtags.size() << endl;
		index.insert(cit);
		delete(xml);
	}
	cerr << "Data loaded, postprocessing... ";
	index.postprocess();
	cerr << "done." << endl;

	DB db(store, index);
	vector<string> meshtags;
	meshtags.push_back("Ovary");
	DB::query<vector<string>::iterator> q = db.start_query<>("", "", meshtags.begin(), meshtags.end());
	while (q.has_next())
		cout << q.get_next() << endl;
/*
	while (!cin.eof()) {
		cout << ">>> ";
		string q, s;
		cin >> q >> ws;
		if (q == "q")
			break;
		getline(cin, s); 
		const vector<pmid_t> *r = NULL;
		Timer timer;
		if (q == "j")
			r = &index.query_journal(s);
		if (q == "d")
			r = &index.query_date(s);
		if (q == "m")
			r = &index.query_mesh(s);
		double time = timer.us();
		if (!r) {
			cout << "> Valid queries: d(ate), j(ournal), m(esh)" << endl;
		} else {
			print(*r);
			cout << "> Fetched records:\t" << r->size() << endl;
		}
		cout << "> Processing time:\t" << time << "us." << endl;
	}
*/
	return 0;
}

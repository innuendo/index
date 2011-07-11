#include <iostream>
#include <cstring>
#include "TagIndex.hpp"
#include "XMLStore.hpp"
#include "Parser.hpp"
#include "Timer.hpp"
using namespace std;

void print(const vector<pmid_t>& v) {
	for (vector<pmid_t>::const_iterator i = v.begin(); i != v.end(); ++i)
		cout << *i << endl;
}

int main(int argc, char *argv[]) {
	TagIndex index;

	for (int i = 1; i < argc; i++) {
		cerr << "Loading " << argv[i] << " (" << i << "/" << argc-1 << ")" <<endl;

		cerr << "Building XMLStore... ";
		XMLStore store(argv[i]);
		cerr << "done." << endl;
	
		cerr << "Indexing... ";
		for (XMLStore::iterator i = store.begin(); i != store.end(); ++i) {
#ifdef DEBUG
			cerr << "Processing PMID " << *i <<endl;
#endif
			char *xml = store.get_xml(*i);
#ifdef DEBUG
			cerr << xml <<endl;
#endif
			Parser parser(xml);
#ifdef DEBUG
			cerr << "Parser loaded, parsing... ";
#endif
			MLCitation cit = parser.parse();
#ifdef DEBUG
			cerr << "done." <<endl;
			if (cit.meshtags.size())
				cerr << *(cit.meshtags.begin()) << ' '<< cit.meshtags.size() << endl;
#endif
			index.insert(cit);
			delete(xml);
		}
		cerr << "done." << endl;
	}
	cerr << "Data loaded, postprocessing... ";
	index.postprocess();
	cerr << "done." << endl;

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
	return 0;
}

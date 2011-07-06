#include <iostream>
#include "DB.hpp"
using namespace std;

int main() {
	MLCitation c;
	c.pmid = 13;
	c.title = "title";
	c.abstract = "abstract";
	c.journal = "journal";
	c.date = "date";
	DB b;
	b.insert(c);
	cout << &c << endl;
	cout << b.query_pmid(13) << endl;
	cout << b.query_title("title")[0] << endl;
	cout << b.query_pmid(12) << endl;
	return 0;
}

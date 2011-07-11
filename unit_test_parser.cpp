#include "Parser.hpp"
#include <iostream>
#include <boost/foreach.hpp>
#define foreach BOOST_FOREACH
int main()
{
    std::cout << "TEST STARTING" << std::endl;
    std::cout << "Opening test.xml...";
    char* read_data;
    FILE *fp;
	long len;
	fp = fopen("test.xml" ,"r");
    assert(fp != NULL);
	fseek(fp, 0, SEEK_END);
	len = ftell(fp);
	fseek(fp, 0, SEEK_SET); 
	read_data = (char*)malloc(len + 1);
	fread(read_data, len, 1, fp);
	fclose(fp);
    read_data[len] = '\0';
    std::cout << "OK" << std::endl << "Creating parser...";
    Parser p(read_data);
    std::cout << "OK" << std::endl << "Parsing...";
    MLCitation m = p.parse();
    std::cout << "OK" << std::endl << "Results: " << std::endl;
    std::cout << "PMID: " << m.pmid << std::endl;
    assert(m.pmid == 18479468);
    std::cout << "Date: " << m.date << std::endl;
    assert(m.date == "2009Feb");
    std::cout << "Journal: " << m.journal << std::endl;
    assert(m.journal == "Diabetes, obesity & metabolism");
    std::cout << "Found " << m.meshtags.size() << " MeSHes" << std::endl;
    assert(m.meshtags.size() == 10);
    foreach(char* mesh, m.meshtags) {
        std::cout << "MeSH: " << mesh << std::endl;
    }
    std::cout << "TEST COMPLETED!" << std::endl;
    return 0;
}
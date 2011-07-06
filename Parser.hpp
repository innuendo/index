#ifndef __PARSER_HPP
#define __PARSER_HPP

#include <vector>
#include <cstdlib>
#include <cstring>
#include <boost/lexical_cast.hpp>

#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"
#include "rapidxml_print.hpp"
//#include "rapidxml_iterators.hpp"
#include "MLCitation.hpp"

class Parser {
	char* read_data;
	std::vector<MLCitation> mlcs;
    char* getTitle(rapidxml::xml_node<> *node);
    char* getAbstract(rapidxml::xml_node<> *node);
    char* getJournal(rapidxml::xml_node<> *node);
    char* getPubDate(rapidxml::xml_node<> *node);
    char* setXML(rapidxml::xml_node<> *node);
    
public:
	typedef std::vector<MLCitation>::iterator MLCitationIter;
	Parser(char const* fileName);
	~Parser();
	std::vector<MLCitation>::iterator parse();	
};

#endif

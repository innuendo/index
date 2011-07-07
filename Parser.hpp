#ifndef __PARSER_HPP
#define __PARSER_HPP

#include <vector>
#include <lzo/lzo1x.h>
#include "lzo/lzoconf.h"
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
    void getJournal(rapidxml::xml_node<> const* node, std::string& s);
    void getPubDate(rapidxml::xml_node<> const* node, std::string& s);
    
public:
	typedef std::vector<MLCitation>::iterator MLCitationIter;
	Parser(char const* fileName);
	~Parser();
	std::vector<MLCitation>::iterator parse();	
};

#endif

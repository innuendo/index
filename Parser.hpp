#ifndef __PARSER_HPP
#define __PARSER_HPP

#include <vector>
#include <cstdlib>
#include <cstring>
#include <boost/lexical_cast.hpp>

#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"
//#include "rapidxml_iterators.hpp"
#include "MLCitation.hpp"

class Parser {
	char* read_data;
	std::vector<MLCitation> mlcs;
    char* getTitle(rapidxml::xml_node<> *node);
    char* getAbstract(rapidxml::xml_node<> *node);
    char* getJournal(rapidxml::xml_node<> *node);
    char* getPubDate(rapidxml::xml_node<> *node);
    
public:
	typedef std::vector<MLCitation>::iterator MLCitationIter;
	Parser(char const* fileName);
	~Parser();
	std::vector<MLCitation>::iterator parse();	
};

class RawXML {
    std::string xml_text;

public:
    RawXML(std::string xml) : xml_text(xml) {}
    virtual std::string get_xml() {
        return xml_text;
    }
};

#endif

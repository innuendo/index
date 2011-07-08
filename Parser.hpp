#ifndef __PARSER_HPP
#define __PARSER_HPP

#include <vector>
#include <cstdlib>
#include <cstring>
#include <boost/lexical_cast.hpp>

#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"
#include "rapidxml_print.hpp"
#include "MLCitation.hpp"

class Parser {
    char* mlc_xml;
    void get_mesh_data(std::vector<char*>& meshes);
    rapidxml::xml_document<> doc;
public:
    Parser(char* mlc_xml) : mlc_xml(mlc_xml) {}
    MLCitation parse();
    std::string get_tag_value(char const** path);
    
};

#endif

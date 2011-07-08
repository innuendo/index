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
    char* mlc_xml;
    
    void getMeshData(rapidxml::xml_node<> const* node,
                     std::vector<char*>& meshes);
    std::string getTagValue(char const** path,
                            rapidxml::xml_node<> const* root);
public:
    MLCitation parse(char* mlc_xml);
};

#endif

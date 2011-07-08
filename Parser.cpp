//#include "rapidxml_print.hpp"
#include "Parser.hpp"
#include <iostream>

#define MLCS_PER_FILE 30000

void Parser::get_mesh_data(std::vector<char*>& meshes) {
//    static int x = 0;
//    cout << ++x <<endl;
    rapidxml::xml_node<> *node = &doc;
    if (node->first_node("MeshHeadingList")) {
        if (node->first_node("MeshHeadingList")->first_node("MeshHeading")) {
            bool descriptorIn = false;
            rapidxml::xml_node<> *MeshNode =
                node->first_node(
                    "MeshHeadingList")->first_node("MeshHeading");
            while (MeshNode) {
                rapidxml::xml_node<> *MeshProp = MeshNode->first_node("DescriptorName");
                if (MeshProp->first_attribute("MajorTopicYN")) {
                    if (strcmp(MeshProp->first_attribute("MajorTopicYN")->value(), "Y")) {
                        meshes.push_back(MeshProp->value());
                        descriptorIn = true;
                    }
                }
                for (; MeshProp; MeshProp = MeshProp->next_sibling()) {
                    if (MeshNode->first_attribute("MajorTopicYN")) {
                        if (strcmp(MeshNode->first_attribute("MajorTopicYN")->value() , "Y")){
                            meshes.push_back(MeshProp->value());
                            if (!descriptorIn) {
                                descriptorIn = true;
                                meshes.push_back(
                                    MeshNode->first_node("DescriptorName")->value());
                            }
                        }
                    }
                }
                MeshNode = MeshNode->next_sibling();
            }
        }
    }
}

std::string Parser::get_tag_value(char const** path) {
    rapidxml::xml_node<> const* node = &doc;
    std::string result = "";
    char const** it = path;
    while (it) {
        if (node->first_node(*it)) {
            node = node->first_node(*it);
        } else {
            break;
        }
        ++it;
    }
    result = node->value();
    return result;
}

MLCitation Parser::parse() {
	doc.parse<0>(mlc_xml);
    MLCitation result;
    char const* year_q[] = {"Article", "Journal", "PubDate", "Year"};
    char const* month_q[] = {"Article", "Journal", "Pubdate", "Month"};
    char const* journal_q[] = {"Article", "Journal", "Title"};
    
    result.pmid = boost::lexical_cast<pmid_t>(doc.first_node("PMID")->value());
    result.date = get_tag_value(year_q);
    result.date += get_tag_value(month_q);
    result.journal = get_tag_value(journal_q);
    get_mesh_data(result.meshtags);
    return result;
}

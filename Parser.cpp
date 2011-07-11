#include "Parser.hpp"

#define MLCS_PER_FILE 30000

void Parser::get_mesh_data(mesh_set_t& meshes) {
    char const* mesh_q[] = 
    {"MedlineCitation", "MeshHeadingList", "MeshHeading", NULL};
    rapidxml::xml_node<> const* MeshNode = get_tag_node(mesh_q);
#ifdef DEBUG
    if (!MeshNode) {
        std::cout << std::endl << "\t[MESH: No such node!]" << std::endl;
    }
    std::cout <<  std::endl << "\t[DEBUG defined]" <<std::endl;
#endif
    while (MeshNode) {
        rapidxml::xml_node<> *MeshProp = MeshNode->first_node("DescriptorName");
        if (MeshProp->first_attribute("MajorTopicYN")) {
            if (!strcmp(MeshProp->first_attribute("MajorTopicYN")->value(),
                        "Y")) {
                meshes.insert(MeshProp->value());
            }
        }
        MeshProp = MeshProp->next_sibling();
        for (; MeshProp; MeshProp = MeshProp->next_sibling()) {
            if (MeshProp->first_attribute("MajorTopicYN")) {
                if (!strcmp(MeshProp->first_attribute("MajorTopicYN")->value() ,
                            "Y")) {
                    meshes.insert(MeshProp->value());
                    meshes.insert(
                        MeshNode->first_node("DescriptorName")->value());
                }
            }
        }
        MeshNode = MeshNode->next_sibling();
    }
}

rapidxml::xml_node<> const* Parser::get_tag_node(char const** path) {
    rapidxml::xml_node<> const* node = &doc;
    char const** it = path;
    while (*it) {
        node = node->first_node(*it);
        if (!node) break;
        ++it;
    }
    return node;
}

std::string Parser::get_tag_value(char const** path) {
    std::string result = "";
    rapidxml::xml_node<> const* node = get_tag_node(path);
    if (node) {
        result = node->value();
    }
    return result;
}

MLCitation Parser::parse() {
	doc.parse<0>(mlc_xml);
    MLCitation result;
    char const* year_q[] = {"MedlineCitation", "Article", "Journal",
        "JournalIssue", "PubDate", "Year", NULL};
    char const* month_q[] = {"MedlineCitation", "Article", "Journal",
        "JournalIssue", "PubDate", "Month", NULL};
    char const* journal_q[] = {"MedlineCitation", "Article", "Journal",
        "Title", NULL};
    
    result.pmid = boost::lexical_cast<pmid_t>
    (doc.first_node()->first_node("PMID")->value());
    result.date = get_tag_value(year_q);
    result.date += get_tag_value(month_q);
    result.journal = get_tag_value(journal_q);
    get_mesh_data(result.meshtags);
    return result;
}

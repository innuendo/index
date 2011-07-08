#include "rapidxml_print.hpp"
#include "XMLStore.hpp"
#include <iostream>
using namespace std;
using namespace boost;
using namespace rapidxml;

#define MLCS_PER_FILE 30000

XMLStore::XMLStore(char const* fileName) {
	FILE *fp;
	long len;
	fp = fopen(fileName ,"r");
	assert(fp != NULL);
	fseek(fp, 0, SEEK_END);
	len = ftell(fp);
	fseek(fp, 0, SEEK_SET); 
	read_data = (char*)malloc(len);
	fread(read_data, len, 1, fp);
	fclose(fp);
	rapidxml::xml_document<> doc;
	doc.parse<0>(read_data);
	rapidxml::xml_node<> *node = doc.first_node();	// <MedlineCitationSet>
	node = node->first_node();			// <MedlineCitation>
	while (node != NULL) {
		if (node->first_node("PMID")) {
			pmid_t pmid = boost::lexical_cast<uint64_t>(
					node->first_node("PMID")->value());
			string xml;
			print(std::back_inserter(xml), *node, 0);
			xmls[pmid] = xml;
		}
		node = node->next_sibling();
	}
}

XMLStore::~XMLStore() {
	free(read_data);
}
/*
char* XMLStore::getAbstract(rapidxml::xml_node<> *node) {
    if (node->first_node("Article")->first_node("Abstract")) {
            return node->first_node("Article")->first_node("Abstract")->value();
    } else if (node->first_node("Article")->first_node("OtherAbstract")) {
        return node->first_node("Article")->first_node(
            "OtherAbstract")->first_node("AbstractText")->value();
    } else {
        return NULL;
    }
}

char* XMLStore::getTitle(rapidxml::xml_node<> *node) {
    if (node->first_node("Article")->first_node("ArticleTitle")) {
        return node->first_node("Article")->first_node("ArticleTitle")->value();
    } else {
        return NULL;
    }
}
*/
char* XMLStore::get_xml(pmid_t id) {
	unordered_map<pmid_t, string>::const_iterator i = xmls.find(id);
	if (i != xmls.end()) {
		const char *xml = i->second.c_str();
		char *buf = new char[strlen(xml)+1];
		strcpy(buf, xml);
		return buf;
	} else {
		return NULL;
	}
}


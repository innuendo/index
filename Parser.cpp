//#include "rapidxml_print.hpp"
#include "Parser.hpp"

#include <cstdio>

using namespace std;

Parser::Parser(char const* fileName) {
	FILE *fp;
	long len;
	fp = fopen(fileName ,"r");
	fseek(fp, 0, SEEK_END);
	len = ftell(fp);
	fseek(fp, 0, SEEK_SET); 
	read_data = (char*)malloc(len);
	fread(read_data, len, 1, fp);
	fclose(fp);
}

Parser::~Parser() {
	free(read_data);
	mlcs.clear();
}

char* Parser::getAbstract(rapidxml::xml_node<> *node) {
    if (node->first_node("Article")->first_node("Abstract")) {
        return node->first_node("Article")->first_node("Abstract")->value();
    } else if (node->first_node("Article")->first_node("OtherAbstract")) {
        return node->first_node("Article")->first_node(
            "OtherAbstract")->first_node("AbstractText")->value();
    } else {
        return NULL;
    }
}

char* Parser::getJournal(rapidxml::xml_node<> *node) {
    if (node->first_node("Article")->first_node("Journal")) {
        if (node->first_node(
                "Article")->first_node("Journal")->first_node("Title")) {
            return node->first_node("Article")->first_node(
                "Journal")->first_node("Title")->value();
        } else {
            return NULL;
        }
    }
    return NULL;
}

char* Parser::getPubDate(rapidxml::xml_node<> *node) {
    if (node->first_node("Article")->first_node("Journal")) {
        if (node->first_node(
                "Article")->first_node("Journal")->first_node("PubDate")) {
            return node->first_node("Article")->first_node(
                "Journal")->first_node("PubDate")->value();
        } else {
            return NULL;
        }
    }
    return NULL;
}

char* Parser::getTitle(rapidxml::xml_node<> *node) {
    if (node->first_node("Article")->first_node("ArticleTitle")) {
        return node->first_node("Article")->first_node("ArticleTitle")->value();
    } else {
        return NULL;
    }
}

vector<MLCitation>::iterator Parser::parse() {
    rapidxml::xml_document<> doc;
	doc.parse<0>(read_data);
	rapidxml::xml_node<> *node = doc.first_node();
    node = node->first_node();
	while (node != NULL) {
        std::string s;
        rapidxml::print(std::back_inserter(s), *node);
        MLCitation tmp(s);
        if (node->first_node("Article")) {
            tmp.pmid	 = boost::lexical_cast<uint64_t>(
                        node->first_node("PMID")->value());
            tmp.title	 = getTitle(node);
            tmp.abstract = getAbstract(node);
            tmp.journal	 = getJournal(node);
            tmp.date 	 = getPubDate(node);
        } else {
            tmp.pmid     = NULL;
            tmp.title    = NULL;
            tmp.abstract = NULL;
            tmp.journal  = NULL;
            tmp.date     = NULL;
        }
        // tmp.attr_string = create_string_args();
		node		 = node->next_sibling();
		mlcs.push_back(tmp);
	}
	return mlcs.begin();
}

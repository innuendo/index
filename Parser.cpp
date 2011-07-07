//#include "rapidxml_print.hpp"
#include "Parser.hpp"

using namespace std;

Parser::Parser(char const* fileName) {
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
}

Parser::~Parser() {
	free(read_data);
	mlcs.clear();
}

void Parser::getJournal(rapidxml::xml_node<> const* node, string& s) {
    if (node->first_node("Article")->first_node("Journal")) {
        if (node->first_node(
                "Article")->first_node("Journal")->first_node("Title")) {
            s = node->first_node("Article")->first_node(
                "Journal")->first_node("Title")->value();
        }
    }
}

void Parser::getPubDate(rapidxml::xml_node<> const* node, string& s) {
    rapidxml::xml_node<> *tmp;
    if (node->first_node("Article")->first_node("Journal")) {
        if (node->first_node(
                "Article")->first_node("Journal")->first_node("PubDate")) {
            s = node->first_node("Article")->first_node(
                "Journal")->first_node("PubDate")->first_node("Year")->value();
            s += node->first_node("Article")->first_node(
                "Journal")->first_node("PubDate")->first_node("Month")->value(); 
        }
    }
}

vector<MLCitation>::iterator Parser::parse() {
//    lzo_bytep in;
//    lzo_bytep out;
//    lzo_voidp wrkmem;
//    lzo_uint in_len;
//    lzo_uint out_len;
//    lzo_uint new_len;
//    
//    if (lzo_init() != LZO_E_OK)
//    {
//        printf("internal error - lzo_init() failed !!!\n");
//        return NULL;
//    }
//    
//    in = (lzo_bytep) malloc(strlen(read_data) * sizeof(char));
//    lzo_memcpy(in, read_data, strlen(read_data) * sizeof(char));
//    out = (lzo_bytep) malloc(2 * strlen(read_data));
//    wrkmem = (lzo_voidp) malloc(LZO1X_1_MEM_COMPRESS);
//    if (in == NULL || out == NULL || wrkmem == NULL)
//    {
//        printf("out of memory\n");
//    }
    
    rapidxml::xml_document<> doc;
	doc.parse<0>(read_data);
    rapidxml::xml_node<> *node = doc.first_node();
    node = node->first_node();
    MLCitation tmp;
	while (node != NULL) {
        if (node->first_node("Article")) {
            tmp.pmid	 = boost::lexical_cast<uint64_t>(
                        node->first_node("PMID")->value());
            getJournal(node, tmp.journal);
            getPubDate(node, tmp.date);
        } else {
            tmp.pmid     = NULL;
        }
        // tmp.attr_string = create_string_args();
		node = node->next_sibling();
		mlcs.push_back(tmp);
	}
	return mlcs.begin();
}

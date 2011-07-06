#include <stdint.h>

struct MLCitation {
	uint64_t pmid;
	char	*title;
	char	*abstract;
	char	*journal;
	char	*date;
	RawXML	xml;
	MLCitation(std::string xml) : xml(xml) {};
	//TODO: Meshe
};

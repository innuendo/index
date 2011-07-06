#include <stdint.h>

struct MLCitation {
	uint64_t pmid;
	char	 *title;
	char	 *abstract;
	char	 *journal;
	char	 *date;
    std::string xml;   
	//TODO: Meshe
};

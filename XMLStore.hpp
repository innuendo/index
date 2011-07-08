#ifndef __XMLSTORE_HPP
#define __XMLSTORE_HPP

#include <vector>
#include <lzo/lzo1x.h>
#include "lzo/lzoconf.h"
#include <cstdlib>
#include <cstring>
#include <utility>
#include <boost/lexical_cast.hpp>
#include <boost/unordered_map.hpp>

#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"
#include "rapidxml_print.hpp"
#include "MLCitation.hpp"

class XMLStore {
	char* read_data;
	boost::unordered_map<pmid_t, std::string> xmls;
public:
	XMLStore(char const* fileName);
	~XMLStore();

	char* get_xml(pmid_t);
	char* get_title(pmid_t);
	char* get_abstract(pmid_t);
	// returned buffers are owned by caller and have to be delete()d

	class iterator {
		boost::unordered_map<pmid_t, std::string>::const_iterator i;
		iterator(boost::unordered_map<pmid_t, std::string>::const_iterator i):
			i(i) {}
		friend class XMLStore;
	public:
		iterator& operator++() {
			++i;
			return *this;
		}
		pmid_t operator*() const {
			return i->first;
		}
		bool operator!=(const iterator& x) const {
			return i != x.i;
		}
	};
	
	iterator begin() {
		return iterator(xmls.begin());
	}
	iterator end() {
		return iterator(xmls.end());
	}
};


#endif

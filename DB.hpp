#ifndef _DB_HPP_
#define _DB_HPP_

#include <list>
#include <string>
#include "TagIndex.hpp"
#include "XMLStore.hpp"

class DB {
	const XMLStore& xml;
	const TagIndex& ti;
public:
	DB(const XMLStore& xml, const TagIndex& ti): xml(xml), ti(ti) {}

	template<class MIter>
	class query {
		typedef std::list<
			std::pair<mlcvect::const_iterator,mlcvect::const_iterator>
			> itlist;
		itlist	iters;
		pmid_t	next;

		void find_next() {
			int eqcount = 0;
			while (eqcount < iters.size())
			for (itlist::iterator i = iters.begin(); i != iters.end(); ++i) {
				while ((i->first != i->second) && (*(i->first) < next))
					++(i->first);
				if (i->first == i->second) {
					next = 0;
					return;
				} //  *i->first >= next
				if (*(i->first) > next) {
					next = *(i->first);
					eqcount = 1;
				} else {
					eqcount++;
				}
			}
		}
		query(const XMLStore& xml, const TagIndex& ti,
			std::string journal, std::string date,
			MIter mesh_begin,
			MIter mesh_end): next(0)
		{
			if (journal != "") {
				const mlcvect& j = ti.query_journal(journal);
				iters.push_back(make_pair(j.begin(), j.end()));
			}
			if (date != "") {
				const mlcvect& d = ti.query_date(date);
				iters.push_back(make_pair(d.begin(), d.end()));
			}
			while (mesh_begin != mesh_end) {
				const mlcvect& m = ti.query_mesh(*mesh_begin);
				iters.push_back(make_pair(m.begin(), m.end()));
				++mesh_begin;
			}
			find_next();
		}
		friend class DB;
	public:
		bool has_next() {
			return next;
		}
		pmid_t get_next() {
			pmid_t ret = next;
			next++;
			find_next();
			return ret;
		}
	};
	template<class MIter>
	query<MIter> start_query(std::string journal, std::string date,
			MIter mesh_begin,
			MIter mesh_end) {
		return query<MIter>(xml, ti, journal, date, mesh_begin, mesh_end);
	}

};


#endif

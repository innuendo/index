#include "Parser.hpp"

int main()
{
	Parser p("/Users/krzysztofwisniewski/Documents/Work/zadanie1/medline.xml");
	Parser::MLCitationIter it = p.parse();
	return 0;
}

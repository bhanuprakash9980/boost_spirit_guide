#include <boost/spirit/include/qi.hpp>
#include <iostream>
#include <string>

namespace qi = boost::spirit::qi;

int main() {
	std::string input = "12345";
	int n;
	qi::parse( input.begin(), input.end(), qi::int_, n );
	std::cout << n << std::endl;
	return 0;
}
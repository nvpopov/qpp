#include "io/strfun.hpp"

namespace qpp{
template<>
bool s2t<bool>(const STRING & s, bool & val)
{
	STRING s1 = tolower(s);
	if ( (s1 == "yes") || (s1 == "true") || (s1 == "t") || (s1 == "1"))
	{
		val = true;
		return true;
	}
	else if ( (s1 == "no") || (s1 == "false") || (s1 == "f") || (s1 == "0"))
	{
		val = false;
		return true;
	}
	else
	{
		return false;
	}
}

STRING tolower(const STRING & s)
// Make lowercase
{
	STRING ss = s;
	std::transform(ss.begin(), ss.end(), ss.begin(), ::tolower);
	return ss;
}

// -----------------------------------------------------------

bool icompare(const STRING & s1, const STRING s2)
// Case insensitive comparison of two strings
{
	return tolower(s1) == tolower(s2);
}

// -----------------------------------------------------------

void split(const STRING &s, std::vector<STRING> &elems, const STRING & delims  )
// fixme - not efficient!
{
	SSTREAM ss(s);
	tokenizer tok(ss);
	tok.dump(delims);
	tok.separate("");
	elems.clear();

	// std::cerr << "split\n";

	do {
		STRING item = tok.get();

		//std::cerr << "split:\"" << item << "\"";
		if (item.size()==0)
			break;
		elems.push_back(item);
	} while(true);

}

// -----------------------------------------------------------

std::vector<STRING> split(const STRING &s, const STRING & delims )
{
	std::vector<STRING> elems;
	split(s, elems, delims);
	return elems;
}

}

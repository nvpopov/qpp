#include <iostream>
#include <sstream>
#include <string>

using namespace std;

int
main (void)
{
	stringstream ss;
	string inp, w;
	int num;
	char ch;

	while (cin >> inp) {
		inp.resize (inp.size () - 1);
		ss.clear ();
		ss.str ("");
		ss << inp;
		ss >> ch >> num >> ch >> w;
		cout << num << " <--> " << w << endl;
	}

	return 0;
}

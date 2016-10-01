#include "sample.h"
#include <fstream>
#include <string>
#include <iostream>

using namespace std;

int main(int argc, const char ** argv)
{
	if(argc != 2) return 0;

	ifstream fin(argv[1]);
	if(fin.fail()) return 0;

	sample sp;

	string s;
	while(getline(fin, s))
	{
		if(s.size() == 0) continue;
		if(s[0] == '#')
		{
			sp.process();
			sp.clear();
		}
		else
		{
			sp.add_position(s);
		}
	}

	fin.close();
	return 0;
}

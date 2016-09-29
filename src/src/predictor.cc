#include "predictor.h"
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <cstdio>
#include <string>

int predictor::process(const string &file)
{
	ifstream fin(file.c_str());
	if(fin.fail()) return -1;

	stringstream sstr;
	string line;
	int k;
	double f;
	int index = 0;
	while(getline(fin, line))
	{
		if(line[0] != '#') continue;

		//printf("%s\n", line.c_str());

		block b;
		b.index = ++index;
		b.ltype = b.rtype = false;

		// labels
		getline(fin, line);
		sstr.clear();
		sstr<<line.c_str();
		while(sstr>>k) b.labels.push_back(k);

		// abundance
		getline(fin, line);
		sstr.clear();
		sstr<<line.c_str();
		while(sstr>>k) b.s.push_back(k);

		// for average quality
		getline(fin, line);
		sstr.clear();
		sstr<<line.c_str();
		while(sstr>>f) b.q.push_back(f);

		// for windows 20
		getline(fin, line);
		sstr.clear();
		sstr<<line.c_str();
		while(sstr>>k) b.fs20.sa.push_back(k);

		getline(fin, line);
		sstr.clear();
		sstr<<line.c_str();
		while(sstr>>k) b.fs20.sb.push_back(k);

		getline(fin, line);
		sstr.clear();
		sstr<<line.c_str();
		while(sstr>>f) b.fs20.va.push_back(f);

		getline(fin, line);
		sstr.clear();
		sstr<<line.c_str();
		while(sstr>>f) b.fs20.vb.push_back(f);

		// for windows 50
		getline(fin, line);
		sstr.clear();
		sstr<<line.c_str();
		while(sstr>>k) b.fs50.sa.push_back(k);

		getline(fin, line);
		sstr.clear();
		sstr<<line.c_str();
		while(sstr>>k) b.fs50.sb.push_back(k);

		getline(fin, line);
		sstr.clear();
		sstr<<line.c_str();
		while(sstr>>f) b.fs50.va.push_back(f);

		getline(fin, line);
		sstr.clear();
		sstr<<line.c_str();
		while(sstr>>f) b.fs50.vb.push_back(f);

		// for windows 100
		getline(fin, line);
		sstr.clear();
		sstr<<line.c_str();
		while(sstr>>k) b.fs100.sa.push_back(k);

		getline(fin, line);
		sstr.clear();
		sstr<<line.c_str();
		while(sstr>>k) b.fs100.sb.push_back(k);

		getline(fin, line);
		sstr.clear();
		sstr<<line.c_str();
		while(sstr>>f) b.fs100.va.push_back(f);

		getline(fin, line);
		sstr.clear();
		sstr<<line.c_str();
		while(sstr>>f) b.fs100.vb.push_back(f);

		b.predict();
	}
	return 0;
}


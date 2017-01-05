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

	int start1 = 0, start2 = 0, start3 = 0;
	int end1 = 0, end2 = 0, end3 = 0;
	while(getline(fin, line))
	{
		if(line[0] != '#') continue;

		//printf("%s\n", line.c_str());

		block b;
		b.index = ++index;

		// labels
		getline(fin, line);
		sstr.clear();
		sstr<<line.c_str();
		while(sstr>>k) b.labels.push_back(k);

		// real abundance
		getline(fin, line);
		sstr.clear();
		sstr<<line.c_str();
		while(sstr>>k) b.abd.push_back(k);

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

		// for sequences A, C, G, and T
		getline(fin, line);
		sstr.clear();
		sstr<<line.c_str();
		while(sstr>>k) b.seqa.push_back(k);

		getline(fin, line);
		sstr.clear();
		sstr<<line.c_str();
		while(sstr>>k) b.seqc.push_back(k);

		getline(fin, line);
		sstr.clear();
		sstr<<line.c_str();
		while(sstr>>k) b.seqg.push_back(k);

		getline(fin, line);
		sstr.clear();
		sstr<<line.c_str();
		while(sstr>>k) b.seqt.push_back(k);

		// for boundaries
		getline(fin, line);
		sstr.clear();
		sstr<<line.c_str();
		while(sstr>>k) b.pstart.push_back(k);

		getline(fin, line);
		sstr.clear();
		sstr<<line.c_str();
		while(sstr>>k) b.pend.push_back(k);

		b.predict();

		start1 += b.start1;
		start2 += b.start2;
		start3 += b.start2;
		end1 += b.end1;
		end2 += b.end2;
		end3 += b.end2;
	}

	printf("summary START = %d / %d / %d (corrrect / prediction / label), sensitivity = %.3lf, precision = %.3lf\n", 
			start1, start2, start3, start1 * 1.0 / start3, start1 * 1.0 / start2);

	printf("summary END = %d / %d / %d (corrrect / prediction / label), sensitivity = %.3lf, precision = %.3lf\n", 
			end1, end2, end3, end1 * 1.0 / end3, end1 * 1.0 / end2);

	return 0;
}


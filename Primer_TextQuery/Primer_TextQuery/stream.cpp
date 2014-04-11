#include "stream.h"

//open in 
ifstream& open_file(ifstream &in, const string &file)
{
	in.close();
	in.clear();
	in.open(file.c_str());
	return in;
}

//open out into file
ofstream& out_file(ofstream &out, const string &ofile)
{
	out.close();
	out.clear();
	out.open(ofile.c_str());
	return out;
}
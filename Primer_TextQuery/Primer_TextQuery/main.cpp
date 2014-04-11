#include "stream.h"
#include "TextQuery.h"

void print_results(const set<TextQuery::line_no>&, const string&, const TextQuery&);
//return plural(¸´Êý) version of word if ctr is not 1;
string make_plural(size_t, const string&, const string&);

int main(int argc, char **argv)
{
	string fileName;
	cout << "Enter filename" << endl;
	//cin >> fileName;
	fileName = "D:\\git_local\\progam\\Primer_TextQuery\\Primer_TextQuery\\test.txt";
	//open the file from which user will query words
	ifstream infile;
	//if (argc < 2 || !open_file(infile, argv[1]))
	if (!open_file(infile, fileName.c_str()))
	{
		cerr << "NO input file" << endl;
		return EXIT_FAILURE;
	}
	TextQuery tq;
	//builds query map
	tq.read_file(infile);
	//iterator with the user:prompt for a word to find and print results
	//loop indefinitely; the loop exit is inside the while
	while (true)
	{
		cout << "Enter word to look for, or q to quit \n";
		string s;
		cin >> s;
		//stop if hit eof on input or a 'q' is entered
	    if (!cin|| s == "q") 
	    {
			break;
	    }
		//get the set of line numbers on which this word appears
		set<TextQuery::line_no> locs = tq.run_query(s);
		print_results(locs, s, tq);
	}
	return 0;
}

void print_results(const set<TextQuery::line_no>& locs, const string& sought, const TextQuery& file)
{
	//if the word was found, then print count and all occurrences
	typedef set<TextQuery::line_no> line_nums;
	line_nums::size_type size = locs.size();
	cout << "\n" << sought << " occurs "
		<< size << "  "
		<< make_plural(size, "time", "s") << endl;
	//print each line in which the word appeared
	line_nums::const_iterator it = locs.begin();
	for (; it != locs.end(); it++)
	{
		cout << "\t(line "
			<< (*it) + 1 << ") "
			<< file.text_line(*it) << endl;
	}
}

string make_plural(size_t ctr, const string& word, const string& ending)
{
	return (ctr == 1) ? word : word + ending;
}
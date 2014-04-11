#include "TextQuery.h"

 //read_input file:store each line as element in line_of_text
void TextQuery::store_file(ifstream& is)
{
	string textline;
	while (getline(is, textline))
	{
		lines_of_text.push_back(textline);
	}
}

//finds whitespace-separated words in the input vector
//and puts the word in word_map along with the line number
void TextQuery::build_map()
{
	//process each line from the input vector
	for (line_no line_num = 0; line_num != lines_of_text.size();
		++line_num)
	{
		//we will use line to read the text a word at a time
		istringstream line(lines_of_text[line_num]);
		string word;
		while (line >> word)
		{
			//add this line number to the set;
			//subscript will add word to the map if it is not
			//already there
			word_map[word].insert(line_num);
		}
	}
}

set<TextQuery::line_no>
TextQuery::run_query(const string& query_word) const
{
	//Note:must use find and not subscript the map directly
	//to avoid adding words to word_map
	map<string, set<line_no> >::const_iterator loc
		= word_map.find(query_word);
	if (loc == word_map.end())
		return set<line_no>(); //not found return empty set
	else
		//fetch and return set of line numbers for this word
		return loc->second;
}

string TextQuery::text_line(line_no line) const
{
	if (line < lines_of_text.size())
	{
		return lines_of_text[line];
	}
	throw out_of_range("line number out of number");
}

//returns union of its operands' result sets
set<TextQuery::line_no>
OrQuery::eval(const TextQuery& file) const
{
	//virtual calls through the Query handle to get results sets for the operands
	set<line_no> right = rhs.eval(file),
		ret_lines = lhs.eval(file);
	//inserts the lines from right that are not already in ret_lines
	ret_lines.insert(right.begin(), right.end());
	return ret_lines;
}

//returns intersection of its operands' result sets
set<TextQuery::line_no>
AndQuery::eval(const TextQuery& file) const
{
	//virtual calls through the Query handle to get results sets for the operands
	set<line_no> left = lhs.eval(file),
		right = rhs.eval(file);
	set<line_no> ret_lines;
	set_intersection(left.begin(), left.end(), right.begin(), right.end(), inserter(ret_lines, ret_lines.begin()));
	return ret_lines;
}

//returns lines not in its operands' result set
set<TextQuery::line_no>
NotQuery::eval(const TextQuery& file) const
{
	//virtual calls through the Query handle to get results sets for the operands
	set<TextQuery::line_no> has_val = query.eval(file);
	set<line_no> ret_lines;
	for (TextQuery::line_no n = 0; n != file.size(); ++n)
	{
		if (has_val.find(n) == has_val.end())
		{
			ret_lines.insert(n);
		}
	}
	return ret_lines;
}

//Query ÀàÖØÔØ²Ù×÷·û:& | ~ 
inline Query operator&(const Query &lhs, const Query &rhs)
{
	return new AndQuery(lhs, rhs);
}

inline Query operator|(const Query &lhs, const Query &rhs)
{
	return new OrQuery(lhs, rhs);
}

inline Query operator~(const Query& oper)
{
	return new NotQuery(oper);
}


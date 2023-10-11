#pragma once
#include"json.h"
#include<string>
namespace GGo {
namespace Json {


//Json½âÎöÆ÷Àà
class Parser {

public:
	Parser();
	~Parser() = default;
	void load(const string& str);
	Json Parse();
private:
	void skip_white_space();
	void skip_comment();
	char get_next_token();

	Json parse_null();
	Json parse_bool();
	Json parse_number();
	Json parse_string();
	Json parse_array();
	Json parse_object();
	

	bool is_esc_consume(size_t pos);
private:
	string m_str;
	size_t m_index;
};

}}
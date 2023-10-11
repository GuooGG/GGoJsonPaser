#include"parser.h"

using namespace GGo::Json;

Parser::Parser() 
	:m_index(0)
{

}

void GGo::Json::Parser::load(const string& str)
{
	m_str = str;
	m_index = 0;
}



void GGo::Json::Parser::skip_white_space()
{
	while (m_str[m_index] == ' '
		|| m_str[m_index] == '\r'
		|| m_str[m_index] == '\n'
		|| m_str[m_index] == '\t'
		) {
		m_index++;
	}
}

void GGo::Json::Parser::skip_comment()
{
	//����ע��
	if (m_str.compare(m_index, 2, R"(//)") == 0) {
		while (true) {
			auto next_pos = m_str.find('\n', m_index);
			if (next_pos == string::npos) {
				throw logic_error("invalid comment area!");
			}
			//��һ������
			m_index = next_pos + 1;
			while (isspace(m_str[m_index])) {
				m_index++;
			}
			if (m_str.compare(m_index, 2, R"(\\)") != 0) {
				//�ҵ���Ϊע�͵�����
				return;
			}
		}
	}
}

char GGo::Json::Parser::get_next_token()
{
	//�����հ��ַ�
	while (std::isspace(m_str[m_index]))m_index++;
	if (m_index >= m_str.size()) {
		throw logic_error("unexpected end of input");
	}
	//����ע��
	skip_comment();
	return m_str[m_index];
}


Json GGo::Json::Parser::Parse()
{
	char token = get_next_token();
	if (token == 'n') {
		return parse_null();
	}
	if (token == 't' || token == 'f') {
		return parse_bool();
	}
	if (token == '-' || std::isdigit(token)) {
		return parse_number();
	}
	if (token == '\"') {
		return parse_string();
	}
	if (token == '[') {
		return parse_array();
	}
	if (token == '{') {
		return parse_object();
	}
	throw logic_error("unexpected character while parsing json");
}

Json GGo::Json::Parser::parse_null()
{
	if (m_str.compare(m_index, 4, "null") == 0) {
		m_index += 4;
		return Json();
	}
	throw logic_error("parse null error");
}

Json GGo::Json::Parser::parse_bool()
{
	if (m_str.compare(m_index, 4, "true") == 0) {
		m_index += 4;
		return Json(true);
	}
	if (m_str.compare(m_index, 5, "false") == 0) {
		m_index += 5;
		return Json(false);
	}
	throw logic_error("parse bool error");
}

Json GGo::Json::Parser::parse_number() {
	size_t pos = m_index;
	if (m_str[m_index] == '-') {
		m_index++;
	}
	//��������
	if (isdigit(m_str[m_index])) {
		while (isdigit(m_str[m_index])) {
			m_index++;
		}
	}
	else {
		throw logic_error("invalid character in number parse");
	}
	if (m_str[m_index] != '.') {
		return Json(std::atoi(m_str.c_str() + pos));
	}
	//���㲿��
	if (m_str[m_index] == '.') {
		m_index++;
		if (!isdigit(m_str[m_index])) {
			throw logic_error("invalid character in number parse");
		}
		while (isdigit(m_str[m_index])) {
			m_index++;
		}
	}
	return Json(std::atof(m_str.c_str() + pos));
}
Json GGo::Json::Parser::parse_string() {
	auto pre_pos = ++m_index;
	auto pos = m_str.find('"', m_index);
	if (pos != string::npos)
	{
		//������û�н�������Ҫ�ж��Ƿ���ת��Ľ������ţ������ת�壬����Ҫ����̽��
		while (true)
		{
			if (m_str[pos - 1] != '\\') //�������ת�����������
			{
				break;
			}
			//�����ת���ַ������ж��Ƿ��Ѿ����������Ѿ������������������������Ѱ���¸��ַ���������
			if (is_esc_consume(pos - 1))
			{
				break;
			}
			pos = m_str.find('"', pos + 1);
			if (pos == string::npos)
			{
				throw std::logic_error(R"(expected left '"' in parse string)");
			}
		}
		m_index = pos + 1;
		return m_str.substr(pre_pos, pos - pre_pos);
	}
	throw std::logic_error("parse string error");
}
bool GGo::Json::Parser::is_esc_consume(size_t pos)
{
	size_t end_pos = pos;
	while (m_str[pos] == '\\') pos--;
	auto cnt = end_pos - pos;
	//��� \ �ĸ���Ϊż������ɹ����������Ϊ��������δ����
	return cnt % 2 == 0;
}

Json GGo::Json::Parser::parse_array() {
	Json arr(json_array);
	m_index++;
	char ch = get_next_token();
	if (ch == ']')
	{
		m_index++;
		return arr;
	}

	while (true)
	{
		arr.append(Parse());
		ch = get_next_token();
		if (ch == ']')
		{
			m_index++;
			break;
		}

		if (ch != ',') //������Ƕ���
		{
			throw std::logic_error("expected ',' in parse list");
		}
		//��������
		m_index++;
	}
	return arr;
}
Json GGo::Json::Parser::parse_object() {
	Json obj(json_object);
	m_index++;
	char ch = get_next_token();
	if (ch == '}')
	{
		m_index++;
		return obj;
	}
	while (true)
	{
		//����key
		string key = std::move(Parse());
		ch = get_next_token();
		if (ch != ':')
		{
			throw std::logic_error("expected ':' in parse dict");
		}
		m_index++;

		//����value
		obj[key] = Parse();
		ch = get_next_token();
		if (ch == '}')
		{
			m_index++;
			break; //�������
		}
		if (ch != ',')//û�н�������ʱ����Ϊ����
		{
			throw std::logic_error("expected ',' in parse dict");
		}
		//��������
		m_index++;
	}
	return obj;
}
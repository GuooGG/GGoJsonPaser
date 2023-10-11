#include"json.h"

using namespace GGo::Json;

Json::Json()
	:m_type(json_null)
	, m_value("null")
{}
Json::Json(bool value)
	: m_type(json_bool)
	, m_value(value)
{}
Json::Json(int value)
	: m_type(json_int)
	, m_value(value)
{}
Json::Json(double value)
	: m_type(json_double)
	, m_value(value)
{}
Json::Json(const char* value)
	: m_type(json_string)
	, m_value(string(value))
{}
Json::Json(const string& value)
	: m_type(json_string)
	, m_value(value)
{}
Json::Json(Type type)
	: m_type(type)
{
	switch (m_type)
	{
	case json_null:
		m_value = "null";
		break;
	case json_bool:
		m_value = false;
		break;
	case json_int:
		m_value = 0;
		break;
	case json_double:
		m_value = 0.0f;
		break;
	case json_string:
		m_value = "";
		break;
	case json_array:
		m_value = array_t();
	case json_object:
		m_value = object_t();
	default:
		throw logic_error("Invalid type.");
	}
}
//�������캯����std::variant���͵ĳ�Ա�����Զ��Ե�ǰ�洢��ֵ����
//������Ӧ���������
Json::Json(const Json& other)
	:m_type(other.m_type)
	, m_value(other.m_value)
{}
//Json����ת���ڻ�������
Json::operator bool() {
	if (m_type != json_bool) {
		throw std::logic_error("function Json::operator (bool) requires bool value");
	}
	return get<bool>(m_value);
}
Json::operator int() {
	if (m_type != json_int) {
		throw std::logic_error("function Json::operator (int) requires int value");
	}
	return get<int>(m_value);
}
Json::operator double() {
	if (m_type != json_double) {
		throw std::logic_error("function Json::operator (double) requires double value");
	}
	return get<double>(m_value);
}
Json::operator string() {
	if (m_type != json_string) {
		throw std::logic_error("function Json::operator (string) requires string value");
	}
	return get<string>(m_value);
}
//ʵ����������
Json& Json::operator[](int index)
{
	if (m_type != json_array) {
		//�����Ͳ�Ϊ����,������Ϊnull
		if (m_type == json_null) {
			//����������תΪ����
			//std::variant���Զ���վ��ڴ棬�����ֶ����
			m_type = json_array;
			m_value = array_t();
		}
		else {
			//�������Ͳ�Ϊ������Ҳ��Ϊnull�������˳�
			throw std::logic_error("need  array type json.");
		}
	}
	if (index < 0)
	{
		throw std::logic_error("function Json::operator [int] index less than 0");
	}
	array_t& arr = get<array_t>(m_value);
	int size = arr.size();
	if (index < size) {
		auto it = arr.begin();
		for (int i = 0; i < index; i++) {
			it++;
		}
		return *it;
	}
	for (int i = size; i <= index; i++) {
		arr.push_back(Json());
	}
	return arr.back();
}
void Json::append(Json other) {
	if (m_type != json_array) {

	}
}
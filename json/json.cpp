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
		break;
	case json_object:
		m_value = object_t();
		break;
	default:
		throw logic_error("Invalid type.");
	}
}
//拷贝构造函数，std::variant类型的成员变量自动对当前存储的值类型
//进行相应的深拷贝操作
Json::Json(const Json& other)
	:m_type(other.m_type)
	, m_value(other.m_value)
{}
//Json类型转化内基础类型
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
		throw logic_error("function Json::operator (double) requires double value");
	}
	return get<double>(m_value);
}
Json::operator string() {
	if (m_type != json_string) {
		throw logic_error("function Json::operator (string) requires string value");
	}
	return get<string>(m_value);
}
//实现数组类型
Json& Json::operator[](int index)
{
	if (m_type != json_array) {
		//若类型不为数组,且类型为null
		if (m_type == json_null) {
			//将自身类型转为数组
			//std::variant会自动清空旧内存，无需手动清空
			m_type = json_array;
			m_value = array_t();
		}
		else {
			//自身类型不为数组且也不为null，报错退出
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
		if (m_type == json_null) {
			m_type = json_array;
			m_value = array_t();
		}
		throw std::logic_error("need  array type json.");
	}
	auto& arr = get<array_t>(m_value);
	arr.push_back(std::move(other));
	return;
}


//实现Json对象类型API
Json& Json::operator[](const char* key) {
	return (*this)[string(key)];
}
Json& Json::operator[](const string& key) {
	if (m_type == json_null) {
		m_type = json_object;
		m_value = object_t();
	}
	if (m_type == json_object) {
		auto& obj = get<object_t>(m_value);
		return obj[key];
	}
	throw std::logic_error("not dict type! JObject::opertor[]()");
}
Json& Json::operator = (const Json& other) {
	m_type = other.m_type;
	m_value = other.m_value;
	return *this;
}


//Json类型可视化
string Json::str()const {
	stringstream ss;
	switch (m_type)
	{
	case json_null:
		ss << "null";
		break;
	case json_bool:
		if (get<bool_t>(m_value))
		{
			ss << "true";
		}
		else
		{
			ss << "false";
		}
		break;
	case json_int:
		ss << get<int_t>(m_value);
		break;
	case json_double:
		ss << get<double_t>(m_value);
		break;
	case json_string:
		ss << "\"" << get<string_t>(m_value) << "\"";
		break;
	case json_array:
	{
		auto& arr = get<array_t>(m_value);
		ss << "[";
		for (auto it = arr.begin(); it != arr.end(); it++) {
			if (it != arr.begin()) {
				ss << ",";
			}
			ss << it->str();
		}
		ss << "]";
	}
	break;
	case json_object:
	{
		auto& obj = get<object_t>(m_value);
		ss << "{";
		for (auto it = obj.begin(); it != obj.end(); it++) 
		{
			if (it != obj.begin())
			{
				ss << ",";
			}
			ss << "\"" << it->first << "\":" << it->second.str();
		}
		ss << "}";
	}
	break;
	default:
		break;
	}
	return ss.str();
}
/*
��Ŀ����: GGoJsonPaser
��Ŀ���ܣ�һ���򵥵�Json������demo��������ϰ��Ŀ����ʹ�������������⣬�ܹ���ƽ̨ʹ��
���ߣ�	GGo
��ʼʱ�䣺2023/10/10 20��00
*/
#pragma once

#include<string>
#include<vector>
#include<stdexcept>
#include<map>
#include<sstream>
#include<variant>
#include<string_view>
//�����ռ�������
namespace GGo {
namespace Json {
	//variant��C++17�������һ�����ͣ�������һ�����Ͱ�ȫ��������
	using std::variant;
	using std::string;
	using std::vector;
	using std::map;
	using std::stringstream;
	using std::logic_error;
	using std::string_view;
	using std::get_if;
	//Json����ö����
	enum class Type {
		json_null = 0,
		json_bool,
		json_int,
		json_double,
		json_string,
		json_array,
		json_object
	};
	using enum Type;
	class Json;
	//����������
	using null_t = string;
	using int_t = int;
	using bool_t = bool;
	using double_t = double;
	using string_t = string;
	using array_t = vector<Json>;
	using object_t = map<string, Json>;

//Json����ʵ��
class Json {
public:
	using Value = variant<bool_t, int_t, double_t, string_t, array_t, object_t>;
	//��������ת��ΪJson���͹��캯��
	Json();
	//��������ת��ΪJson���͹��캯��
	Json(bool value);
	Json(int value);
	Json(double value);
	Json(const char* value);
	Json(const string & value);
	Json(Type type);
	//��������
	Json(const Json& other);
	//�����������ͷŷ����ڴ�
	~Json() = default;
	//Json����ת��Ϊ��������API
	operator bool();
	operator int();
	operator double();
	operator string();

	//ʵ��Json��������API
	Json& operator[](int index);
	void append(Json other);
	
	//ʵ��Json��������API
	Json& operator[](const char* key);
	Json& operator[](const string& key);

	//�������������
	void operator = (const Json& other);
	bool operator == (const Json& other);
	bool operator != (const Json& other);
	//Json���Ϳ��ӻ�
	string str()const;
	//����ڴ�
	void clear();

private:
	////������洢Jsonֵ��ʡ�ڴ濪��
	//union Value {
	//	bool m_bool;
	//	int m_int;
	//	double m_double;
	//	std::string* m_string;
	//	std::vector<Json>* m_array;
	//	std::map<std::string, Json>* m_object;
	//};
	Type m_type;
	Value m_value;
};


}
}

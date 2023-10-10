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
//�����ռ�������
namespace GGo {
namespace Json {
//Json����ʵ��
class Json {
public:
	enum Type {
		json_null = 0,
		json_bool,
		json_int,
		json_double,
		json_string,
		json_array,
		json_object
	};
	//��������ת��ΪJson����API
	Json();
	Json(bool value);
	Json(int value);
	Json(double value);
	Json(const char* value);
	Json(const std::string & value);
	Json(Type type);
	Json(const Json& other);
	//��������
	void copy(const Json& other);
	//Json����ת��Ϊ��������API
	operator bool();
	operator int();
	operator double();
	operator std::string();

	//ʵ��Json��������API
	Json& operator[](int index);
	void append(const Json& other);
	
	//ʵ��Json��������API
	Json& operator[](const char* key);
	Json& operator[](const std::string& key);
	void operator = (const Json& other);
	bool operator == (const Json& other);
	bool operator != (const Json& other);
	//Json���Ϳ��ӻ�
	std::string str()const;
	//����ڴ�
	void clear();
	//������������������������json,��δ���û�д������Ͳ�Ϊ������������bug
	typedef std::vector<Json>::iterator iterator;
	iterator begin() {
		return m_value.m_array->begin();
	}
	iterator end() {
		return m_value.m_array->end();
	}
private:
	//������洢Jsonֵ��ʡ�ڴ濪��
	union Value {
		bool m_bool;
		int m_int;
		double m_double;
		std::string* m_string;
		std::vector<Json>* m_array;
		std::map<std::string, Json>* m_object;
	};
	Type m_type;
	Value m_value;
};


}
}

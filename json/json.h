/*
项目名称: GGoJsonPaser
项目介绍：一个简单的Json解析器demo，个人练习项目，不使用其他第三方库，能够跨平台使用
作者：	GGo
开始时间：2023/10/10 20：00
*/
#pragma once

#include<string>
#include<vector>
#include<stdexcept>
#include<map>
//命名空间隔离变量
namespace GGo {
namespace Json {
//Json类型实现
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
	//基本类型转换为Json类型API
	Json();
	Json(bool value);
	Json(int value);
	Json(double value);
	Json(const char* value);
	Json(const std::string & value);
	Json(Type type);
	Json(const Json& other);
	//拷贝方法
	void copy(const Json& other);
	//Json类型转换为基本类型API
	operator bool();
	operator int();
	operator double();
	operator std::string();

	//实现Json数组类型API
	Json& operator[](int index);
	void append(const Json& other);
	
	//实现Json对象类型API
	Json& operator[](const char* key);
	Json& operator[](const std::string& key);
	void operator = (const Json& other);
	bool operator == (const Json& other);
	bool operator != (const Json& other);
	//Json类型可视化
	std::string str()const;
	//清空内存
	void clear();
	//定义迭代器方便遍历数组类型json,这段代码没有处理类型不为数组的情况，有bug
	typedef std::vector<Json>::iterator iterator;
	iterator begin() {
		return m_value.m_array->begin();
	}
	iterator end() {
		return m_value.m_array->end();
	}
private:
	//联合体存储Json值节省内存开销
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

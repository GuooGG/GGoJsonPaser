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
#include<sstream>
#include<variant>
#include<string_view>
//命名空间隔离变量
namespace GGo {
namespace Json {
	//variant是C++17新引入的一种类型，代表了一种类型安全的联合体
	using std::variant;
	using std::string;
	using std::vector;
	using std::map;
	using std::stringstream;
	using std::logic_error;
	using std::string_view;
	using std::get_if;
	//Json类型枚举类
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
	//类型名定义
	using null_t = string;
	using int_t = int;
	using bool_t = bool;
	using double_t = double;
	using string_t = string;
	using array_t = vector<Json>;
	using object_t = map<string, Json>;

//Json类型实现
class Json {
public:
	using Value = variant<bool_t, int_t, double_t, string_t, array_t, object_t>;
	//基本类型转换为Json类型构造函数
	Json();
	//基本类型转换为Json类型构造函数
	Json(bool value);
	Json(int value);
	Json(double value);
	Json(const char* value);
	Json(const string & value);
	Json(Type type);
	//拷贝方法
	Json(const Json& other);
	//析构函数，释放分配内存
	~Json() = default;
	//Json类型转换为基本类型API
	operator bool();
	operator int();
	operator double();
	operator string();

	//实现Json数组类型API
	Json& operator[](int index);
	void append(Json other);
	
	//实现Json对象类型API
	Json& operator[](const char* key);
	Json& operator[](const string& key);

	//基本运算符重载
	void operator = (const Json& other);
	bool operator == (const Json& other);
	bool operator != (const Json& other);
	//Json类型可视化
	string str()const;
	//清空内存
	void clear();

private:
	////联合体存储Json值节省内存开销
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

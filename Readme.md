# GGoJsonParser
项目简介：一个简单的json解析器，不使用其他第三方库，API友好易懂，是个人造轮子的练习项目。

完成时间：2023/10/11 18：33

作者：        GGo

## 结构
### 主目录
* main.cpp
集中测试代码
### json文件夹
 * json.h\json.cpp
完成json类型的编写
 * parser.h\parser.cpp
完成json解析器类型的编写

## 项目解析与使用方法
 * 所有非测试代码集中在`namespace GGo::Json`中以用来隔离变量
 * 使用C++17标准中新加入的`std::varient`,一种全新的类型安全联合体类型，同时方便内存的自动管理
 

### Json基本类型
Json中的数据类型如下图
![](https://www.json.org/img/value.png)
```
	enum class Type {
		json_null = 0,
		json_bool,
		json_int,
		json_double,
		json_string,
		json_array,
		json_object
	};
```
以上枚举类型对应Value的Type：
1. null类型
2. 布尔类型
3. 整型类型
4. 浮点类型
5. 字符串类型
6. 数组类型
7. 对象类型
其中**6.数组类型**和**7.对象类型**为**复合类型**，可互相包含全部七种类型。
定义`using Value = variant<bool_t, int_t, double_t, string_t, array_t, object_t>;`作为值的类型（上文提到的类型安全联合体类型）
```C++
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
	Json& operator = (const Json& other);

	//Json类型可视化
	string str()const;

private:

	Type m_type;
	Value m_value;
};
```
### 基本类型与Json对象的相互转换
```C++
Json v1;
Json v2 = true;
Json v3 = 3;
Json v4 = "json4";
Json v5 = 5.5;

int a3 = v3;
bool a2 = v2;
string a4 = v4;
double a5 = v5;
```
为了实现以上的功能，需要编写完善以下若干函数
```C++
//基本类型转换为Json类型构造函数
Json(bool value);
Json(int value);
Json(double value);
Json(const char* value);
Json(const string & value);
Json(Type type);
//Json类型转换为基本类型API
operator bool();
operator int();
operator double();
operator string();
	
```
### Json的数组功能API
```C++
Json arr;
Json arr2;
arr[0] = true;
arr[1] = 123;
arr.append(1.23);
arr.append("hello,world!");
arr2[0] = false;
arr2[1] = 234;
arr2[2] = 3.56;
arr.append(arr2);
bool b = arr[0];
int i = arr[1];
double f = arr[2];
const string& s = arr[3];	
```
下列函数实现以上功能
```C++
//实现Json数组类型API
Json& operator[](int index);
void append(Json other);
```
### Json的对象功能API
```C++
Json obj;
obj["bool"] = true;
obj["int"] = 123;
obj["double"] = 1.23f;
obj["str"] = "hello obj!";
```
下列函数需要实现，同时支持C/C++风格的字符串
```C++
//实现Json对象类型API
Json& operator[](const char* key);
Json& operator[](const string& key);
Json& operator = (const Json& other);
```
### 其他功能
同时还应该支持拷贝方法：
```C++
//拷贝方法
Json(const Json& other);
```
字符串化方法：
```C++
//Json类型可视化
string str()const;
```
以上便是一个基本Json类型具有的核心API。具体实现见[json.cpp](json/json.cpp)
### Parser类型
类型定义代码
```C++
//Json解析器类
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
```
Parser类内部包含的成员：
1. `string m_str;`待解析的Json字符串
2. `size_t m_index`指向当前解析位置的指针
3. `void load(const string& str)`传入待解析的Json字符串
4. `Json Parse()`解析m_str
5. `void skip_white_space()`跳过空白字符
6. `void skip_comment()`跳过注释
7. `char get_next_token()`得到下一个token
8. `Json parse_null()`等等方法，解析特定值的内容
9. `bool is_esc_consume(size_t pos)`检查反斜杠是否可以折叠
#### 解析m_str
```C++
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

```
#### 解析null
```C++
Json GGo::Json::Parser::parse_null()
{
	if (m_str.compare(m_index, 4, "null") == 0) {
		m_index += 4;
		return Json();
	}
	throw logic_error("parse null error");
}
```
#### 解析bool
```C++
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
```
#### 解析number
```C++
Json GGo::Json::Parser::parse_number() {
	size_t pos = m_index;
	if (m_str[m_index] == '-') {
		m_index++;
	}
	//整数部分
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
	//浮点部分
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
```
#### 解析string
```C++
Json GGo::Json::Parser::parse_string() {
	auto pre_pos = ++m_index;
	auto pos = m_str.find('"', m_index);
	if (pos != string::npos)
	{
		//解析还没有结束，需要判断是否是转义的结束符号，如果是转义，则需要继续探查
		while (true)
		{
			if (m_str[pos - 1] != '\\') //如果不是转义则解析结束
			{
				break;
			}
			//如果是转义字符，则判断是否已经被抵消，已经被消耗完则跳出，否则继续寻找下个字符串结束符
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
```
#### 解析array
```C++
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

		if (ch != ',') //如果不是逗号
		{
			throw std::logic_error("expected ',' in parse list");
		}
		//跳过逗号
		m_index++;
	}
	return arr;
}
```
#### 解析object
```C++
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
		//解析key
		string key = std::move(Parse());
		ch = get_next_token();
		if (ch != ':')
		{
			throw std::logic_error("expected ':' in parse dict");
		}
		m_index++;

		//解析value
		obj[key] = Parse();
		ch = get_next_token();
		if (ch == '}')
		{
			m_index++;
			break; //解析完毕
		}
		if (ch != ',')//没有结束，此时必须为逗号
		{
			throw std::logic_error("expected ',' in parse dict");
		}
		//跳过逗号
		m_index++;
	}
	return obj;
}
```
详细实现代码见[parser.cpp](json/parser.cpp)
### 使用方法
```C++
	string json = R"()";
	//测试json解析器代码
	Parser parser;
	parser.load(json);
	Json parsed = parser.Parse();
	cout << parsed.str();
```





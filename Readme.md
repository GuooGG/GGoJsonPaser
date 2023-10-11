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

## 项目解析简使用方法
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




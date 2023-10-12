#include<iostream>
using namespace std;

#include"json/json.h"
#include"json/parser.h"
using namespace GGo::Json;
int main() {
	//std::cout << "hello json!" << std::endl;
	//基本类型转换成json构造函数
	//Json v1;
	//Json v2 = true;
	//Json v3 = 3;
	//Json v4 = "json4";
	//Json v5 = 5.5;

	//int a3 = v3;
	//bool a2 = v2;
	//string a4 = v4;
	//double a5 = v5;
	//
	//Json arr;
	//Json arr2;
	//arr[0] = true;
	//arr[1] = 123;
	//arr.append(1.23);
	//arr.append("hello,world!");
	//arr2[0] = false;
	//arr2[1] = 234;
	//arr2[2] = 3.56;
	//arr.append(arr2);
	////bool b = arr[0];
	////int i = arr[1];
	////double f = arr[2];
	////const string& s = arr[3];	
	Json obj;
	obj["bool"] = true;
	obj["int"] = 123;
	obj["double"] = 1.23f;
	obj["str"] = "hello obj!";
	//arr.append(obj);
	//string json = obj.str();
	////cout << json << endl;

	Json arr;
	Json arr2(json_array);
	arr[0] = 1;
	arr2.append(1);
	arr2.append(2);
	arr2.append(3);
	arr2.append("hello");
	arr.append(arr2);
	arr.append(obj);

	string json = R"()";
	//测试json解析器代码
	Parser parser;
	parser.load(json);
	Json parsed = parser.Parse();
	cout << parsed.str();
	return 0;
}
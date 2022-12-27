#pragma once
#include <string>

class Object
{
public:
	Object(const char* type,const char* name,bool isBase = false);
private:
	std::string type;
	std::string name;
	//是否为基础对象
	bool isBase;
};
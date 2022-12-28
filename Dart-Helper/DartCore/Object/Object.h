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


namespace Dart212
{
	class TypedDataBase
	{
	public:
		static intptr_t ElementSizeInBytes(int32_t cid);
		static intptr_t ElementType(int32_t cid);
	private:
		static intptr_t element_size(intptr_t index);
	};
	class TypedData :public TypedDataBase {
	public:

	};
}


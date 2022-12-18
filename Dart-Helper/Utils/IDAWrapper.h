#pragma once

#include <string>
#include <vector>
#include <map>

class IDAWrapper
{
public:
	//导出函数相关
	static unsigned int get_entry_qty();
	static unsigned int get_entry_ordinal(size_t idx);
	static unsigned int get_entry(size_t order);
	static std::string get_entry_name(size_t order);
	//获取name->addr导出表
	static std::map<std::string, unsigned int> get_entry_map();

	//加载区段数据
	//传入区段任一地址,返回整个区段数据
	static std::vector<unsigned char>read_seg_data(unsigned int addr);
};
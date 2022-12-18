#include "IDAWrapper.h"
#include <pro.h>
#include <entry.hpp>
#include <bytes.hpp>
#include <segment.hpp>

unsigned int IDAWrapper::get_entry_qty()
{
	return ::get_entry_qty();
}

unsigned int IDAWrapper::get_entry_ordinal(size_t idx)
{
	return ::get_entry_ordinal(idx);
}

unsigned int IDAWrapper::get_entry(size_t ord)
{
	return ::get_entry(ord);
}

std::string IDAWrapper::get_entry_name(size_t order)
{
	std::string retName;
	qstring buf;
	if (::get_entry_name(&buf, order) == -1) {
		return retName;
	}
	retName.assign(buf.c_str(),buf.length());
	return retName;
}

std::map<std::string, unsigned int> IDAWrapper::get_entry_map()
{
	std::map<std::string, unsigned int> retMap;
	size_t entryCount = ::get_entry_qty();
	for (unsigned int idx = 0; idx < entryCount; ++idx) {
		unsigned int order = ::get_entry_ordinal(idx);
		unsigned int funcAddr = ::get_entry(order);
		retMap[IDAWrapper::get_entry_name(order)] = funcAddr;
	}
	return retMap;
}

std::vector<unsigned char> IDAWrapper::read_seg_data(unsigned int addr)
{
	std::vector<unsigned char> retBuf;
	segment_t* pSeg = ::getseg(addr);
	if (!pSeg) {
		return retBuf;
	}
	std::uint32_t segmentSize = pSeg->size();
	retBuf.resize(segmentSize, 0x0);
	::get_bytes(&retBuf[0], segmentSize, pSeg->start_ea);
	return retBuf;
}

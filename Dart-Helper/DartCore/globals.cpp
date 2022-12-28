#include "globals.h"
#include "class_id.h"
#include "utils.h"

int kWordSizeLog2;
int kWordSize;
int kObjectAlignment;
int kObjectAlignmentLog2;
int kBitsPerWordLog2;
int kBitsPerWord;

namespace Dart212
{
	bool IsTypedDataClassId(intptr_t index)
	{
		return IsTypedDataBaseClassId(index) && ((index - kTypedDataInt8ArrayCid) %
			3) == kTypedDataCidRemainderInternal;
	}

	bool IsTypedDataBaseClassId(intptr_t index) {
		return index >= kTypedDataInt8ArrayCid && index < kByteDataViewCid;
	}

	bool IsTypedDataViewClassId(intptr_t index) {
		const bool is_byte_data_view = index == kByteDataViewCid;
		return is_byte_data_view ||
			(IsTypedDataBaseClassId(index) &&
				((index - kTypedDataInt8ArrayCid) % 3) == kTypedDataCidRemainderView);
	}

	bool IsExternalTypedDataClassId(intptr_t index)
	{
		return IsTypedDataBaseClassId(index) && ((index - kTypedDataInt8ArrayCid) %
			3) == kTypedDataCidRemainderExternal;
	}

}



intptr_t RoundedAllocationSize(intptr_t size)
{
	return Utils::RoundUp(size, kObjectAlignment);
}
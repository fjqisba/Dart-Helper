#include "globals.h"
#include "class_id.h"
#include "utils.h"

int kWordSizeLog2;
int kWordSize;
int kObjectAlignment;
int kObjectAlignmentLog2;
int kBitsPerWordLog2;
int kBitsPerWord;

bool IsTypedDataViewClassId(intptr_t index)
{
	if (index == kByteDataViewCid) {
		return true;
	}
	if (IsTypedDataBaseClassId(index) && ((index - kTypedDataInt8ArrayCid) % 4) == kTypedDataCidRemainderView) {
		return true;
	}
	return false;
}

bool IsTypedDataBaseClassId(intptr_t index) {
	// Make sure this is updated when new TypedData types are added.
	return index >= kTypedDataInt8ArrayCid && index < kByteDataViewCid;
}

bool IsExternalTypedDataClassId(intptr_t index) {
	// Make sure this is updated when new TypedData types are added.
	return IsTypedDataBaseClassId(index) && ((index - kTypedDataInt8ArrayCid) %
		4) == kTypedDataCidRemainderExternal;
}

intptr_t RoundedAllocationSize(intptr_t size)
{
	return Utils::RoundUp(size, kObjectAlignment);
}
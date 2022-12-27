#pragma once
#include <cstdint>

constexpr uint32_t kMaxUint32 = 0xFFFFFFFF;

// System-wide named constants.
constexpr intptr_t KBLog2 = 10;
constexpr intptr_t KB = 1 << KBLog2;
constexpr intptr_t MBLog2 = KBLog2 + KBLog2;
constexpr intptr_t MB = 1 << MBLog2;
constexpr intptr_t GBLog2 = MBLog2 + KBLog2;
constexpr intptr_t GB = 1 << GBLog2;

// Keep these in sync with the cid numbering above.
const int kTypedDataCidRemainderInternal = 0;
const int kTypedDataCidRemainderView = 1;
const int kTypedDataCidRemainderExternal = 2;
const int kTypedDataCidRemainderUnmodifiable = 3;

const int kCachedDescriptorCount = 32;
const int kCachedICDataArrayCount = 4;

template <class D, class S>
__forceinline D bit_cast(const S& source) {
    D destination;
    // This use of memcpy is safe: source and destination cannot overlap.
    memcpy(&destination, &source, sizeof(destination));
    return destination;
}

bool IsTypedDataBaseClassId(intptr_t index);

bool IsTypedDataViewClassId(intptr_t index);

bool IsTypedDataBaseClassId(intptr_t index);

bool IsExternalTypedDataClassId(intptr_t index);
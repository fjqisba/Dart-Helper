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

constexpr int kInt8SizeLog2 = 0;
constexpr int kInt8Size = 1 << kInt8SizeLog2;
constexpr int kInt16SizeLog2 = 1;
constexpr int kInt16Size = 1 << kInt16SizeLog2;
constexpr int kInt32SizeLog2 = 2;
constexpr int kInt32Size = 1 << kInt32SizeLog2;
constexpr int kInt64SizeLog2 = 3;
constexpr int kInt64Size = 1 << kInt64SizeLog2;

// Bit sizes.
constexpr int kBitsPerByteLog2 = 3;
constexpr int kBitsPerByte = 1 << kBitsPerByteLog2;
constexpr int kBitsPerInt8 = kInt8Size * kBitsPerByte;
constexpr int kBitsPerInt16 = kInt16Size * kBitsPerByte;
constexpr int kBitsPerInt32 = kInt32Size * kBitsPerByte;
constexpr int kBitsPerInt64 = kInt64Size * kBitsPerByte;

// Byte sizes for native machine words.
extern int kWordSizeLog2;
extern int kWordSize;
extern int kObjectAlignment;
extern int kObjectAlignmentLog2;
extern int kBitsPerWordLog2;
extern int kBitsPerWord;

struct simd128_value_t {
    union {
        int32_t int_storage[4];
        int64_t int64_storage[2];
        float float_storage[4];
        double double_storage[2];
    };
    simd128_value_t& readFrom(const float* v) {
        float_storage[0] = v[0];
        float_storage[1] = v[1];
        float_storage[2] = v[2];
        float_storage[3] = v[3];
        return *this;
    }
    simd128_value_t& readFrom(const int32_t* v) {
        int_storage[0] = v[0];
        int_storage[1] = v[1];
        int_storage[2] = v[2];
        int_storage[3] = v[3];
        return *this;
    }
    simd128_value_t& readFrom(const double* v) {
        double_storage[0] = v[0];
        double_storage[1] = v[1];
        return *this;
    }
    simd128_value_t& readFrom(const simd128_value_t* v) {
        *this = *v;
        return *this;
    }
    void writeTo(float* v) {
        v[0] = float_storage[0];
        v[1] = float_storage[1];
        v[2] = float_storage[2];
        v[3] = float_storage[3];
    }
    void writeTo(int32_t* v) {
        v[0] = int_storage[0];
        v[1] = int_storage[1];
        v[2] = int_storage[2];
        v[3] = int_storage[3];
    }
    void writeTo(double* v) {
        v[0] = double_storage[0];
        v[1] = double_storage[1];
    }
    void writeTo(simd128_value_t* v) { *v = *this; }
};

template <class D, class S>
__forceinline D bit_cast(const S& source) {
    D destination;
    // This use of memcpy is safe: source and destination cannot overlap.
    memcpy(&destination, &source, sizeof(destination));
    return destination;
}

namespace Dart212
{
    bool IsTypedDataClassId(intptr_t index);
    bool IsTypedDataBaseClassId(intptr_t index);
    bool IsTypedDataViewClassId(intptr_t index);
    bool IsExternalTypedDataClassId(intptr_t index);
}



intptr_t RoundedAllocationSize(intptr_t size);
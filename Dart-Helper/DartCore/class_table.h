#pragma once
#include "globals.h"
#include "utils.h"

class UnboxedFieldBitmap {
public:
    UnboxedFieldBitmap() : bitmap_(0) {}
    explicit UnboxedFieldBitmap(uint64_t bitmap) : bitmap_(bitmap) {}
    UnboxedFieldBitmap(const UnboxedFieldBitmap&) = default;
    UnboxedFieldBitmap& operator=(const UnboxedFieldBitmap&) = default;

    bool Get(intptr_t position) const {
        if (position >= Length()) return false;
        return Utils::TestBit(bitmap_, position);
    }
    void Set(intptr_t position) {
        bitmap_ |= Utils::Bit<decltype(bitmap_)>(position);
    }
    uint64_t Value() const { return bitmap_; }
    bool IsEmpty() const { return bitmap_ == 0; }
    void Reset() { bitmap_ = 0; }

    static constexpr intptr_t Length() {
        return sizeof(decltype(bitmap_)) * kBitsPerByte;
    }
private:
    uint64_t bitmap_;
};
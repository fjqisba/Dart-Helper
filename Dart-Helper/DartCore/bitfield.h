#pragma once
#include "globals.h"

static const uintptr_t kUwordOne = 1U;

namespace Dart212
{
    // BitField is a template for encoding and decoding a value of type T
// inside a storage of type S.
    template <typename S,
        typename T,
        int position,
        int size = (sizeof(S)* kBitsPerByte) - position,
        bool sign_extend = false,
        typename Enable = void>
    class BitField {
    public:
        typedef T Type;

        static_assert((sizeof(S)* kBitsPerByte) >= (position + size),
            "BitField does not fit into the type.");
        static_assert(!sign_extend || std::is_signed<T>::value,
            "Should only sign extend signed bitfield types");

        static const intptr_t kNextBit = position + size;

        // Tells whether the provided value fits into the bit field.
        static constexpr bool is_valid(T value) {
            return decode(encode_unchecked(value)) == value;
        }

        // Returns a S mask of the bit field.
        static constexpr S mask() { return (kUwordOne << size) - 1; }

        // Returns a S mask of the bit field which can be applied directly to
        // to the raw unshifted bits.
        static constexpr S mask_in_place() { return mask() << position; }

        // Returns the shift count needed to right-shift the bit field to
        // the least-significant bits.
        static constexpr int shift() { return position; }

        // Returns the size of the bit field.
        static constexpr int bitsize() { return size; }

        // Returns an S with the bit field value encoded.
        static constexpr S encode(T value) {
            ASSERT(is_valid(value));
            return encode_unchecked(value);
        }

        // Extracts the bit field from the value.
        static constexpr T decode(S value) {
            // Ensure we slide down the sign bit if the value in the bit field is signed
            // and negative. We use 64-bit ints inside the expression since we can have
            // both cases: sizeof(S) > sizeof(T) or sizeof(S) < sizeof(T).
            if constexpr (sign_extend) {
                auto const u = static_cast<uint64_t>(value);
                return static_cast<T>((static_cast<int64_t>(u << (64 - kNextBit))) >>
                    (64 - size));
            }
            else {
                auto const u = static_cast<typename std::make_unsigned<S>::type>(value);
                return static_cast<T>((u >> position) & mask());
            }
        }

        // Returns an S with the bit field value encoded based on the
        // original value. Only the bits corresponding to this bit field
        // will be changed.
        static constexpr S update(T value, S original) {
            return encode(value) | (~mask_in_place() & original);
        }

    private:
        // Returns an S with the bit field value encoded.
        static constexpr S encode_unchecked(T value) {
            auto const u = static_cast<typename std::make_unsigned<S>::type>(value);
            return (u & mask()) << position;
        }
    };
}


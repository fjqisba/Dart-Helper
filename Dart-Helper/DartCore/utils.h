#pragma once
#include <cstdint>
#include <string>

class Utils {
public:
	template <typename T>
	static inline T Minimum(T x, T y) {
		return x < y ? x : y;
	}

	template <typename T>
	static constexpr inline T Maximum(T x, T y) {
		return x > y ? x : y;
	}

	// Calculates absolute value of a given signed integer.
// `x` must not be equal to minimum value representable by `T`
// as its absolute value is out of range.
	template <typename T>
	static inline T Abs(T x) {
		// Note: as a general rule, it is not OK to use STL in Dart VM.
		// However, std::numeric_limits<T>::min() and max() are harmless
		// and worthwhile exception from this rule.
		ASSERT(x != std::numeric_limits<T>::min());
		if (x < 0) return -x;
		return x;
	}

	// Calculates absolute value of a given signed integer with saturation.
// If `x` equals to minimum value representable by `T`, then
// absolute value is saturated to the maximum value representable by `T`.
	template <typename T>
	static inline T AbsWithSaturation(T x) {
		if (x < 0) {
			// Note: as a general rule, it is not OK to use STL in Dart VM.
			// However, std::numeric_limits<T>::min() and max() are harmless
			// and worthwhile exception from this rule.
			if (x == std::numeric_limits<T>::min()) {
				return std::numeric_limits<T>::max();
			}
			return -x;
		}
		return x;
	}

	template <typename T>
	static constexpr bool IsPowerOfTwo(T x) {
		return ((x & (x - 1)) == 0) && (x != 0);
	}

	template <typename T>
	static inline int ShiftForPowerOfTwo(T x) {
		ASSERT(IsPowerOfTwo(x));
		int num_shifts = 0;
		while (x > 1) {
			num_shifts++;
			x = x >> 1;
		}
		return num_shifts;
	}

	template <typename T>
	static constexpr bool IsAligned(T x,
		uintptr_t alignment,
		uintptr_t offset = 0) {
		return (x & (alignment - 1)) == offset;
	}

	template <typename T>
	static constexpr bool IsAligned(T* x,
		uintptr_t alignment,
		uintptr_t offset = 0) {
		return IsAligned(reinterpret_cast<uintptr_t>(x), alignment, offset);
	}

	template <typename T>
	static constexpr inline T RoundDown(T x, intptr_t alignment) {
		return (x & -alignment);
	}

	template <typename T>
	static inline T* RoundDown(T* x, intptr_t alignment) {
		return reinterpret_cast<T*>(
			RoundDown(reinterpret_cast<uintptr_t>(x), alignment));
	}

	template <typename T>
	static constexpr inline T RoundUp(T x,
		uintptr_t alignment,
		uintptr_t offset = 0) {
		return RoundDown(x + alignment - 1 + offset, alignment) - offset;
	}

	template <typename T>
	static inline T* RoundUp(T* x, uintptr_t alignment, uintptr_t offset = 0) {
		return reinterpret_cast<T*>(
			RoundUp(reinterpret_cast<uintptr_t>(x), alignment, offset));
	}

	template <typename T = uintptr_t>
	static constexpr T Bit(size_t n) {
		T bit = 1;
		return bit << n;
	}

	template <typename T>
	static constexpr bool TestBit(T mask, size_t position) {
		return ((mask >> position) & 1) != 0;
	}

	static intptr_t Utils::StrNLen(const char* s, intptr_t n);
};
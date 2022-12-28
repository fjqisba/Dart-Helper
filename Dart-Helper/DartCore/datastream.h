#pragma once
#include <string>
#include "globals.h"

static const std::int8_t kDataBitsPerByte = 7;
static const std::int8_t kByteMask = (1 << kDataBitsPerByte) - 1;
static const std::int8_t kMaxUnsignedDataPerByte = kByteMask;
static const std::int8_t kMinDataPerByte = -(1 << (kDataBitsPerByte - 1));
static const std::int8_t kMaxDataPerByte = (~kMinDataPerByte & kByteMask);  // NOLINT
static const std::uint8_t kEndByteMarker = (255 - kMaxDataPerByte);
static const std::uint8_t kEndUnsignedByteMarker = (255 - kMaxUnsignedDataPerByte);

class ReadStream
{
public:
	ReadStream();
	ReadStream(const unsigned char* buffer, intptr_t size)
		: buffer_(buffer), current_(buffer), end_(buffer + size) {}
	// Creates a ReadStream that starts at a given position in the buffer.
	ReadStream(const unsigned char* buffer, intptr_t size, intptr_t pos)
		: ReadStream(buffer, size) {
		SetPosition(pos);
	}

	template <int N, typename T>
	class Raw {};

	template <typename T>
	class Raw<1, T> {
	public:
		static T Read(ReadStream* st) { return bit_cast<T>(st->ReadByte()); }
	};

	template <typename T>
	class Raw<2, T> {
	public:
		static T Read(ReadStream* st) { return bit_cast<T>(st->Read16()); }
	};

	template <typename T>
	class Raw<4, T> {
	public:
		static T Read(ReadStream* st) { return bit_cast<T>(st->Read32()); }
	};

	template <typename T>
	class Raw<8, T> {
	public:
		static T Read(ReadStream* st) { return bit_cast<T>(st->Read64()); }
	};

	//读取指定字节数
	void ReadBytes(void* addr, intptr_t len);

	template <typename T = intptr_t>
	T ReadUnsigned() {
		return Read<T>(kEndUnsignedByteMarker);
	}

	template <typename T> 
	T ReadAny() {
		T val = *(T*)current_;
		current_ += sizeof(T);
		return val;
	}

	intptr_t ReadRefId();

	intptr_t Position() const;
	void SetPosition(intptr_t value);

	//获取当前位置
	const uint8_t* AddressOfCurrentPosition() const;

	//前进
	void Advance(intptr_t value);

	//剩余的字节数
	intptr_t PendingBytes() const;

	template <typename T>
	T Read() {
		return Read<T>(kEndByteMarker);
	}
private:
	uint16_t Read16() { return Read16(kEndByteMarker); }
	uint32_t Read32() { return Read32(kEndByteMarker); }
	uint64_t Read64() { return Read64(kEndByteMarker); }

	uintptr_t ReadWordWith32BitReads();

	__forceinline std::uint8_t ReadByte() {
		return *current_++;
	}
	template <typename T>
	T Read(uint8_t end_byte_marker) {
		using Unsigned = typename std::make_unsigned<T>::type;
		Unsigned b = ReadByte();
		if (b > kMaxUnsignedDataPerByte) {
			return b - end_byte_marker;
		}
		T r = 0;
		uint8_t s = 0;
		do {
			r |= static_cast<Unsigned>(b) << s;
			s += kDataBitsPerByte;
			b = ReadByte();
		} while (b <= kMaxUnsignedDataPerByte);
		return r | (static_cast<Unsigned>(b - end_byte_marker) << s);
	}

	// Setting up needed variables for the unrolled loop sections below.
#define UNROLLED_INIT()                                                        \
  using Unsigned = typename std::make_unsigned<T>::type;                       \
  Unsigned b = ReadByte();                                                     \
  if (b > kMaxUnsignedDataPerByte) {                                           \
    return b - end_byte_marker;                                                \
  }                                                                            \
  T r = b;

// Part of the unrolled loop where the loop may stop, having read the last part,
// or continue reading.
#define UNROLLED_BODY(bit_start)                                               \
  b = ReadByte();                                                              \
  if (b > kMaxUnsignedDataPerByte) {                                           \
    return r | (static_cast<T>(b - end_byte_marker) << bit_start);             \
  }                                                                            \
  r |= b << bit_start;

// The end of the unrolled loop.
#define UNROLLED_END(bit_start)                                                \
  b = ReadByte();                                                              \
  return r | (static_cast<T>(b - end_byte_marker) << bit_start);

	uint16_t Read16(uint8_t end_byte_marker) {
		using T = uint16_t;
		UNROLLED_INIT();
		UNROLLED_BODY(7);
		UNROLLED_END(14);
	}

	uint32_t Read32(uint8_t end_byte_marker) {
		using T = uint32_t;
		UNROLLED_INIT();
		UNROLLED_BODY(7);
		UNROLLED_BODY(14);
		UNROLLED_BODY(21);
		UNROLLED_END(28);
	}

	uint64_t Read64(uint8_t end_byte_marker) {
		using T = uint64_t;
		UNROLLED_INIT();
		UNROLLED_BODY(7);
		UNROLLED_BODY(14);
		UNROLLED_BODY(21);
		UNROLLED_BODY(28);
		UNROLLED_BODY(35);
		UNROLLED_BODY(42);
		UNROLLED_BODY(49);
		UNROLLED_BODY(56);
		UNROLLED_END(63);
	}
private:
	const unsigned char* buffer_;
	const unsigned char* current_;
	const unsigned char* end_;

	friend class Deserializer;
};
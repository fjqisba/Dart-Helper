#include "datastream.h"

ReadStream::ReadStream()
{
	buffer_ = nullptr;
	current_ = nullptr;
	end_ = nullptr;
}

void ReadStream::ReadBytes(void* addr, intptr_t len)
{
	if (len != 0) {
		memmove(addr, current_, len);
	}
	current_ += len;
}

const uint8_t* ReadStream::AddressOfCurrentPosition() const
{
	return current_;
}

intptr_t ReadStream::PendingBytes() const
{
	return (end_ - current_);
}

intptr_t ReadStream::ReadRefId()
{
    const int8_t* cursor = reinterpret_cast<const int8_t*>(current_);
    intptr_t result = 0;
    intptr_t byte;
    // clang-format off
#define STAGE                                                                  \
    byte = *cursor++;              /* ldrsb byte, [result], 1  */              \
    result = byte + (result << 7); /* add result, byte, result lsl 7 */        \
    if (byte < 0) goto done;       /* tbnz byte, 63, done */
    STAGE  // 0-7
        STAGE  // 8-14
        STAGE  // 15-21
        STAGE  // 22-28
#undef STAGE
    // clang-format on
done:
    current_ = reinterpret_cast<const uint8_t*>(cursor);
    // With big-endian order and the has-more marker being 0, the correction
    // factor to remove the last-byte marker is a constant, which can be folded
    // in to subsequent load offsets.
    return result + 128;
}

intptr_t ReadStream::Position() const
{
    return current_ - buffer_;
}

void ReadStream::SetPosition(intptr_t value)
{
    current_ = buffer_ + value;
}

void ReadStream::Advance(intptr_t value)
{
    current_ = current_ + value;
}

uintptr_t ReadStream::ReadWordWith32BitReads()
{
    intptr_t kNumRead32PerWord = kBitsPerWord / kBitsPerInt32;

    uintptr_t value = 0;
    for (intptr_t j = 0; j < kNumRead32PerWord; j++) {
        const auto partial_value = Raw<kInt32Size, uint32_t>::Read(this);
        value |= (static_cast<uintptr_t>(partial_value) << (j * kBitsPerInt32));
    }
    return value;
}
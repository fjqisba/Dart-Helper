#include "app_snapshot.h"
#include "datastream.h"
#include "utils.h"

Deserializer::Deserializer()
{

}

Deserializer::~Deserializer()
{

}

uint32_t Deserializer::ReadUInt32()
{
	return stream_.ReadAny<uint32_t>();
}

uint64_t Deserializer::ReadUInt64()
{
	return stream_.ReadAny<uint64_t>();
}

std::string Deserializer::ReadStr()
{
	std::string retStr;
	const char* cursor =
		reinterpret_cast<const char*>(stream_.AddressOfCurrentPosition());
	const intptr_t length = Utils::StrNLen(cursor, stream_.PendingBytes());
	if (length >= stream_.PendingBytes()) {
		return "";
	}
	retStr.assign(cursor, length);
	stream_.Advance(length + 1);
	return retStr;
}

std::string Deserializer::ReadVersion()
{
	std::string retVer;
	retVer.assign((const char*)stream_.AddressOfCurrentPosition(),32);
	stream_.Advance(32);
	return retVer;
}


bool Deserializer::InitDeserializer(std::vector<unsigned char>& snapshotData)
{
	stream_ = ReadStream(snapshotData.data(), snapshotData.size());

	return true;
}


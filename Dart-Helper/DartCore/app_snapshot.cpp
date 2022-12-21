#include "app_snapshot.h"
#include "datastream.h"
#include "utils.h"
#include "globals.h"
#include "./Cluster/FunctionDeserializationCluster.h"

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

intptr_t Deserializer::next_index() const
{
	return next_ref_index_;
}

void Deserializer::set_code_start_index(intptr_t value)
{
	code_start_index_ = value;
}

void Deserializer::set_code_stop_index(intptr_t value)
{
	code_stop_index_ = value;
}

void Deserializer::AssignRef(void* object)
{

}

DeserializationCluster* Deserializer::ReadCluster()
{
	const uint64_t cid_and_canonical = Read<uint64_t>();
	const intptr_t cid = (cid_and_canonical >> 1) & kMaxUint32;
	const bool is_canonical = (cid_and_canonical & 0x1) == 0x1;

	switch (cid) {
	case 0:
		return nullptr;
	case 7:
		return new FunctionDeserializationCluster();
	case 17:
		break;
	case 92:

		break;
	}
	return nullptr;
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


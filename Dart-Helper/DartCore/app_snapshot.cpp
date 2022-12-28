#include "app_snapshot.h"
#include "datastream.h"
#include "utils.h"
#include "globals.h"
#include "class_id.h"
#include "./Cluster/FunctionDeserializationCluster.h"
#include "./Cluster/InstanceDeserializationCluster.h"
#include "./Cluster/TypedDataViewDeserializationCluster.h"
#include "./Cluster/ExternalTypedDataDeserializationCluster.h"
#include "./Cluster/StringDeserializationCluster.h"
#include "./Cluster/MintDeserializationCluster.h"
#include "./Cluster/OneByteStringDeserializationCluster.h"
#include "./Cluster/CodeDeserializationCluster.h"

Deserializer::Deserializer()
{

}

Deserializer::~Deserializer()
{
	for (unsigned int n = 0; n < refs_.size(); ++n) {
		if (refs_[n]) {
			delete refs_[n];
		}
	}
}

uint32_t Deserializer::ReadUInt32()
{
	return stream_.ReadAny<uint32_t>();
}

uint64_t Deserializer::ReadUnsigned64()
{
	return stream_.ReadUnsigned<uint64_t>();
}

uintptr_t Deserializer::ReadWordWith32BitReads()
{
	return stream_.ReadWordWith32BitReads();
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
	refs_.push_back(object);
	next_ref_index_++;
}

void* Deserializer::ReadRef()
{
	return Ref(ReadUnsigned());
}

void* Deserializer::Ref(intptr_t index)
{
	return refs_.at(index);
}

DeserializationCluster2_1_2* Deserializer::ReadCluster_2_1_2(Deserializer* d)
{
	intptr_t cid = d->ReadCid();
	if (cid >= kNumPredefinedCids || cid == kInstanceCid) {
		return new InstanceDeserializationCluster(cid);
	}
	if (IsTypedDataViewClassId(cid)) {
		//return new TypedDataViewDeserializationCluster(cid);
	}
	if (IsExternalTypedDataClassId(cid)) {
		//return new ExternalTypedDataDeserializationCluster(cid);
	}
	//if (IsTypedDataClassId(cid)) {
		//return new (Z) TypedDataDeserializationCluster(cid);
	//}

	//switch (cid) {
	//case 14:
	//	return new CodeDeserializationCluster();
	//case 50:
	//	return new MintDeserializationCluster();
	//case 78:
	//	return new OneByteStringDeserializationCluster();
	//}
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

intptr_t Deserializer::ReadCid()
{
	return Read<int32_t>();
}

std::string Deserializer::ReadVersion()
{
	std::string retVer;
	retVer.assign((const char*)stream_.AddressOfCurrentPosition(),32);
	stream_.Advance(32);
	return retVer;
}

void Deserializer::AddBaseObject(void* base_object)
{
	AssignRef(base_object);
}

bool Deserializer::InitDeserializer(std::vector<unsigned char>& snapshotData)
{
	stream_ = ReadStream(snapshotData.data(), snapshotData.size());

	return true;
}


#pragma once
#include "datastream.h"
#include "snapshot.h"
#include <vector>
#include "./Cluster/DeserializationCluster.h"

static constexpr intptr_t kUnreachableReference = 0;
static constexpr intptr_t kFirstReference = 1;

namespace Dart212
{
	class Code;
}

class Deserializer
{
public:
	Deserializer();
	~Deserializer();
public:
	template <typename T>
	T Read() {
		return ReadStream::Raw<sizeof(T), T>::Read(&stream_);
	}
	bool InitDeserializer(std::vector<unsigned char>& snapshotData);
	intptr_t ReadUnsigned() { return stream_.ReadUnsigned(); }

	void AddBaseObject(void* base_object);

	//暴力读取32,非内置
	uint32_t ReadUInt32();
	//暴力读取64,非内置
	uint64_t ReadUInt64();

	void ReadInstructions_212(Dart212::Code* code, bool deferred);

	uint64_t ReadUnsigned64();

	//读取版本号
	std::string ReadVersion();
	std::string ReadStr();
	intptr_t ReadCid();
	Dart212::DeserializationCluster* ReadCluster_2_1_2(Deserializer* d);
	uintptr_t ReadWordWith32BitReads();
	intptr_t next_index() const;
	void set_code_start_index(intptr_t value);
	void set_code_stop_index(intptr_t value);
	void AssignRef(void* object);
	void* Ref(intptr_t index);
	void* ReadRef();
	SnapshotKind kind();
	void ReadBytes(uint8_t* addr, intptr_t len) { stream_.ReadBytes(addr, len); }
	void Advance(intptr_t value) { stream_.Advance(value); }
public:
	SnapshotKind kind_;
private:
	ReadStream stream_;
	intptr_t num_base_objects_;
	intptr_t num_objects_;
	intptr_t num_clusters_;
	intptr_t code_start_index_ = 0;
	intptr_t code_stop_index_ = 0;
	intptr_t instructions_index_ = 0;
	const bool is_non_root_unit_;
	std::vector<void*> refs_;
	intptr_t next_ref_index_ = 0;
	intptr_t previous_text_offset_ = 0;
};

#pragma once
#include "datastream.h"
#include "snapshot.h"
#include <vector>
#include "./Cluster/DeserializationCluster.h"

static constexpr intptr_t kUnreachableReference = 0;
static constexpr intptr_t kFirstReference = 1;

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

	uint32_t ReadUInt32();

	uint64_t ReadUnsigned64();

	//∂¡»°∞Ê±æ∫≈
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

	void ReadBytes(uint8_t* addr, intptr_t len) { stream_.ReadBytes(addr, len); }
	void Advance(intptr_t value) { stream_.Advance(value); }
private:
	ReadStream stream_;
	intptr_t next_ref_index_ = 0;
	intptr_t code_start_index_ = 0;
	intptr_t code_stop_index_ = 0;
	intptr_t instructions_index_ = 0;
	std::vector<void*> refs_;
};

#pragma once
#include "datastream.h"
#include "snapshot.h"
#include <vector>

class Deserializer
{
public:
	Deserializer();
	~Deserializer();
	bool InitDeserializer(std::vector<unsigned char>& snapshotData);
	intptr_t ReadUnsigned() { return stream_.ReadUnsigned(); }

	uint32_t ReadUInt32();
	uint64_t ReadUInt64();
	//∂¡»°∞Ê±æ∫≈
	std::string ReadVersion();
	std::string ReadStr();
private:
	ReadStream stream_;
};

#pragma once
#include "DeserializationCluster.h"

class ExternalTypedDataDeserializationCluster : public DeserializationCluster
{
public:
	explicit ExternalTypedDataDeserializationCluster(intptr_t cid);

	void ReadAlloc(Deserializer* d);
private:
	const intptr_t cid_;
};
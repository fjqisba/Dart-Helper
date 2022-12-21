#pragma once
#include "DeserializationCluster.h"
#include "CanonicalSetDeserializationCluster.h"

class RODataDeserializationCluster :public CanonicalSetDeserializationCluster
{
public:
	RODataDeserializationCluster(bool is_canonical, bool is_root_unit, intptr_t cid);
	void ReadAlloc(Deserializer* d);
private:
	const intptr_t cid_;
};


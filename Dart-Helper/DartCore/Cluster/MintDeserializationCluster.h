#pragma once
#include "DeserializationCluster.h"

class MintDeserializationCluster : public DeserializationCluster
{
public:
	MintDeserializationCluster();
	void ReadAlloc(Deserializer* d);
};
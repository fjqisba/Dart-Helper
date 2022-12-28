#pragma once
#include "DeserializationCluster.h"

class MintDeserializationCluster2_1_2 : public DeserializationCluster2_1_2
{
public:
	MintDeserializationCluster2_1_2();
	void ReadAlloc(Deserializer* d);
};
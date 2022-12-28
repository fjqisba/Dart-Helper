#pragma once
#include "DeserializationCluster.h"

class OneByteStringDeserializationCluster:public DeserializationCluster2_1_2
{
public:
	OneByteStringDeserializationCluster();
	void ReadAlloc(Deserializer* d);
};
#pragma once
#include "DeserializationCluster.h"

class OneByteStringDeserializationCluster:public DeserializationCluster
{
public:
	OneByteStringDeserializationCluster();
	void ReadAlloc(Deserializer* d);
};
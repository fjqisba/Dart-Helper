#pragma once
#include "DeserializationCluster.h"

class FunctionDeserializationCluster :public DeserializationCluster2_1_2
{
public:
	FunctionDeserializationCluster() : DeserializationCluster2_1_2("Function") {}
	~FunctionDeserializationCluster() {}
	void ReadAlloc(Deserializer* d);
};
#pragma once
#include "DeserializationCluster.h"

class FunctionDeserializationCluster :public DeserializationCluster
{
public:
	FunctionDeserializationCluster() : DeserializationCluster("Function") {}
	~FunctionDeserializationCluster() {}
	void ReadAlloc(Deserializer* d);
};
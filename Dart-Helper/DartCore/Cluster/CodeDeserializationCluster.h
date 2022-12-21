#pragma once
#include "DeserializationCluster.h"

class CodeDeserializationCluster :public DeserializationCluster
{
public:
	void ReadAlloc(Deserializer* d);
	void ReadAllocOneCode(Deserializer* d);
private:
	intptr_t deferred_start_index_;
	intptr_t deferred_stop_index_;
};
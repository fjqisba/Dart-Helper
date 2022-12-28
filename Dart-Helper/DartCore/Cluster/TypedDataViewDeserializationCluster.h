#pragma once
#include "DeserializationCluster.h"

class TypedDataViewDeserializationCluster : public DeserializationCluster2_1_2
{
public:
	explicit TypedDataViewDeserializationCluster(intptr_t cid);
private:
	const intptr_t cid_;
};
#pragma once
#include "DeserializationCluster.h"

class TypedDataViewDeserializationCluster : public DeserializationCluster
{
public:
	explicit TypedDataViewDeserializationCluster(intptr_t cid);
private:
	const intptr_t cid_;
};
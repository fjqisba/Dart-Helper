#pragma once
#include "SerializationCluster.h"

class ArraySerializationCluster : public SerializationCluster
{
public:
	ArraySerializationCluster(bool is_canonical, intptr_t cid);
	~ArraySerializationCluster();
};
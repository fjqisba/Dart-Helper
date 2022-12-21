#include "ArraySerializationCluster.h"

ArraySerializationCluster::ArraySerializationCluster(bool is_canonical, intptr_t cid) : SerializationCluster("Array", cid, kSizeVaries, is_canonical)
{

}

ArraySerializationCluster::~ArraySerializationCluster()
{

}
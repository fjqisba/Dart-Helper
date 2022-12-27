#include "ExternalTypedDataDeserializationCluster.h"

ExternalTypedDataDeserializationCluster::ExternalTypedDataDeserializationCluster(intptr_t cid) : DeserializationCluster("ExternalTypedData"), cid_(cid)
{

}

void ExternalTypedDataDeserializationCluster::ReadAlloc(Deserializer* d)
{
	ReadAllocFixedSize(d,0x0);
}
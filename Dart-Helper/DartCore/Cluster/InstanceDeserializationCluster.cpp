#include "InstanceDeserializationCluster.h"

InstanceDeserializationCluster::InstanceDeserializationCluster(intptr_t cid, bool is_canonical):AbstractInstanceDeserializationCluster("Instance", is_canonical),cid_(cid)
{

}
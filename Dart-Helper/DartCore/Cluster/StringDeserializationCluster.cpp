#include "StringDeserializationCluster.h"

StringDeserializationCluster::StringDeserializationCluster(bool is_canonical, bool is_root_unit): CanonicalSetDeserializationCluster(is_canonical, is_root_unit, "String")
{

}


void StringDeserializationCluster::ReadAlloc(Deserializer* d)
{
    start_index_ = d->next_index();
    const intptr_t count = d->ReadUnsigned();
    for (intptr_t i = 0; i < count; i++) {
        const intptr_t encoded = d->ReadUnsigned();
        intptr_t cid = 0;
        const intptr_t length = DecodeLengthAndCid(encoded, &cid);
        //d->AssignRef(old_space->AllocateSnapshot(InstanceSize(length, cid)));
    }
    stop_index_ = d->next_index();
    BuildCanonicalSetFromLayout(d);
}
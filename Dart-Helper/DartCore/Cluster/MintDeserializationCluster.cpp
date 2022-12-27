#include "MintDeserializationCluster.h"
#include "../app_snapshot.h"

MintDeserializationCluster::MintDeserializationCluster() : DeserializationCluster("int")
{

}

void MintDeserializationCluster::ReadAlloc(Deserializer* d)
{
    start_index_ = d->next_index();
    const intptr_t count = d->ReadUnsigned();
    for (intptr_t i = 0; i < count; i++) {
        int64_t value = d->Read<int64_t>();
        d->AssignRef(nullptr);
    }
    stop_index_ = d->next_index();
}
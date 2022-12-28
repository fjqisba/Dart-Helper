#include "CodeDeserializationCluster.h"
#include "../app_snapshot.h"

CodeDeserializationCluster::CodeDeserializationCluster():DeserializationCluster2_1_2("Code")
{

}

void CodeDeserializationCluster::ReadAllocOneCode(Deserializer * d)
{
    const int32_t state_bits = d->Read<int32_t>();
    d->AssignRef(0);
}

void CodeDeserializationCluster::ReadAlloc(Deserializer* d)
{
    start_index_ = d->next_index();
    const intptr_t count = d->ReadUnsigned();
    for (intptr_t i = 0; i < count; i++) {
        d->AssignRef(0x0);
    }
    stop_index_ = d->next_index();
    deferred_start_index_ = d->next_index();
    const intptr_t deferred_count = d->ReadUnsigned();
    for (intptr_t i = 0; i < deferred_count; i++) {
        d->AssignRef(0x0);
    }
    deferred_stop_index_ = d->next_index();
}



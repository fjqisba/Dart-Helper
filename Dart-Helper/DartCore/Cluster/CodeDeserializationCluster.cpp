#include "CodeDeserializationCluster.h"
#include "../app_snapshot.h"


void CodeDeserializationCluster::ReadAllocOneCode(Deserializer * d)
{
    const int32_t state_bits = d->Read<int32_t>();
    d->AssignRef(0);
}

void CodeDeserializationCluster::ReadAlloc(Deserializer* d)
{
	start_index_ = d->next_index();
    d->set_code_start_index(start_index_);
    const intptr_t count = d->ReadUnsigned();
    for (intptr_t i = 0; i < count; i++) {
        ReadAllocOneCode(d);
    }
    stop_index_ = d->next_index();
    d->set_code_stop_index(stop_index_);
    deferred_start_index_ = d->next_index();
    const intptr_t deferred_count = d->ReadUnsigned();
    for (intptr_t i = 0; i < deferred_count; i++) {
        ReadAllocOneCode(d);
    }
    deferred_stop_index_ = d->next_index();
}



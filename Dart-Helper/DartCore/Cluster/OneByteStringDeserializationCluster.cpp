#include "OneByteStringDeserializationCluster.h"
#include "../app_snapshot.h"

OneByteStringDeserializationCluster::OneByteStringDeserializationCluster() : DeserializationCluster2_1_2("OneByteString")
{

}

void OneByteStringDeserializationCluster::ReadAlloc(Deserializer* d)
{
    start_index_ = d->next_index();
    const intptr_t count = d->ReadUnsigned();
    for (intptr_t i = 0; i < count; i++) {
        const intptr_t length = d->ReadUnsigned();
        d->AssignRef(nullptr);
    }
    stop_index_ = d->next_index();
}
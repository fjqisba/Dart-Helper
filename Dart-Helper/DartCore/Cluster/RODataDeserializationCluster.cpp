#include "RODataDeserializationCluster.h"
#include "../app_snapshot.h"
#include "../globals.h"
#include "../class_id.h"

RODataDeserializationCluster::RODataDeserializationCluster(bool is_canonical, bool is_root_unit, intptr_t cid) : CanonicalSetDeserializationCluster(is_canonical, is_root_unit,"ROData"),cid_(cid)
{

}

void RODataDeserializationCluster::ReadAlloc(Deserializer* d)
{
    start_index_ = d->next_index();
    intptr_t count = d->ReadUnsigned();
    uint32_t running_offset = 0;
    for (intptr_t i = 0; i < count; i++) {
        running_offset += d->ReadUnsigned() << 0x4;
        d->AssignRef(0x0);
    }
    stop_index_ = d->next_index();
    if (cid_ == kStringCid) {
        BuildCanonicalSetFromLayout(d);
    }
}
#pragma once
#include "DeserializationCluster.h"
#include "../app_snapshot.h"

namespace Dart212
{
    class RODataDeserializationCluster : public DeserializationCluster {
    public:
        explicit RODataDeserializationCluster(intptr_t cid)
            : DeserializationCluster("ROData"), cid_(cid) {}
        ~RODataDeserializationCluster() {}

        void ReadAlloc(Deserializer* d, bool is_canonical) {
            start_index_ = d->next_index();
            intptr_t count = d->ReadUnsigned();
            uint32_t running_offset = 0;
            for (intptr_t i = 0; i < count; i++) {
                running_offset += d->ReadUnsigned() << kObjectAlignmentLog2;
                d->AssignRef(0x0);
            }
            stop_index_ = d->next_index();
        }

        void ReadFill(Deserializer* d, bool is_canonical) {
            // No-op.
        }

    private:
        const intptr_t cid_;
    };
}
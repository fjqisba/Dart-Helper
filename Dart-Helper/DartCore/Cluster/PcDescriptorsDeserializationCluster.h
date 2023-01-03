#pragma once
#include "DeserializationCluster.h"
#include "../app_snapshot.h"

namespace Dart212
{
    class PcDescriptorsDeserializationCluster : public DeserializationCluster {
    public:
        PcDescriptorsDeserializationCluster()
            : DeserializationCluster("PcDescriptors") {}
        ~PcDescriptorsDeserializationCluster() {}

        void ReadAlloc(Deserializer* d, bool is_canonical) {
            start_index_ = d->next_index();
            const intptr_t count = d->ReadUnsigned();
            for (intptr_t i = 0; i < count; i++) {
                const intptr_t length = d->ReadUnsigned();
                d->AssignRef(0x0);
            }
            stop_index_ = d->next_index();
        }

        void ReadFill(Deserializer* d, bool is_canonical) {
            for (intptr_t id = start_index_; id < stop_index_; id += 1) {
                const intptr_t length = d->ReadUnsigned();
                //uint8_t* cdata = reinterpret_cast<uint8_t*>(desc->untag()->data());
                d->Advance(length);
            }
        }
    };
}
#pragma once
#include "DeserializationCluster.h"
#include "../app_snapshot.h"

namespace Dart212
{
    class MintDeserializationCluster : public DeserializationCluster {
    public:
        MintDeserializationCluster() : DeserializationCluster("int") {}
        ~MintDeserializationCluster() {}

        void ReadAlloc(Deserializer* d, bool is_canonical) {
            start_index_ = d->next_index();
            const intptr_t count = d->ReadUnsigned();
            for (intptr_t i = 0; i < count; i++) {
                int64_t value = d->Read<int64_t>();
                d->AssignRef(0x0);
            }
            stop_index_ = d->next_index();
        }

        void ReadFill(Deserializer* d, bool is_canonical) {}

  /*      void PostLoad(Deserializer* d, const Array& refs, bool is_canonical) {
            
        }*/
    };
}
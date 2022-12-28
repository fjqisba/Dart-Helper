#pragma once
#include "DeserializationCluster.h"
#include "../app_snapshot.h"
#include "../Object/Object.h"

namespace Dart212
{
    class TypedDataDeserializationCluster : public DeserializationCluster {
    public:
        explicit TypedDataDeserializationCluster(intptr_t cid)
            : DeserializationCluster("TypedData"), cid_(cid) {}
        ~TypedDataDeserializationCluster() {}

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
            intptr_t element_size = TypedData::ElementSizeInBytes(cid_);
            for (intptr_t id = start_index_; id < stop_index_; id++) {
                const intptr_t length = d->ReadUnsigned();
                const intptr_t length_in_bytes = length * element_size;
                d->Advance(length_in_bytes);
            }
        }

    private:
        const intptr_t cid_;
    };
}


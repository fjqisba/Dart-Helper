#pragma once
#include "DeserializationCluster.h"
#include "../app_snapshot.h"

namespace Dart212
{
    class ArrayDeserializationCluster : public DeserializationCluster {
    public:
        explicit ArrayDeserializationCluster(intptr_t cid)
            : DeserializationCluster("Array"), cid_(cid) {}
        ~ArrayDeserializationCluster() {}

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
            for (intptr_t id = start_index_; id < stop_index_; id++) {
                const intptr_t length = d->ReadUnsigned();
                void* TypeArgumentsPtr = d->ReadRef();
                for (intptr_t j = 0; j < length; j++) {
                    d->ReadRef();
                }
            }
        }

    private:
        const intptr_t cid_;
    };
}
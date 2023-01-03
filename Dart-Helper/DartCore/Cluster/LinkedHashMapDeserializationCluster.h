#pragma once
#include "DeserializationCluster.h"
#include "../app_snapshot.h"

namespace Dart212
{
    class LinkedHashMapDeserializationCluster : public DeserializationCluster {
    public:
        LinkedHashMapDeserializationCluster()
            : DeserializationCluster("LinkedHashMap") {}
        ~LinkedHashMapDeserializationCluster() {}

        void ReadAlloc(Deserializer* d, bool is_canonical) {
            start_index_ = d->next_index();
            const intptr_t count = d->ReadUnsigned();
            for (intptr_t i = 0; i < count; i++) {
                d->AssignRef(0x0);
            }
            stop_index_ = d->next_index();
        }

        void ReadFill(Deserializer* d, bool is_canonical) {

            for (intptr_t id = start_index_; id < stop_index_; id++) {
                void *type_arguments_ = d->ReadRef();
                intptr_t pairs = d->Read<int32_t>();
                intptr_t used_data = pairs << 1;
                intptr_t i;
                for (i = 0; i < used_data; i++) {
                    d->ReadRef();
                }
            }
        }
    };

}
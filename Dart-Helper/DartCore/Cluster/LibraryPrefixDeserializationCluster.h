#pragma once
#include "DeserializationCluster.h"
#include "../app_snapshot.h"

namespace Dart212
{
    class LibraryPrefixDeserializationCluster : public DeserializationCluster {
    public:
        LibraryPrefixDeserializationCluster()
            : DeserializationCluster("LibraryPrefix") {}
        ~LibraryPrefixDeserializationCluster() {}

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
                uint16_t num_imports_ = d->Read<uint16_t>();
                bool is_deferred_load_ = d->Read<bool>();
            }
        }
    };

}
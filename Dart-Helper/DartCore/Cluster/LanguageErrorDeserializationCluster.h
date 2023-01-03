#pragma once
#include "DeserializationCluster.h"
#include "../app_snapshot.h"

namespace Dart212
{
    class LanguageErrorDeserializationCluster : public DeserializationCluster {
    public:
        LanguageErrorDeserializationCluster()
            : DeserializationCluster("LanguageError") {}
        ~LanguageErrorDeserializationCluster() {}

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
                int32_t token_pos_ = d->Read<int32_t>();
                bool report_after_token_ = d->Read<bool>();
                int8_t kind_ = d->Read<int8_t>();
            }
        }
    };
	
}
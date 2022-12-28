#pragma once
#include "DeserializationCluster.h"
#include "../app_snapshot.h"

namespace Dart212
{
    class ScriptDeserializationCluster : public DeserializationCluster {
    public:
        ScriptDeserializationCluster() : DeserializationCluster("Script") {}
        ~ScriptDeserializationCluster() {}

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
                int32_t line_offset_ = d->Read<int32_t>();
                int32_t col_offset_ = d->Read<int32_t>();
                if (DartSetup::IsPrecompiled() == false) {
                    int32_t flags_and_max_position_ = d->Read<int32_t>();
                }
                int32_t kernel_script_index_ = d->Read<int32_t>();
            }
        }
    };
}
#pragma once
#include "DeserializationCluster.h"
#include "../app_snapshot.h"

namespace Dart212
{
    class ExceptionHandlersDeserializationCluster : public DeserializationCluster {
    public:
        ExceptionHandlersDeserializationCluster()
            : DeserializationCluster("ExceptionHandlers") {}
        ~ExceptionHandlersDeserializationCluster() {}

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
                void *handled_types_data_ = d->ReadRef();
                for (intptr_t j = 0; j < length; j++) {
                    uint32_t handler_pc_offset = d->Read<uint32_t>();
                    int16_t outer_try_index = d->Read<int16_t>();
                    int8_t needs_stacktrace = d->Read<int8_t>();
                    int8_t has_catch_all = d->Read<int8_t>();
                    int8_t is_generated = d->Read<int8_t>();
                }
            }
        }
    };
}
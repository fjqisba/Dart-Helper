#pragma once
#include "DeserializationCluster.h"
#include "../app_snapshot.h"

namespace Dart212
{
    class ClosureDataDeserializationCluster : public DeserializationCluster {
    public:
        ClosureDataDeserializationCluster() : DeserializationCluster("ClosureData") {}
        ~ClosureDataDeserializationCluster() {}

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
                if (d->kind() == kFullAOT) {
                    //data->untag()->context_scope_ = ContextScope::null();
                }
                else {
                    d->ReadRef();
                }
                void* parent_function_ = d->ReadRef();
                void* closure_ = d->ReadRef();
                void* default_type_arguments_ = d->ReadRef();
                void* default_type_arguments_info_ = d->ReadRef();
            }
        }
    };
}
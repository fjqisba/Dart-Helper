#pragma once
#include "DeserializationCluster.h"
#include "../app_snapshot.h"
#include "../Object/Object.h"

namespace Dart212
{
    class CodeDeserializationCluster : public DeserializationCluster {
    public:
        CodeDeserializationCluster() : DeserializationCluster("Code") {}
        ~CodeDeserializationCluster() {}

        void ReadAlloc(Deserializer* d, bool is_canonical) {
            start_index_ = d->next_index();
            const intptr_t count = d->ReadUnsigned();
            for (intptr_t i = 0; i < count; i++) {
                d->AssignRef(0x0);
            }
            stop_index_ = d->next_index();
            deferred_start_index_ = d->next_index();
            const intptr_t deferred_count = d->ReadUnsigned();
            for (intptr_t i = 0; i < deferred_count; i++) {
                d->AssignRef(0x0);
            }
            deferred_stop_index_ = d->next_index();
        }

        void ReadFill(Deserializer* d, bool is_canonical) {
            for (intptr_t id = start_index_; id < stop_index_; id++) {
                ReadFill(d, id, false);
            }
            for (intptr_t id = deferred_start_index_; id < deferred_stop_index_; id++) {
                ReadFill(d, id, true);
            }
        }

        void ReadFill(Deserializer* d, intptr_t id, bool deferred) {
          
              Dart212::Code tmpCode;
              d->ReadInstructions_212(&tmpCode, deferred);

              if (!(d->kind() == kFullAOT && DartSetup::UseBareInstructions())) {
                  d->ReadRef();
              }
              else {
                  
              }
              void* owner_ = d->ReadRef();
              void* exception_handlers_ = d->ReadRef();
              void* pc_descriptors_ = d->ReadRef();
              void* catch_entry_ = d->ReadRef();
              void* compressed_stackmaps_ = d->ReadRef();
              void* inlined_id_to_function_ = d->ReadRef();
              void* code_source_map_ = d->ReadRef();
              if (!DartSetup::IsPrecompiled() && d->kind() == kFullJIT) {
                  void* deopt_info_array_ = d->ReadRef();
                  void* static_calls_target_table_ = d->ReadRef();
              }
              if (!DartSetup::IsProduct()) {
                  void* return_address_metadata_ = d->ReadRef();
                  void* comments_ = d->ReadRef();
              }
              int32_t state_bits_ = d->Read<int32_t>();
        }
    private:
        intptr_t deferred_start_index_;
        intptr_t deferred_stop_index_;
    };
}
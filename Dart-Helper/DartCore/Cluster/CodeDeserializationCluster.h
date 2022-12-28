#pragma once
#include "DeserializationCluster.h"
#include "../app_snapshot.h"

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

//            d->ReadInstructions(code, deferred);
//            // There would be a single global pool if this is a full AOT snapshot
//            // with bare instructions.
//            if (!(d->kind() == Snapshot::kFullAOT && FLAG_use_bare_instructions)) {
//                code->untag()->object_pool_ = static_cast<ObjectPoolPtr>(d->ReadRef());
//            }
//            else {
//                code->untag()->object_pool_ = ObjectPool::null();
//            }
//            void* owner_ = d->ReadRef();
//            void* exception_handlers_ = d->ReadRef();
//            void* pc_descriptors_ = d->ReadRef();
//            void* catch_entry_ = d->ReadRef();
//            void* compressed_stackmaps_ = d->ReadRef();
//            void* inlined_id_to_function_ = d->ReadRef();
//            void* code_source_map_ = d->ReadRef();
//
//#if !defined(PRODUCT)
//            code->untag()->return_address_metadata_ = d->ReadRef();
//            code->untag()->var_descriptors_ = LocalVarDescriptors::null();
//            code->untag()->comments_ = FLAG_code_comments
//                ? static_cast<ArrayPtr>(d->ReadRef())
//                : Array::null();
//            code->untag()->compile_timestamp_ = 0;
//#endif
//
//            code->untag()->state_bits_ = d->Read<int32_t>();
        }

        //void PostLoad(Deserializer* d, const Array& refs, bool is_canonical) {

        //}

    private:
        intptr_t deferred_start_index_;
        intptr_t deferred_stop_index_;
    };
}
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
          
//           d->ReadInstructions(code, deferred);
//
//            // There would be a single global pool if this is a full AOT snapshot
//            // with bare instructions.
//            if (!(d->kind() == Snapshot::kFullAOT && FLAG_use_bare_instructions)) {
//                code->untag()->object_pool_ = static_cast<ObjectPoolPtr>(d->ReadRef());
//            }
//            else {
//                code->untag()->object_pool_ = ObjectPool::null();
//            }
//            code->untag()->owner_ = d->ReadRef();
//            code->untag()->exception_handlers_ =
//                static_cast<ExceptionHandlersPtr>(d->ReadRef());
//            code->untag()->pc_descriptors_ =
//                static_cast<PcDescriptorsPtr>(d->ReadRef());
//            code->untag()->catch_entry_ = d->ReadRef();
//            code->untag()->compressed_stackmaps_ =
//                static_cast<CompressedStackMapsPtr>(d->ReadRef());
//            code->untag()->inlined_id_to_function_ =
//                static_cast<ArrayPtr>(d->ReadRef());
//            code->untag()->code_source_map_ =
//                static_cast<CodeSourceMapPtr>(d->ReadRef());
//
//#if !defined(DART_PRECOMPILED_RUNTIME)
//            if (d->kind() == Snapshot::kFullJIT) {
//                code->untag()->deopt_info_array_ = static_cast<ArrayPtr>(d->ReadRef());
//                code->untag()->static_calls_target_table_ =
//                    static_cast<ArrayPtr>(d->ReadRef());
//            }
//#endif  // !DART_PRECOMPILED_RUNTIME
//
//#if !defined(PRODUCT)
//            code->untag()->return_address_metadata_ = d->ReadRef();
//            code->untag()->var_descriptors_ = LocalVarDescriptors::null();
//            code->untag()->comments_ = FLAG_code_comments
//                ? static_cast<ArrayPtr>(d->ReadRef())
//                : Array::null();
//#endif
//
//            int32_t state_bits_ = d->Read<int32_t>();
        }

//        void PostLoad(Deserializer* d, const Array& refs, bool is_canonical) {
//            d->EndInstructions(refs, start_index_, stop_index_);
//
//#if !defined(PRODUCT)
//            if (!CodeObservers::AreActive() && !FLAG_support_disassembler) return;
//#endif
//            Code& code = Code::Handle(d->zone());
//#if !defined(PRODUCT) || defined(FORCE_INCLUDE_DISASSEMBLER)
//            Object& owner = Object::Handle(d->zone());
//#endif
//            for (intptr_t id = start_index_; id < stop_index_; id++) {
//                code ^= refs.At(id);
//#if !defined(DART_PRECOMPILED_RUNTIME) && !defined(PRODUCT)
//                if (CodeObservers::AreActive()) {
//                    Code::NotifyCodeObservers(code, code.is_optimized());
//                }
//#endif
//#if !defined(PRODUCT) || defined(FORCE_INCLUDE_DISASSEMBLER)
//                owner = code.owner();
//                if (owner.IsFunction()) {
//                    if ((FLAG_disassemble ||
//                        (code.is_optimized() && FLAG_disassemble_optimized)) &&
//                        compiler::PrintFilter::ShouldPrint(Function::Cast(owner))) {
//                        Disassembler::DisassembleCode(Function::Cast(owner), code,
//                            code.is_optimized());
//                    }
//                }
//                else if (FLAG_disassemble_stubs) {
//                    Disassembler::DisassembleStub(code.Name(), code);
//                }
//#endif  // !defined(PRODUCT) || defined(FORCE_INCLUDE_DISASSEMBLER)
//            }
//        }

    private:
        intptr_t deferred_start_index_;
        intptr_t deferred_stop_index_;
    };
}
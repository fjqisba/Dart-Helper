#pragma once
#include "DeserializationCluster.h"
#include "../app_snapshot.h"

namespace Dart212
{
    class FunctionDeserializationCluster : public DeserializationCluster {
    public:
        FunctionDeserializationCluster() : DeserializationCluster("Function") {}
        ~FunctionDeserializationCluster() {}

        void ReadAlloc(Deserializer* d, bool is_canonical) {
            start_index_ = d->next_index();
            const intptr_t count = d->ReadUnsigned();
            for (intptr_t i = 0; i < count; i++) {
                d->AssignRef(0x0);
            }
            stop_index_ = d->next_index();
        }

        void ReadFill(Deserializer* d, bool is_canonical) {
            auto kind = d->kind();
            for (intptr_t id = start_index_; id < stop_index_; id++) {
                if (kind == kFullAOT) {
                    d->ReadRef();
                }
                else if (kind == kFullJIT) {
                    d->ReadRef();
                    d->ReadRef();
                    d->ReadRef();
                }
                
                if (DartSetup::IsPrecompiled() == false) {
                    if (kind != kFullAOT) {
                        //func->untag()->token_pos_ = d->ReadTokenPosition();
                        //func->untag()->end_token_pos_ = d->ReadTokenPosition();
                        //func->untag()->kernel_offset_ = d->Read<uint32_t>();
                    }
                }

                uint32_t packed_fields_ = d->Read<uint32_t>();
                uint32_t kind_tag_ = d->Read<uint32_t>();
                if (kind == kFullAOT) {
                    // Omit fields used to support de/reoptimization.
                }
                else {
                    
                }
            }
        }

        //void PostLoad(Deserializer* d, const Array& refs, bool is_canonical) {
        //    if (d->kind() == Snapshot::kFullAOT) {
        //        Function& func = Function::Handle(d->zone());
        //        for (intptr_t i = start_index_; i < stop_index_; i++) {
        //            func ^= refs.At(i);
        //            ASSERT(func.ptr()->untag()->code_->IsCode());
        //            uword entry_point = func.ptr()->untag()->code_->untag()->entry_point_;
        //            ASSERT(entry_point != 0);
        //            func.ptr()->untag()->entry_point_ = entry_point;
        //            uword unchecked_entry_point =
        //                func.ptr()->untag()->code_->untag()->unchecked_entry_point_;
        //            ASSERT(unchecked_entry_point != 0);
        //            func.ptr()->untag()->unchecked_entry_point_ = unchecked_entry_point;
        //        }
        //    }
        //    else if (d->kind() == Snapshot::kFullJIT) {
        //        Function& func = Function::Handle(d->zone());
        //        Code& code = Code::Handle(d->zone());
        //        for (intptr_t i = start_index_; i < stop_index_; i++) {
        //            func ^= refs.At(i);
        //            code = func.CurrentCode();
        //            if (func.HasCode() && !code.IsDisabled()) {
        //                func.SetInstructionsSafe(code);  // Set entrypoint.
        //                func.SetWasCompiled(true);
        //            }
        //            else {
        //                func.ClearCodeSafe();  // Set code and entrypoint to lazy compile stub
        //            }
        //        }
        //    }
        //    else {
        //        Function& func = Function::Handle(d->zone());
        //        for (intptr_t i = start_index_; i < stop_index_; i++) {
        //            func ^= refs.At(i);
        //            func.ClearCodeSafe();  // Set code and entrypoint to lazy compile stub.
        //        }
        //    }
        //}
    };
}
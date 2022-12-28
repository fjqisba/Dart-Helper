#pragma once
#include "DeserializationCluster.h"
#include "../app_snapshot.h"
#include "../object.h"

namespace Dart212
{
    class FieldDeserializationCluster : public DeserializationCluster {
    public:
        FieldDeserializationCluster() : DeserializationCluster("Field") {}
        ~FieldDeserializationCluster() {}

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
                if (kind != kFullAOT) {
                   void* guarded_list_length_ = d->ReadRef();
                }
                if (kind == kFullJIT) {
                    void* ependent_code_ = d->ReadRef();
                }
                uint16_t kind_bits_ = d->Read<uint16_t>();
                void* value_or_offset = d->ReadRef();
                if (Field::StaticBit::decode(kind_bits_)) {
                    const intptr_t field_id = d->ReadUnsigned();
                }
                else {

                }
            }
        }

        //void PostLoad(Deserializer* d, const Array& refs, bool is_canonical) {
        //    Field& field = Field::Handle(d->zone());
        //    if (!IsolateGroup::Current()->use_field_guards()) {
        //        for (intptr_t i = start_index_; i < stop_index_; i++) {
        //            field ^= refs.At(i);
        //            field.set_guarded_cid_unsafe(kDynamicCid);
        //            field.set_is_nullable_unsafe(true);
        //            field.set_guarded_list_length_unsafe(Field::kNoFixedLength);
        //            field.set_guarded_list_length_in_object_offset_unsafe(
        //                Field::kUnknownLengthOffset);
        //            field.set_static_type_exactness_state(
        //                StaticTypeExactnessState::NotTracking());
        //        }
        //    }
        //    else {
        //        for (intptr_t i = start_index_; i < stop_index_; i++) {
        //            field ^= refs.At(i);
        //            field.InitializeGuardedListLengthInObjectOffset(/*unsafe=*/true);
        //        }
        //    }
        //}
    };
}
#pragma once
#include "DeserializationCluster.h"
#include "../app_snapshot.h"

namespace Dart212
{
    class TypeArgumentsDeserializationCluster : public DeserializationCluster {
    public:
        TypeArgumentsDeserializationCluster()
            : DeserializationCluster("TypeArguments") {}
        ~TypeArgumentsDeserializationCluster() {}

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
                int32_t hash_ = d->Read<int32_t>();
                intptr_t nullability_ = d->ReadUnsigned();
                d->ReadRef();
                for (intptr_t j = 0; j < length; j++) {
                    d->ReadRef();
                }
            }
        }

        //void PostLoad(Deserializer* d, const Array& refs, bool is_canonical) {
        //    if (is_canonical && (d->isolate() != Dart::vm_isolate())) {
        //        CanonicalTypeArgumentsSet table(
        //            d->zone(),
        //            d->isolate_group()->object_store()->canonical_type_arguments());
        //        TypeArguments& type_arg = TypeArguments::Handle(d->zone());
        //        for (intptr_t i = start_index_; i < stop_index_; i++) {
        //            type_arg ^= refs.At(i);
        //            ASSERT(type_arg.IsCanonical());
        //            bool present = table.Insert(type_arg);
        //            // Two recursive types with different topology (and hashes) may be
        //            // equal.
        //            ASSERT(!present || type_arg.IsRecursive());
        //        }
        //        d->isolate_group()->object_store()->set_canonical_type_arguments(
        //            table.Release());
        //    }
        //}
    };
}
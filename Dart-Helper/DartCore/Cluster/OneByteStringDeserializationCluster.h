#pragma once
#include "DeserializationCluster.h"
#include "../app_snapshot.h"

namespace Dart212
{
    class OneByteStringDeserializationCluster : public DeserializationCluster {
    public:
        OneByteStringDeserializationCluster()
            : DeserializationCluster("OneByteString") {}
        ~OneByteStringDeserializationCluster() {}

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
                for (intptr_t j = 0; j < length; j++) {
                    uint8_t code_unit = d->Read<uint8_t>();
                }
            }
        }

        //void PostLoad(Deserializer* d, const Array& refs, bool is_canonical) {
        //    if (is_canonical && (d->isolate() != Dart::vm_isolate())) {
        //        CanonicalStringSet table(
        //            d->zone(), d->isolate_group()->object_store()->symbol_table());
        //        String& str = String::Handle(d->zone());
        //        for (intptr_t i = start_index_; i < stop_index_; i++) {
        //            str ^= refs.At(i);
        //            ASSERT(str.IsCanonical());
        //            bool present = table.Insert(str);
        //            ASSERT(!present);
        //        }
        //        d->isolate_group()->object_store()->set_symbol_table(table.Release());
        //    }
        //}
    };
}
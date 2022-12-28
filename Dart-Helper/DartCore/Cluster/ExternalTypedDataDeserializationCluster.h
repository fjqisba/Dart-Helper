#pragma once
#include "DeserializationCluster.h"
#include "../app_snapshot.h"

namespace Dart212
{
    class ExternalTypedDataDeserializationCluster : public DeserializationCluster {
    public:
        explicit ExternalTypedDataDeserializationCluster(intptr_t cid)
            : DeserializationCluster("ExternalTypedData"), cid_(cid) {}
        ~ExternalTypedDataDeserializationCluster() {}

        void ReadAlloc(Deserializer* d, bool is_canonical) {
            start_index_ = d->next_index();
            const intptr_t count = d->ReadUnsigned();
            for (intptr_t i = 0; i < count; i++) {
                d->AssignRef(0x0);
            }
            stop_index_ = d->next_index();
        }

        void ReadFill(Deserializer* d, bool is_canonical) {
            throw("干,先不实现了");
            //intptr_t element_size = ExternalTypedData::ElementSizeInBytes(cid_);
            //for (intptr_t id = start_index_; id < stop_index_; id++) {
            //    const intptr_t length = d->ReadUnsigned();
            //    d->Align(ExternalTypedData::kDataSerializationAlignment);
            //    d->Advance(length * element_size);
            //}
        };

    private:
        const intptr_t cid_;
    };
}


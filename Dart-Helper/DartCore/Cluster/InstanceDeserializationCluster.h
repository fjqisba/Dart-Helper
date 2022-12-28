#pragma once
#include "AbstractInstanceDeserializationCluster.h"
#include "../app_snapshot.h"
#include "../class_table.h"

class InstanceDeserializationCluster : public DeserializationCluster2_1_2 {
public:
    explicit InstanceDeserializationCluster(intptr_t cid)
        : DeserializationCluster2_1_2("Instance"), cid_(cid) {}
    ~InstanceDeserializationCluster() {}

    void ReadAlloc(Deserializer* d, bool is_canonical) {
        start_index_ = d->next_index();
        const intptr_t count = d->ReadUnsigned();
        next_field_offset_in_words_ = d->Read<int32_t>();
        instance_size_in_words_ = d->Read<int32_t>();
        for (intptr_t i = 0; i < count; i++) {
            d->AssignRef(0x0);
        }
        stop_index_ = d->next_index();
    }

    void ReadFill(Deserializer* d, bool is_canonical) {
        intptr_t next_field_offset = next_field_offset_in_words_ << kWordSizeLog2;
        intptr_t instance_size = RoundedAllocationSize(instance_size_in_words_ * kWordSize);
        const UnboxedFieldBitmap unboxed_fields_bitmap(d->ReadUnsigned64());
        for (intptr_t id = start_index_; id < stop_index_; id++) {
#ifdef __EA64__
            intptr_t offset = 8;
#else
            intptr_t offset = 4;
#endif
            while (offset < next_field_offset) {
                if (unboxed_fields_bitmap.Get(offset / kWordSize)) {
                    d->ReadWordWith32BitReads();
                }
                else {
                    d->ReadRef();
                }
                offset += kWordSize;
            }
            if (offset < instance_size) {
                offset += kWordSize;
            }
        }
    }

private:
    const intptr_t cid_;
    intptr_t next_field_offset_in_words_;
    intptr_t instance_size_in_words_;
};
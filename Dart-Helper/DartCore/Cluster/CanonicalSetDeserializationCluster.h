#pragma once
#include "DeserializationCluster.h"
#include "../app_snapshot.h"

class CanonicalSetDeserializationCluster : public DeserializationCluster
{
public:
    CanonicalSetDeserializationCluster(bool is_canonical, bool is_root_unit, const char* name) : DeserializationCluster(name, is_canonical), is_root_unit_(is_root_unit) {};
    void BuildCanonicalSetFromLayout(Deserializer* d) {
        if (!is_root_unit_ || !is_canonical()) {
            return;
        }
        const auto table_length = d->ReadUnsigned();
        first_element_ = d->ReadUnsigned();
        const intptr_t count = stop_index_ - (start_index_ + first_element_);
        //auto table = StartDeserialization(d, table_length, count);
        for (intptr_t i = start_index_ + first_element_; i < stop_index_; i++) {
            d->ReadUnsigned();
        }
        //table_ = table.Finish();
    };
protected:
    const bool is_root_unit_;
    intptr_t first_element_;
};
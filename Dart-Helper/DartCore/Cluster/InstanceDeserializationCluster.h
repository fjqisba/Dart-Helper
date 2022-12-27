#pragma once
#include "AbstractInstanceDeserializationCluster.h"

class InstanceDeserializationCluster:public AbstractInstanceDeserializationCluster
{
public:
    explicit InstanceDeserializationCluster(intptr_t cid, bool is_canonical);
private:
    const intptr_t cid_;
    intptr_t next_field_offset_in_words_;
    intptr_t instance_size_in_words_;
};
#pragma once
#include "DeserializationCluster.h"

class AbstractInstanceDeserializationCluster2_1_2 : public DeserializationCluster2_1_2 {
protected:
    explicit AbstractInstanceDeserializationCluster2_1_2(const char* name, bool is_canonical);
};
#pragma once
#include "DeserializationCluster.h"
#include "../app_snapshot.h"

class CanonicalSetDeserializationCluster : public DeserializationCluster2_1_2
{
public:
protected:
    const bool is_root_unit_;
    intptr_t first_element_;
};
#pragma once
#include "DeserializationCluster.h"

class AbstractInstanceDeserializationCluster : public DeserializationCluster {
protected:
    explicit AbstractInstanceDeserializationCluster(const char* name, bool is_canonical);
};
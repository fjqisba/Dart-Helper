#pragma once
#include "CanonicalSetDeserializationCluster.h"
#include "../class_id.h"

class StringDeserializationCluster : public CanonicalSetDeserializationCluster
{
public:
    static intptr_t DecodeLengthAndCid(intptr_t encoded, intptr_t* out_cid) {
        *out_cid = (encoded & 0x1) != 0 ? kTwoByteStringCid : kOneByteStringCid;
        return encoded >> 1;
    }
    explicit StringDeserializationCluster(bool is_canonical, bool is_root_unit);
    void ReadAlloc(Deserializer* d);
};
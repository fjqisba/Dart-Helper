#pragma once
#include <cstdint>

class SerializationCluster
{
public:
    static constexpr intptr_t kSizeVaries = -1;
    explicit SerializationCluster(const char* name,intptr_t cid,intptr_t target_instance_size = kSizeVaries,bool is_canonical = false);
    virtual ~SerializationCluster() {}
protected:
    const char* const name_;
    const intptr_t cid_;
    const intptr_t target_instance_size_;
    const bool is_canonical_;
    intptr_t size_ = 0;
    intptr_t num_objects_ = 0;
    intptr_t target_memory_size_ = 0;
};
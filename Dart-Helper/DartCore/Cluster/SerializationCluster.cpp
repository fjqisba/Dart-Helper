#include "SerializationCluster.h"

SerializationCluster::SerializationCluster(const char* name, intptr_t cid, intptr_t target_instance_size, bool is_canonical) : name_(name),cid_(cid),target_instance_size_(target_instance_size),is_canonical_(is_canonical)
{

}
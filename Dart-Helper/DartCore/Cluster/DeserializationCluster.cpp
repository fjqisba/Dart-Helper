#include "DeserializationCluster.h"
#include "../app_snapshot.h"


DeserializationCluster::DeserializationCluster(const char* name, bool is_canonical): name_(name),is_canonical_(is_canonical),start_index_(-1),stop_index_(-1)
{

}

void DeserializationCluster::ReadAlloc(Deserializer* d)
{

}

void DeserializationCluster::ReadAllocFixedSize(Deserializer* d, intptr_t instance_size)
{
	start_index_ = d->next_index();
	intptr_t count = d->ReadUnsigned();
	for (intptr_t i = 0; i < count; i++) {
		d->AssignRef(0x0);
	}
	stop_index_ = d->next_index();
}
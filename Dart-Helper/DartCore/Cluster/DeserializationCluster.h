#pragma once
#include <cstdint>

class Deserializer;
class DeserializationCluster
{
public:
	explicit DeserializationCluster(const char* name, bool is_canonical = false);
	virtual void ReadAlloc(Deserializer* d);

	const char* name() const { return name_; }
	bool is_canonical() const { return is_canonical_; }
protected:
	void ReadAllocFixedSize(Deserializer* deserializer, intptr_t instance_size);
protected:
	const char* const name_;
	const bool is_canonical_;
	// The range of the ref array that belongs to this cluster.
	intptr_t start_index_;
	intptr_t stop_index_;
};

#pragma once
#include <cstdint>

class Deserializer;

class DeserializationCluster2_1_2
{
public:
	explicit DeserializationCluster2_1_2(const char* name)
		: name_(name), start_index_(-1), stop_index_(-1) {}
	virtual ~DeserializationCluster2_1_2() {}

	virtual void ReadAlloc(Deserializer* deserializer, bool is_canonical) = 0;
	virtual void ReadFill(Deserializer* deserializer, bool is_canonical) = 0;
	//virtual void PostLoad(Deserializer* deserializer,
	//	const Array& refs,
	//	bool is_canonical) {}
	const char* name() const { return name_; }
protected:
	const char* name_;
	// The range of the ref array that belongs to this cluster.
	intptr_t start_index_;
	intptr_t stop_index_;
};

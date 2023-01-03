#pragma once
#include "DeserializationCluster.h"
#include "../app_snapshot.h"
#include "../Object/Object.h"

namespace Dart212
{
    class ObjectPoolDeserializationCluster : public DeserializationCluster {
    public:
        ObjectPoolDeserializationCluster() : DeserializationCluster("ObjectPool") {}
        ~ObjectPoolDeserializationCluster() {}

        void ReadAlloc(Deserializer* d, bool is_canonical) {
            start_index_ = d->next_index();
            const intptr_t count = d->ReadUnsigned();
            for (intptr_t i = 0; i < count; i++) {
                const intptr_t length = d->ReadUnsigned();
                d->AssignRef(0x0);
            }
            stop_index_ = d->next_index();
        }

        void ReadFill(Deserializer* d, bool is_canonical) {
            for (intptr_t id = start_index_; id < stop_index_; id += 1) {
                const intptr_t length = d->ReadUnsigned();
                ObjectPool* pool = static_cast<ObjectPool*>(d->Ref(id + 0));
                pool->length_ = length;
                for (intptr_t j = 0; j < length; j++) {
                    const uint8_t entry_bits = d->Read<uint8_t>();
                    //pool->untag()->entry_bits()[j] = entry_bits;
                    //UntaggedObjectPool::Entry& entry = pool->untag()->data()[j];
                    switch (ObjectPool::TypeBits::decode(entry_bits)) {
                    case ObjectPool::EntryType::kTaggedObject:
                        d->ReadRef();
                        break;
                    case ObjectPool::EntryType::kImmediate:
                        d->Read<intptr_t>();
                        break;
                    case ObjectPool::EntryType::kNativeFunction: {
                        // Read nothing. Initialize with the lazy link entry.
                        //uword new_entry = NativeEntry::LinkNativeCallEntry();
                        //entry.raw_value_ = static_cast<intptr_t>(new_entry);
                        break;
                    }
                    default:
                        break;
                    }
                }
            }
        }
    };
}
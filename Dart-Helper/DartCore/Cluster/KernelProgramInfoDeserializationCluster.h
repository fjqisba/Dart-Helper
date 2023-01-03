#pragma once
#include "DeserializationCluster.h"
#include "../app_snapshot.h"

namespace Dart212
{
    class KernelProgramInfoDeserializationCluster : public DeserializationCluster {
    public:
        KernelProgramInfoDeserializationCluster()
            : DeserializationCluster("KernelProgramInfo") {}
        ~KernelProgramInfoDeserializationCluster() {}

        void ReadAlloc(Deserializer* d, bool is_canonical) {
            start_index_ = d->next_index();
            const intptr_t count = d->ReadUnsigned();
            for (intptr_t i = 0; i < count; i++) {
                d->AssignRef(0x0);
            }
            stop_index_ = d->next_index();
        }

        void ReadFill(Deserializer* d, bool is_canonical) {
            for (intptr_t id = start_index_; id < stop_index_; id++) {
                uint32_t kernel_binary_version_ = d->Read<uint32_t>();
            }
        }

        //void PostLoad(Deserializer* d, const Array& refs, bool is_canonical) {
        //    Array& array = Array::Handle(d->zone());
        //    KernelProgramInfo& info = KernelProgramInfo::Handle(d->zone());
        //    for (intptr_t id = start_index_; id < stop_index_; id++) {
        //        info ^= refs.At(id);
        //        array = HashTables::New<UnorderedHashMap<SmiTraits>>(16, Heap::kOld);
        //        info.set_libraries_cache(array);
        //        array = HashTables::New<UnorderedHashMap<SmiTraits>>(16, Heap::kOld);
        //        info.set_classes_cache(array);
        //    }
        //}
    };
}
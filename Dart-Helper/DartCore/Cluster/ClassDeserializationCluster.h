#pragma once
#include "DeserializationCluster.h"
#include "../app_snapshot.h"

namespace Dart212
{
    class ClassDeserializationCluster : public DeserializationCluster 
    {
    public:
        ClassDeserializationCluster() : DeserializationCluster("Class") {}
        ~ClassDeserializationCluster() {}

        void ReadAlloc(Deserializer* d, bool is_canonical) {
            predefined_start_index_ = d->next_index();
            intptr_t count = d->ReadUnsigned();
            for (intptr_t i = 0; i < count; i++) {
                intptr_t class_id = d->ReadCid();
                d->AssignRef(0x0);
            }
            predefined_stop_index_ = d->next_index();
            start_index_ = d->next_index();
            count = d->ReadUnsigned();
            for (intptr_t i = 0; i < count; i++) {
                d->AssignRef(0x0);
            }
            stop_index_ = d->next_index();
        }

        void ReadFill(Deserializer* d, bool is_canonical) {

        };

    private:
        intptr_t predefined_start_index_;
        intptr_t predefined_stop_index_;
    };
}

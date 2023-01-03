#pragma once
#include "../globals.h"
#include "../bitfield.h"


namespace Dart212
{
    class Object;
	namespace compiler
	{
        struct ObjectPoolBuilderEntry {
            enum Patchability {
                kPatchable,
                kNotPatchable,
            };

            enum EntryType {
                kTaggedObject,
                kImmediate,
                kNativeFunction,

                // Used only during AOT snapshot serialization/deserialization.
                // Denotes kImmediate entry with
                //  - StubCode::SwitchableCallMiss().MonomorphicEntryPoint()
                //  - StubCode::MegamorphicCall().MonomorphicEntryPoint()
                // values which become known only at run time.
                kSwitchableCallMissEntryPoint,
                kMegamorphicCallEntryPoint,
#if defined(TARGET_ARCH_IS_32_BIT)
                kImmediate64,
#endif
                kImmediate128,
            };

            using TypeBits = BitField<uint8_t, EntryType, 0, 7>;
            using PatchableBit = BitField<uint8_t, Patchability, TypeBits::kNextBit, 1>;

            static inline uint8_t EncodeTraits(EntryType type, Patchability patchable) {
                return TypeBits::encode(type) | PatchableBit::encode(patchable);
            }

            ObjectPoolBuilderEntry() : imm128_(), entry_bits_(0), equivalence_() {}
            ObjectPoolBuilderEntry(const Object* obj, Patchability patchable)
                : ObjectPoolBuilderEntry(obj, obj, patchable) {}
            ObjectPoolBuilderEntry(const Object* obj,
                const Object* eqv,
                Patchability patchable)
                : obj_(obj),
                entry_bits_(EncodeTraits(kTaggedObject, patchable)),
                equivalence_(eqv) {}
            ObjectPoolBuilderEntry(uintptr_t value, EntryType info, Patchability patchable)
                : imm_(value),
                entry_bits_(EncodeTraits(info, patchable)),
                equivalence_() {}
#if defined(ARCH_IS_32_BIT)
            ObjectPoolBuilderEntry(uint64_t value, EntryType info, Patchability patchable)
                : imm64_(value),
                entry_bits_(EncodeTraits(info, patchable)),
                equivalence_() {}
#endif
            ObjectPoolBuilderEntry(simd128_value_t value,
                EntryType info,
                Patchability patchable)
                : imm128_(value),
                entry_bits_(EncodeTraits(info, patchable)),
                equivalence_() {}

            EntryType type() const { return TypeBits::decode(entry_bits_); }

            Patchability patchable() const { return PatchableBit::decode(entry_bits_); }

            union {
                const Object* obj_;
                uintptr_t imm_;
                uint64_t imm64_;
                simd128_value_t imm128_;
            };
            uint8_t entry_bits_;
            const Object* equivalence_;
        };
	}
}
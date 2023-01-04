#pragma once
#include <string>
#include "object_pool_builder.h"

namespace Dart212
{
	class Object
	{
	public:
		Object(const char* type, const char* name, bool isBase = false);
	private:
		std::string type;
		std::string name;
		//是否为基础对象
		bool isBase;

	};
	class TypedDataBase
	{
	public:
		static intptr_t ElementSizeInBytes(int32_t cid);
		static intptr_t ElementType(int32_t cid);
	private:
		static intptr_t element_size(intptr_t index);
	};
	class TypedData :public TypedDataBase {
	public:

	};

	class Code :public Object
	{
	public:
		Code() :Object("Code", "Object") {};
	};
	class Field
	{
	public:
	private:
		enum {
			kConstBit = 0,
			kStaticBit,
			kFinalBit,
			kHasNontrivialInitializerBit,
			kUnboxedBit,
			kReflectableBit,
			kInitializerChangedAfterInitializatonBit,
			kHasPragmaBit,
			kCovariantBit,
			kGenericCovariantImplBit,
			kIsLateBit,
			kIsExtensionMemberBit,
			kNeedsLoadGuardBit,
			kHasInitializerBit,
		};
		class ConstBit : public BitField<uint16_t, bool, kConstBit, 1> {};
		class StaticBit : public BitField<uint16_t, bool, kStaticBit, 1> {};
		class FinalBit : public BitField<uint16_t, bool, kFinalBit, 1> {};
		class HasNontrivialInitializerBit
			: public BitField<uint16_t, bool, kHasNontrivialInitializerBit, 1> {};
		class UnboxedBit : public BitField<uint16_t, bool, kUnboxedBit, 1> {};
		class ReflectableBit : public BitField<uint16_t, bool, kReflectableBit, 1> {};
		class InitializerChangedAfterInitializatonBit
			: public BitField<uint16_t,
			bool,
			kInitializerChangedAfterInitializatonBit,
			1> {};
		class HasPragmaBit : public BitField<uint16_t, bool, kHasPragmaBit, 1> {};
		class CovariantBit : public BitField<uint16_t, bool, kCovariantBit, 1> {};
		class GenericCovariantImplBit
			: public BitField<uint16_t, bool, kGenericCovariantImplBit, 1> {};
		class IsLateBit : public BitField<uint16_t, bool, kIsLateBit, 1> {};
		class IsExtensionMemberBit
			: public BitField<uint16_t, bool, kIsExtensionMemberBit, 1> {};
		class NeedsLoadGuardBit
			: public BitField<uint16_t, bool, kNeedsLoadGuardBit, 1> {};
		class HasInitializerBit
			: public BitField<uint16_t, bool, kHasInitializerBit, 1> {};
		friend class FieldDeserializationCluster;
	};


	class ObjectPool:public Object
	{
	public:
		using EntryType = compiler::ObjectPoolBuilderEntry::EntryType;
		using Patchability = compiler::ObjectPoolBuilderEntry::Patchability;
		using TypeBits = compiler::ObjectPoolBuilderEntry::TypeBits;
		using PatchableBit = compiler::ObjectPoolBuilderEntry::PatchableBit;
	public:
		intptr_t length_;
	};
}


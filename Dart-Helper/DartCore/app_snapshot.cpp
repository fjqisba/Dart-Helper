#include "app_snapshot.h"
#include "datastream.h"
#include "utils.h"
#include "globals.h"
#include "class_id.h"
#include "./Cluster/FunctionDeserializationCluster.h"
#include "./Cluster/InstanceDeserializationCluster.h"
#include "./Cluster/TypedDataViewDeserializationCluster.h"
#include "./Cluster/ExternalTypedDataDeserializationCluster.h"
#include "./Cluster/StringDeserializationCluster.h"
#include "./Cluster/MintDeserializationCluster.h"
#include "./Cluster/OneByteStringDeserializationCluster.h"
#include "./Cluster/CodeDeserializationCluster.h"
#include "./Cluster/TypedDataDeserializationCluster.h"
#include "./Cluster/ClassDeserializationCluster.h"
#include "./Cluster/TypeArgumentsDeserializationCluster.h"
#include "./Cluster/PatchClassDeserializationCluster.h"
#include "./Cluster/ClosureDataDeserializationCluster.h"
#include "./Cluster/FfiTrampolineDataDeserializationCluster.h"
#include "./Cluster/FieldDeserializationCluster.h"
#include "./Cluster/ScriptDeserializationCluster.h"

Deserializer::Deserializer(SnapshotKind kind):kind_(kind)
{

}

Deserializer::~Deserializer()
{
	for (unsigned int n = 0; n < refs_.size(); ++n) {
		if (refs_[n]) {
			delete refs_[n];
		}
	}
}

uint32_t Deserializer::ReadUInt32()
{
	return stream_.ReadAny<uint32_t>();
}

uint64_t Deserializer::ReadUInt64()
{
	return stream_.ReadAny<uint64_t>();
}

uint64_t Deserializer::ReadUnsigned64()
{
	return stream_.ReadUnsigned<uint64_t>();
}

uintptr_t Deserializer::ReadWordWith32BitReads()
{
	return stream_.ReadWordWith32BitReads();
}

intptr_t Deserializer::next_index() const
{
	return next_ref_index_;
}

void Deserializer::set_code_start_index(intptr_t value)
{
	code_start_index_ = value;
}

void Deserializer::set_code_stop_index(intptr_t value)
{
	code_stop_index_ = value;
}

void Deserializer::AssignRef(void* object)
{
	refs_.push_back(object);
	next_ref_index_++;
}

void* Deserializer::ReadRef()
{
	return Ref(ReadUnsigned());
}

SnapshotKind Deserializer::kind()
{
	return kind_;
}

void* Deserializer::Ref(intptr_t index)
{
	return refs_.at(index);
}

Dart212::DeserializationCluster* Deserializer::ReadCluster_2_1_2(Deserializer* d)
{
	using namespace Dart212;
	intptr_t cid = d->ReadCid();
	if (cid >= kNumPredefinedCids || cid == kInstanceCid) {
		return new InstanceDeserializationCluster(cid);
	}	
	if (IsTypedDataViewClassId(cid)) {
		return new TypedDataViewDeserializationCluster(cid);
	}
	if (IsExternalTypedDataClassId(cid)) {
		return new ExternalTypedDataDeserializationCluster(cid);
	}
	if (IsTypedDataClassId(cid)) {
		return new TypedDataDeserializationCluster(cid);
	}

	if (DartSetup::IncludesCode()) {
		switch (cid) {
		case kPcDescriptorsCid:
		case kCodeSourceMapCid:
		case kCompressedStackMapsCid:
			//return new (Z) RODataDeserializationCluster(cid);
		case kOneByteStringCid:
		case kTwoByteStringCid:
			//if (!is_non_root_unit_) {
			//	return new (Z) RODataDeserializationCluster(cid);
			//}
			break;
		}
	}
	
	switch (cid) {
	case kClassCid:
		return new ClassDeserializationCluster();
	case kTypeArgumentsCid:
		return new TypeArgumentsDeserializationCluster();
	case kPatchClassCid:
		return new PatchClassDeserializationCluster();
	case kFunctionCid:
		return new FunctionDeserializationCluster();
	case kClosureDataCid:
		return new ClosureDataDeserializationCluster();
	case kFfiTrampolineDataCid:
		return new FfiTrampolineDataDeserializationCluster();
	case kFieldCid:
		return new FieldDeserializationCluster();
	case kScriptCid:
		return new ScriptDeserializationCluster();
 //   case kLibraryCid:
 //       return new (Z) LibraryDeserializationCluster();
 //   case kNamespaceCid:
 //       return new (Z) NamespaceDeserializationCluster();
 //   case kKernelProgramInfoCid:
 //       return new (Z) KernelProgramInfoDeserializationCluster();
case kCodeCid:
	return new CodeDeserializationCluster();
 //   case kObjectPoolCid:
 //       return new (Z) ObjectPoolDeserializationCluster();
 //   case kPcDescriptorsCid:
 //       return new (Z) PcDescriptorsDeserializationCluster();
 //   case kExceptionHandlersCid:
 //       return new (Z) ExceptionHandlersDeserializationCluster();
 //   case kContextCid:
 //       return new (Z) ContextDeserializationCluster();
 //   case kContextScopeCid:
 //       return new (Z) ContextScopeDeserializationCluster();
 //   case kUnlinkedCallCid:
 //       return new (Z) UnlinkedCallDeserializationCluster();
 //   case kICDataCid:
 //       return new (Z) ICDataDeserializationCluster();
 //   case kMegamorphicCacheCid:
 //       return new (Z) MegamorphicCacheDeserializationCluster();
 //   case kSubtypeTestCacheCid:
 //       return new (Z) SubtypeTestCacheDeserializationCluster();
 //   case kLoadingUnitCid:
 //       return new (Z) LoadingUnitDeserializationCluster();
 //   case kLanguageErrorCid:
 //       return new (Z) LanguageErrorDeserializationCluster();
 //   case kUnhandledExceptionCid:
 //       return new (Z) UnhandledExceptionDeserializationCluster();
 //   case kLibraryPrefixCid:
 //       return new (Z) LibraryPrefixDeserializationCluster();
 //   case kTypeCid:
 //       return new (Z) TypeDeserializationCluster();
 //   case kFunctionTypeCid:
 //       return new (Z) FunctionTypeDeserializationCluster();
 //   case kTypeRefCid:
 //       return new (Z) TypeRefDeserializationCluster();
 //   case kTypeParameterCid:
 //       return new (Z) TypeParameterDeserializationCluster();
 //   case kClosureCid:
 //       return new (Z) ClosureDeserializationCluster();
	case kMintCid:
		return new MintDeserializationCluster();
 //   case kDoubleCid:
 //       return new (Z) DoubleDeserializationCluster();
 //   case kGrowableObjectArrayCid:
 //       return new (Z) GrowableObjectArrayDeserializationCluster();
 //   case kStackTraceCid:
 //       return new (Z) StackTraceDeserializationCluster();
 //   case kRegExpCid:
 //       return new (Z) RegExpDeserializationCluster();
 //   case kWeakPropertyCid:
 //       return new (Z) WeakPropertyDeserializationCluster();
 //   case kLinkedHashMapCid:
 //       return new (Z) LinkedHashMapDeserializationCluster();
 //   case kArrayCid:
 //       return new (Z) ArrayDeserializationCluster(kArrayCid);
 //   case kImmutableArrayCid:
 //       return new (Z) ArrayDeserializationCluster(kImmutableArrayCid);
	case kOneByteStringCid:
		return new OneByteStringDeserializationCluster();
 //   case kTwoByteStringCid:
 //       return new (Z) TwoByteStringDeserializationCluster();
 //   case kWeakSerializationReferenceCid:
 //       return new (Z) WeakSerializationReferenceDeserializationCluster();
    default:
        break;
	}
	return nullptr;
}

std::string Deserializer::ReadStr()
{
	std::string retStr;
	const char* cursor =
		reinterpret_cast<const char*>(stream_.AddressOfCurrentPosition());
	const intptr_t length = Utils::StrNLen(cursor, stream_.PendingBytes());
	if (length >= stream_.PendingBytes()) {
		return "";
	}
	retStr.assign(cursor, length);
	stream_.Advance(length + 1);
	return retStr;
}

intptr_t Deserializer::ReadCid()
{
	return Read<int32_t>();
}

std::string Deserializer::ReadVersion()
{
	std::string retVer;
	retVer.assign((const char*)stream_.AddressOfCurrentPosition(),32);
	stream_.Advance(32);
	return retVer;
}

void Deserializer::AddBaseObject(void* base_object)
{
	AssignRef(base_object);
}

bool Deserializer::InitDeserializer(std::vector<unsigned char>& snapshotData)
{
	stream_ = ReadStream(snapshotData.data(), snapshotData.size());

	return true;
}


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
#include "./Cluster/LibraryDeserializationCluster.h"
#include "./Cluster/NamespaceDeserializationCluster.h"
#include "./Cluster/KernelProgramInfoDeserializationCluster.h"
#include "./Cluster/ObjectPoolDeserializationCluster.h"
#include "./Cluster/PcDescriptorsDeserializationCluster.h"
#include "./Cluster/ExceptionHandlersDeserializationCluster.h"
#include "./Cluster/ContextDeserializationCluster.h"
#include "./Cluster/ContextScopeDeserializationCluster.h"
#include "./Cluster/UnlinkedCallDeserializationCluster.h"
#include "./Cluster/ICDataDeserializationCluster.h"
#include "./Cluster/MegamorphicCacheDeserializationCluster.h"
#include "./Cluster/SubtypeTestCacheDeserializationCluster.h"
#include "./Cluster/LoadingUnitDeserializationCluster.h"
#include "./Cluster/LanguageErrorDeserializationCluster.h"
#include "./Cluster/UnhandledExceptionDeserializationCluster.h"
#include "./Cluster/LibraryPrefixDeserializationCluster.h"
#include "./Cluster/TypeDeserializationCluster.h"
#include "./Cluster/FunctionTypeDeserializationCluster.h"
#include "./Cluster/TypeRefDeserializationCluster.h"
#include "./Cluster/TypeParameterDeserializationCluster.h"
#include "./Cluster/ClosureDeserializationCluster.h"
#include "./Cluster/DoubleDeserializationCluster.h"
#include "./Cluster/GrowableObjectArrayDeserializationCluster.h"
#include "./Cluster/StackTraceDeserializationCluster.h"
#include "./Cluster/RegExpDeserializationCluster.h"
#include "./Cluster/WeakPropertyDeserializationCluster.h"
#include "./Cluster/LinkedHashMapDeserializationCluster.h"
#include "./Cluster/ArrayDeserializationCluster.h"
#include "./Cluster/TwoByteStringDeserializationCluster.h"
#include "./Cluster/WeakSerializationReferenceDeserializationCluster.h"

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
	case kLibraryCid:
		return new LibraryDeserializationCluster();
	case kNamespaceCid:
		return new NamespaceDeserializationCluster();
	case kKernelProgramInfoCid:
		return new KernelProgramInfoDeserializationCluster();
	case kCodeCid:
		return new CodeDeserializationCluster();
	case kObjectPoolCid:
		return new ObjectPoolDeserializationCluster();
	case kPcDescriptorsCid:
		return new PcDescriptorsDeserializationCluster();
	case kExceptionHandlersCid:
		return new ExceptionHandlersDeserializationCluster();
	case kContextCid:
		return new ContextDeserializationCluster();
	case kContextScopeCid:
		return new ContextScopeDeserializationCluster();
	case kUnlinkedCallCid:
		return new UnlinkedCallDeserializationCluster();
	case kICDataCid:
		return new ICDataDeserializationCluster();
	case kMegamorphicCacheCid:
		return new MegamorphicCacheDeserializationCluster();
	case kSubtypeTestCacheCid:
		return new SubtypeTestCacheDeserializationCluster();
	case kLoadingUnitCid:
		return new LoadingUnitDeserializationCluster();
	 case kLanguageErrorCid:
		return new LanguageErrorDeserializationCluster();
	case kUnhandledExceptionCid:
		return new UnhandledExceptionDeserializationCluster();
	case kLibraryPrefixCid:
		return new LibraryPrefixDeserializationCluster();
	case kTypeCid:
		return new TypeDeserializationCluster();
	case kFunctionTypeCid:
		return new FunctionTypeDeserializationCluster();
	case kTypeRefCid:
		return new TypeRefDeserializationCluster();
	case kTypeParameterCid:
		return new TypeParameterDeserializationCluster();
	case kClosureCid:
		 return new ClosureDeserializationCluster();
	case kMintCid:
		return new MintDeserializationCluster();
	case kDoubleCid:
		return new DoubleDeserializationCluster();
	case kGrowableObjectArrayCid:
		return new GrowableObjectArrayDeserializationCluster();
	case kStackTraceCid:
		return new StackTraceDeserializationCluster();
	case kRegExpCid:
		 return new RegExpDeserializationCluster();
	case kWeakPropertyCid:
		return new WeakPropertyDeserializationCluster();
	case kLinkedHashMapCid:
		return new LinkedHashMapDeserializationCluster();
	 case kArrayCid:
		return new ArrayDeserializationCluster(kArrayCid);
	case kImmutableArrayCid:
		return new ArrayDeserializationCluster(kImmutableArrayCid);
	case kOneByteStringCid:
		return new OneByteStringDeserializationCluster();
	 case kTwoByteStringCid:
		return new TwoByteStringDeserializationCluster();
	case kWeakSerializationReferenceCid:
		 return new WeakSerializationReferenceDeserializationCluster();
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


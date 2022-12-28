#include "snapshot.h"
#include "../Utils/IDAWrapper.h"
#include "app_snapshot.h"
#include "class_id.h"
#include "./Object/Object.h"


void Snapshot::InitDartSetup()
{
	DartSetup::SetSnapshotKind(this->header.Kind);
	if (header.Features.find("product") != std::string::npos) {
		DartSetup::SetIsProduct(true);
		if (this->header.Kind == kFullAOT) {
			DartSetup::SetIsPrecompiled(true);
		}
	}
	if (header.Features.find("debug") != std::string::npos) {
		DartSetup::SetIsDebug(true);
	}
	if (header.Features.find("use_bare_instructions") != std::string::npos) {
		DartSetup::SetUseBareInstructions(true);
	}
	if (header.Features.find("x64-sysv") != std::string::npos) {
		DartSetup::SetArch("X64");
	}
	else if (header.Features.find("arm-eabi") != std::string::npos) {
		DartSetup::SetArch("ARM");
	}
	else if (header.Features.find("arm64-sysv") != std::string::npos) {
		DartSetup::SetArch("ARM64");
	}
	
	if (this->header.Kind == kFullJIT || this->header.Kind == kFullAOT) {
		DartSetup::SetIncludesCode(true);
	}

	//初始化常量
	std::string arch = DartSetup::Arch();
	if (arch == "X64") {

	}
	else if (arch == "ARM") {
		kWordSizeLog2 = 2;
		kWordSize = 1 < kWordSizeLog2;
		kObjectAlignment = 8;
		kObjectAlignmentLog2 = 3;
	}
	else if (arch == "ARM64") {
		kWordSizeLog2 = 3;
		kWordSize = 1 < kWordSizeLog2;
		kObjectAlignment = 16;
		kObjectAlignmentLog2 = 4;
	}


	kBitsPerWordLog2 = kWordSizeLog2 + kBitsPerByteLog2;
	kBitsPerWord = 1 << kBitsPerWordLog2;
}

bool Snapshot::parseHeader(Deserializer& d)
{
	header.MagicValue = d.ReadUInt32();
	header.Length = d.ReadUInt64();
	header.Kind = (SnapshotKind)d.ReadUInt64();
	if (header.MagicValue != kMagicValue) {
		return false;
	}
	header.VersionHash = d.ReadVersion();
	header.Features = d.ReadStr();
	return true;
}

bool Snapshot::parseRoots_2_1_2(Deserializer& d)
{
	intptr_t num_base_objects_ = d.ReadUnsigned();
	intptr_t num_objects_ = d.ReadUnsigned();
	intptr_t num_canonical_clusters_ = d.ReadUnsigned();
	const intptr_t num_clusters_ = d.ReadUnsigned();
	const uint32_t initial_field_table_len = d.ReadUnsigned();

	Dart212::DeserializationCluster** canonical_clusters_ = new Dart212::DeserializationCluster *[num_canonical_clusters_];
	Dart212::DeserializationCluster** clusters_ = new Dart212::DeserializationCluster *[num_clusters_];

	for (intptr_t i = 0; i < num_canonical_clusters_; i++) {
		canonical_clusters_[i] = d.ReadCluster_2_1_2(&d);
		if (!canonical_clusters_[i]) {
			return false;
		}
		canonical_clusters_[i]->ReadAlloc(&d, true);
	}

	for (intptr_t i = 0; i < num_clusters_; i++) {
		clusters_[i] = d.ReadCluster_2_1_2(&d);
		if (!clusters_[i]) {
			return false;
		}
		clusters_[i]->ReadAlloc(&d, false);
	}

	//开始填充结构
	for (intptr_t i = 0; i < num_canonical_clusters_; i++) {
		canonical_clusters_[i]->ReadFill(&d, true);
	}
	for (intptr_t i = 0; i < num_clusters_; i++) {
		clusters_[i]->ReadFill(&d, false);
	}

	//for (intptr_t i = 0; i < num_canonical_clusters_; i++) {
 //     canonical_clusters_[i]->PostLoad(this, refs, /*is_canonical*/ true);
 //   }
	//for (intptr_t i = 0; i < num_clusters_; i++) {
	//	clusters_[i]->PostLoad(this, refs, /*is_canonical*/ false);
	//}
	return true;
}

bool Snapshot::parseRoots_3_0_0(Deserializer& d)
{
	intptr_t num_base_objects_ = d.ReadUnsigned();
	intptr_t num_objects_ = d.ReadUnsigned();
	intptr_t num_clusters_ = d.ReadUnsigned();
	const intptr_t instructions_table_len = d.ReadUnsigned();
	const uint32_t instruction_table_data_offset = d.ReadUnsigned();

	if (instructions_table_len > 0) {
		const intptr_t start_pc = 0x0;

		if (instruction_table_data_offset != 0) {

		}
	}
	return true;
}

bool Snapshot::parseRoots(Deserializer& d)
{
	switch (this->dartVer) {
	case Dart2_1_2:
		return this->parseRoots_2_1_2(d);
	case Dart3_0_0:
		return this->parseRoots_3_0_0(d);
	}
	return false;
}

//解析Dart版本号
DartVersion parseDartVersion(std::string& snapshot_hash)
{
	std::map<std::string, DartVersion> hashMap = {
		{"8ee4ef7a67df9845fba331734198a953",Dart2_1_0},
		{"5b97292b25f0a715613b7a28e0734f77",Dart2_1_2},
		{"c4781d920d6f2d466dde7b9ca5ca533f",Dart3_0_0},
	};
	return hashMap[snapshot_hash];
}

void Snapshot::AddBaseObjects_2_1_2(Deserializer* d)
{
	d->AddBaseObject(new Object("", "", true));
	d->AddBaseObject(new Object("Null", "null", true));
	d->AddBaseObject(new Object("Null", "sentinel", true));
	d->AddBaseObject(new Object("Null", "transition_sentinel", true));
	d->AddBaseObject(new Object("Array", "<empty_array>", true));
	d->AddBaseObject(new Object("Array", "<zero_array>", true));
	d->AddBaseObject(new Object("Type", "<dynamic type>", true));
	d->AddBaseObject(new Object("Type", "<void type>", true));
	d->AddBaseObject(new Object("TypeArguments", "[]", true));
	d->AddBaseObject(new Object("bool", "true", true));
	d->AddBaseObject(new Object("bool", "false", true));
	d->AddBaseObject(new Object("Array", "<extractor parameter types>", true));
	d->AddBaseObject(new Object("Array", "<extractor parameter names>", true));
	d->AddBaseObject(new Object("ContextScope", "<empty>", true));
	d->AddBaseObject(new Object("ObjectPool", "<empty>", true));
	d->AddBaseObject(new Object("CompressedStackMaps", "<empty>", true));
	d->AddBaseObject(new Object("PcDescriptors", "<empty>", true));
	d->AddBaseObject(new Object("LocalVarDescriptors", "<empty>", true));
	d->AddBaseObject(new Object("ExceptionHandlers", "<empty>", true));
	for (int i = 0; i < kCachedDescriptorCount; i++) {
		d->AddBaseObject(new Object("ArgumentsDescriptor", "<cached arguments descriptor>", true));
	}
	for (int i = 0; i < kCachedICDataArrayCount; i++) {
		d->AddBaseObject(new Object("Array", "<empty icdata entries>", true));
	}
	d->AddBaseObject(new Object("Array", "<empty subtype entries>", true));

	//添加类枚举
	d->AddBaseObject(new Object("Class", "Class", true));
	d->AddBaseObject(new Object("PatchClass", "Class", true));
	d->AddBaseObject(new Object("Function", "Class", true));
	d->AddBaseObject(new Object("ClosureData", "Class", true));
	d->AddBaseObject(new Object("FfiTrampolineData", "Class", true));
	d->AddBaseObject(new Object("Field", "Class", true));
	d->AddBaseObject(new Object("Script", "Class", true));
	d->AddBaseObject(new Object("Library", "Class", true));
	d->AddBaseObject(new Object("Namespace", "Class", true));
	d->AddBaseObject(new Object("KernelProgramInfo", "Class", true));
	d->AddBaseObject(new Object("Code", "Class", true));
	d->AddBaseObject(new Object("Instructions", "Class", true));
	d->AddBaseObject(new Object("InstructionsSection", "Class", true));
	d->AddBaseObject(new Object("ObjectPool", "Class", true));
	d->AddBaseObject(new Object("PcDescriptors", "Class", true));
	d->AddBaseObject(new Object("CodeSourceMap", "Class", true));
	d->AddBaseObject(new Object("CompressedStackMaps", "Class", true));
	d->AddBaseObject(new Object("LocalVarDescriptors", "Class", true));
	d->AddBaseObject(new Object("ExceptionHandlers", "Class", true));
	d->AddBaseObject(new Object("Context", "Class", true));
	d->AddBaseObject(new Object("ContextScope", "Class", true));
	d->AddBaseObject(new Object("SingleTargetCache", "Class", true));
	d->AddBaseObject(new Object("UnlinkedCall", "Class", true));
	d->AddBaseObject(new Object("MonomorphicSmiableCall", "Class", true));
	d->AddBaseObject(new Object("ICData", "Class", true));
	d->AddBaseObject(new Object("MegamorphicCache", "Class", true));
	d->AddBaseObject(new Object("SubtypeTestCache", "Class", true));
	d->AddBaseObject(new Object("LoadingUnit", "Class", true));
	d->AddBaseObject(new Object("ApiError", "Class", true));
	d->AddBaseObject(new Object("LanguageError", "Class", true));
	d->AddBaseObject(new Object("UnhandledException", "Class", true));
	d->AddBaseObject(new Object("UnwindError", "Class", true));	

	d->AddBaseObject(new Object("Dynamic", "Class", true));
	d->AddBaseObject(new Object("Void", "Class", true));
}

void Snapshot::AddBaseObjects(Deserializer* d)
{
	switch (this->dartVer) {
	case Dart2_1_2:
		AddBaseObjects_2_1_2(d);
	case Dart3_0_0:
		return;
	}
	return;
}

bool Snapshot::ParseSnapshot()
{
	std::map<std::string, unsigned int> entryMap = IDAWrapper::get_entry_map();
	unsigned int funcAddr = entryMap["_kDartVmSnapshotData"];
	std::vector<unsigned char> snapshotData = IDAWrapper::read_seg_data(funcAddr);
	if (!snapshotData.size()) {
		return false;
	}
	Deserializer d(header.Kind);
	if (!d.InitDeserializer(snapshotData)) {
		return false;
	}
	if (!parseHeader(d)) {
		return false;
	}
	this->dartVer = parseDartVersion(this->header.VersionHash);
	InitDartSetup();
	AddBaseObjects(&d);
	if (!parseRoots(d)) {
		return false;
	}
	return true;
}
#include "snapshot.h"
#include "../Utils/IDAWrapper.h"
#include "app_snapshot.h"

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

bool Snapshot::parseRoots(Deserializer& d)
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

	for (intptr_t i = 0; i < num_clusters_; i++) {
		DeserializationCluster* cluster = d.ReadCluster();
		if (!cluster) {
			continue;
		}
		cluster->ReadAlloc(&d);
	}

	return true;
}

//Ω‚ŒˆDart∞Ê±æ∫≈
DartVersion parseDartVersion(std::string& snapshot_hash)
{
	std::map<std::string, DartVersion> hashMap = {
		{"8ee4ef7a67df9845fba331734198a953",Dart2_1_0},
		{"5b97292b25f0a715613b7a28e0734f77",Dart2_1_2},
	};
	return hashMap[snapshot_hash];
}

bool Snapshot::ParseSnapshot()
{
	std::map<std::string, unsigned int> entryMap = IDAWrapper::get_entry_map();
	unsigned int funcAddr = entryMap["_kDartVmSnapshotData"];
	std::vector<unsigned char> snapshotData = IDAWrapper::read_seg_data(funcAddr);
	if (!snapshotData.size()) {
		return false;
	}
	Deserializer d;
	if (!d.InitDeserializer(snapshotData)) {
		return false;
	}
	if (!parseHeader(d)) {
		return false;
	}
	this->dartVer = parseDartVersion(this->header.VersionHash);
	SetGlobalDartVersion(this->dartVer);
	if (!parseRoots(d)) {
		return false;
	}
	return true;
}
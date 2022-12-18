#include "snapshot.h"
#include "../Utils/IDAWrapper.h"
#include "app_snapshot.h"

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
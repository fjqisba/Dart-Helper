#include "globals.h"

DartVersion gDartVersion;

void SetGlobalDartVersion(DartVersion ver)
{
	gDartVersion = ver;
}

ClassId getClassId_212(ClassId id)
{
	switch (id) {
	case kIllegalCid:
		return ClassId(0);
    case kNativePointer:
        return ClassId(1);
    case kFreeListElement:
        return ClassId(2);
    case kForwardingCorpse:
        return ClassId(3);
    case kObjectCid:
        return ClassId(4);
    case kClassCid:
        return ClassId(5);
	}
	return ClassId(0x0);
}

ClassId getClassId(ClassId id)
{
	switch (gDartVersion) {
	case Dart2_1_2:
		return getClassId_212(id);
	}
	return kIllegalCid;
}
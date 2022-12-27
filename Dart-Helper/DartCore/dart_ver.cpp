#include "dart_ver.h"

DartVersion gDartVerison;

void DartVer::SetCurrentVersion(DartVersion ver)
{
	gDartVerison = ver;
}

DartVersion DartVer::Version()
{
	return gDartVerison;
}
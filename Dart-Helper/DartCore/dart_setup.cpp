#include "dart_setup.h"
#include "snapshot.h"

DartVersion gDartVerison;
char gArch[16] = { 0 };
bool gIsProduct = false;
bool gIsPrecompiled = false;
bool gIsDebug = false;
bool gIncludesCode = false;
SnapshotKind gSnapshotKind;
bool gUseBareInstructions = false;

void DartSetup::SetCurrentVersion(DartVersion ver)
{
	gDartVerison = ver;
}

DartVersion DartSetup::Version()
{
	return gDartVerison;
}

void DartSetup::SetArch(const char* arch)
{
	memset(gArch,0x0,sizeof(gArch));
	strcpy(gArch, arch);
}

const char* DartSetup::Arch()
{
	return gArch;
}

void DartSetup::SetIsProduct(bool isProduct)
{
	gIsProduct = gIsProduct;
}

bool DartSetup::IsProduct(bool isProduct)
{
	return gIsProduct;
}

void DartSetup::SetIsPrecompiled(bool isPrecom)
{
	gIsPrecompiled = isPrecom;
}

bool DartSetup::IsPrecompiled()
{
	return gIsPrecompiled;
}

void DartSetup::SetIsDebug(bool isDbg)
{
	gIsDebug = isDbg;
}

bool DartSetup::IsDebug()
{
	return gIsDebug;
}

void DartSetup::SetIncludesCode(bool bInclude)
{
	gIncludesCode = bInclude;
}

bool DartSetup::IncludesCode()
{
	return gIncludesCode;
}

void DartSetup::SetSnapshotKind(::SnapshotKind kind)
{
	gSnapshotKind = kind;
}

SnapshotKind DartSetup::SnapshotKind()
{
	return gSnapshotKind;
}

void DartSetup::SetUseBareInstructions(bool bUse)
{
	gUseBareInstructions = bUse;
}

bool DartSetup::UseBareInstructions()
{
	return gUseBareInstructions;
}
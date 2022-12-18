#include "DartHelper.h"
#include "DartCore/snapshot.h"
#include "./Utils/IDAWrapper.h"

DartHelper::DartHelper()
{

}

DartHelper::~DartHelper()
{

}


bool DartHelper::InitDartHelper()
{
	Snapshot shotData;
	if (!shotData.ParseSnapshot()) {
		return false;
	}

	return true;
}
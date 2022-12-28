#pragma once
#include <string>

//和配置项有关的一些东东

enum DartVersion {
    DartUnknown = 0x0,
    Dart2_1_0,
    Dart2_1_2,
    Dart3_0_0,
};


class DartSetup
{
public:
    static void SetCurrentVersion(DartVersion ver);
    static DartVersion Version();
    static void SetArch(const char* arch);
    static const char* Arch();

    static void SetIsProduct(bool isProduct);
    static bool IsProduct(bool isProduct);

    static void SetIsPrecompiled(bool isPrecom);
    static bool IsPrecompiled();

    static void SetIsDebug(bool isDbg);
    static bool IsDebug();

    static void SetIncludesCode(bool bInclude);
    static bool IncludesCode();
};
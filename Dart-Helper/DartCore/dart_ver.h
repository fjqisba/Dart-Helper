#pragma once

enum DartVersion {
    DartUnknown = 0x0,
    Dart2_1_0,
    Dart2_1_2,
    Dart3_0_0,
};


class DartVer
{
public:
    static void SetCurrentVersion(DartVersion ver);
    static DartVersion Version();
};
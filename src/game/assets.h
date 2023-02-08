#include <iostream>
#include <fstream>
#include <map>
#include <zlib.h>
#include <map>
#include <vector>
#include <stdint.h>
#include <skia/core/SkStream.h>

using namespace std;

#ifndef THGAME_ASSETS_H
#define THGAME_ASSETS_H

class Assets{
private:
    static Assets Instance;

    typedef struct {
        uint32_t filePointer;
        uint32_t originSize;
        uint32_t compressedSize;
    } DataTableHeader;

    typedef struct {
        uint32_t assetsCount;
        DataTableHeader stringTable;
        DataTableHeader assestsTableHeader;
    } GameDataHeader;

    typedef struct {
        uint32_t filePointer;
        uint32_t originSize;
        uint32_t compressedSize;
        uint32_t namePointer;
        char type[4];
    } AssestTableHeader;

    typedef struct {
        uint32_t filePointer;
        uint32_t originSize;
        uint32_t compressedSize;
        bool loaded;
        char* memoryPointer;
    } AssetTableInfo;

    typedef map<string,AssetTableInfo> AssetsTable;

    AssetsTable AssetsList;

private:
    Assets();

public:
    static Assets* GetInstance();

    bool GetAssetsList();

    sk_sp<SkData> GetAsset(const string& name);

    bool LoadAssetFromFile(const string& name);

    void CleanUp();
};

#endif //UNTITLED_ASSETS_H

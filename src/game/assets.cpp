#include "assets.h"

using namespace std;

Assets Assets::Instance;

Assets::Assets() = default;

bool Assets::GetAssetsList(){
    try {
        ifstream fs;
        fs.open("./game.dat", ios::in|ios::binary);
        GameDataHeader game_data_header{};
        fs.seekg(4);
        fs.read((char *)&game_data_header,sizeof(game_data_header));

        DataTableHeader string_table = game_data_header.stringTable;
        auto* string_table_compressed = (unsigned char*)malloc(string_table.compressedSize);
        fs.seekg(string_table.filePointer);
        fs.read((char *)string_table_compressed,string_table.compressedSize);
        char* string_table_origin = (char *)malloc(string_table.originSize);
        uncompress((Bytef*)string_table_origin,(uLongf*)&string_table.originSize,
                   string_table_compressed,string_table.originSize);
        free(string_table_compressed);

        DataTableHeader assests_table_header = game_data_header.assestsTableHeader;
        auto* assests_table_header_compressed = (unsigned char*)malloc(assests_table_header.compressedSize);
        fs.seekg(assests_table_header.filePointer);
        fs.read((char *)assests_table_header_compressed,assests_table_header.compressedSize);
        auto* assests_table_header_origin = new AssestTableHeader[game_data_header.assetsCount];
        uncompress((Bytef*)assests_table_header_origin,(uLongf*)&assests_table_header.originSize,
                   assests_table_header_compressed,assests_table_header.originSize);
        free(assests_table_header_compressed);

        for (int i=0;i<game_data_header.assetsCount;i++){
            string name = string_table_origin+assests_table_header_origin[i].namePointer;
            name.append(".").append(assests_table_header_origin[i].type);
            AssetsList.insert(AssetsTable::value_type{name,AssetTableInfo(
                    {assests_table_header_origin[i].filePointer,
                     assests_table_header_origin[i].originSize,
                     assests_table_header_origin[i].compressedSize})});
            }
        free(string_table_origin);
        fs.close();
        return true;
    }catch (const char* e){
        printf("GetAssetsList error: %s", e);
        return false;
    }
}
sk_sp<SkData> Assets::GetAsset(const string& name){

    if (!AssetsList[name].loaded){
        LoadAssetFromFile(name);
    }
    if (!AssetsList.contains(name)){
        printf("Get asset %s error: no such file.", name.c_str());
    }
    return SkData::MakeFromMalloc(AssetsList[name].memoryPointer, AssetsList[name].originSize);
}

bool Assets::LoadAssetFromFile(const std::string &name) {
    try{
        ifstream fs;
        fs.open("./game.dat", ios::in|ios::binary);
        uint32_t _pointer = AssetsList[name].filePointer;
        uint32_t _origin_size = AssetsList[name].originSize;
        uint32_t _compressed_size = AssetsList[name].compressedSize;
        auto* assest_compressed = (unsigned char*)malloc(_compressed_size);
        fs.seekg(_pointer);
        fs.read((char *)assest_compressed,_compressed_size);
        auto* assest_origin = (char *)malloc(_origin_size);
        uncompress((Bytef*)assest_origin,(uLongf*)&_origin_size,assest_compressed,
                   _origin_size);
        free(assest_compressed);
        //free(assest_origin);
        AssetsList[name].loaded = true;
        AssetsList[name].memoryPointer = assest_origin;
        fs.close();
        return true;
    }catch (const char* e){
        printf("Get asset %s error: %s", name.c_str(), e);
        return false;
    }
}

void Assets::CleanUp() {
    for (const auto& asset : AssetsList) {
        free(asset.second.memoryPointer);
    }
}

Assets* Assets::GetInstance() {
    return &Assets::Instance;
}
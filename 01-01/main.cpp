#include <cstring> // strcmp
#include <list>
#include <stdio.h>

using namespace std;

// 駅リストを表示する関数
void PrintStations(const list<const char*>& stations, const char* title)
{
    printf("=== %s ===\n", title);
    int i = 1;
    for (auto itr = stations.begin(); itr != stations.end(); ++itr, ++i) {
        printf("%2d: %s\n", i, *itr);
    }
    printf("\n");
}

// 駅リストの指定された駅名の前に新しい駅名を挿入する関数
void InsertStation(list<const char*>& stations, const char* targetName, const char* newName)
{
    for (auto itr = stations.begin(); itr != stations.end(); ++itr) {
        if (strcmp(*itr, targetName) == 0) {
            stations.insert(itr, newName); // target の「前」に挿入
            return;
        }
    }
    stations.push_back(newName);
}

int main()
{
    // 山手線のリスト
    list<const char*> yamanote = { "Tokyo", "Kanda", "Akihabara", "Okachimachi", "Ueno",
        "Uguisudani", "Nippori", "Tabata", "Komagome",
        "Sugamo", "Otsuka", "Ikebukuro", "Mejiro", "Takadanobaba",
        "Shin-Okubo", "Shinjuku", "Yoyogi", "Harajuku", "Shibuya",
        "Ebisu", "Meguro", "Gotanda", "Osaki", "Shinagawa",
        "Tamachi", "Hamamatsucho", "Shimbashi", "Yurakucho" };

    // 2022年山手線
    list<const char*> yamanote2022 = yamanote;
    InsertStation(yamanote2022, "Tabata", "Nishi-Nippori");
    InsertStation(yamanote2022, "Tamachi", "Takanawa Gateway");

    //// 2019年山手線(高輪ゲートウェイ駅無)
    list<const char*> yamanote2019 = yamanote;
    InsertStation(yamanote2019, "Tabata", "Nishi-Nippori");

    // 1970年山手線（西日暮里駅・高輪ゲートウェイ無）
    list<const char*> yamanote1970 = yamanote;

    // 各年代毎の駅リストを表示
    PrintStations(yamanote2022, "2022年山手線(西日暮里駅・高輪ゲートウェイ有)");
    PrintStations(yamanote2019, "2019年山手線(西日暮里駅有・高輪ゲートウェイ無)");
    PrintStations(yamanote1970, "1970年山手線(西日暮里駅・高輪ゲートウェイ無)");

    return 0;
}
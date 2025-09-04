#ifndef __ORIGINAL_AVZ_ASM_H__
#define __ORIGINAL_AVZ_ASM_H__

#include "avz_multi_platform.h"
#include "avz_pvz_struct.h"
#include "avz_types.h"

#define ASaveAllRegister "esp", "eax", "ebx", "ecx", "edx", "esi", "edi"

// 使用汇编代码调用 PvZ 游戏内部的函数
namespace NS_ORIGIN(AAsm) {
    // key 1: left click
    // key -1: right click
    // key 3: middle click
    void ClickScene(AMainObject* level, int x, int y, int key);

    void Click(AMouseWindow* mw, int x, int y, int key);

    void SaveData();

    void LoadData();

    // 进入战斗页面，开始游戏
    void Rock();

    void MouseClick(int x, int y, int key);

    // 鼠标按下
    void MouseDown(int x, int y, int key);

    // 鼠标松开
    void MouseUp(int x, int y, int key);

    // 移动鼠标
    void MouseMove(int x, int y);

    // 发射炮
    void Fire(int x, int y, int rank);

    // 种卡函数
    void PlantCard(int x, int y, int index);

    // 铲除函数
    void ShovelPlant(int x, int y);

    // 选择卡片
    void ChooseCard(int card_type);

    // 选择模仿者卡片
    void ChooseImitatorCard(int card_type);

    enum PlantReject {
        NIL, // 没有植物, 即可以种植
        NOT_HERE,
        ONLY_ON_GRAVES,
        ONLY_IN_POOL,
        ONLY_ON_GROUND,
        NEEDS_POT,
        NOT_ON_ART,
        NOT_PASSED_LINE,
        NEEDS_UPGRADE,
        NOT_ON_GRAVE,
        NOT_ON_CRATER,
        NOT_ON_WATER,
        NEEDS_GROUND,
        NEEDS_SLEEPING
    };

    // 是否可种卡片
    // 返回值意义查看 `enum PlantReject`
    // *** 使用示例:
    // if(AAsm::GetPlantRejectType(AXRK_1, 1, 1) == AAsm::NIL) { // NIL 表示可以种植物， 检查一下 2 行 2 列是否可以种植物
    //
    // }
    __ANodiscard int GetPlantRejectType(int cardType, int row, int col);

    // 战斗界面刷新函数
    void GameFightLoop();

    // 游戏整体刷新函数
    void GameTotalLoop();

    // 游戏最完整刷新函数，带帧率控制
    void GameSleepLoop();

    // 控件管理器在一次更新中递归地更新其中所有的控件
    void UpdateFrame();

    void ClearObjectMemory();

    void CheckFightExit();

    void KillZombiesPreview();

    void SetImprovePerformance(bool is_improve_performance);

    void ReleaseMouse();

    __ANodiscard int GridToAbscissa(int row, int col);

    __ANodiscard int GridToOrdinate(int row, int col);

    // 放置一个植物
    // PutPlant(1, 1, ANGT_30) ----- 在2行2列放置一个南瓜头
    APlant* PutPlant(int row, int col, APlantType type);

    // 放置一个僵尸
    // PutZombie(1, 1, APJ_0) ----- 在2行2列放置一个普通僵尸
    AZombie* PutZombie(int row, int col, AZombieType type);

    void RemovePlant(APlant* plant);

    void KillZombie(AZombie* zombie);
    void RemoveZombie(AZombie* zombie);

    bool IsSeedUsable(ASeed* seed);
    int GetSeedSunVal(int type, int iType);
    void UpdateMousePos();

    void MakePvzString(const char* str, void* strObj);
    void FreePvzString(void* strObj);
    void MakeNewBoard();
    void LoadGame(const std::string& file);
    void SaveGame(const std::string& file);

    bool CanSpawnZombies(int row);
    bool IsNight();
    bool IsRoof();
    bool HasGrave();
    bool HasPool();

    int ZombieTotalHp(int wave);

    enum GameMode {
        ADVENTURE,
        SURVIVAL_NORMAL_STAGE_1,
        SURVIVAL_NORMAL_STAGE_2,
        SURVIVAL_NORMAL_STAGE_3,
        SURVIVAL_NORMAL_STAGE_4,
        SURVIVAL_NORMAL_STAGE_5,
        SURVIVAL_HARD_STAGE_1,
        SURVIVAL_HARD_STAGE_2,
        SURVIVAL_HARD_STAGE_3,
        SURVIVAL_HARD_STAGE_4,
        SURVIVAL_HARD_STAGE_5,
        SURVIVAL_ENDLESS_STAGE_1,
        SURVIVAL_ENDLESS_STAGE_2,
        SURVIVAL_ENDLESS_STAGE_3,
        SURVIVAL_ENDLESS_STAGE_4,
        SURVIVAL_ENDLESS_STAGE_5,
        CHALLENGE_WAR_AND_PEAS,
        CHALLENGE_WALLNUT_BOWLING,
        CHALLENGE_SLOT_MACHINE,
        CHALLENGE_RAINING_SEEDS,
        CHALLENGE_BEGHOULED,
        CHALLENGE_INVISIGHOUL,
        CHALLENGE_SEEING_STARS,
        CHALLENGE_ZOMBIQUARIUM,
        CHALLENGE_BEGHOULED_TWIST,
        CHALLENGE_LITTLE_TROUBLE,
        CHALLENGE_PORTAL_COMBAT,
        CHALLENGE_COLUMN,
        CHALLENGE_BOBSLED_BONANZA,
        CHALLENGE_SPEED,
        CHALLENGE_WHACK_A_ZOMBIE,
        CHALLENGE_LAST_STAND,
        CHALLENGE_WAR_AND_PEAS_2,
        CHALLENGE_WALLNUT_BOWLING_2,
        CHALLENGE_POGO_PARTY,
        CHALLENGE_FINAL_BOSS,
        CHALLENGE_ART_CHALLENGE_WALLNUT,
        CHALLENGE_SUNNY_DAY,
        CHALLENGE_RESODDED,
        CHALLENGE_BIG_TIME,
        CHALLENGE_ART_CHALLENGE_SUNFLOWER,
        CHALLENGE_AIR_RAID,
        CHALLENGE_ICE,
        CHALLENGE_ZEN_GARDEN,
        CHALLENGE_HIGH_GRAVITY,
        CHALLENGE_GRAVE_DANGER,
        CHALLENGE_SHOVEL,
        CHALLENGE_STORMY_NIGHT,
        CHALLENGE_BUNGEE_BLITZ,
        CHALLENGE_SQUIRREL,
        TREE_OF_WISDOM,
        SCARY_POTTER_1,
        SCARY_POTTER_2,
        SCARY_POTTER_3,
        SCARY_POTTER_4,
        SCARY_POTTER_5,
        SCARY_POTTER_6,
        SCARY_POTTER_7,
        SCARY_POTTER_8,
        SCARY_POTTER_9,
        SCARY_POTTER_ENDLESS,
        PUZZLE_I_ZOMBIE_1,
        PUZZLE_I_ZOMBIE_2,
        PUZZLE_I_ZOMBIE_3,
        PUZZLE_I_ZOMBIE_4,
        PUZZLE_I_ZOMBIE_5,
        PUZZLE_I_ZOMBIE_6,
        PUZZLE_I_ZOMBIE_7,
        PUZZLE_I_ZOMBIE_8,
        PUZZLE_I_ZOMBIE_9,
        PUZZLE_I_ZOMBIE_ENDLESS,
        UPSELL,
        INTRO,
        NUM_GAME_MODES
    };

    // 进入游戏
    void EnterGame(int gameMode);

    // 直接返回主界面
    void DoBackToMain();

    enum GameScenes {
        LOADING,
        MENU,
        LEVEL_INTRO,
        PLAYING,
        ZOMBIES_WON,
        AWARD,
        CREDIT,
        CHALLENGE
    };

    // 内置生成僵尸列表的函数
    void PickZombieWaves();

    // 选卡界面点击调试试玩按钮时，以随机选卡填充卡槽，立即完成所有选卡的移动，然后结束选卡。
    void PickRandomSeeds();

    constexpr int JACK_MUSIC_IDX = 0x0e;   // 小丑音效
    constexpr int MJ_MUSIC_IDX = 0x64;     // 舞王音效
    constexpr int DIGGER_MUSIC_IDX = 0x21; // 矿工音效

    // 增加音效的引用计数
    void PlayFoleyPitch(int idx);

    // 减少音效的引用计数
    void StopFoley(int idx);

    // 播放僵尸的出场音效
    void PlayZombieAppearSound(AZombie* zombie);

    // 播放音乐
    void PlaySample(int idx);

    // 更新鼠标和预览
    void UpdateCursorObjectAndPreview();

    // 刷新卡片冷却
    void RefreshAllSeedPackets();

    __ADeprecated() void* SaveToMemory();
    __ADeprecated() void LoadFromMemory(void*& p);
    __ADeprecated() void FreeMemory(void*& p);
};



#endif

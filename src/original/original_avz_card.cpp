#include "avz_multi_platform.h"
#include HEADER_ORIGINAL(libavz.h)


std::vector<std::string> __ACardManager::_cardName = {
    "豌豆射手",
    "向日葵",
    "樱桃炸弹",
    "坚果",
    "土豆地雷",
    "寒冰射手",
    "大嘴花",
    "双重射手",
    "小喷菇",
    "阳光菇",
    "大喷菇",
    "墓碑吞噬者",
    "魅惑菇",
    "胆小菇",
    "寒冰菇",
    "毁灭菇",
    "荷叶",
    "倭瓜",
    "三发射手",
    "缠绕海藻",
    "火爆辣椒",
    "地刺",
    "火炬树桩",
    "高坚果",
    "水兵菇",
    "路灯花",
    "仙人掌",
    "三叶草",
    "裂荚射手",
    "杨桃",
    "南瓜头",
    "磁力菇",
    "卷心菜投手",
    "花盆",
    "玉米投手",
    "咖啡豆",
    "大蒜",
    "叶子保护伞",
    "金盏花",
    "西瓜投手",
    "机枪射手",
    "双子向日葵",
    "忧郁菇",
    "香蒲",
    "冰西瓜投手",
    "吸金磁",
    "地刺王",
    "玉米加农炮",
    "模仿者",
    "模仿豌豆射手",
    "模仿向日葵",
    "模仿樱桃炸弹",
    "模仿坚果",
    "模仿土豆地雷",
    "模仿寒冰射手",
    "模仿大嘴花",
    "模仿双重射手",
    "模仿小喷菇",
    "模仿阳光菇",
    "模仿大喷菇",
    "模仿墓碑吞噬者",
    "模仿魅惑菇",
    "模仿胆小菇",
    "模仿寒冰菇",
    "模仿毁灭菇",
    "模仿荷叶",
    "模仿倭瓜",
    "模仿三发射手",
    "模仿缠绕海藻",
    "模仿火爆辣椒",
    "模仿地刺",
    "模仿火炬树桩",
    "模仿高坚果",
    "模仿水兵菇",
    "模仿路灯花",
    "模仿仙人掌",
    "模仿三叶草",
    "模仿裂荚射手",
    "模仿杨桃",
    "模仿南瓜头",
    "模仿磁力菇",
    "模仿卷心菜投手",
    "模仿花盆",
    "模仿玉米投手",
    "模仿咖啡豆",
    "模仿大蒜",
    "模仿叶子保护伞",
    "模仿金盏花",
    "模仿西瓜投手",
    "未知",
};

void __ACardManager::_BeforeScript() {
    _isSelectCards = false;
    _tickRunner.Start([this] {
        _selectInterval = std::max(1, _selectInterval);
        if (AGetMainObject()->GlobalClock() % _selectInterval != 0)
            return; // 选卡间隔为 _selectInterval
        __aCardManager._ChooseSingleCard();
    },
        ATickRunner::GLOBAL);
}

void __ACardManager::_EnterFight() {
    _tickRunner.Stop();
    _cardNameToIndexMap.clear();
    _selectCardVec.clear();

    if (AGetPvzBase()->GameUi() != 3)
        return;

    for (auto& seed : ABasicFilter<ASeed>()) {
        int seedType = seed.Type(), index = &seed - AGetMainObject()->SeedArray();
        if (seedType == AIMITATOR) {
            seedType = seed.ImitatorType();
            _cardNameToIndexMap.emplace(seedType + AM_PEASHOOTER, index);
        } else
            _cardNameToIndexMap.emplace(seedType, index);
    }
}

const std::string& __ACardManager::GetCardName(APlantType type) {
    if (std::size_t(type) > _cardName.size() - 1) {
        aLogger->Error("GetCardName : 您选择的代号为 {} 的卡片在 PvZ 中不存在", int(type));
        return _cardName.back();
    }
    return _cardName[std::size_t(type)];
}

const std::string& __ACardManager::GetCardName(ASeed* seed) {
    if (seed == nullptr) {
        aLogger->Error("GetCardName : 您传入的参数为 nullptr");
        return _cardName.back();
    }
    int type = seed->Type();
    if (type == AIMITATOR)
        type = AM_PEASHOOTER + seed->ImitatorType();
    return GetCardName(APlantType(type));
}

void __ACardManager::_ChooseSingleCard() {
    static auto iter = _selectCardVec.begin();
    if (AGetMainObject()->Words()->DisappearCountdown() || //
        AGetMainObject()->SelectCardUi_m()->OrizontalScreenOffset() != 4250) {
        iter = _selectCardVec.begin();
        return;
    }

    if (!_isSelectCards)
        return;

    if (iter != _selectCardVec.end()) {
        if (*iter >= AM_PEASHOOTER)
            AAsm::ChooseImitatorCard(*iter - AM_PEASHOOTER);
        else
            AAsm::ChooseCard(*iter);
        ++iter;
        return;
    }

    int okCnt = 0;
    for (auto&& type : _selectCardVec) {
        int idx = std::min(48, type);
        int state = AGetPvzBase()->SelectCardUi_p()->CardMoveState(idx);
        if (state == 1 || state == 0)
            ++okCnt;
    }

    if (okCnt != _selectCardVec.size()) {
        static int cnt = 0;
        ++cnt;
        AAsm::Click(AGetPvzBase()->MouseWindow(), 100, 50, 1);
        if (cnt == 10) {
            cnt = 0;
            iter = _selectCardVec.begin();
        }
        return;
    }
    AAsm::PickRandomSeeds();
}

void __ACardManager::SelectCards(const std::vector<int>& lst, int selectInterval) {
    if (selectInterval < 0) {
        aLogger->Error("ASelectCards 不允许选卡间隔小于 0cs");
        return;
    }
    if (lst.size() > AGetMainObject()->SeedArray()->Count()) {
        aLogger->Error("ASelectCards 不允许选卡的数量大于卡片的数量");
        return;
    }
    _selectInterval = std::max(1, selectInterval);

    _selectCardVec.clear();
    std::unordered_set<int> repetitiveTypeSet;
    bool isImitatorSelected = false;
    for (const auto& cardType : lst) {
        if (cardType > AM_MELON_PULT) {
            aLogger->Error("您选择的代号为 {} 的卡片在 PvZ 中不存在", cardType);
            return;
        }

        if (repetitiveTypeSet.find(cardType) == repetitiveTypeSet.end()) { // 没有被选择的卡片
            repetitiveTypeSet.insert(cardType);
        } else {
            aLogger->Error("您重复选择了 {} 卡片", GetCardName(APlantType(cardType)));
            return;
        }

        if (!isImitatorSelected) {
            isImitatorSelected = (cardType > AIMITATOR);
        } else if (cardType > AIMITATOR) {
            aLogger->Error("您重复选择了模仿者卡片");
            return;
        }
    }

    _selectCardVec = lst;
    _isSelectCards = true;
    AWaitForFight(selectInterval == 0);
}

APlant* __ACardManager::_CardWithoutCheck(int seedIndex, int row, float col) {
    auto mainObject = AGetMainObject();
    auto seed = mainObject->SeedArray() + seedIndex - 1;
    col = int(col + 0.5);
    std::string msg = std::format("放置 {} 卡片到 {}", GetCardName(seed), APosition(row, col));
    int type = seed->Type() == AIMITATOR ? seed->ImitatorType() : seed->Type();
    if (AAsm::GetPlantRejectType(type, row - 1, col - 1) != AAsm::NIL) {
        aLogger->Info(msg + " 失败");
        return nullptr;
    }
    auto [x, y] = AGridToCoordinate(row, col);
    auto currentIdx = mainObject->PlantNext();
    AAsm::PlantCard(x, y, seedIndex - 1);
    AAsm::ReleaseMouse();
    if (currentIdx != mainObject->PlantNext()) {
        aLogger->Info(msg + " 成功");
        return mainObject->PlantArray() + currentIdx;
    }

    // 这里几乎不可能执行
    // 因为前面已经做了检查
    aLogger->Info(msg + " 失败");
    return nullptr;
}

bool __ACardManager::_CheckCard(int seedIndex) {
    auto seedCount = AGetMainObject()->SeedArray()->Count();
    if (seedIndex > seedCount || seedIndex < 1) {
        aLogger->Error("Card : 您填写的参数 {} 已溢出", seedIndex);
        return false;
    }
    AAsm::ReleaseMouse();
    auto seed = AGetMainObject()->SeedArray() + seedIndex - 1;
    if (!AIsSeedUsable(seed)) {
        int cd = seed->InitialCd() - seed->Cd() + 1;
        if (cd > 0)
            aLogger->Error("Card : {} 卡片还有 {} cs 才能使用", GetCardName(seed), cd);
        else
            aLogger->Error("Card : {} 卡片无法使用，这可能是因为阳光不足或者未放置相应的绿卡", GetCardName(seed));
        return false;
    }
    return true;
}

APlant* __ACardManager::_BasicCard(int seedIndex, int row, float col) {
    if (!_CheckCard(seedIndex))
        return nullptr;

    return _CardWithoutCheck(seedIndex, row, col);
}

APlant* __ACardManager::_BasicCard(int seedIndex, const std::vector<APosition>& lst) {
    if (!_CheckCard(seedIndex))
        return nullptr;

    for (auto&& [row, col] : lst) {
        auto ret = _CardWithoutCheck(seedIndex, row, col);
        if (ret != nullptr)
            return ret;
    }
    return nullptr;
}

int __ACardManager::GetCardIndex(APlantType plantType) {
    auto it = _cardNameToIndexMap.find(plantType);
    return it == _cardNameToIndexMap.end() ? -1 : it->second;
}

__ANodiscard ASeed* AGetCardPtr(APlantType plantType) {
    auto index = __aCardManager.GetCardIndex(plantType);
    return index < 0 ? nullptr : AGetMainObject()->SeedArray() + index;
}

APlant* __ACardManager::Card(int seedIndex, int row, float col) {
    return _BasicCard(seedIndex, row, col);
}

APlant* __ACardManager::Card(APlantType plantType, int row, float col) {
    int seedIndex = GetCardIndex(plantType);
    if (seedIndex == -1) {
        aLogger->Error("您没有选择 {} 卡片", GetCardName(plantType));
        return nullptr;
    }
    return _BasicCard(seedIndex + 1, row, col);
}

std::vector<APlant*> __ACardManager::Card(const std::vector<ACardName>& lst) {
    std::vector<APlant*> vec;
    for (const auto& each : lst)
        vec.push_back(Card(each.plantType, each.row, each.col));
    return vec;
}

APlant* __ACardManager::Card(int seedIndex, const std::vector<APosition>& lst) {
    return _BasicCard(seedIndex, lst);
}

APlant* __ACardManager::Card(APlantType plantType, const std::vector<APosition>& lst) {
    int seedIndex = GetCardIndex(plantType);
    if (seedIndex == -1) {
        aLogger->Error("您没有选择 {} 卡片", GetCardName(plantType));
        return nullptr;
    }
    return _BasicCard(seedIndex + 1, lst);
}

std::vector<APosition> __AVecGridToVecPosition(const std::vector<AGrid>& lst) {
    std::vector<APosition> ret;
    ret.reserve(lst.size());
    for (auto&& grid : lst)
        ret.emplace_back(grid.row, grid.col);
    return ret;
}

std::vector<APlant*> ACard(const std::vector<ACardName>& lst) {
    return __aCardManager.Card(lst);
}

APlant* ACard(int seedIndex, int row, float col) {
    return __aCardManager.Card(seedIndex, row, col);
}

APlant* ACard(int seedIndex, const std::vector<APosition>& lst) {
    return __aCardManager.Card(seedIndex, lst);
}

APlant* ACard(int seedIndex, const std::vector<AGrid>& lst) {
    return __aCardManager.Card(seedIndex, __AVecGridToVecPosition(lst));
}

APlant* ACard(int seedIndex, std::initializer_list<AGrid> lst) {
    return __aCardManager.Card(seedIndex, __AVecGridToVecPosition(lst));
}

APlant* ACard(APlantType plantType, int row, float col) {
    return __aCardManager.Card(plantType, row, col);
}

APlant* ACard(APlantType plantType, const std::vector<APosition>& lst) {
    return __aCardManager.Card(plantType, lst);
}

APlant* ACard(APlantType plantType, const std::vector<AGrid>& lst) {
    return __aCardManager.Card(plantType, __AVecGridToVecPosition(lst));
}

APlant* ACard(APlantType plantType, std::initializer_list<AGrid> lst) {
    return __aCardManager.Card(plantType, __AVecGridToVecPosition(lst));
}

std::vector<APlant*> ACard(const std::vector<APlantType>& plantTypeVec, int row, float col) {
    std::vector<APlant*> ret;
    for (auto&& plantType : plantTypeVec)
        ret.push_back(__aCardManager.Card(plantType, row, col));
    return ret;
}

std::vector<APlant*> ACard(const std::vector<APlantType>& plantTypeVec, const std::vector<APosition>& lst) {
    std::vector<APlant*> ret;
    for (auto&& plantType : plantTypeVec) {
        for (auto&& pos : lst) {
            auto ptr = __aCardManager.Card(plantType, pos.row, pos.col);
            if (ptr != nullptr) {
                ret.push_back(ptr);
                break;
            }
        }
    }
    return ret;
}

std::vector<APlant*> ACard(const std::vector<APlantType>& plantTypeVec, const std::vector<AGrid>& lst) {
    return ACard(plantTypeVec, __AVecGridToVecPosition(lst));
}

std::vector<APlant*> ACard(const std::vector<APlantType>& plantTypeVec, std::initializer_list<AGrid> lst) {
    return ACard(plantTypeVec, __AVecGridToVecPosition(lst));
}

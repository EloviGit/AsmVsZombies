#include "avz_multi_platform.h"
#include HEADER_ORIGINAL(libavz.h)

NS_ORIGINAL_BEGIN(libavz)

AIceFiller aIceFiller;
APlantFixer aPlantFixer;
ACobManager aCobManager;
AAliveFilter<AZombie> aAliveZombieFilter;
AAliveFilter<APlant> aAlivePlantFilter;
AAliveFilter<ASeed> aAliveSeedFilter;
AAliveFilter<AItem> aAliveItemFilter;
AAliveFilter<APlaceItem> aAlivePlaceItemFilter;
APainter aPainter;

NS_END
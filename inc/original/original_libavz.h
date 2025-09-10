#ifndef __ORIGINAL_LIBAVZ_H__
#define __ORIGINAL_LIBAVZ_H__

#include "avz_multi_platform.h"
#include FILE_SHARED(libavz.h)

#include FILE_ORIGINAL(avz_connector.h)
#include FILE_ORIGINAL(avz_game_controllor.h)
#include FILE_ORIGINAL(avz_memory.h)
#include FILE_ORIGINAL(avz_pvz_struct.h)
#include FILE_ORIGINAL(avz_replay.h)
#include FILE_ORIGINAL(avz_script.h)

inline AItemCollector aItemCollector;
inline AIceFiller aIceFiller;
inline APlantFixer aPlantFixer;
inline ACobManager aCobManager;
inline AAliveFilter<AZombie> aAliveZombieFilter;
inline AAliveFilter<APlant> aAlivePlantFilter;
inline AAliveFilter<ASeed> aAliveSeedFilter;
inline AAliveFilter<AItem> aAliveItemFilter;
inline AAliveFilter<APlaceItem> aAlivePlaceItemFilter;
inline APainter aPainter;

#endif

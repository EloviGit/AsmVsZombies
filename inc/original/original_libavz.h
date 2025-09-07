#ifndef __ORIGINAL_LIBAVZ_H__
#define __ORIGINAL_LIBAVZ_H__

// #define __AVZ_VERSION__ 250823

#include "avz_multi_platform.h"

#include HEADER_SHARED(libavz.h)

#include HEADER_ORIGINAL(avz_asm.h)
#include HEADER_ORIGINAL(avz_card.h)
#include HEADER_ORIGINAL(avz_click.h)
#include HEADER_ORIGINAL(avz_cob_manager.h)
#include HEADER_ORIGINAL(avz_connector.h)
#include HEADER_ORIGINAL(avz_game_controllor.h)
#include HEADER_ORIGINAL(avz_iterator.h)
#include HEADER_ORIGINAL(avz_memory.h)
#include HEADER_ORIGINAL(avz_replay.h)
#include HEADER_ORIGINAL(avz_script.h)
#include HEADER_ORIGINAL(avz_smart.h)
#include HEADER_ORIGINAL(avz_time_queue.h)
#include HEADER_ORIGINAL(avz_timeline.h)

NS_ORIGINAL_BEGIN(libavz)

USING_NS_ORIGINAL(avz_asm)
USING_NS_ORIGINAL(avz_card)
USING_NS_ORIGINAL(avz_click)
USING_NS_ORIGINAL(avz_cob_manager)
USING_NS_ORIGINAL(avz_connector)
USING_NS_ORIGINAL(avz_game_controllor)
USING_NS_ORIGINAL(avz_iterator)
USING_NS_ORIGINAL(avz_memory)
USING_NS_ORIGINAL(avz_replay)
USING_NS_ORIGINAL(avz_script)
USING_NS_ORIGINAL(avz_smart)
USING_NS_ORIGINAL(avz_time_queue)
USING_NS_ORIGINAL(avz_timeline)

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

NS_END

#endif

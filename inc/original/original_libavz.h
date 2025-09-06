#ifndef __ORIGINAL_LIBAVZ_H__
#define __ORIGINAL_LIBAVZ_H__

// #define __AVZ_VERSION__ 250823

#include "avz_multi_platform.h"

#include HEADER_ORIGINAL(avz_asm.h)
#include HEADER_ORIGINAL(avz_card.h)
#include HEADER_ORIGINAL(avz_click.h)
#include HEADER_ORIGINAL(avz_cob_manager.h)
#include HEADER_ORIGINAL(avz_connector.h)
#include HEADER_ORIGINAL(avz_exception.h)
#include HEADER_ORIGINAL(avz_game_controllor.h)
#include HEADER_ORIGINAL(avz_iterator.h)
#include HEADER_ORIGINAL(avz_memory.h)
#include HEADER_ORIGINAL(avz_replay.h)
#include HEADER_ORIGINAL(avz_script.h)
#include HEADER_ORIGINAL(avz_seh.h)
#include HEADER_ORIGINAL(avz_smart.h)
#include HEADER_ORIGINAL(avz_time_queue.h)
#include HEADER_ORIGINAL(avz_timeline.h)

NS_ORIGINAL_BEGIN(libavz)

USING_NS_ORIGINAL(avz_asm)
USING_NS_ORIGINAL(avz_card)
USING_NS_ORIGINAL(avz_click)
USING_NS_ORIGINAL(avz_cob_manager)
USING_NS_ORIGINAL(avz_connector)
USING_NS_ORIGINAL(avz_exception)
USING_NS_ORIGINAL(avz_game_controllor)
USING_NS_ORIGINAL(avz_iterator)
USING_NS_ORIGINAL(avz_memory)
USING_NS_ORIGINAL(avz_replay)
USING_NS_ORIGINAL(avz_script)
USING_NS_ORIGINAL(avz_seh)
USING_NS_ORIGINAL(avz_smart)
USING_NS_ORIGINAL(avz_time_queue)
USING_NS_ORIGINAL(avz_timeline)

inline AItemCollector aItemCollector;
extern AIceFiller aIceFiller;
extern APlantFixer aPlantFixer;
extern ACobManager aCobManager;
extern AAliveFilter<AZombie> aAliveZombieFilter;
extern AAliveFilter<APlant> aAlivePlantFilter;
extern AAliveFilter<ASeed> aAliveSeedFilter;
extern AAliveFilter<AItem> aAliveItemFilter;
extern AAliveFilter<APlaceItem> aAlivePlaceItemFilter;
extern APainter aPainter;

NS_END

#endif

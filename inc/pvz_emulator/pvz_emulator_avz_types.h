#ifndef __PVZ_EMULATOR_TYPES_H__
#define __PVZ_EMULATOR_TYPES_H__

#include "avz_multi_platform.h"
#include "world.h"
#include FILE_SHARED(avz_types.h)


// We use APvzEMulatorBridge to unlock some private/protected members of classes in pvz_emulator.
// And if new access authorization is needed in the future, please add it in APvzEmulatorBridge.

namespace pe = pvz_emulator;
namespace peo = pvz_emulator::object;
namespace pes = pvz_emulator::system;

class APvzEmulatorBridge {
protected:

    template <typename T, size_t S>
    class obj_wrap : public peo::obj_list<T, S>::obj_wrap {};

    using PEZombie = obj_wrap<peo::zombie, 1024>;
    using PEPlant = obj_wrap<peo::plant, 512>;
    using PEPlaceItem = obj_wrap<peo::griditem, 128>;
    // projectile does not seem to be used in original avz.
    using PEProjectile = obj_wrap<peo::projectile, 1024>;

    





    void clean_obj_lists(pe::world& w) {
        w.clean_obj_lists();
    }

};





#endif
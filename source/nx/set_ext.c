#include "set_ext.h"

#include "../service_guard.h"

#include <switch/services/sm.h>
#include <switch/types.h>

static Service g_setcalSrv;

NX_GENERATE_SERVICE_GUARD(setcal);

Result _setcalInitialize() {
    return smGetService(&g_setcalSrv, "set:cal");
}

void _setcalCleanup() {
    serviceClose(&g_setcalSrv);
}

Result setcalGetEticketDeviceKey(void *key)
{
    return serviceDispatch(&g_setcalSrv, 21,
        .buffer_attrs = { SfBufferAttr_HipcMapAlias | SfBufferAttr_Out },
        .buffers = { { key, 0x244 } },
    );
}
#include "es.h"

#include "../service_guard.h"

#include <switch/kernel/ipc.h>
#include <switch/services/sm.h>

static Service g_esSrv;

NX_GENERATE_SERVICE_GUARD(es);

Result _esInitialize() {
    return smGetService(&g_esSrv, "es");
}

void _esCleanup() {
    serviceClose(&g_esSrv);
}

Result esCountCommonTicket(u32 *out_count)
{
    u32 num_tickets;

    Result rc = serviceDispatchOut(&g_esSrv, 9, num_tickets);
    if (R_SUCCEEDED(rc) && out_count) *out_count = num_tickets;

    return rc;
}

Result esCountPersonalizedTicket(u32 *out_count)
{
    u32 num_tickets;

    Result rc = serviceDispatchOut(&g_esSrv, 10, num_tickets);
    if (R_SUCCEEDED(rc) && out_count) *out_count = num_tickets;

    return rc;
}

Result esListCommonTicket(u32 *numRightsIdsWritten, RightsId *outBuf, size_t bufSize)
{
    u32 num_rights_ids_written;

    Result rc = serviceDispatchOut(&g_esSrv, 11, num_rights_ids_written,
        .buffer_attrs = { SfBufferAttr_HipcMapAlias | SfBufferAttr_Out },
        .buffers = { { outBuf, bufSize } },
    );
    if (R_SUCCEEDED(rc) && numRightsIdsWritten) *numRightsIdsWritten = num_rights_ids_written;

    return rc;
}

Result esListPersonalizedTicket(u32 *numRightsIdsWritten, RightsId *outBuf, size_t bufSize)
{
    u32 num_rights_ids_written;

    Result rc = serviceDispatchOut(&g_esSrv, 12, num_rights_ids_written,
        .buffer_attrs = { SfBufferAttr_HipcMapAlias | SfBufferAttr_Out },
        .buffers = { { outBuf, bufSize } },
    );
    if (R_SUCCEEDED(rc) && numRightsIdsWritten) *numRightsIdsWritten = num_rights_ids_written;

    return rc;
}

#pragma once

#include <switch/types.h>
#include <switch/services/ncm.h>

typedef struct {
    u8 c[0x10];
} RightsId;

Result esInitialize();
void esExit();

Result esCountCommonTicket(u32 *num_tickets); //9
Result esCountPersonalizedTicket(u32 *num_tickets); // 10
Result esListCommonTicket(u32 *numRightsIdsWritten, RightsId *outBuf, size_t bufSize);
Result esListPersonalizedTicket(u32 *numRightsIdsWritten, RightsId *outBuf, size_t bufSize);

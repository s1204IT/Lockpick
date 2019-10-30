#pragma once

#include <switch/types.h>
#include <switch/services/ncm.h>

Result esInitialize();
void esExit();

Result esCountCommonTicket(u32 *num_tickets); //9
Result esCountPersonalizedTicket(u32 *num_tickets); // 10
Result esListCommonTicket(u32 *numRightsIdsWritten, NcmRightsId *outBuf, size_t bufSize);
Result esListPersonalizedTicket(u32 *numRightsIdsWritten, NcmRightsId *outBuf, size_t bufSize);
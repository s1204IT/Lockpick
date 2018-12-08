/*
 * Copyright (c) 2018 shchmue
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "KeyLocation.hpp"

#include <filesystem>
#include <fstream>

#include "creport_debug_types.hpp"

void KeyLocation::get_from_memory(u64 tid, u8 segMask) {
    Handle debug_handle = INVALID_HANDLE;
    DebugEventInfo d;

    // if not a kernel process, get pid from pm:dmnt
    if ((tid > 0x0100000000000005) && (tid != 0x0100000000000028)) {
        u64 pid;
        pmdmntGetTitlePid(&pid, tid);

        if (R_FAILED(svcDebugActiveProcess(&debug_handle, pid)) ||
            R_FAILED(svcGetDebugEvent(reinterpret_cast<u8 *>(&d), debug_handle)))
        {
            return;
        }
    } else { // otherwise query svc for the process list
        u64 pids[300];
        u32 num_processes;

        svcGetProcessList(&num_processes, pids, 300);
        u32 i;
        for (i = 0; i < num_processes - 1; i++) {
            if (R_SUCCEEDED(svcDebugActiveProcess(&debug_handle, pids[i])) &&
                R_SUCCEEDED(svcGetDebugEvent(reinterpret_cast<u8 *>(&d), debug_handle)) &&
                (d.info.attach_process.title_id == tid))
            {
                break;
            }
            if (debug_handle) svcCloseHandle(debug_handle);
        }
        if (i == num_processes - 1) {
            if (debug_handle) svcCloseHandle(debug_handle);
            return;
        }
    }

    MemoryInfo mem_info = {};

    u32 page_info;
    u64 addr = 0;

    for (u8 segment = 1; segment < BIT(3); )
    {
        svcQueryDebugProcessMemory(&mem_info, &page_info, debug_handle, addr);
        // weird code to allow for bitmasking segments
        if ((mem_info.perm & Perm_R) &&
            ((mem_info.type & 0xff) >= MemType_CodeStatic) &&
            ((mem_info.type & 0xff) < MemType_Heap) &&
            ((segment <<= 1) >> 1 & segMask) > 0)
        {
            data.resize(data.size() + mem_info.size);
            if(R_FAILED(svcReadDebugProcessMemory(data.data() + data.size() - mem_info.size, debug_handle, mem_info.addr, mem_info.size))) {
                if (debug_handle) svcCloseHandle(debug_handle);
                return;
            }
        }
        addr = mem_info.addr + mem_info.size;
        if (addr == 0) break;
    }
    
    svcCloseHandle(debug_handle);
}

void KeyLocation::get_keyblobs() {
    FsStorage boot0;
    fsOpenBisStorage(&boot0, 0);
    data.resize(0x200 * KNOWN_KEYBLOBS);
    fsStorageRead(&boot0, KEYBLOB_OFFSET, data.data(), data.size());
    fsStorageClose(&boot0);
}
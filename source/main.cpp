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

#include <switch.h>

#include "Common.hpp"
#include "KeyCollection.hpp"

extern "C" void userAppInit()
{
    plInitialize();
    pmdmntInitialize();
    splInitialize();
}

extern "C" void userAppExit()
{
    plExit();
    pmdmntExit();
    splExit();
}

int main(int argc, char **argv) {
    Common::intro();

    KeyCollection Keys;
    Keys.get_keys();
    Common::wait_to_exit();

    return 0;
}
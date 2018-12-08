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

#pragma once

#include "Key.hpp"
#include "KeyLocation.hpp"

class KeyCollection {
public:
    KeyCollection();

    // get KeyLocations and find keys in them
    int get_keys();

private:
    // utility functions called by get_keys
    void get_master_keys();
    void get_memory_keys();
    // derive calculated/encrypted keys
    void derive_keys();
    // save keys to key file
    void save_keys();

    // get titlekeys from es syssaves
    void get_titlekeys();
    // mask generation function used by get_titlekeys
    void mgf1(const u8 *data, size_t data_length, u8 *mask, size_t mask_length);
    // key pair tester for get_titlekeys
    bool test_key_pair(const void *E, const void *D, const void *N);

    Key // dumped by payload
        sbk,
        tsec,
        tsec_root_key,
        // from TZ
        aes_kek_generation_source,
        aes_kek_seed_01,
        aes_kek_seed_03,
        package2_key_source,
        titlekek_source,
        retail_specific_aes_key_source,
        // from Package1ldr
        keyblob_mac_key_source,
        master_key_source,
        per_console_key_source,
        // from FS
        bis_kek_source,
        bis_key_source_00,
        bis_key_source_01,
        bis_key_source_02,
        header_kek_source,
        header_key_source,
        key_area_key_application_source,
        key_area_key_ocean_source,
        key_area_key_system_source,
        save_mac_kek_source,
        save_mac_key_source,
        sd_card_kek_source,
        sd_card_nca_key_source,
        sd_card_save_key_source,
        // from SPL
        aes_key_generation_source,
        // from ES
        eticket_rsa_kek_source,
        eticket_rsa_kekek_source,
        // from SSL
        ssl_rsa_kek_source_x,
        ssl_rsa_kek_source_y,
        // derived keys
        device_key,
        eticket_rsa_kek,
        header_key,
        rsa_oaep_kek_generation_source,
        rsa_private_kek_generation_source,
        save_mac_key,
        ssl_rsa_kek;

    // key families
    std::vector<Key>
        bis_key,
        encrypted_keyblob,
        key_area_key_application,
        key_area_key_ocean,
        key_area_key_system,
        keyblob,
        keyblob_key,
        keyblob_key_source,
        keyblob_mac_key,
        master_kek,
        master_kek_source,
        master_key,
        mkey_vector,
        package1_key,
        package2_key,
        titlekek;

    std::vector<Key *>
        es_keys, fs_rodata_keys, package1ldr_keys, ssl_keys, tz_keys;

    // hash of empty string used to verify titlekeys for personalized tickets
    static const u8 null_hash[0x20];

    size_t titlekeys_dumped = 0;
};
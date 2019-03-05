# Changelog
## Version 1.2.2
* Do not overwrite existing keyfile that contains master_key_07
* Read eticket_rsa_kek from existing keyfile in case user is only running this for titlekeys
* Create /switch folder if needed

## Version 1.2.1
* Generate bis keys without master keys
* Update file size check to support Hekate v4.8 TSEC dump
* Fixed prod.keys alphabetization error
* Fixed build warning for ff.c
* Added in-app disclaimer about which keys can be dumped

## Version 1.2
* Update for libnx v2.0.0 compatibility and still runs when built with v1.6.0
  * The binary got even smaller!
* Accelerate finding FS keys
  * No longer find BIS sources as they're hardcoded (whoops)
  * Find all keys on first pass hashing FS instead of hashing the whole thing from the beginning repeatedly (__*whoops*__)

## Version 1.1.1
* No longer try to dump SD seed and ES keys on 1.0.0 as they're not available until 2.0.0

## Version 1.1
* Changed titlekey dump methodology
  * No longer crashes sysmodule, reboot no longer needed
  * Queries ES to verify ticket list is accurate
  * May take slightly longer than before on systems with hundreds of tickets
* Now dumps SD seed
* Reorganized and clarified UI text
  * Now indicates if no titles are installed to dump titlekeys from
* Swapped C++ stream functions for C I/O to reclaim some speed and binary size
* Tightened up dependencies
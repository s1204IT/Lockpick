# Changelog
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
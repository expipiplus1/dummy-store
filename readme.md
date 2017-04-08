# A Dummy Nix Store

This project demonstrates loading an implementation of the nix store API.

Run with `LD_PRELOAD=libdummy-store.so NIX_REMOTE=dummy://123 nix-build` on
Linux and `DYLD_INSERT_LIBRARIES=libdummy-store.dylib NIX_REMOTE=dummy://123
nix-buld` on OS X.

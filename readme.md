# A Dummy Nix Store

This project demonstrates an example implementation of the nix-store API. This
implementation reports when it is registered and when `buildPaths` is called.

## Building

Simply run `nix-build` in the repo root.

## Developing

- Run `nix-shell` in the repo root to drop to a shell with the required libraries present.
- Run `mkdir build` to create a directory for the build products.
- Run `cmake -Bbuild -H.` to generate the MakeFile.
- Run `cmake --build build` to build the library.

## Using

### On Linux

Assuming `libdummy-store.so` is in the current directory: run
`LD_PRELOAD=libdummy-store.so NIX_REMOTE=dummy:// nix-build`.

### On OS X

Assuming `libdummy-store.dylib` is in the current directory: run
`DYLD_INSERT_LIBRARIES=libdummy-store.dylib NIX_REMOTE=dummy:// nix-buld`.

### Forcing a local or remote store

- To force a local store run with `NIX_REMOTE=dummy://local`.
- To force a daemon accessed store run with `NIX_REMOTE=dummy://daemon`

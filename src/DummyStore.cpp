#include <algorithm>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>

#include <nix/local-store.hh>
#include <nix/remote-store.hh>
#include <nix/store-api.hh>

namespace nix {

template <class BaseStore> class DummyStore : public BaseStore {
public:
  ~DummyStore();

  DummyStore(const Store::Params &params, const std::string &something)
      : Store(params), BaseStore(params){};

  void buildPaths(const PathSet &paths, BuildMode buildMode) override;
  BuildResult buildDerivation(const Path & drvPath, const BasicDerivation & drv,
      BuildMode buildMode = bmNormal) override;
  void ensurePath(const Path &path) override;
};

template <class BaseStore> DummyStore<BaseStore>::~DummyStore() {}

template <class BaseStore>
void DummyStore<BaseStore>::buildPaths(const PathSet &paths,
                                       BuildMode buildMode) {
  std::cerr << "buildPaths called for" << std::endl;
  std::for_each(paths.begin(), paths.end(), [](const Path &path) {
    std::cerr << "  - " << path << std::endl;
  });

  BaseStore::buildPaths(paths, buildMode);
}

template <class BaseStore>
BuildResult DummyStore<BaseStore>::buildDerivation(const Path & drvPath, const BasicDerivation & drv, BuildMode buildMode) {
  std::cerr << "buildDerivation called for" << std::endl;
  std::cerr << "  - " << drvPath << std::endl;

  return BaseStore::buildDerivation(drvPath, drv, buildMode);
};

template <class BaseStore>
void DummyStore<BaseStore>::ensurePath(const Path &path) {
  std::cerr << "ensurePath called for" << std::endl;
  std::cerr << "  - " << path << std::endl;

  BaseStore::ensurePath(path);
}

////////////////////////////////////////////////////////////////////////////////
// Register the store
////////////////////////////////////////////////////////////////////////////////

static RegisterStoreImplementation
regStore([](const std::string &uri,
            const Store::Params &params) -> std::shared_ptr<Store> {
  const std::string prefix = "dummy://";
  if (std::string(uri, 0, prefix.length()) != prefix) {
    return nullptr;
  }

  const std::string resource(uri, prefix.length());

  switch (getStoreType(resource, get(params, "state", settings.nixStateDir))) {
  case tDaemon:
    std::cerr
        << "Registering dummy store with UDSRemoteStore (daemon) underneath"
        << std::endl;
    return std::shared_ptr<Store>(
        std::make_shared<DummyStore<UDSRemoteStore>>(params, ""));
  case tLocal:
    std::cerr << "Registering dummy store with LocalStore underneath"
              << std::endl;
    return std::shared_ptr<Store>(
        std::make_shared<DummyStore<LocalStore>>(params, ""));
  default:
    return nullptr;
  }
});
};

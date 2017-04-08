#include <cstdio>
#include <memory>
#include <sstream>
#include <string>

#include <nix/store-api.hh>

namespace nix {

static RegisterStoreImplementation regStore([](
    const std::string & uri, const Store::Params & params)
    -> std::shared_ptr<Store>
{
  printf("Dummy Store registering\n");
  return nullptr;
});

};

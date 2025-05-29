#include <BTBKit/JSONManifestBuilder.h>

#ifndef _WIN32
static auto kPath = "./posix.json";
#else
static auto kPath = ".\win64.json";
#endif

int main(int argc, char** argv) {
  auto builder = new BTB::JSONManifestBuilder();
  return builder->buildTarget(strlen(kPath), kPath);
}

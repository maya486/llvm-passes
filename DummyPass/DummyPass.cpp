// DummyPass.cpp
#include "llvm/IR/PassManager.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"
#include "llvm/IR/Function.h"
#include "llvm/Support/raw_ostream.h"

using namespace llvm;

struct DummyPass : PassInfoMixin<DummyPass> {
  PreservedAnalyses run(Function &F, FunctionAnalysisManager &AM) {
    errs() << "Running DummyPass on function: " << F.getName() << "\n";
    return PreservedAnalyses::all();
  }
};

// Register the pass with opt
llvm::PassPluginLibraryInfo getDummyPassPluginInfo() {
  return {LLVM_PLUGIN_API_VERSION, "DummyPass", LLVM_VERSION_STRING,
          [](PassBuilder &PB) {
            PB.registerPipelineParsingCallback(
              [](StringRef Name, FunctionPassManager &FPM,
                 ArrayRef<PassBuilder::PipelineElement>) {
                if (Name == "dummy-pass") {
                  FPM.addPass(DummyPass());
                  return true;
                }
                return false;
              });
          }};
}

extern "C" LLVM_ATTRIBUTE_WEAK ::llvm::PassPluginLibraryInfo
llvmGetPassPluginInfo() {
  return getDummyPassPluginInfo();
}


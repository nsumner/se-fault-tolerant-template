

#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/Transforms/Utils/ModuleUtils.h"
#include "Tolerator.h"


using namespace llvm;
using tolerator::Tolerator;


namespace tolerator {

char Tolerator::ID = 0;

}


bool
Tolerator::runOnModule(Module& m) {
  auto& context = m.getContext();

  // This analysis just prints a message when the program starts or exits.
  // You should modify this code as you see fit.
  auto* voidTy = Type::getVoidTy(context);

  auto helloworld = m.getOrInsertFunction("ToLeRaToR_helloworld", voidTy);
  appendToGlobalCtors(m, llvm::cast<Function>(helloworld.getCallee()), 0);

  auto goodbyeworld = m.getOrInsertFunction("ToLeRaToR_goodbyeworld", voidTy);
  appendToGlobalDtors(m, llvm::cast<Function>(goodbyeworld.getCallee()), 0);

  return true;
}


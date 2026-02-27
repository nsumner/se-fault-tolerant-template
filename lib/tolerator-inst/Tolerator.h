// 4e91f891e8c74607adf501dbeaa18a1d

#pragma once


#include "llvm/ADT/DenseMap.h"
#include "llvm/ADT/DenseSet.h"
#include "llvm/IR/InstrTypes.h"
#include "llvm/IR/Module.h"
#include "llvm/Pass.h"
#include "llvm/Support/raw_ostream.h"


namespace tolerator {


enum class AnalysisType {
  LOGGING,
  IGNORING,
  DEFAULTING,
  BYPASSING
};


struct Tolerator : public llvm::PassInfoMixin<Tolerator> {

  Tolerator(AnalysisType analysisType)
    : analysisType{analysisType}
      { }

  llvm::PreservedAnalyses run(llvm::Module &m, llvm::ModuleAnalysisManager &mam);

  AnalysisType analysisType;
};


}  // namespace tolerator



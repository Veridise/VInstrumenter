#ifndef VINSTRUMENTER_VASTVISITOR_H
#define VINSTRUMENTER_VASTVISITOR_H

#include <string>
#include "antlr4-runtime.h"
#include "../libs/VParserBaseVisitor.h"
#include "../libs/VParser.h"
#include "../ast/VAST.h"

using namespace std;
using namespace vast;

namespace vastvisitor {
  class VASTVisitor {
  public:
    VAST* visitSpec(VParser::SpecContext *ctx);
  private:
  };
}

#endif

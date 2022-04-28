#include <string>
#include "antlr4-runtime.h"
#include "../libs/VParserBaseVisitor.h"
#include "../libs/VParser.h"
#include "../ast/VAST.h"

namespace vastvisitor {
  class VASTVisitor : VParserBaseVisitor {
  public:
    antlrcpp::Any visitSpec(VParser::SpecContext *ctx);
  private:
  };
}

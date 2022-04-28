#include <string>
#include "antlr4-runtime.h"
#include "../libs/VParserBaseVisitor.h"
#include "../libs/VParser.h"
#include "../ast/VAST.h"

using namespace std;

namespace vastvisitor {
  class VASTVisitor {
  public:
    string visitSpec(VParser::SpecContext *ctx);
  private:
  };
}

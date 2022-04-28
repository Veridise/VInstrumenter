#include "VASTVisitor.h"

namespace vastvisitor {
  antlrcpp::Any VASTVisitor::visitSpec(VParser::SpecContext *ctx) {
    return "Hello World!\n";
  }
}

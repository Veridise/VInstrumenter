#include "VASTVisitor.h"

using namespace std;

namespace vastvisitor {
  string VASTVisitor::visitSpec(VParser::SpecContext *ctx) {
    return "Hello World!\n";
  }
}

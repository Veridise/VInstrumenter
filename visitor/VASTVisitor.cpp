#include "VASTVisitor.h"

using namespace std;
using namespace vast;

namespace vastvisitor {
  VAST* VASTVisitor::visitSpec(VParser::SpecContext *ctx) {
    if (ctx->behavioralSpec()) {
      cout << "PREPOST\n";
    } else if (ctx->testSpec()) {
      cout << "TEST\n";
    } else if (ctx->tempSpec()) {
      cout << "LTL\n";
    }

    return nullptr;
  }
}

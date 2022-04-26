#include <iostream>

#include "antlr4-runtime.h"
#include "TLexer.h"
#include "TParser.h"

namespace Test {
  class Tester {
  public:
    virtual ~Tester() = default;
    virtual bool runTests() = 0;
  };
}

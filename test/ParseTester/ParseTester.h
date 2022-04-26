#include <iostream>

#include "antlr4-runtime.h"
#include "TLexer.h"
#include "TParser.h"
#include "../Tester.h"

using namespace Test;

namespace ParseTest {
  class ParseTester : public Tester {
  public:
    ParseTester();
    bool runTests() override;
    bool testParse(const char *);
  };
}

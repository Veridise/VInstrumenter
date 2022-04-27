#include <iostream>
#include <fstream>
#include <string>

#include "antlr4-runtime.h"
#include "VLexer.h"
#include "VParser.h"
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

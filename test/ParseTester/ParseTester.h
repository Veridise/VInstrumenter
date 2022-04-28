#include <iostream>
#include <fstream>
#include <string>

#include "antlr4-runtime.h"
#include "../../libs/VLexer.h"
#include "../../libs/VParser.h"
#include "../Tester.h"
#include "../visitor/VASTVisitor.h"

using namespace Test;

namespace ParseTest {
  class ParseTester : public Tester {
  public:
    ParseTester();
    bool runTests() override;
    bool testParse(const char *);
  };
}

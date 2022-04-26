#include "ParseTester.h"

using namespace antlr4;
using namespace antlrcpptest;

namespace ParseTest {
  ParseTester::ParseTester() : Tester() {

  }

  bool ParseTester::runTests() {
    return testParse("Pre: started(ERC20.totalSupply(), this.totalSupply > 0)\nPost: finished(ERC20.totalSupply(), return == this.totalSupply)");
  }

  bool ParseTester::testParse(const char *spec) {
    ANTLRInputStream input(spec);
    TLexer lexer(&input);
    CommonTokenStream tokens(&lexer);

    tokens.fill();
    for (auto token : tokens.getTokens()) {
      std::cout << token->toString() << std::endl;
    }

    TParser parser(&tokens);
    tree::ParseTree* tree = parser.spec();

    std::cout << tree->toStringTree(&parser) << std::endl << std::endl;

    return true;
  }
}

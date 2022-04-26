#include "ParseTester.h"

using namespace antlr4;
using namespace antlrcpptest;

namespace ParseTest {
  ParseTester::ParseTester() : Tester() {

  }

  bool ParseTester::runTests() {
    std::ifstream specfile ("/workspaces/VInstrumenter/example_specs/prepost1.spec");
    std::string spec((std::istreambuf_iterator<char>(specfile)),
                     (std::istreambuf_iterator<char>()));
    return testParse(spec.c_str());
    // return testParse("Pre: started(ERC20.totalSupply(), this.totalSupply > 0)\nPost: finished(ERC20.totalSupply(), return == this.totalSupply)");
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

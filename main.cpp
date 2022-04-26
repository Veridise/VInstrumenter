// #include <iostream>

// #include "antlr4-runtime.h"
// #include "TLexer.h"
// #include "TParser.h"
#include "test/ParseTester/ParseTester.h"

using namespace antlrcpptest;
using namespace ParseTest;

int main(int , const char **) {
  ParseTester *pt = new ParseTester();
  pt->runTests();
  // ANTLRInputStream input("Pre: started(ERC20.totalSupply(), this.totalSupply > 0)\nPost: finished(ERC20.totalSupply(), return == this.totalSupply)");
  // TLexer lexer(&input);
  // CommonTokenStream tokens(&lexer);

  // tokens.fill();
  // for (auto token : tokens.getTokens()) {
  //   std::cout << token->toString() << std::endl;
  // }

  // TParser parser(&tokens);
  // tree::ParseTree* tree = parser.spec();

  // std::cout << tree->toStringTree(&parser) << std::endl << std::endl;

  return 0;
}

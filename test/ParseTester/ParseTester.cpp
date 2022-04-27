#include "ParseTester.h"
#define BOOST_NO_CXX11_SCOPED_ENUMS
#include "boost/filesystem.hpp"
#undef BOOST_NO_CXX11_SCOPED_ENUMS

using namespace boost::filesystem;
using namespace antlr4;
using namespace antlrcpptest;

namespace ParseTest {
  ParseTester::ParseTester() : Tester() {

  }

  bool ParseTester::runTests() {
    directory_iterator end_itr;
    for (directory_iterator itr ("/workspaces/VInstrumenter/example_specs"); itr != end_itr; ++itr) {
      if (!is_directory(itr->status())) {
        std::cout << "Testing " << itr->path() << "\n--------\n";
        std::ifstream specfile (itr->path());
        std::string spec((std::istreambuf_iterator<char>(specfile)),
                         (std::istreambuf_iterator<char>()));
        if (!testParse(spec.c_str())) {
          return false; // Unreachable at the moment
        }
        std::cout << "----------------\n";
      }
    }
    return true;
  }

  bool ParseTester::testParse(const char *spec) {
    ANTLRInputStream input(spec);
    TLexer lexer(&input);
    CommonTokenStream tokens(&lexer);

    // tokens.fill();
    // for (auto token : tokens.getTokens()) {
    //   std::cout << token->toString() << std::endl;
    // }

    TParser parser(&tokens);
    tree::ParseTree* tree = parser.spec();

    // std::cout << tree->toStringTree(&parser) << std::endl << std::endl;

    return true;
  }
}

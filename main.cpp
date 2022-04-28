#include "test/ParseTester/ParseTester.h"

using namespace ParseTest;

int main(int , const char **) {
  ParseTester *pt = new ParseTester();
  pt->runTests();

  return 0;
}

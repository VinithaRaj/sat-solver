#include <iostream>
#include <string>
#include <map>
#include "parser.h"
#include "treeNode.h"

// a helper function parsing the input into the formula string and the assignment string
void parseLine(const std::string &line, std::string &formulaStr, std::string &assignmentStr) {
  int scPos = line.find(";");
  if (scPos == -1) throw "Error: invalid input";
  else {
    formulaStr =  line.substr(0, scPos);
    assignmentStr = line.substr(scPos+1, std::string::npos);
  }
}

// The program shall continuously ask for new inputs from standard input and output to the standard output
// The program should terminate gracefully (and quietly) once it sees EOF
int main() {
  while (true) // continuously asking for new inputs from standard input
  {
    std::string line; // store each input line
    std::string formulaStr; // store the formula string
    std::string assignmentStr; // store the assignment string
    std::getline(std::cin, line);
    if (std::cin.eof()) break; // terminate gracefully encountering eof
    try {
      parseLine(line, formulaStr, assignmentStr);
    } catch (const char *e) {
      std::cout << e << std::endl;
      continue;
    }
    // std::cout << "formula: " << formulaStr << "; assignment: " << assignmentStr << std::endl;
    FormulaParser fParser{formulaStr};
    AssignmentParser aParser{assignmentStr};
    TreeNode *treeRoot = nullptr;
    try {
      treeRoot = fParser.getTreeRoot();
      std::map<std::string, bool> assignment = aParser.parseAssignment();
      bool result = treeRoot->evaluate(assignment);
      std::cout << result << std::endl;
    } catch (const char *e) {
      delete treeRoot;
      std::cout << e << std::endl;
      continue;
    }
    delete treeRoot;
  }
}

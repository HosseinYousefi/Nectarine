//
//  main.cpp
//  Nectarine
//
//  Created by Hossein Yousefi on 12/12/2018.
//  Copyright © 2018 Harbour Space. All rights reserved.
//

#include "NectAST.hpp"
#include "NectStack.hpp"
#include "NectCompiler.hpp"
#include "NectStatement.hpp"
#include "NectError.hpp"
#include "NectConfig.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int main(int argc, const char* argv[]) {
  using namespace std;
  #ifdef DEBUG
  const char *path = "/Users/Hossein/Courses/Systems Programming/Nectarine/Nectarine/example.nect";
  #else
  const char *path = argv[1];
  #endif
  ifstream fin(path);
  string str;
  string source;
  while (getline(fin, str)) {
    if (str.empty())
      break;
    source += str + '\n';
  }
  
  using nectarine::parser::iterator_type;
  iterator_type iter(source.begin());
  iterator_type end(source.end());
  
  nectarine::vmachine vm;
  nectarine::code_gen::program program;
  nectarine::ast::statement_list ast;
  
  using boost::spirit::x3::with;
  using nectarine::parser::error_handler_type;
  error_handler_type error_handler(iter, end, cerr);
  
  nectarine::code_gen::compiler compile(program, error_handler);
  
  auto const parser =
  with<nectarine::parser::error_handler_tag>(ref(error_handler)) [
    nectarine::statement()
  ];
  
  using boost::spirit::x3::ascii::space;
  bool success = phrase_parse(iter, end, parser, space, ast);
  
  if (success && iter == end) {
    if (compile.start(ast)) {
      cout << "Build Succeeded!" << endl;
      vm.execute(program());
      program.print_assembler();
      cout << "Variables {" << endl;
      program.print_variables(vm.get_stack());
      cout << "}" << endl;
    } else {
      cout << "Build Failed!" << endl;
    }
  } else {
    cout << "Compilation Error!" << endl;
  }
  return 0;
}

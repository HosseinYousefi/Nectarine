//
//  NectCompiler.hpp
//  Nectarine
//
//  Created by Hossein Yousefi on 14/12/2018.
//  Copyright © 2018 Harbour Space. All rights reserved.
//

#ifndef NectCompiler_hpp
#define NectCompiler_hpp

#include "NectAST.hpp"
#include "NectError.hpp"
#include <vector>
#include <map>

namespace nectarine { namespace code_gen {
    struct program {
      void op(int a);
      void op(int a, int b);
      void op(int a, int b, int c);
      
      int& operator[](std::size_t i) { return code[i]; }
      int operator[](std::size_t i) const { return code[i]; }
      void clear() { code.clear(); variables.clear(); }
      std::size_t size() const { return code.size(); }
      std::vector<int> const& operator()() const { return code; }
      
      std::size_t nvars() const { return variables.size(); }
      int const* find_var(std::string const& name) const;
      void add_var(std::string const& name);
      
      void print_variables(std::vector<int> const& stack) const;
      void print_assembler() const;
      
    private:
      std::map<std::string, int> variables;
      std::vector<int> code;
    };
    
    struct compiler {
      typedef bool result_type;
      typedef std::function<
      void(x3::position_tagged, std::string const&)>
      error_handler_type;
      
      template <typename ErrorHandler>
      compiler(
        nectarine::code_gen::program& program,
        ErrorHandler const& error_handler
      ): program(program), error_handler(
        [&](x3::position_tagged pos, std::string const& msg) {
          error_handler(pos, msg);
        }
      ) {}
      
      bool operator()(ast::nil) const { BOOST_ASSERT(0); return false; }
      bool operator()(unsigned int x) const;
      bool operator()(bool x) const;
      bool operator()(ast::variable const& x) const;
      bool operator()(ast::operation const& x) const;
      bool operator()(ast::unary const& x) const;
      bool operator()(ast::expression const& x) const;
      bool operator()(ast::assignment const& x) const;
      bool operator()(ast::variable_declaration const& x) const;
      bool operator()(ast::statement_list const& x) const;
      bool operator()(ast::statement const& x) const;
      bool operator()(ast::if_statement const& x) const;
      bool operator()(ast::while_statement const& x) const;
      
      bool start(ast::statement_list const& x) const;
      
      nectarine::code_gen::program& program;
      error_handler_type error_handler;
    };
  }}

#endif /* NectCompiler_hpp */

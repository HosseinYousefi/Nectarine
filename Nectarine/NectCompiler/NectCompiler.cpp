//
//  NectCompiler.cpp
//  Nectarine
//
//  Created by Hossein Yousefi on 14/12/2018.
//  Copyright © 2018 Harbour Space. All rights reserved.
//

#include "NectCompiler.hpp"
#include "NectStack.hpp"
#include <boost/variant/apply_visitor.hpp>
#include <boost/assert.hpp>
#include <boost/lexical_cast.hpp>
#include <iostream>
#include <set>
#include <iostream>

namespace nectarine { namespace code_gen {
  void program::op(int a) {
    code.push_back(a);
  }
  
  void program::op(int a, int b) {
    code.push_back(a);
    code.push_back(b);
  }
  
  void program::op(int a, int b, int c) {
    code.push_back(a);
    code.push_back(b);
    code.push_back(c);
  }
  
  int const* program::find_var(std::string const& name) const {
    auto i = variables.find(name);
    if (i == variables.end())
      return 0;
    return &i->second;
  }
  
  void program::add_var(std::string const& name) {
    std::size_t n = variables.size();
    variables[name] = int(n);
  }
  
  void program::print_variables(std::vector<int> const& stack) const {
    for (auto const& p : variables) {
      std::cout << "  " << p.first << ": " << stack[p.second] << std::endl;
    }
  }
  
  void program::print_assembler() const {
    auto pc = code.begin();
    
    std::vector<std::string> locals(variables.size());
    typedef std::pair<std::string, int> pair;
    for (pair const& p: variables) {
      locals[p.second] = p.first;
      std::cout << "local  "
      << p.first << ", @" << p.second << std::endl;
    }
    
    std::map<std::size_t, std::string> lines;
    std::set<std::size_t> jumps;
    
    while (pc != code.end()) {
      std::string line;
      std::size_t address = pc - code.begin();
      
      switch (*pc++) {
        case NEG:
          line += "  NEG";
          break;
          
        case NOT:
          line += "  NOT";
          break;
          
        case ADD:
          line += "  ADD";
          break;
          
        case SUB:
          line += "  SUB";
          break;
          
        case MUL:
          line += "  MUL";
          break;
          
        case DIV:
          line += "  DIV";
          break;
          
        case EQ:
          line += "  EQ";
          break;
          
        case NEQ:
          line += "  NEQ";
          break;
          
        case LT:
          line += "  LT";
          break;
          
        case LTE:
          line += "  LTE";
          break;
          
        case GT:
          line += "  GT";
          break;
          
        case GTE:
          line += "  GTE";
          break;
          
        case AND:
          line += "  AND";
          break;
          
        case OR:
          line += "  OR";
          break;
          
        case LOAD:
          line += "  LOAD  ";
          line += boost::lexical_cast<std::string>(locals[*pc++]);
          break;
          
        case STORE:
          line += "  STORE ";
          line += boost::lexical_cast<std::string>(locals[*pc++]);
          break;
          
        case INT:
          line += "  INT   ";
          line += boost::lexical_cast<std::string>(*pc++);
          break;
          
        case TRUE:
          line += "  TRUE";
          break;
          
        case FALSE:
          line += "  FALSE";
          break;
          
        case JMP: {
          line += "  JMP   ";
          std::size_t pos = (pc - code.begin()) + *pc++;
          if (pos == code.size())
            line += "END";
          else
            line += "l" + boost::lexical_cast<std::string>(pos);
          jumps.insert(pos);
        }
          break;
          
        case JIF: {
          line += "  JIF   ";
          std::size_t pos = (pc - code.begin()) + *pc++;
          if (pos == code.size())
            line += "END";
          else
            line += "L_" + boost::lexical_cast<std::string>(pos);
          jumps.insert(pos);
        }
          break;
          
        case ADJ:
          line += "  ADJ   ";
          line += boost::lexical_cast<std::string>(*pc++);
          break;
      }
      lines[address] = line;
    }
    
    std::cout << "START:" << std::endl;
    for (auto const& l: lines) {
      std::size_t pos = l.first;
      if (jumps.find(pos) != jumps.end())
        std::cout << "L_" << pos << ':' << std::endl;
      std::cout << l.second << std::endl;
    }
    
    std::cout << "END:" << std::endl;
  }
  
  bool compiler::operator()(unsigned int x) const {
    program.op(INT, x);
    return true;
  }
  
  bool compiler::operator()(bool x) const {
    program.op(x? TRUE: FALSE);
    return true;
  }
  
  bool compiler::operator()(ast::variable const& x) const {
    int const* p = program.find_var(x.name);
    if (p == 0) {
      error_handler(x, "Undeclared variable: " + x.name);
      return false;
    }
    program.op(LOAD, *p);
    return true;
  }
  
  bool compiler::operator()(ast::operation const& x) const {
    if (!boost::apply_visitor(*this, x.operand_))
      return false;
    switch (x.operator_) {
      case ast::op_plus:          program.op(ADD); break;
      case ast::op_minus:         program.op(SUB); break;
      case ast::op_times:         program.op(MUL); break;
      case ast::op_divide:        program.op(DIV); break;
        
      case ast::op_equal:         program.op(EQ);  break;
      case ast::op_not_equal:     program.op(NEQ); break;
      case ast::op_less:          program.op(LT);  break;
      case ast::op_less_equal:    program.op(LTE); break;
      case ast::op_greater:       program.op(GT);  break;
      case ast::op_greater_equal: program.op(GTE); break;
        
      case ast::op_and:           program.op(AND); break;
      case ast::op_or:            program.op(OR);  break;
      default: BOOST_ASSERT(0); return false;
    }
    return true;
  }
  
  bool compiler::operator()(ast::unary const& x) const {
    if (!boost::apply_visitor(*this, x.operand_))
      return false;
    switch (x.operator_) {
      case ast::op_negative: program.op(NEG); break;
      case ast::op_not:      program.op(NOT); break;
      case ast::op_positive:                  break;
      default: BOOST_ASSERT(0); return false;
    }
    return true;
  }
  
  bool compiler::operator()(ast::expression const& x) const {
    if (!boost::apply_visitor(*this, x.first))
      return false;
    for (ast::operation const& oper : x.rest) {
      if (!(*this)(oper))
        return false;
    }
    return true;
  }
  
  bool compiler::operator()(ast::assignment const& x) const {
    if (!(*this)(x.rhs))
      return false;
    int const* p = program.find_var(x.lhs.name);
    if (p == 0) {
      error_handler(x.lhs, "Undeclared variable: " + x.lhs.name);
      return false;
    }
    program.op(STORE, *p);
    return true;
  }
  
  bool compiler::operator()(ast::variable_declaration const& x) const {
    int const* p = program.find_var(x.assign.lhs.name);
    if (p != 0) {
      error_handler(x.assign.lhs, "Duplicate variable: " + x.assign.lhs.name);
      return false;
    }
    bool r = (*this)(x.assign.rhs);
    if (r) {
      program.add_var(x.assign.lhs.name);
      program.op(STORE, *program.find_var(x.assign.lhs.name));
    }
    return r;
  }
  
  bool compiler::operator()(ast::statement const& x) const {
    return boost::apply_visitor(*this, x);
  }
  
  bool compiler::operator()(ast::statement_list const& x) const {
    for (auto const& s: x) {
      if (!(*this)(s))
        return false;
    }
    return true;
  }
  
  bool compiler::operator()(ast::if_statement const& x) const {
    if (!(*this)(x.condition))
      return false;
    program.op(JIF, 0 /* UNDEFINED */);
    std::size_t skip = program.size() - 1;
    if (!(*this)(x.then))
      return false;
    program[skip] = int(program.size() - skip);
    
    if (x.else_) {
      program[skip] += 2; // it has else, so skip more
      program.op(JMP, 0 /* UNDEFINED */);
      std::size_t exit = program.size() - 1;
      if (!(*this)(*x.else_))
        return false;
      program[exit] = int(program.size() - exit);
    }
    return true;
  }
  
  bool compiler::operator()(ast::while_statement const& x) const {
    std::size_t loop = program.size();
    if (!(*this)(x.condition))
      return false;
    program.op(JIF, 0 /* UNDEFINED */);
    std::size_t exit = program.size() - 1;
    if (!(*this)(x.body))
      return false;
    program.op(JMP, int(loop - 1) - int(program.size()));
    program[exit] = int(program.size() - exit);
    return true;
  }
  
  bool compiler::start(ast::statement_list const& x) const {
    program.clear();
    program.op(ADJ, 0);
    if (!(*this)(x)) {
      program.clear();
      return false;
    }
    program[1] = int(program.nvars());
    return true;
  }
}}

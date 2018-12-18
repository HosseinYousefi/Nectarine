//
//  NectDefinition.hpp
//  Nectarine
//
//  Created by Hossein Yousefi on 14/12/2018.
//  Copyright © 2018 Harbour Space. All rights reserved.
//

#ifndef NectDefinition_hpp
#define NectDefinition_hpp

#include <boost/spirit/home/x3.hpp>
#include <boost/spirit/home/x3/support/utility/annotate_on_success.hpp>
#include "NectAST.hpp"
#include "NectAdapt.hpp"
#include "NectStatement.hpp"
#include "NectExpression.hpp"
#include "NectCommon.hpp"
#include "NectError.hpp"

namespace nectarine { namespace parser {
  using x3::raw;
  using x3::lexeme;
  using x3::rule;
  using namespace x3::ascii;
  
  struct statement_list_class;
  struct variable_declaration_class;
  struct assignment_class;
  struct variable_class;
  struct if_statement_class;
  struct while_statement_class;
  
  using statement_list_type       = rule<statement_list_class,       ast::statement_list>;
  using variable_declaration_type = rule<variable_declaration_class, ast::variable_declaration>;
  using assignment_type           = rule<assignment_class,           ast::assignment>;
  using variable_type             = rule<variable_class,             ast::variable>;
  using if_statement_type         = rule<if_statement_class,         ast::if_statement>;
  using while_statement_type      = rule<while_statement_class,      ast::while_statement>;
  
  statement_type            const statement            = "statement";
  statement_list_type       const statement_list       = "statement_list";
  variable_declaration_type const variable_declaration = "variable_declaration";
  assignment_type           const assignment           = "assignment";
  variable_type             const variable             = "variable";
  if_statement_type         const if_statement         = "if_statement";
  while_statement_type      const while_statement      = "while_statement";
  
  auto const& expression = nectarine::expression();
  
  auto const statement_list_def = (
    +(while_statement | if_statement | variable_declaration | assignment)
  );
  
  auto const variable_declaration_def = (
    lexeme["var" >> !(alnum | '_')] >
    assignment
  );
  
  auto const assignment_def = (
    variable >
    '=' >
    expression >
    ';'
  );
  
  auto const if_statement_def = (
    lexeme["if" >> !(alnum | '_')] >
    expression >
    '{' >
    statement_list >
    '}' >
    -(
      lexeme["else" >> !(alnum | '_')] >
      '{' >
      -statement_list >
      '}'
    )
  );
  
  auto const while_statement_def = (
    lexeme["while" >> !(alnum | '_')] >
    expression >
    '{' >
    statement_list >
    '}'
  );
  
  auto const variable_def = identifier;
  auto const statement_def = statement_list;
  
  BOOST_SPIRIT_DEFINE(
    statement,
    statement_list,
    variable_declaration,
    assignment,
    if_statement,
    while_statement,
    variable
  );
  
  struct statement_class: error_handler_base, x3::annotate_on_success {};
  struct if_statement_class: x3::annotate_on_success {};
  struct while_statement_class: x3::annotate_on_success {};
  struct assignment_class: x3::annotate_on_success {};
  struct variable_class: x3::annotate_on_success {};
}}

namespace nectarine {
  parser::statement_type const& statement() {
    return parser::statement;
  }
}


#endif /* NectDefinition_hpp */

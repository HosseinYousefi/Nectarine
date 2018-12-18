//
//  NectAdapt.hpp
//  Nectarine
//
//  Created by Hossein Yousefi on 14/12/2018.
//  Copyright © 2018 Harbour Space. All rights reserved.
//

#ifndef NectAdapt_hpp
#define NectAdapt_hpp

#include "NectAST.hpp"
#include <boost/fusion/include/adapt_struct.hpp>

using namespace nectarine::ast;

BOOST_FUSION_ADAPT_STRUCT(
  unary,
  operator_, operand_
)

BOOST_FUSION_ADAPT_STRUCT(
  operation,
  operator_, operand_
)

BOOST_FUSION_ADAPT_STRUCT(
  expression,
  first, rest
)

BOOST_FUSION_ADAPT_STRUCT(
  variable_declaration,
  assign
)

BOOST_FUSION_ADAPT_STRUCT(
  assignment,
  lhs, rhs
)

BOOST_FUSION_ADAPT_STRUCT(
  if_statement,
  condition, then, else_
)

BOOST_FUSION_ADAPT_STRUCT(
  while_statement,
  condition, body
)

#endif /* NectAdapt_hpp */

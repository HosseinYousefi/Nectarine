//
//  NectExpression.cpp
//  Nectarine
//
//  Created by Hossein Yousefi on 14/12/2018.
//  Copyright © 2018 Harbour Space. All rights reserved.
//

#include "NectExpressionDefinition.hpp"
#include "NectConfig.hpp"

namespace nectarine { namespace parser {
  BOOST_SPIRIT_INSTANTIATE(expression_type, iterator_type, context_type);
}}

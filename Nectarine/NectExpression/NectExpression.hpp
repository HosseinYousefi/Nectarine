//
//  NectExpression.hpp
//  Nectarine
//
//  Created by Hossein Yousefi on 14/12/2018.
//  Copyright © 2018 Harbour Space. All rights reserved.
//

#ifndef NectExpression_hpp
#define NectExpression_hpp

#include <boost/spirit/home/x3.hpp>
#include "NectAST.hpp"

namespace nectarine {
  namespace x3 = boost::spirit::x3;
  namespace parser {
    struct expression_class;
    typedef x3::rule<expression_class, ast::expression> expression_type;
    BOOST_SPIRIT_DECLARE(expression_type);
  }
  parser::expression_type const& expression();
}

#endif /* NectExpression_hpp */

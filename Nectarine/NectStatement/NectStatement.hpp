//
//  NectStatement.hpp
//  Nectarine
//
//  Created by Hossein Yousefi on 14/12/2018.
//  Copyright © 2018 Harbour Space. All rights reserved.
//

#ifndef NectStatement_hpp
#define NectStatement_hpp

#include <boost/spirit/home/x3.hpp>
#include "NectAST.hpp"


namespace nectarine {
  namespace x3 = boost::spirit::x3;
  namespace parser {
    struct statement_class;
    using statement_type = x3::rule<statement_class, ast::statement_list>;
    using statement_id = statement_type::id;
    BOOST_SPIRIT_DECLARE(statement_type);
  }
  
  parser::statement_type const& statement();
}


#endif /* NectStatement_hpp */

//
//  NectError.hpp
//  Nectarine
//
//  Created by Hossein Yousefi on 14/12/2018.
//  Copyright © 2018 Harbour Space. All rights reserved.
//

#ifndef NectError_hpp
#define NectError_hpp

#include <boost/spirit/home/x3.hpp>
#include <boost/spirit/home/x3/support/utility/error_reporting.hpp>
#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include "NectExpression.hpp"
#include "NectStatement.hpp"

namespace nectarine { namespace parser {
  namespace x3 = boost::spirit::x3;
  
  template <typename Iterator>
  using error_handler = x3::error_handler<Iterator>;
  
  using error_handler_tag = x3::error_handler_tag;
  
  struct error_handler_base {
    template <typename Iterator, typename Exception, typename Context>
    x3::error_handler_result on_error(Iterator& first, Iterator const& last,
                                      Exception const& x, Context const& context) {
      std::string message = "Error! Expecting: " + x.which() + " here:";
      auto& error_handler = x3::get<error_handler_tag>(context).get();
      error_handler(x.where(), message);
      return x3::error_handler_result::fail;
    }
  };
}}

#endif /* NectError_hpp */

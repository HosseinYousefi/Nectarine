//
//  NectConfig.hpp
//  Nectarine
//
//  Created by Hossein Yousefi on 14/12/2018.
//  Copyright © 2018 Harbour Space. All rights reserved.
//

#ifndef NectConfig_hpp
#define NectConfig_hpp

#include <boost/spirit/home/x3.hpp>
#include "NectError.hpp"

namespace nectarine { namespace parser {
  using iterator_type = std::string::const_iterator;
  using phrase_context_type = x3::phrase_parse_context<x3::ascii::space_type>::type;
  using error_handler_type = error_handler<iterator_type>;
  
  using context_type =
  x3::context<
    error_handler_tag,
    std::reference_wrapper<error_handler_type>,
    phrase_context_type
  >;
}}


#endif /* NectConfig_hpp */

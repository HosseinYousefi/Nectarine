//
//  NectCommon.hpp
//  Nectarine
//
//  Created by Hossein Yousefi on 14/12/2018.
//  Copyright © 2018 Harbour Space. All rights reserved.
//

#ifndef NectCommon_hpp
#define NectCommon_hpp

#include <boost/spirit/home/x3.hpp>
namespace nectarine { namespace parser {
  using x3::raw;
  using x3::lexeme;
  using x3::alpha;
  using x3::alnum;
    
  struct identifier_class;
  using identifier_type = x3::rule<identifier_class, std::string>;
  identifier_type const identifier = "identifier";
  
  auto const identifier_def = raw[lexeme[(alpha | '_') >> *(alnum | '_')]];
    
  BOOST_SPIRIT_DEFINE(identifier);
}}

#endif /* NectCommon_hpp */

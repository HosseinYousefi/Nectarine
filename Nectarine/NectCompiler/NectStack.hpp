//
//  NectStack.hpp
//  Nectarine
//
//  Created by Hossein Yousefi on 14/12/2018.
//  Copyright © 2018 Harbour Space. All rights reserved.
//

#ifndef NectStack_hpp
#define NectStack_hpp

#include <vector>

namespace nectarine {
  enum byte_code {
    NEG,         //  Negate
    ADD,         //  Add
    SUB,         //  Substract
    MUL,         //  Multiply
    DIV,         //  Division
    
    NOT,         //  Boolean Not
    EQ,          //  Equal
    NEQ,         //  Not Equal
    LT,          //  Less Than
    LTE,         //  Less Than or Equal
    GT,          //  Greater Than
    GTE,         //  Greater Than or Equal
    
    AND,         //  Boolean And
    OR,          //  Boolean Or
    
    LOAD,        //  Load a variable
    STORE,       //  Store in a variable
    
    INT,         //  Integer
    TRUE,        //  1
    FALSE,       //  0
    
    JIF,         //  Jump if false
    JMP,         //  Jump
    
    ADJ,         //  Adjust the stack
    CALL,        //  Function call
    RET          //  Return from function
  };
  
  class vmachine {
  public:
    vmachine(unsigned stackSize = 4096): stack(stackSize) {}
    
    int execute(
      std::vector<int> const& code,
      std::vector<int>::const_iterator pc,
      std::vector<int>::iterator frame_ptr
    );
    
    int execute(std::vector<int> const& code) {
      return execute(code, code.begin(), stack.begin());
    };
    
    std::vector<int> const& get_stack() const { return stack; };
    
  private:
    std::vector<int> stack;
  };
}


#endif /* NectStack_hpp */

//
//  NectStack.cpp
//  Nectarine
//
//  Created by Hossein Yousefi on 14/12/2018.
//  Copyright © 2018 Harbour Space. All rights reserved.
//

#include "NectStack.hpp"
#include <boost/assert.hpp>

namespace nectarine {
  int vmachine::execute(std::vector<int> const& code,
                        std::vector<int>::const_iterator pc,
                        std::vector<int>::iterator frame_ptr) {
    std::vector<int>::iterator stack_ptr = frame_ptr;
    
    while (pc != code.end()) {
      switch (*pc++) {
        case NEG:
          stack_ptr[-1] = -stack_ptr[-1];
          break;
          
        case NOT:
          stack_ptr[-1] = !bool(stack_ptr[-1]);
          break;
          
        case ADD:
          --stack_ptr;
          stack_ptr[-1] += stack_ptr[0];
          break;
          
        case SUB:
          --stack_ptr;
          stack_ptr[-1] -= stack_ptr[0];
          break;
          
        case MUL:
          --stack_ptr;
          stack_ptr[-1] *= stack_ptr[0];
          break;
          
        case DIV:
          --stack_ptr;
          stack_ptr[-1] /= stack_ptr[0];
          break;
          
        case EQ:
          --stack_ptr;
          stack_ptr[-1] = bool(stack_ptr[-1] == stack_ptr[0]);
          break;
          
        case NEQ:
          --stack_ptr;
          stack_ptr[-1] = bool(stack_ptr[-1] != stack_ptr[0]);
          break;
          
        case LT:
          --stack_ptr;
          stack_ptr[-1] = bool(stack_ptr[-1] < stack_ptr[0]);
          break;
          
        case LTE:
          --stack_ptr;
          stack_ptr[-1] = bool(stack_ptr[-1] <= stack_ptr[0]);
          break;
          
        case GT:
          --stack_ptr;
          stack_ptr[-1] = bool(stack_ptr[-1] > stack_ptr[0]);
          break;
          
        case GTE:
          --stack_ptr;
          stack_ptr[-1] = bool(stack_ptr[-1] >= stack_ptr[0]);
          break;
          
        case AND:
          --stack_ptr;
          stack_ptr[-1] = bool(stack_ptr[-1]) && bool(stack_ptr[0]);
          break;
          
        case OR:
          --stack_ptr;
          stack_ptr[-1] = bool(stack_ptr[-1]) || bool(stack_ptr[0]);
          break;
          
        case LOAD:
          *stack_ptr++ = frame_ptr[*pc++];
          break;
          
        case STORE:
          --stack_ptr;
          frame_ptr[*pc++] = stack_ptr[0];
          break;
          
        case INT:
          *stack_ptr++ = *pc++;
          break;
          
        case TRUE:
          *stack_ptr++ = true;
          break;
          
        case FALSE:
          *stack_ptr++ = false;
          break;
          
        case JMP:
          pc += *pc;
          break;
          
        case JIF:
          if (!bool(stack_ptr[-1]))
            pc += *pc;
          else
            ++pc;
          --stack_ptr;
          break;
          
        case ADJ:
          stack_ptr = stack.begin() + *pc++;
          break;
          
        case CALL: {
          int nargs = *pc++;
          int jump = *pc++;
          
          int r = execute(code,
                          code.begin() + jump,
                          stack_ptr - nargs);
          
          // cleanup after return from function
          stack_ptr[-nargs] = r;      //  get return value
          stack_ptr -= (nargs - 1);
        }
          break;
          
        case RET:
          return stack_ptr[-1];
      }
    }
    return -1;
  }
}

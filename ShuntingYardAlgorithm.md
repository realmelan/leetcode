# Shunting-yard Algorithm

Shunting-yard algorithm can be used to parse expression containing parenthesis and operators with different precedence and associativity. It uses one stack to store operands from the expression and one stack to store the operators.

The algorithm goes like this: whenever an operator is found, it iterates through the operator stack, and see whether the top operator at the stack has higher precedence or equal precedence but left associativity. If so, pop 2 operands from the operand stack, do calculation and push result back to the operand stack. it does this until the operator stack is empty or the operator at the top doesn't have higher precedence or equal precedence but not left associativity.

If there is parenthesis, then treat parenthesis as having highest precedence. When seeing an open parenthesis, push it onto operator stack so as to know where to stop when popping operators for the closing parenthesis. When seeing an closing parenthesis, pop operators from stack till the open parenthesis, and push the result onto the operand stack.

The final result is on the operand stack.

```
/* This implementation does not implement composite functions,functions with variable number of arguments, and unary operators. */

while there are tokens to be read:
    read a token.
    if the token is a number, then:
        push it to the output queue.
    else if the token is a function then:
        push it onto the operator stack 
    else if the token is an operator then:
        while ((there is an operator at the top of the operator stack)
              and ((the operator at the top of the operator stack has greater precedence)
                  or (the operator at the top of the operator stack has equal precedence and the token is left associative))
              and (the operator at the top of the operator stack is not a left parenthesis)):
            pop operators from the operator stack onto the output queue.
        push it onto the operator stack.
    else if the token is a left parenthesis (i.e. "("), then:
        push it onto the operator stack.
    else if the token is a right parenthesis (i.e. ")"), then:
        while the operator at the top of the operator stack is not a left parenthesis:
            pop the operator from the operator stack onto the output queue.
        /* If the stack runs out without finding a left parenthesis, then there are mismatched parentheses. */
        if there is a left parenthesis at the top of the operator stack, then:
            pop the operator from the operator stack and discard it
        if there is a function token at the top of the operator stack, then:
            pop the function from the operator stack onto the output queue.
/* After while loop, if operator stack not null, pop everything to output queue */
if there are no more tokens to read then:
    while there are still operator tokens on the stack:
        /* If the operator token on the top of the stack is a parenthesis, then there are mismatched parentheses. */
        pop the operator from the operator stack onto the output queue.
exit.
```

This algorithm can be used to solve all kinds of calculator problems like

# Problems:
* https://leetcode.com/problems/basic-calculator-iv/
* https://leetcode.com/problems/brace-expansion-ii/

# Ref
* https://en.wikipedia.org/wiki/Shunting-yard_algorithm

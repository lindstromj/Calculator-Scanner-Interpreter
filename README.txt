# Calculator-Scanner-Interpreter
A Lexical Scanner and Interpreter for the Calculator Language

3 Statement Types: Assignment ( id:= expression)
                   read id
                   write id
Expressions:       normal infix expressions with nested parentheses, operators +, -, *, /
                   identifiers ( L | (L | d | _)* ), and numeric constants ( d+ or d+.d+)
Comments:          /* ... */


Language Grammar:
<program>       -> <stmnt_list)   $$
<stmt_list>     -> <stmt> <stmt_list> | Epsilon
<stmt>          -> id := <expr> | read id | write <expr>
<expr>          -> <term> <term_tail>
<term_tail>     -> <add_op> <term> <term_tail> | Epsilon
<term>          -> <factor> <factor_tail>
<factor_tail>   -> <mul_op> <factor> <factor_tail> | Epsilon
<factor>        -> ( <expr> ) | id | number
<add_op>        -> + | -
<mul_op>        -> * | / 

# agu_dtl


```ebnf
<program> ::= <constdecls> <forstatement>

<constdecls> ::= <constdecls> <constdecl> | epsilon

<constdecl> ::= <opt> <type> ID ASSIGN INTLITERAL SEMICOL
              | <opt> <type> ID ASSIGN LCURLY <intlist> RCURLY SEMICOL

<opt> ::= NOPT | epsilon

<intlist> ::= INTLITERAL COMMA <intlist>
            | INTLITERAL
            | epsilon

<fortstatement> ::= FOR LPAREN <constdecl> <id> LT <expr> SEMICOL 
                    <unarystmt> RPAREN LCURLY <forstatement> 
                    RCURLY
                    | FOR LPAREN <constdecl> <id> LT <expr>  
                    SEMICOL <unarystmt> RPAREN LCURLY <innernest> 
                    RCURLY

<innernest> ::= <outstatements>
                | <ifstatement>
                | <switchstatement>

<outstatements> ::= <outstatements> <outstatement>
                    | <outstatement>

<ifstatement> ::= IF LPAREN <ifpredicate> RPAREN LCURLY 
                  <outstatements> RCURLY ELSE LCURLY
                  <outstatements> RCURLY
                
<ifpredicate> ::= <id> <compareop> <id>
                  | ISEVEN id
                  | PAD <id> <id> <id> <id>
                  | ISEDGE <id>
                  | ISEDGE <id> OR <id>
                  | ISEDGE <id> AND <id>

<compareop> ::= LT | LTE | GT | GTE
<boolop> ::= AND | OR

<switchstatement> ::= SWITCH LPAREN <id> RPAREN LCURLY <casestatements> RCURLY

<casestatements> ::= <casestatement> <casestatements>
                     | <casestatement>

<casestatement> ::= CASE COLON <outstatements>

<outstatement> ::= OUT ASSIGN <expr> SEMICOL

<type> ::= INT

<expr> ::= <expr> <exprop> <expr>
           | < term>

<exprop> ::= CROSS | STAR | MINUS | LT

<term> ::= <factor>
           | LPAREN <expr> RPAREN

<factor> ::= INTLITERAL
             | <loc>

<loc> ::= <id>
          | <id> LBRACKET <id> RBRACKET

<id> ::= ID







```

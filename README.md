# DTL: Data Transfomration Language

DTL is a domain-specific language for describing logical data layout transformations as mappings from a logical coordinate space to a positional memory space.

Unlike conventional transformation pipelines that materialize intermediate tensors, DTL describes transformations as views over underlying data. A DTL kernel defines how data should be exposed rather than how it should be explicitly rearranged in memory.

This repository contains:

- DTL language definitions
- DTL compiler infrastructure
- Lowering to MLIR Affine
- Raising from Affine back to DTL
- Analysis and transformation utilities
- DTU targeted backend
- DTL API/Runtime

# Motivation
Modern tensor frameworks routinely perform transformations such as:

NHWC → NCHW permutations
Im2Col
Vol2Col
tensor unfolding
image augmentation
projections
rotations/reflections
reshape operations

These transformations are often implemented through explicit materialization:
Input Tensor
      ↓
Transform A
      ↓
Temporary Tensor
      ↓
Transform B
      ↓
Temporary Tensor
      ↓
Compute

## Materialization:
- increases memory traffic
- inflates working set size
- introduces additional allocations
- adds transformation latency

DTL instead treats transformations as logical mappings. The transformation exists as an address-generation function in the DTU, with the desired data layout exposed directly to the programmer. 


## Example
Horizontal reflection expressed as a DTL kernel:

```c
int stride_h = WIDTH;

for (int h = 0; h < HEIGHT; h++) {
    for (int w = 0; w < WIDTH; w++) {
        out = h * stride_h + (WIDTH - 1 - w);
    }
}
```

Conceptually:

| Input | Output View |
|--------|-------------|
| A B C D | D C B A |
| E F G H | H G F E |

No data movement occurs. The desired view is exposed directly to the programmer.




## Full Grammar Specification
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

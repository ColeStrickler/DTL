// A Bison parser, made by GNU Bison 3.8.2.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015, 2018-2021 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.

// DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
// especially those whose name start with YY_ or yy_.  They are
// private implementation details that can be changed or removed.





#include "frontend.hh"


// Unqualified %code blocks.
#line 38 "parser.yy"

   // C std code for utility functions
   #include <iostream>
   #include <cstdlib>
   #include <fstream>
   #include <algorithm>

   // Our code for interoperation between scanner/parser
   #include "scanner.hpp"
   #include "ast.hpp"
   #include "tokens.hpp"

  //Request tokens from our scanner member, not 
  // from a global function
  #undef yylex
  #define yylex scanner.yylex




#line 67 "parser.cc"


#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif


// Whether we are compiled with exception support.
#ifndef YY_EXCEPTIONS
# if defined __GNUC__ && !defined __EXCEPTIONS
#  define YY_EXCEPTIONS 0
# else
#  define YY_EXCEPTIONS 1
# endif
#endif



// Enable debugging if requested.
#if YYDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << '\n';                       \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yy_stack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YY_USE (Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void> (0)
# define YY_STACK_PRINT()                static_cast<void> (0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

#line 5 "parser.yy"
namespace DTL {
#line 141 "parser.cc"

  /// Build a parser object.
  Parser::Parser (DTL::Scanner &scanner_yyarg, DTL::TransformGraph** root_yyarg)
#if YYDEBUG
    : yydebug_ (false),
      yycdebug_ (&std::cerr),
#else
    :
#endif
      scanner (scanner_yyarg),
      root (root_yyarg)
  {}

  Parser::~Parser ()
  {}

  Parser::syntax_error::~syntax_error () YY_NOEXCEPT YY_NOTHROW
  {}

  /*---------.
  | symbol.  |
  `---------*/

  // basic_symbol.
  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (const basic_symbol& that)
    : Base (that)
    , value ()
  {
    switch (this->kind ())
    {
      case symbol_kind::S_kernel: // kernel
        value.copy< DTL::DTLKernelNode* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr: // expr
      case symbol_kind::S_term: // term
      case symbol_kind::S_factor: // factor
        value.copy< DTL::ExpNode* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_forstatement: // forstatement
        value.copy< DTL::ForStmtNode* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_activenode: // activenode
      case symbol_kind::S_id: // id
        value.copy< DTL::IDNode* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_ID: // ID
        value.copy< DTL::IDToken * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_backingphyssize: // backingphyssize
      case symbol_kind::S_intlit: // intlit
        value.copy< DTL::IntLitNode* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_INTLITERAL: // INTLITERAL
        value.copy< DTL::IntLitToken * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_loc: // loc
        value.copy< DTL::LocNode* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_metadatastreamdecl: // metadatastreamdecl
        value.copy< DTL::MetadataStreamDeclNode* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_program: // program
        value.copy< DTL::ProgramNode* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_constdecl: // constdecl
      case symbol_kind::S_ifstatement: // ifstatement
      case symbol_kind::S_switchstatement: // switchstatement
      case symbol_kind::S_outstatement: // outstatement
      case symbol_kind::S_unarystmt: // unarystmt
        value.copy< DTL::StmtNode* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_ASSIGN: // ASSIGN
      case symbol_kind::S_NOPT: // NOPT
      case symbol_kind::S_INT: // INT
      case symbol_kind::S_LCURLY: // LCURLY
      case symbol_kind::S_LESS: // LESS
      case symbol_kind::S_LESSEQUAL: // LESSEQUAL
      case symbol_kind::S_GREATER: // GREATER
      case symbol_kind::S_GREATEREQUAL: // GREATEREQUAL
      case symbol_kind::S_LPAREN: // LPAREN
      case symbol_kind::S_CROSS: // CROSS
      case symbol_kind::S_POSTINC: // POSTINC
      case symbol_kind::S_RCURLY: // RCURLY
      case symbol_kind::S_RPAREN: // RPAREN
      case symbol_kind::S_SEMICOL: // SEMICOL
      case symbol_kind::S_STAR: // STAR
      case symbol_kind::S_FOR: // FOR
      case symbol_kind::S_OUT: // OUT
      case symbol_kind::S_COMMA: // COMMA
      case symbol_kind::S_LBRACKET: // LBRACKET
      case symbol_kind::S_RBRACKET: // RBRACKET
      case symbol_kind::S_MINUS: // MINUS
      case symbol_kind::S_COLON: // COLON
      case symbol_kind::S_CASE: // CASE
      case symbol_kind::S_SWITCH: // SWITCH
      case symbol_kind::S_IF: // IF
      case symbol_kind::S_ELSE: // ELSE
      case symbol_kind::S_ISEVEN: // ISEVEN
      case symbol_kind::S_ISEDGE: // ISEDGE
      case symbol_kind::S_OR: // OR
      case symbol_kind::S_AND: // AND
      case symbol_kind::S_PAD: // PAD
      case symbol_kind::S_METADATASTREAM: // METADATASTREAM
      case symbol_kind::S_DTL: // DTL
      case symbol_kind::S_ACTIVE: // ACTIVE
        value.copy< DTL::Token * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_transformgraph: // transformgraph
        value.copy< DTL::TransformGraph* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_type: // type
        value.copy< DTL::TypeNode* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_kernellist: // kernellist
        value.copy< std::vector<DTL::DTLKernelNode*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_inputlistwrapper: // inputlistwrapper
      case symbol_kind::S_inputlist: // inputlist
        value.copy< std::vector<DTL::IDNode*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_constdecls: // constdecls
      case symbol_kind::S_outstatements: // outstatements
      case symbol_kind::S_innernest: // innernest
      case symbol_kind::S_casestatement: // casestatement
        value.copy< std::vector<DTL::StmtNode*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_intlist: // intlist
        value.copy< std::vector<IntLitNode*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_casestatements: // casestatements
        value.copy< std::vector<std::vector<DTL::StmtNode*>> > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

  }




  template <typename Base>
  Parser::symbol_kind_type
  Parser::basic_symbol<Base>::type_get () const YY_NOEXCEPT
  {
    return this->kind ();
  }


  template <typename Base>
  bool
  Parser::basic_symbol<Base>::empty () const YY_NOEXCEPT
  {
    return this->kind () == symbol_kind::S_YYEMPTY;
  }

  template <typename Base>
  void
  Parser::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move (s);
    switch (this->kind ())
    {
      case symbol_kind::S_kernel: // kernel
        value.move< DTL::DTLKernelNode* > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_expr: // expr
      case symbol_kind::S_term: // term
      case symbol_kind::S_factor: // factor
        value.move< DTL::ExpNode* > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_forstatement: // forstatement
        value.move< DTL::ForStmtNode* > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_activenode: // activenode
      case symbol_kind::S_id: // id
        value.move< DTL::IDNode* > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_ID: // ID
        value.move< DTL::IDToken * > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_backingphyssize: // backingphyssize
      case symbol_kind::S_intlit: // intlit
        value.move< DTL::IntLitNode* > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_INTLITERAL: // INTLITERAL
        value.move< DTL::IntLitToken * > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_loc: // loc
        value.move< DTL::LocNode* > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_metadatastreamdecl: // metadatastreamdecl
        value.move< DTL::MetadataStreamDeclNode* > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_program: // program
        value.move< DTL::ProgramNode* > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_constdecl: // constdecl
      case symbol_kind::S_ifstatement: // ifstatement
      case symbol_kind::S_switchstatement: // switchstatement
      case symbol_kind::S_outstatement: // outstatement
      case symbol_kind::S_unarystmt: // unarystmt
        value.move< DTL::StmtNode* > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_ASSIGN: // ASSIGN
      case symbol_kind::S_NOPT: // NOPT
      case symbol_kind::S_INT: // INT
      case symbol_kind::S_LCURLY: // LCURLY
      case symbol_kind::S_LESS: // LESS
      case symbol_kind::S_LESSEQUAL: // LESSEQUAL
      case symbol_kind::S_GREATER: // GREATER
      case symbol_kind::S_GREATEREQUAL: // GREATEREQUAL
      case symbol_kind::S_LPAREN: // LPAREN
      case symbol_kind::S_CROSS: // CROSS
      case symbol_kind::S_POSTINC: // POSTINC
      case symbol_kind::S_RCURLY: // RCURLY
      case symbol_kind::S_RPAREN: // RPAREN
      case symbol_kind::S_SEMICOL: // SEMICOL
      case symbol_kind::S_STAR: // STAR
      case symbol_kind::S_FOR: // FOR
      case symbol_kind::S_OUT: // OUT
      case symbol_kind::S_COMMA: // COMMA
      case symbol_kind::S_LBRACKET: // LBRACKET
      case symbol_kind::S_RBRACKET: // RBRACKET
      case symbol_kind::S_MINUS: // MINUS
      case symbol_kind::S_COLON: // COLON
      case symbol_kind::S_CASE: // CASE
      case symbol_kind::S_SWITCH: // SWITCH
      case symbol_kind::S_IF: // IF
      case symbol_kind::S_ELSE: // ELSE
      case symbol_kind::S_ISEVEN: // ISEVEN
      case symbol_kind::S_ISEDGE: // ISEDGE
      case symbol_kind::S_OR: // OR
      case symbol_kind::S_AND: // AND
      case symbol_kind::S_PAD: // PAD
      case symbol_kind::S_METADATASTREAM: // METADATASTREAM
      case symbol_kind::S_DTL: // DTL
      case symbol_kind::S_ACTIVE: // ACTIVE
        value.move< DTL::Token * > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_transformgraph: // transformgraph
        value.move< DTL::TransformGraph* > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_type: // type
        value.move< DTL::TypeNode* > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_kernellist: // kernellist
        value.move< std::vector<DTL::DTLKernelNode*> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_inputlistwrapper: // inputlistwrapper
      case symbol_kind::S_inputlist: // inputlist
        value.move< std::vector<DTL::IDNode*> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_constdecls: // constdecls
      case symbol_kind::S_outstatements: // outstatements
      case symbol_kind::S_innernest: // innernest
      case symbol_kind::S_casestatement: // casestatement
        value.move< std::vector<DTL::StmtNode*> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_intlist: // intlist
        value.move< std::vector<IntLitNode*> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_casestatements: // casestatements
        value.move< std::vector<std::vector<DTL::StmtNode*>> > (YY_MOVE (s.value));
        break;

      default:
        break;
    }

  }

  // by_kind.
  Parser::by_kind::by_kind () YY_NOEXCEPT
    : kind_ (symbol_kind::S_YYEMPTY)
  {}

#if 201103L <= YY_CPLUSPLUS
  Parser::by_kind::by_kind (by_kind&& that) YY_NOEXCEPT
    : kind_ (that.kind_)
  {
    that.clear ();
  }
#endif

  Parser::by_kind::by_kind (const by_kind& that) YY_NOEXCEPT
    : kind_ (that.kind_)
  {}

  Parser::by_kind::by_kind (token_kind_type t) YY_NOEXCEPT
    : kind_ (yytranslate_ (t))
  {}



  void
  Parser::by_kind::clear () YY_NOEXCEPT
  {
    kind_ = symbol_kind::S_YYEMPTY;
  }

  void
  Parser::by_kind::move (by_kind& that)
  {
    kind_ = that.kind_;
    that.clear ();
  }

  Parser::symbol_kind_type
  Parser::by_kind::kind () const YY_NOEXCEPT
  {
    return kind_;
  }


  Parser::symbol_kind_type
  Parser::by_kind::type_get () const YY_NOEXCEPT
  {
    return this->kind ();
  }



  // by_state.
  Parser::by_state::by_state () YY_NOEXCEPT
    : state (empty_state)
  {}

  Parser::by_state::by_state (const by_state& that) YY_NOEXCEPT
    : state (that.state)
  {}

  void
  Parser::by_state::clear () YY_NOEXCEPT
  {
    state = empty_state;
  }

  void
  Parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  Parser::by_state::by_state (state_type s) YY_NOEXCEPT
    : state (s)
  {}

  Parser::symbol_kind_type
  Parser::by_state::kind () const YY_NOEXCEPT
  {
    if (state == empty_state)
      return symbol_kind::S_YYEMPTY;
    else
      return YY_CAST (symbol_kind_type, yystos_[+state]);
  }

  Parser::stack_symbol_type::stack_symbol_type ()
  {}

  Parser::stack_symbol_type::stack_symbol_type (YY_RVREF (stack_symbol_type) that)
    : super_type (YY_MOVE (that.state))
  {
    switch (that.kind ())
    {
      case symbol_kind::S_kernel: // kernel
        value.YY_MOVE_OR_COPY< DTL::DTLKernelNode* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr: // expr
      case symbol_kind::S_term: // term
      case symbol_kind::S_factor: // factor
        value.YY_MOVE_OR_COPY< DTL::ExpNode* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_forstatement: // forstatement
        value.YY_MOVE_OR_COPY< DTL::ForStmtNode* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_activenode: // activenode
      case symbol_kind::S_id: // id
        value.YY_MOVE_OR_COPY< DTL::IDNode* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_ID: // ID
        value.YY_MOVE_OR_COPY< DTL::IDToken * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_backingphyssize: // backingphyssize
      case symbol_kind::S_intlit: // intlit
        value.YY_MOVE_OR_COPY< DTL::IntLitNode* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_INTLITERAL: // INTLITERAL
        value.YY_MOVE_OR_COPY< DTL::IntLitToken * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_loc: // loc
        value.YY_MOVE_OR_COPY< DTL::LocNode* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_metadatastreamdecl: // metadatastreamdecl
        value.YY_MOVE_OR_COPY< DTL::MetadataStreamDeclNode* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_program: // program
        value.YY_MOVE_OR_COPY< DTL::ProgramNode* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_constdecl: // constdecl
      case symbol_kind::S_ifstatement: // ifstatement
      case symbol_kind::S_switchstatement: // switchstatement
      case symbol_kind::S_outstatement: // outstatement
      case symbol_kind::S_unarystmt: // unarystmt
        value.YY_MOVE_OR_COPY< DTL::StmtNode* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_ASSIGN: // ASSIGN
      case symbol_kind::S_NOPT: // NOPT
      case symbol_kind::S_INT: // INT
      case symbol_kind::S_LCURLY: // LCURLY
      case symbol_kind::S_LESS: // LESS
      case symbol_kind::S_LESSEQUAL: // LESSEQUAL
      case symbol_kind::S_GREATER: // GREATER
      case symbol_kind::S_GREATEREQUAL: // GREATEREQUAL
      case symbol_kind::S_LPAREN: // LPAREN
      case symbol_kind::S_CROSS: // CROSS
      case symbol_kind::S_POSTINC: // POSTINC
      case symbol_kind::S_RCURLY: // RCURLY
      case symbol_kind::S_RPAREN: // RPAREN
      case symbol_kind::S_SEMICOL: // SEMICOL
      case symbol_kind::S_STAR: // STAR
      case symbol_kind::S_FOR: // FOR
      case symbol_kind::S_OUT: // OUT
      case symbol_kind::S_COMMA: // COMMA
      case symbol_kind::S_LBRACKET: // LBRACKET
      case symbol_kind::S_RBRACKET: // RBRACKET
      case symbol_kind::S_MINUS: // MINUS
      case symbol_kind::S_COLON: // COLON
      case symbol_kind::S_CASE: // CASE
      case symbol_kind::S_SWITCH: // SWITCH
      case symbol_kind::S_IF: // IF
      case symbol_kind::S_ELSE: // ELSE
      case symbol_kind::S_ISEVEN: // ISEVEN
      case symbol_kind::S_ISEDGE: // ISEDGE
      case symbol_kind::S_OR: // OR
      case symbol_kind::S_AND: // AND
      case symbol_kind::S_PAD: // PAD
      case symbol_kind::S_METADATASTREAM: // METADATASTREAM
      case symbol_kind::S_DTL: // DTL
      case symbol_kind::S_ACTIVE: // ACTIVE
        value.YY_MOVE_OR_COPY< DTL::Token * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_transformgraph: // transformgraph
        value.YY_MOVE_OR_COPY< DTL::TransformGraph* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_type: // type
        value.YY_MOVE_OR_COPY< DTL::TypeNode* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_kernellist: // kernellist
        value.YY_MOVE_OR_COPY< std::vector<DTL::DTLKernelNode*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_inputlistwrapper: // inputlistwrapper
      case symbol_kind::S_inputlist: // inputlist
        value.YY_MOVE_OR_COPY< std::vector<DTL::IDNode*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_constdecls: // constdecls
      case symbol_kind::S_outstatements: // outstatements
      case symbol_kind::S_innernest: // innernest
      case symbol_kind::S_casestatement: // casestatement
        value.YY_MOVE_OR_COPY< std::vector<DTL::StmtNode*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_intlist: // intlist
        value.YY_MOVE_OR_COPY< std::vector<IntLitNode*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_casestatements: // casestatements
        value.YY_MOVE_OR_COPY< std::vector<std::vector<DTL::StmtNode*>> > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

#if 201103L <= YY_CPLUSPLUS
    // that is emptied.
    that.state = empty_state;
#endif
  }

  Parser::stack_symbol_type::stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) that)
    : super_type (s)
  {
    switch (that.kind ())
    {
      case symbol_kind::S_kernel: // kernel
        value.move< DTL::DTLKernelNode* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr: // expr
      case symbol_kind::S_term: // term
      case symbol_kind::S_factor: // factor
        value.move< DTL::ExpNode* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_forstatement: // forstatement
        value.move< DTL::ForStmtNode* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_activenode: // activenode
      case symbol_kind::S_id: // id
        value.move< DTL::IDNode* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_ID: // ID
        value.move< DTL::IDToken * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_backingphyssize: // backingphyssize
      case symbol_kind::S_intlit: // intlit
        value.move< DTL::IntLitNode* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_INTLITERAL: // INTLITERAL
        value.move< DTL::IntLitToken * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_loc: // loc
        value.move< DTL::LocNode* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_metadatastreamdecl: // metadatastreamdecl
        value.move< DTL::MetadataStreamDeclNode* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_program: // program
        value.move< DTL::ProgramNode* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_constdecl: // constdecl
      case symbol_kind::S_ifstatement: // ifstatement
      case symbol_kind::S_switchstatement: // switchstatement
      case symbol_kind::S_outstatement: // outstatement
      case symbol_kind::S_unarystmt: // unarystmt
        value.move< DTL::StmtNode* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_ASSIGN: // ASSIGN
      case symbol_kind::S_NOPT: // NOPT
      case symbol_kind::S_INT: // INT
      case symbol_kind::S_LCURLY: // LCURLY
      case symbol_kind::S_LESS: // LESS
      case symbol_kind::S_LESSEQUAL: // LESSEQUAL
      case symbol_kind::S_GREATER: // GREATER
      case symbol_kind::S_GREATEREQUAL: // GREATEREQUAL
      case symbol_kind::S_LPAREN: // LPAREN
      case symbol_kind::S_CROSS: // CROSS
      case symbol_kind::S_POSTINC: // POSTINC
      case symbol_kind::S_RCURLY: // RCURLY
      case symbol_kind::S_RPAREN: // RPAREN
      case symbol_kind::S_SEMICOL: // SEMICOL
      case symbol_kind::S_STAR: // STAR
      case symbol_kind::S_FOR: // FOR
      case symbol_kind::S_OUT: // OUT
      case symbol_kind::S_COMMA: // COMMA
      case symbol_kind::S_LBRACKET: // LBRACKET
      case symbol_kind::S_RBRACKET: // RBRACKET
      case symbol_kind::S_MINUS: // MINUS
      case symbol_kind::S_COLON: // COLON
      case symbol_kind::S_CASE: // CASE
      case symbol_kind::S_SWITCH: // SWITCH
      case symbol_kind::S_IF: // IF
      case symbol_kind::S_ELSE: // ELSE
      case symbol_kind::S_ISEVEN: // ISEVEN
      case symbol_kind::S_ISEDGE: // ISEDGE
      case symbol_kind::S_OR: // OR
      case symbol_kind::S_AND: // AND
      case symbol_kind::S_PAD: // PAD
      case symbol_kind::S_METADATASTREAM: // METADATASTREAM
      case symbol_kind::S_DTL: // DTL
      case symbol_kind::S_ACTIVE: // ACTIVE
        value.move< DTL::Token * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_transformgraph: // transformgraph
        value.move< DTL::TransformGraph* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_type: // type
        value.move< DTL::TypeNode* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_kernellist: // kernellist
        value.move< std::vector<DTL::DTLKernelNode*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_inputlistwrapper: // inputlistwrapper
      case symbol_kind::S_inputlist: // inputlist
        value.move< std::vector<DTL::IDNode*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_constdecls: // constdecls
      case symbol_kind::S_outstatements: // outstatements
      case symbol_kind::S_innernest: // innernest
      case symbol_kind::S_casestatement: // casestatement
        value.move< std::vector<DTL::StmtNode*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_intlist: // intlist
        value.move< std::vector<IntLitNode*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_casestatements: // casestatements
        value.move< std::vector<std::vector<DTL::StmtNode*>> > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

    // that is emptied.
    that.kind_ = symbol_kind::S_YYEMPTY;
  }

#if YY_CPLUSPLUS < 201103L
  Parser::stack_symbol_type&
  Parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    switch (that.kind ())
    {
      case symbol_kind::S_kernel: // kernel
        value.copy< DTL::DTLKernelNode* > (that.value);
        break;

      case symbol_kind::S_expr: // expr
      case symbol_kind::S_term: // term
      case symbol_kind::S_factor: // factor
        value.copy< DTL::ExpNode* > (that.value);
        break;

      case symbol_kind::S_forstatement: // forstatement
        value.copy< DTL::ForStmtNode* > (that.value);
        break;

      case symbol_kind::S_activenode: // activenode
      case symbol_kind::S_id: // id
        value.copy< DTL::IDNode* > (that.value);
        break;

      case symbol_kind::S_ID: // ID
        value.copy< DTL::IDToken * > (that.value);
        break;

      case symbol_kind::S_backingphyssize: // backingphyssize
      case symbol_kind::S_intlit: // intlit
        value.copy< DTL::IntLitNode* > (that.value);
        break;

      case symbol_kind::S_INTLITERAL: // INTLITERAL
        value.copy< DTL::IntLitToken * > (that.value);
        break;

      case symbol_kind::S_loc: // loc
        value.copy< DTL::LocNode* > (that.value);
        break;

      case symbol_kind::S_metadatastreamdecl: // metadatastreamdecl
        value.copy< DTL::MetadataStreamDeclNode* > (that.value);
        break;

      case symbol_kind::S_program: // program
        value.copy< DTL::ProgramNode* > (that.value);
        break;

      case symbol_kind::S_constdecl: // constdecl
      case symbol_kind::S_ifstatement: // ifstatement
      case symbol_kind::S_switchstatement: // switchstatement
      case symbol_kind::S_outstatement: // outstatement
      case symbol_kind::S_unarystmt: // unarystmt
        value.copy< DTL::StmtNode* > (that.value);
        break;

      case symbol_kind::S_ASSIGN: // ASSIGN
      case symbol_kind::S_NOPT: // NOPT
      case symbol_kind::S_INT: // INT
      case symbol_kind::S_LCURLY: // LCURLY
      case symbol_kind::S_LESS: // LESS
      case symbol_kind::S_LESSEQUAL: // LESSEQUAL
      case symbol_kind::S_GREATER: // GREATER
      case symbol_kind::S_GREATEREQUAL: // GREATEREQUAL
      case symbol_kind::S_LPAREN: // LPAREN
      case symbol_kind::S_CROSS: // CROSS
      case symbol_kind::S_POSTINC: // POSTINC
      case symbol_kind::S_RCURLY: // RCURLY
      case symbol_kind::S_RPAREN: // RPAREN
      case symbol_kind::S_SEMICOL: // SEMICOL
      case symbol_kind::S_STAR: // STAR
      case symbol_kind::S_FOR: // FOR
      case symbol_kind::S_OUT: // OUT
      case symbol_kind::S_COMMA: // COMMA
      case symbol_kind::S_LBRACKET: // LBRACKET
      case symbol_kind::S_RBRACKET: // RBRACKET
      case symbol_kind::S_MINUS: // MINUS
      case symbol_kind::S_COLON: // COLON
      case symbol_kind::S_CASE: // CASE
      case symbol_kind::S_SWITCH: // SWITCH
      case symbol_kind::S_IF: // IF
      case symbol_kind::S_ELSE: // ELSE
      case symbol_kind::S_ISEVEN: // ISEVEN
      case symbol_kind::S_ISEDGE: // ISEDGE
      case symbol_kind::S_OR: // OR
      case symbol_kind::S_AND: // AND
      case symbol_kind::S_PAD: // PAD
      case symbol_kind::S_METADATASTREAM: // METADATASTREAM
      case symbol_kind::S_DTL: // DTL
      case symbol_kind::S_ACTIVE: // ACTIVE
        value.copy< DTL::Token * > (that.value);
        break;

      case symbol_kind::S_transformgraph: // transformgraph
        value.copy< DTL::TransformGraph* > (that.value);
        break;

      case symbol_kind::S_type: // type
        value.copy< DTL::TypeNode* > (that.value);
        break;

      case symbol_kind::S_kernellist: // kernellist
        value.copy< std::vector<DTL::DTLKernelNode*> > (that.value);
        break;

      case symbol_kind::S_inputlistwrapper: // inputlistwrapper
      case symbol_kind::S_inputlist: // inputlist
        value.copy< std::vector<DTL::IDNode*> > (that.value);
        break;

      case symbol_kind::S_constdecls: // constdecls
      case symbol_kind::S_outstatements: // outstatements
      case symbol_kind::S_innernest: // innernest
      case symbol_kind::S_casestatement: // casestatement
        value.copy< std::vector<DTL::StmtNode*> > (that.value);
        break;

      case symbol_kind::S_intlist: // intlist
        value.copy< std::vector<IntLitNode*> > (that.value);
        break;

      case symbol_kind::S_casestatements: // casestatements
        value.copy< std::vector<std::vector<DTL::StmtNode*>> > (that.value);
        break;

      default:
        break;
    }

    return *this;
  }

  Parser::stack_symbol_type&
  Parser::stack_symbol_type::operator= (stack_symbol_type& that)
  {
    state = that.state;
    switch (that.kind ())
    {
      case symbol_kind::S_kernel: // kernel
        value.move< DTL::DTLKernelNode* > (that.value);
        break;

      case symbol_kind::S_expr: // expr
      case symbol_kind::S_term: // term
      case symbol_kind::S_factor: // factor
        value.move< DTL::ExpNode* > (that.value);
        break;

      case symbol_kind::S_forstatement: // forstatement
        value.move< DTL::ForStmtNode* > (that.value);
        break;

      case symbol_kind::S_activenode: // activenode
      case symbol_kind::S_id: // id
        value.move< DTL::IDNode* > (that.value);
        break;

      case symbol_kind::S_ID: // ID
        value.move< DTL::IDToken * > (that.value);
        break;

      case symbol_kind::S_backingphyssize: // backingphyssize
      case symbol_kind::S_intlit: // intlit
        value.move< DTL::IntLitNode* > (that.value);
        break;

      case symbol_kind::S_INTLITERAL: // INTLITERAL
        value.move< DTL::IntLitToken * > (that.value);
        break;

      case symbol_kind::S_loc: // loc
        value.move< DTL::LocNode* > (that.value);
        break;

      case symbol_kind::S_metadatastreamdecl: // metadatastreamdecl
        value.move< DTL::MetadataStreamDeclNode* > (that.value);
        break;

      case symbol_kind::S_program: // program
        value.move< DTL::ProgramNode* > (that.value);
        break;

      case symbol_kind::S_constdecl: // constdecl
      case symbol_kind::S_ifstatement: // ifstatement
      case symbol_kind::S_switchstatement: // switchstatement
      case symbol_kind::S_outstatement: // outstatement
      case symbol_kind::S_unarystmt: // unarystmt
        value.move< DTL::StmtNode* > (that.value);
        break;

      case symbol_kind::S_ASSIGN: // ASSIGN
      case symbol_kind::S_NOPT: // NOPT
      case symbol_kind::S_INT: // INT
      case symbol_kind::S_LCURLY: // LCURLY
      case symbol_kind::S_LESS: // LESS
      case symbol_kind::S_LESSEQUAL: // LESSEQUAL
      case symbol_kind::S_GREATER: // GREATER
      case symbol_kind::S_GREATEREQUAL: // GREATEREQUAL
      case symbol_kind::S_LPAREN: // LPAREN
      case symbol_kind::S_CROSS: // CROSS
      case symbol_kind::S_POSTINC: // POSTINC
      case symbol_kind::S_RCURLY: // RCURLY
      case symbol_kind::S_RPAREN: // RPAREN
      case symbol_kind::S_SEMICOL: // SEMICOL
      case symbol_kind::S_STAR: // STAR
      case symbol_kind::S_FOR: // FOR
      case symbol_kind::S_OUT: // OUT
      case symbol_kind::S_COMMA: // COMMA
      case symbol_kind::S_LBRACKET: // LBRACKET
      case symbol_kind::S_RBRACKET: // RBRACKET
      case symbol_kind::S_MINUS: // MINUS
      case symbol_kind::S_COLON: // COLON
      case symbol_kind::S_CASE: // CASE
      case symbol_kind::S_SWITCH: // SWITCH
      case symbol_kind::S_IF: // IF
      case symbol_kind::S_ELSE: // ELSE
      case symbol_kind::S_ISEVEN: // ISEVEN
      case symbol_kind::S_ISEDGE: // ISEDGE
      case symbol_kind::S_OR: // OR
      case symbol_kind::S_AND: // AND
      case symbol_kind::S_PAD: // PAD
      case symbol_kind::S_METADATASTREAM: // METADATASTREAM
      case symbol_kind::S_DTL: // DTL
      case symbol_kind::S_ACTIVE: // ACTIVE
        value.move< DTL::Token * > (that.value);
        break;

      case symbol_kind::S_transformgraph: // transformgraph
        value.move< DTL::TransformGraph* > (that.value);
        break;

      case symbol_kind::S_type: // type
        value.move< DTL::TypeNode* > (that.value);
        break;

      case symbol_kind::S_kernellist: // kernellist
        value.move< std::vector<DTL::DTLKernelNode*> > (that.value);
        break;

      case symbol_kind::S_inputlistwrapper: // inputlistwrapper
      case symbol_kind::S_inputlist: // inputlist
        value.move< std::vector<DTL::IDNode*> > (that.value);
        break;

      case symbol_kind::S_constdecls: // constdecls
      case symbol_kind::S_outstatements: // outstatements
      case symbol_kind::S_innernest: // innernest
      case symbol_kind::S_casestatement: // casestatement
        value.move< std::vector<DTL::StmtNode*> > (that.value);
        break;

      case symbol_kind::S_intlist: // intlist
        value.move< std::vector<IntLitNode*> > (that.value);
        break;

      case symbol_kind::S_casestatements: // casestatements
        value.move< std::vector<std::vector<DTL::StmtNode*>> > (that.value);
        break;

      default:
        break;
    }

    // that is emptied.
    that.state = empty_state;
    return *this;
  }
#endif

  template <typename Base>
  void
  Parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if YYDEBUG
  template <typename Base>
  void
  Parser::yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YY_USE (yyoutput);
    if (yysym.empty ())
      yyo << "empty symbol";
    else
      {
        symbol_kind_type yykind = yysym.kind ();
        yyo << (yykind < YYNTOKENS ? "token" : "nterm")
            << ' ' << yysym.name () << " (";
        YY_USE (yykind);
        yyo << ')';
      }
  }
#endif

  void
  Parser::yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym)
  {
    if (m)
      YY_SYMBOL_PRINT (m, sym);
    yystack_.push (YY_MOVE (sym));
  }

  void
  Parser::yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym)
  {
#if 201103L <= YY_CPLUSPLUS
    yypush_ (m, stack_symbol_type (s, std::move (sym)));
#else
    stack_symbol_type ss (s, sym);
    yypush_ (m, ss);
#endif
  }

  void
  Parser::yypop_ (int n) YY_NOEXCEPT
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  Parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  Parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  Parser::debug_level_type
  Parser::debug_level () const
  {
    return yydebug_;
  }

  void
  Parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  Parser::state_type
  Parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - YYNTOKENS] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - YYNTOKENS];
  }

  bool
  Parser::yy_pact_value_is_default_ (int yyvalue) YY_NOEXCEPT
  {
    return yyvalue == yypact_ninf_;
  }

  bool
  Parser::yy_table_value_is_error_ (int yyvalue) YY_NOEXCEPT
  {
    return yyvalue == yytable_ninf_;
  }

  int
  Parser::operator() ()
  {
    return parse ();
  }

  int
  Parser::parse ()
  {
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The return value of parse ().
    int yyresult;

#if YY_EXCEPTIONS
    try
#endif // YY_EXCEPTIONS
      {
    YYCDEBUG << "Starting parse\n";


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, YY_MOVE (yyla));

  /*-----------------------------------------------.
  | yynewstate -- push a new symbol on the stack.  |
  `-----------------------------------------------*/
  yynewstate:
    YYCDEBUG << "Entering state " << int (yystack_[0].state) << '\n';
    YY_STACK_PRINT ();

    // Accept?
    if (yystack_[0].state == yyfinal_)
      YYACCEPT;

    goto yybackup;


  /*-----------.
  | yybackup.  |
  `-----------*/
  yybackup:
    // Try to take a decision without lookahead.
    yyn = yypact_[+yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token\n";
#if YY_EXCEPTIONS
        try
#endif // YY_EXCEPTIONS
          {
            yyla.kind_ = yytranslate_ (yylex (&yyla.value));
          }
#if YY_EXCEPTIONS
        catch (const syntax_error& yyexc)
          {
            YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
            error (yyexc);
            goto yyerrlab1;
          }
#endif // YY_EXCEPTIONS
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    if (yyla.kind () == symbol_kind::S_YYerror)
    {
      // The scanner already issued an error message, process directly
      // to error recovery.  But do not keep the error token as
      // lookahead, it is too special and may lead us to an endless
      // loop in error recovery. */
      yyla.kind_ = symbol_kind::S_YYUNDEF;
      goto yyerrlab1;
    }

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.kind ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.kind ())
      {
        goto yydefault;
      }

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
      }

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", state_type (yyn), YY_MOVE (yyla));
    goto yynewstate;


  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[+yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;


  /*-----------------------------.
  | yyreduce -- do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_ (yystack_[yylen].state, yyr1_[yyn]);
      /* Variants are always initialized to an empty instance of the
         correct type. The default '$$ = $1' action is NOT applied
         when using variants.  */
      switch (yyr1_[yyn])
    {
      case symbol_kind::S_kernel: // kernel
        yylhs.value.emplace< DTL::DTLKernelNode* > ();
        break;

      case symbol_kind::S_expr: // expr
      case symbol_kind::S_term: // term
      case symbol_kind::S_factor: // factor
        yylhs.value.emplace< DTL::ExpNode* > ();
        break;

      case symbol_kind::S_forstatement: // forstatement
        yylhs.value.emplace< DTL::ForStmtNode* > ();
        break;

      case symbol_kind::S_activenode: // activenode
      case symbol_kind::S_id: // id
        yylhs.value.emplace< DTL::IDNode* > ();
        break;

      case symbol_kind::S_ID: // ID
        yylhs.value.emplace< DTL::IDToken * > ();
        break;

      case symbol_kind::S_backingphyssize: // backingphyssize
      case symbol_kind::S_intlit: // intlit
        yylhs.value.emplace< DTL::IntLitNode* > ();
        break;

      case symbol_kind::S_INTLITERAL: // INTLITERAL
        yylhs.value.emplace< DTL::IntLitToken * > ();
        break;

      case symbol_kind::S_loc: // loc
        yylhs.value.emplace< DTL::LocNode* > ();
        break;

      case symbol_kind::S_metadatastreamdecl: // metadatastreamdecl
        yylhs.value.emplace< DTL::MetadataStreamDeclNode* > ();
        break;

      case symbol_kind::S_program: // program
        yylhs.value.emplace< DTL::ProgramNode* > ();
        break;

      case symbol_kind::S_constdecl: // constdecl
      case symbol_kind::S_ifstatement: // ifstatement
      case symbol_kind::S_switchstatement: // switchstatement
      case symbol_kind::S_outstatement: // outstatement
      case symbol_kind::S_unarystmt: // unarystmt
        yylhs.value.emplace< DTL::StmtNode* > ();
        break;

      case symbol_kind::S_ASSIGN: // ASSIGN
      case symbol_kind::S_NOPT: // NOPT
      case symbol_kind::S_INT: // INT
      case symbol_kind::S_LCURLY: // LCURLY
      case symbol_kind::S_LESS: // LESS
      case symbol_kind::S_LESSEQUAL: // LESSEQUAL
      case symbol_kind::S_GREATER: // GREATER
      case symbol_kind::S_GREATEREQUAL: // GREATEREQUAL
      case symbol_kind::S_LPAREN: // LPAREN
      case symbol_kind::S_CROSS: // CROSS
      case symbol_kind::S_POSTINC: // POSTINC
      case symbol_kind::S_RCURLY: // RCURLY
      case symbol_kind::S_RPAREN: // RPAREN
      case symbol_kind::S_SEMICOL: // SEMICOL
      case symbol_kind::S_STAR: // STAR
      case symbol_kind::S_FOR: // FOR
      case symbol_kind::S_OUT: // OUT
      case symbol_kind::S_COMMA: // COMMA
      case symbol_kind::S_LBRACKET: // LBRACKET
      case symbol_kind::S_RBRACKET: // RBRACKET
      case symbol_kind::S_MINUS: // MINUS
      case symbol_kind::S_COLON: // COLON
      case symbol_kind::S_CASE: // CASE
      case symbol_kind::S_SWITCH: // SWITCH
      case symbol_kind::S_IF: // IF
      case symbol_kind::S_ELSE: // ELSE
      case symbol_kind::S_ISEVEN: // ISEVEN
      case symbol_kind::S_ISEDGE: // ISEDGE
      case symbol_kind::S_OR: // OR
      case symbol_kind::S_AND: // AND
      case symbol_kind::S_PAD: // PAD
      case symbol_kind::S_METADATASTREAM: // METADATASTREAM
      case symbol_kind::S_DTL: // DTL
      case symbol_kind::S_ACTIVE: // ACTIVE
        yylhs.value.emplace< DTL::Token * > ();
        break;

      case symbol_kind::S_transformgraph: // transformgraph
        yylhs.value.emplace< DTL::TransformGraph* > ();
        break;

      case symbol_kind::S_type: // type
        yylhs.value.emplace< DTL::TypeNode* > ();
        break;

      case symbol_kind::S_kernellist: // kernellist
        yylhs.value.emplace< std::vector<DTL::DTLKernelNode*> > ();
        break;

      case symbol_kind::S_inputlistwrapper: // inputlistwrapper
      case symbol_kind::S_inputlist: // inputlist
        yylhs.value.emplace< std::vector<DTL::IDNode*> > ();
        break;

      case symbol_kind::S_constdecls: // constdecls
      case symbol_kind::S_outstatements: // outstatements
      case symbol_kind::S_innernest: // innernest
      case symbol_kind::S_casestatement: // casestatement
        yylhs.value.emplace< std::vector<DTL::StmtNode*> > ();
        break;

      case symbol_kind::S_intlist: // intlist
        yylhs.value.emplace< std::vector<IntLitNode*> > ();
        break;

      case symbol_kind::S_casestatements: // casestatements
        yylhs.value.emplace< std::vector<std::vector<DTL::StmtNode*>> > ();
        break;

      default:
        break;
    }



      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
#if YY_EXCEPTIONS
      try
#endif // YY_EXCEPTIONS
        {
          switch (yyn)
            {
  case 2: // transformgraph: kernellist activenode
#line 135 "parser.yy"
        {
            yylhs.value.as < DTL::TransformGraph* > () = new TransformGraph(yystack_[1].value.as < std::vector<DTL::DTLKernelNode*> > (), yystack_[0].value.as < DTL::IDNode* > ());
            *root = yylhs.value.as < DTL::TransformGraph* > ();
        }
#line 1467 "parser.cc"
    break;

  case 3: // activenode: ACTIVE id SEMICOL
#line 141 "parser.yy"
        {
            yylhs.value.as < DTL::IDNode* > () = yystack_[1].value.as < DTL::IDNode* > ();
        }
#line 1475 "parser.cc"
    break;

  case 4: // kernellist: kernel kernellist
#line 146 "parser.yy"
        {
            yylhs.value.as < std::vector<DTL::DTLKernelNode*> > () = std::vector<DTL::DTLKernelNode*>();
            yylhs.value.as < std::vector<DTL::DTLKernelNode*> > ().push_back(yystack_[1].value.as < DTL::DTLKernelNode* > ());
            yylhs.value.as < std::vector<DTL::DTLKernelNode*> > ().insert(yylhs.value.as < std::vector<DTL::DTLKernelNode*> > ().end(), yystack_[0].value.as < std::vector<DTL::DTLKernelNode*> > ().begin(), yystack_[0].value.as < std::vector<DTL::DTLKernelNode*> > ().end());
        }
#line 1485 "parser.cc"
    break;

  case 5: // kernellist: %empty
#line 152 "parser.yy"
        {
            yylhs.value.as < std::vector<DTL::DTLKernelNode*> > () = std::vector<DTL::DTLKernelNode*>();
        }
#line 1493 "parser.cc"
    break;

  case 6: // kernel: DTL backingphyssize id inputlistwrapper ASSIGN LCURLY program RCURLY
#line 158 "parser.yy"
        {
            yylhs.value.as < DTL::DTLKernelNode* > () = new DTLKernelNode(yystack_[5].value.as < DTL::IDNode* > (), yystack_[4].value.as < std::vector<DTL::IDNode*> > (), yystack_[1].value.as < DTL::ProgramNode* > (), yystack_[6].value.as < DTL::IntLitNode* > ());
        }
#line 1501 "parser.cc"
    break;

  case 7: // backingphyssize: LESS intlit GREATER
#line 163 "parser.yy"
        {
            yylhs.value.as < DTL::IntLitNode* > () = yystack_[1].value.as < DTL::IntLitNode* > ();
        }
#line 1509 "parser.cc"
    break;

  case 8: // inputlistwrapper: COLON inputlist
#line 168 "parser.yy"
        {
            yylhs.value.as < std::vector<DTL::IDNode*> > () = yystack_[0].value.as < std::vector<DTL::IDNode*> > ();
        }
#line 1517 "parser.cc"
    break;

  case 9: // inputlistwrapper: %empty
#line 172 "parser.yy"
        {
            yylhs.value.as < std::vector<DTL::IDNode*> > () = std::vector<IDNode*>();
        }
#line 1525 "parser.cc"
    break;

  case 10: // inputlist: id COMMA inputlist
#line 177 "parser.yy"
        {
            yylhs.value.as < std::vector<DTL::IDNode*> > () = std::vector<IDNode*>();
            yylhs.value.as < std::vector<DTL::IDNode*> > ().push_back(yystack_[2].value.as < DTL::IDNode* > ());
            yylhs.value.as < std::vector<DTL::IDNode*> > ().insert(yylhs.value.as < std::vector<DTL::IDNode*> > ().end(), yystack_[0].value.as < std::vector<DTL::IDNode*> > ().begin(), yystack_[0].value.as < std::vector<DTL::IDNode*> > ().end());
        }
#line 1535 "parser.cc"
    break;

  case 11: // inputlist: id
#line 183 "parser.yy"
        {
            yylhs.value.as < std::vector<DTL::IDNode*> > () = std::vector<IDNode*>();
            yylhs.value.as < std::vector<DTL::IDNode*> > ().push_back(yystack_[0].value.as < DTL::IDNode* > ());
        }
#line 1544 "parser.cc"
    break;

  case 12: // program: constdecls forstatement
#line 190 "parser.yy"
        {
            yystack_[1].value.as < std::vector<DTL::StmtNode*> > ().push_back(yystack_[0].value.as < DTL::ForStmtNode* > ());
            yylhs.value.as < DTL::ProgramNode* > () = new ProgramNode(yystack_[1].value.as < std::vector<DTL::StmtNode*> > ());
  
        }
#line 1554 "parser.cc"
    break;

  case 13: // constdecls: constdecls constdecl
#line 196 "parser.yy"
        {
            yystack_[1].value.as < std::vector<DTL::StmtNode*> > ().push_back(yystack_[0].value.as < DTL::StmtNode* > ());
            yylhs.value.as < std::vector<DTL::StmtNode*> > () = yystack_[1].value.as < std::vector<DTL::StmtNode*> > ();
        }
#line 1563 "parser.cc"
    break;

  case 14: // constdecls: constdecls metadatastreamdecl
#line 201 "parser.yy"
        {
            yystack_[1].value.as < std::vector<DTL::StmtNode*> > ().push_back(yystack_[0].value.as < DTL::MetadataStreamDeclNode* > ());
            yylhs.value.as < std::vector<DTL::StmtNode*> > () = yystack_[1].value.as < std::vector<DTL::StmtNode*> > ();
        }
#line 1572 "parser.cc"
    break;

  case 15: // constdecls: %empty
#line 206 "parser.yy"
        {
            auto ret = std::vector<DTL::StmtNode*>();
            yylhs.value.as < std::vector<DTL::StmtNode*> > () = ret;
        }
#line 1581 "parser.cc"
    break;

  case 16: // metadatastreamdecl: METADATASTREAM LESS intlit COMMA intlit GREATER id SEMICOL
#line 212 "parser.yy"
        {
            const Position * p = new Position(yystack_[7].value.as < DTL::Token * > ()->pos(), yystack_[0].value.as < DTL::Token * > ()->pos());
            yylhs.value.as < DTL::MetadataStreamDeclNode* > () = new MetadataStreamDeclNode(p, new MetadataStreamTypeNode(yystack_[7].value.as < DTL::Token * > ()->pos()), yystack_[1].value.as < DTL::IDNode* > (), yystack_[5].value.as < DTL::IntLitNode* > (), yystack_[3].value.as < DTL::IntLitNode* > ());
        }
#line 1590 "parser.cc"
    break;

  case 17: // metadatastreamdecl: METADATASTREAM LESS intlit COMMA id GREATER id SEMICOL
#line 217 "parser.yy"
        {
            const Position * p = new Position(yystack_[7].value.as < DTL::Token * > ()->pos(), yystack_[0].value.as < DTL::Token * > ()->pos());
            yylhs.value.as < DTL::MetadataStreamDeclNode* > () = new MetadataStreamDeclNode(p, new MetadataStreamTypeNode(yystack_[7].value.as < DTL::Token * > ()->pos()), yystack_[1].value.as < DTL::IDNode* > (), yystack_[5].value.as < DTL::IntLitNode* > (), yystack_[3].value.as < DTL::IDNode* > ());
        }
#line 1599 "parser.cc"
    break;

  case 18: // constdecl: type id ASSIGN intlit SEMICOL
#line 223 "parser.yy"
        {
            const Position * p = new Position(yystack_[4].value.as < DTL::TypeNode* > ()->pos(), yystack_[0].value.as < DTL::Token * > ()->pos());
            yylhs.value.as < DTL::StmtNode* > () = new ConstDeclNode(p, yystack_[4].value.as < DTL::TypeNode* > (), yystack_[3].value.as < DTL::IDNode* > (), yystack_[1].value.as < DTL::IntLitNode* > ());
        }
#line 1608 "parser.cc"
    break;

  case 19: // constdecl: NOPT type id ASSIGN intlit SEMICOL
#line 228 "parser.yy"
        {
            const Position * p = new Position(yystack_[4].value.as < DTL::TypeNode* > ()->pos(), yystack_[0].value.as < DTL::Token * > ()->pos());
            auto decl = new ConstDeclNode(p, yystack_[4].value.as < DTL::TypeNode* > (), yystack_[3].value.as < DTL::IDNode* > (), yystack_[1].value.as < DTL::IntLitNode* > ());
            decl->SetOpt(false);
            yylhs.value.as < DTL::StmtNode* > () = decl;
        }
#line 1619 "parser.cc"
    break;

  case 20: // constdecl: type id ASSIGN LCURLY intlist RCURLY SEMICOL
#line 235 "parser.yy"
        {
             const Position * p = new Position(yystack_[6].value.as < DTL::TypeNode* > ()->pos(), yystack_[1].value.as < DTL::Token * > ()->pos());
            yylhs.value.as < DTL::StmtNode* > () = new ConstArrayDeclNode(yystack_[6].value.as < DTL::TypeNode* > ()->pos(), yystack_[6].value.as < DTL::TypeNode* > (), yystack_[5].value.as < DTL::IDNode* > (), yystack_[2].value.as < std::vector<IntLitNode*> > ());
        }
#line 1628 "parser.cc"
    break;

  case 21: // intlist: intlit COMMA intlist
#line 242 "parser.yy"
        {
            yylhs.value.as < std::vector<IntLitNode*> > () = std::vector<DTL::IntLitNode*>();
            yylhs.value.as < std::vector<IntLitNode*> > ().push_back(yystack_[2].value.as < DTL::IntLitNode* > ());
            yylhs.value.as < std::vector<IntLitNode*> > ().insert(yylhs.value.as < std::vector<IntLitNode*> > ().end(), yystack_[0].value.as < std::vector<IntLitNode*> > ().begin(), yystack_[0].value.as < std::vector<IntLitNode*> > ().end());
        }
#line 1638 "parser.cc"
    break;

  case 22: // intlist: intlit
#line 248 "parser.yy"
        {
            yylhs.value.as < std::vector<IntLitNode*> > () = std::vector<DTL::IntLitNode*>();
            yylhs.value.as < std::vector<IntLitNode*> > ().push_back(yystack_[0].value.as < DTL::IntLitNode* > ());
        }
#line 1647 "parser.cc"
    break;

  case 23: // intlist: %empty
#line 253 "parser.yy"
        {
            yylhs.value.as < std::vector<IntLitNode*> > () = std::vector<DTL::IntLitNode*>();
        }
#line 1655 "parser.cc"
    break;

  case 24: // forstatement: FOR LPAREN constdecl expr SEMICOL unarystmt RPAREN LCURLY forstatement RCURLY
#line 260 "parser.yy"
        {
            const Position * p = new Position(yystack_[9].value.as < DTL::Token * > ()->pos(), yystack_[0].value.as < DTL::Token * > ()->pos());
            std::vector<StmtNode*> stmt_vec;
            stmt_vec.push_back(yystack_[1].value.as < DTL::ForStmtNode* > ());
            yylhs.value.as < DTL::ForStmtNode* > () = new ForStmtNode(p, yystack_[7].value.as < DTL::StmtNode* > (), yystack_[6].value.as < DTL::ExpNode* > (), yystack_[4].value.as < DTL::StmtNode* > (), stmt_vec);

        }
#line 1667 "parser.cc"
    break;

  case 25: // forstatement: FOR LPAREN constdecl expr SEMICOL unarystmt RPAREN LCURLY innernest RCURLY
#line 268 "parser.yy"
        {
            const Position * p = new Position(yystack_[9].value.as < DTL::Token * > ()->pos(), yystack_[0].value.as < DTL::Token * > ()->pos());
            yylhs.value.as < DTL::ForStmtNode* > () = new ForStmtNode(p, yystack_[7].value.as < DTL::StmtNode* > (), yystack_[6].value.as < DTL::ExpNode* > (), yystack_[4].value.as < DTL::StmtNode* > (), yystack_[1].value.as < std::vector<DTL::StmtNode*> > ());
        }
#line 1676 "parser.cc"
    break;

  case 26: // outstatements: outstatements outstatement
#line 273 "parser.yy"
        {
            yystack_[1].value.as < std::vector<DTL::StmtNode*> > ().push_back(yystack_[0].value.as < DTL::StmtNode* > ());
            yylhs.value.as < std::vector<DTL::StmtNode*> > () = yystack_[1].value.as < std::vector<DTL::StmtNode*> > ();
        }
#line 1685 "parser.cc"
    break;

  case 27: // outstatements: outstatement
#line 278 "parser.yy"
        {
            std::vector<StmtNode*> stmt_vec;
            stmt_vec.push_back(yystack_[0].value.as < DTL::StmtNode* > ());
            yylhs.value.as < std::vector<DTL::StmtNode*> > () = stmt_vec;
        }
#line 1695 "parser.cc"
    break;

  case 28: // innernest: outstatements
#line 286 "parser.yy"
    {
        yylhs.value.as < std::vector<DTL::StmtNode*> > () = yystack_[0].value.as < std::vector<DTL::StmtNode*> > ();
    }
#line 1703 "parser.cc"
    break;

  case 29: // innernest: ifstatement
#line 290 "parser.yy"
    {
        yylhs.value.as < std::vector<DTL::StmtNode*> > () = {yystack_[0].value.as < DTL::StmtNode* > ()};
    }
#line 1711 "parser.cc"
    break;

  case 30: // innernest: switchstatement
#line 294 "parser.yy"
    {
        yylhs.value.as < std::vector<DTL::StmtNode*> > () = {yystack_[0].value.as < DTL::StmtNode* > ()};
    }
#line 1719 "parser.cc"
    break;

  case 31: // ifstatement: IF LPAREN ISEVEN id RPAREN LCURLY outstatements RCURLY ELSE LCURLY outstatements RCURLY
#line 299 "parser.yy"
        {
            yylhs.value.as < DTL::StmtNode* > () = new IfStmtNode(yystack_[11].value.as < DTL::Token * > ()->pos(), std::vector<IDNode*>{yystack_[8].value.as < DTL::IDNode* > ()}, yystack_[5].value.as < std::vector<DTL::StmtNode*> > (), yystack_[1].value.as < std::vector<DTL::StmtNode*> > (), IFSTMTTYPE::IS_EVEN);
        }
#line 1727 "parser.cc"
    break;

  case 32: // ifstatement: IF LPAREN id LESS id RPAREN LCURLY outstatements RCURLY ELSE LCURLY outstatements RCURLY
#line 303 "parser.yy"
        {
            yylhs.value.as < DTL::StmtNode* > () = new IfStmtNode(yystack_[12].value.as < DTL::Token * > ()->pos(), std::vector<IDNode*>{yystack_[10].value.as < DTL::IDNode* > (),yystack_[8].value.as < DTL::IDNode* > ()}, yystack_[5].value.as < std::vector<DTL::StmtNode*> > (), yystack_[1].value.as < std::vector<DTL::StmtNode*> > (), IFSTMTTYPE::LT);
        }
#line 1735 "parser.cc"
    break;

  case 33: // ifstatement: IF LPAREN id LESSEQUAL id RPAREN LCURLY outstatements RCURLY ELSE LCURLY outstatements RCURLY
#line 307 "parser.yy"
        {
            yylhs.value.as < DTL::StmtNode* > () = new IfStmtNode(yystack_[12].value.as < DTL::Token * > ()->pos(), std::vector<IDNode*>{yystack_[10].value.as < DTL::IDNode* > (),yystack_[8].value.as < DTL::IDNode* > ()}, yystack_[5].value.as < std::vector<DTL::StmtNode*> > (), yystack_[1].value.as < std::vector<DTL::StmtNode*> > (), IFSTMTTYPE::LTE);
        }
#line 1743 "parser.cc"
    break;

  case 34: // ifstatement: IF LPAREN id GREATER id RPAREN LCURLY outstatements RCURLY ELSE LCURLY outstatements RCURLY
#line 311 "parser.yy"
        {
            yylhs.value.as < DTL::StmtNode* > () = new IfStmtNode(yystack_[12].value.as < DTL::Token * > ()->pos(), std::vector<IDNode*>{yystack_[10].value.as < DTL::IDNode* > (),yystack_[8].value.as < DTL::IDNode* > ()}, yystack_[5].value.as < std::vector<DTL::StmtNode*> > (), yystack_[1].value.as < std::vector<DTL::StmtNode*> > (), IFSTMTTYPE::GT);
        }
#line 1751 "parser.cc"
    break;

  case 35: // ifstatement: IF LPAREN id GREATEREQUAL id RPAREN LCURLY outstatements RCURLY ELSE LCURLY outstatements RCURLY
#line 315 "parser.yy"
        {
            yylhs.value.as < DTL::StmtNode* > () = new IfStmtNode(yystack_[12].value.as < DTL::Token * > ()->pos(), std::vector<IDNode*>{yystack_[10].value.as < DTL::IDNode* > (),yystack_[8].value.as < DTL::IDNode* > ()}, yystack_[5].value.as < std::vector<DTL::StmtNode*> > (), yystack_[1].value.as < std::vector<DTL::StmtNode*> > (), IFSTMTTYPE::GTE);
        }
#line 1759 "parser.cc"
    break;

  case 36: // ifstatement: IF LPAREN ISEDGE id RPAREN LCURLY outstatements RCURLY ELSE LCURLY outstatements RCURLY
#line 319 "parser.yy"
        {
            yylhs.value.as < DTL::StmtNode* > () = new IfStmtNode(yystack_[11].value.as < DTL::Token * > ()->pos(), std::vector<IDNode*>{yystack_[8].value.as < DTL::IDNode* > ()}, yystack_[5].value.as < std::vector<DTL::StmtNode*> > (),  yystack_[1].value.as < std::vector<DTL::StmtNode*> > (), IFSTMTTYPE::EDGE);
        }
#line 1767 "parser.cc"
    break;

  case 37: // ifstatement: IF LPAREN ISEDGE id OR ISEDGE id RPAREN LCURLY outstatements RCURLY ELSE LCURLY outstatements RCURLY
#line 323 "parser.yy"
        {
            yylhs.value.as < DTL::StmtNode* > () = new IfStmtNode(yystack_[14].value.as < DTL::Token * > ()->pos(), std::vector<IDNode*>{yystack_[11].value.as < DTL::IDNode* > (),yystack_[8].value.as < DTL::IDNode* > ()}, yystack_[5].value.as < std::vector<DTL::StmtNode*> > (), yystack_[1].value.as < std::vector<DTL::StmtNode*> > (), IFSTMTTYPE::EDGE2OR);
        }
#line 1775 "parser.cc"
    break;

  case 38: // ifstatement: IF LPAREN ISEDGE id AND ISEDGE id RPAREN LCURLY outstatements RCURLY ELSE LCURLY outstatements RCURLY
#line 327 "parser.yy"
        {
            yylhs.value.as < DTL::StmtNode* > () = new IfStmtNode(yystack_[14].value.as < DTL::Token * > ()->pos(), std::vector<IDNode*>{yystack_[11].value.as < DTL::IDNode* > (),yystack_[8].value.as < DTL::IDNode* > ()}, yystack_[5].value.as < std::vector<DTL::StmtNode*> > (), yystack_[1].value.as < std::vector<DTL::StmtNode*> > (), IFSTMTTYPE::EDGE2AND);
        }
#line 1783 "parser.cc"
    break;

  case 39: // ifstatement: IF LPAREN PAD id id id id RPAREN LCURLY outstatements RCURLY ELSE LCURLY outstatements RCURLY
#line 331 "parser.yy"
        {
            std::vector<IDNode*> ids = {yystack_[11].value.as < DTL::IDNode* > (), yystack_[10].value.as < DTL::IDNode* > (), yystack_[9].value.as < DTL::IDNode* > (), yystack_[8].value.as < DTL::IDNode* > ()};
            yylhs.value.as < DTL::StmtNode* > () = new IfStmtNode(yystack_[14].value.as < DTL::Token * > ()->pos(), ids, yystack_[5].value.as < std::vector<DTL::StmtNode*> > (), yystack_[1].value.as < std::vector<DTL::StmtNode*> > (), IFSTMTTYPE::PAD);
        }
#line 1792 "parser.cc"
    break;

  case 40: // switchstatement: SWITCH LPAREN id RPAREN LCURLY casestatements RCURLY
#line 343 "parser.yy"
        {
            std::reverse(yystack_[1].value.as < std::vector<std::vector<DTL::StmtNode*>> > ().begin(), yystack_[1].value.as < std::vector<std::vector<DTL::StmtNode*>> > ().end());
            yylhs.value.as < DTL::StmtNode* > () = new SwitchStmtNode(yystack_[6].value.as < DTL::Token * > ()->pos(), yystack_[4].value.as < DTL::IDNode* > (), yystack_[1].value.as < std::vector<std::vector<DTL::StmtNode*>> > ());
        }
#line 1801 "parser.cc"
    break;

  case 41: // casestatements: casestatement casestatements
#line 350 "parser.yy"
    {    
        yystack_[0].value.as < std::vector<std::vector<DTL::StmtNode*>> > ().push_back(yystack_[1].value.as < std::vector<DTL::StmtNode*> > ());
        yylhs.value.as < std::vector<std::vector<DTL::StmtNode*>> > () = yystack_[0].value.as < std::vector<std::vector<DTL::StmtNode*>> > ();
    }
#line 1810 "parser.cc"
    break;

  case 42: // casestatements: casestatement
#line 355 "parser.yy"
    {
        yylhs.value.as < std::vector<std::vector<DTL::StmtNode*>> > () = {yystack_[0].value.as < std::vector<DTL::StmtNode*> > ()};
    }
#line 1818 "parser.cc"
    break;

  case 43: // casestatement: CASE COLON outstatements
#line 360 "parser.yy"
    {
        yylhs.value.as < std::vector<DTL::StmtNode*> > () = yystack_[0].value.as < std::vector<DTL::StmtNode*> > ();
    }
#line 1826 "parser.cc"
    break;

  case 44: // outstatement: OUT ASSIGN expr SEMICOL
#line 367 "parser.yy"
            {
                const Position * p = new Position(yystack_[3].value.as < DTL::Token * > ()->pos(), yystack_[0].value.as < DTL::Token * > ()->pos());
                yylhs.value.as < DTL::StmtNode* > () = new OutStmtNode(p, yystack_[1].value.as < DTL::ExpNode* > ());
            }
#line 1835 "parser.cc"
    break;

  case 45: // type: INT
#line 373 "parser.yy"
    {
        yylhs.value.as < DTL::TypeNode* > () = new IntTypeNode(yystack_[0].value.as < DTL::Token * > ()->pos());
    }
#line 1843 "parser.cc"
    break;

  case 46: // expr: expr CROSS expr
#line 377 "parser.yy"
    {
        const Position * p = new Position(yystack_[2].value.as < DTL::ExpNode* > ()->pos(), yystack_[0].value.as < DTL::ExpNode* > ()->pos());
        yylhs.value.as < DTL::ExpNode* > () = new PlusNode(p, yystack_[2].value.as < DTL::ExpNode* > (), yystack_[0].value.as < DTL::ExpNode* > ());
    }
#line 1852 "parser.cc"
    break;

  case 47: // expr: expr LESS expr
#line 382 "parser.yy"
    {
        const Position * p = new Position(yystack_[2].value.as < DTL::ExpNode* > ()->pos(), yystack_[0].value.as < DTL::ExpNode* > ()->pos());
        yylhs.value.as < DTL::ExpNode* > () = new LessNode(p, yystack_[2].value.as < DTL::ExpNode* > (), yystack_[0].value.as < DTL::ExpNode* > ());
    }
#line 1861 "parser.cc"
    break;

  case 48: // expr: expr STAR expr
#line 387 "parser.yy"
    {
        const Position * p = new Position(yystack_[2].value.as < DTL::ExpNode* > ()->pos(), yystack_[0].value.as < DTL::ExpNode* > ()->pos());
        yylhs.value.as < DTL::ExpNode* > () = new TimesNode(p, yystack_[2].value.as < DTL::ExpNode* > (), yystack_[0].value.as < DTL::ExpNode* > ());
    }
#line 1870 "parser.cc"
    break;

  case 49: // expr: expr MINUS expr
#line 392 "parser.yy"
    {
        const Position * p = new Position(yystack_[2].value.as < DTL::ExpNode* > ()->pos(), yystack_[0].value.as < DTL::ExpNode* > ()->pos());
        yylhs.value.as < DTL::ExpNode* > () = new MinusNode(p, yystack_[2].value.as < DTL::ExpNode* > (), yystack_[0].value.as < DTL::ExpNode* > ());
    }
#line 1879 "parser.cc"
    break;

  case 50: // expr: term
#line 397 "parser.yy"
    {
        yylhs.value.as < DTL::ExpNode* > () = yystack_[0].value.as < DTL::ExpNode* > ();
    }
#line 1887 "parser.cc"
    break;

  case 51: // unarystmt: loc POSTINC
#line 402 "parser.yy"
        {
            const Position* p = new Position(yystack_[1].value.as < DTL::LocNode* > ()->pos(), yystack_[0].value.as < DTL::Token * > ()->pos());
            yylhs.value.as < DTL::StmtNode* > () = new PostIncStmtNode(p, yystack_[1].value.as < DTL::LocNode* > ());
        }
#line 1896 "parser.cc"
    break;

  case 52: // term: factor
#line 410 "parser.yy"
    {
        yylhs.value.as < DTL::ExpNode* > () = yystack_[0].value.as < DTL::ExpNode* > ();
    }
#line 1904 "parser.cc"
    break;

  case 53: // term: LPAREN expr RPAREN
#line 414 "parser.yy"
    {
        yylhs.value.as < DTL::ExpNode* > () = yystack_[1].value.as < DTL::ExpNode* > ();
    }
#line 1912 "parser.cc"
    break;

  case 54: // factor: intlit
#line 418 "parser.yy"
    {
        yylhs.value.as < DTL::ExpNode* > () = yystack_[0].value.as < DTL::IntLitNode* > ();
    }
#line 1920 "parser.cc"
    break;

  case 55: // factor: loc
#line 422 "parser.yy"
    {
        yylhs.value.as < DTL::ExpNode* > () = yystack_[0].value.as < DTL::LocNode* > ();
    }
#line 1928 "parser.cc"
    break;

  case 56: // intlit: INTLITERAL
#line 426 "parser.yy"
    {
        yylhs.value.as < DTL::IntLitNode* > () = new IntLitNode(yystack_[0].value.as < DTL::IntLitToken * > ()->pos(), yystack_[0].value.as < DTL::IntLitToken * > ()->num());
    }
#line 1936 "parser.cc"
    break;

  case 57: // loc: id
#line 431 "parser.yy"
    {
        yylhs.value.as < DTL::LocNode* > () = yystack_[0].value.as < DTL::IDNode* > ();
    }
#line 1944 "parser.cc"
    break;

  case 58: // loc: id LBRACKET id RBRACKET
#line 435 "parser.yy"
    {
        yylhs.value.as < DTL::LocNode* > () = new ArrayIndexNode(yystack_[3].value.as < DTL::IDNode* > ()->pos(), yystack_[3].value.as < DTL::IDNode* > (), yystack_[1].value.as < DTL::IDNode* > ());
    }
#line 1952 "parser.cc"
    break;

  case 59: // id: ID
#line 440 "parser.yy"
    {
        yylhs.value.as < DTL::IDNode* > () = new IDNode(yystack_[0].value.as < DTL::IDToken * > ()->pos(), yystack_[0].value.as < DTL::IDToken * > ()->value());
    }
#line 1960 "parser.cc"
    break;


#line 1964 "parser.cc"

            default:
              break;
            }
        }
#if YY_EXCEPTIONS
      catch (const syntax_error& yyexc)
        {
          YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
          error (yyexc);
          YYERROR;
        }
#endif // YY_EXCEPTIONS
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, YY_MOVE (yylhs));
    }
    goto yynewstate;


  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        context yyctx (*this, yyla);
        std::string msg = yysyntax_error_ (yyctx);
        error (YY_MOVE (msg));
      }


    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.kind () == symbol_kind::S_YYEOF)
          YYABORT;
        else if (!yyla.empty ())
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyla.clear ();
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:
    /* Pacify compilers when the user code never invokes YYERROR and
       the label yyerrorlab therefore never appears in user code.  */
    if (false)
      YYERROR;

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    YY_STACK_PRINT ();
    goto yyerrlab1;


  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    // Pop stack until we find a state that shifts the error token.
    for (;;)
      {
        yyn = yypact_[+yystack_[0].state];
        if (!yy_pact_value_is_default_ (yyn))
          {
            yyn += symbol_kind::S_YYerror;
            if (0 <= yyn && yyn <= yylast_
                && yycheck_[yyn] == symbol_kind::S_YYerror)
              {
                yyn = yytable_[yyn];
                if (0 < yyn)
                  break;
              }
          }

        // Pop the current state because it cannot handle the error token.
        if (yystack_.size () == 1)
          YYABORT;

        yy_destroy_ ("Error: popping", yystack_[0]);
        yypop_ ();
        YY_STACK_PRINT ();
      }
    {
      stack_symbol_type error_token;


      // Shift the error token.
      error_token.state = state_type (yyn);
      yypush_ ("Shifting", YY_MOVE (error_token));
    }
    goto yynewstate;


  /*-------------------------------------.
  | yyacceptlab -- YYACCEPT comes here.  |
  `-------------------------------------*/
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;


  /*-----------------------------------.
  | yyabortlab -- YYABORT comes here.  |
  `-----------------------------------*/
  yyabortlab:
    yyresult = 1;
    goto yyreturn;


  /*-----------------------------------------------------.
  | yyreturn -- parsing is finished, return the result.  |
  `-----------------------------------------------------*/
  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    YY_STACK_PRINT ();
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
#if YY_EXCEPTIONS
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack\n";
        // Do not try to display the values of the reclaimed symbols,
        // as their printers might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
#endif // YY_EXCEPTIONS
  }

  void
  Parser::error (const syntax_error& yyexc)
  {
    error (yyexc.what ());
  }

  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  Parser::yytnamerr_ (const char *yystr)
  {
    if (*yystr == '"')
      {
        std::string yyr;
        char const *yyp = yystr;

        for (;;)
          switch (*++yyp)
            {
            case '\'':
            case ',':
              goto do_not_strip_quotes;

            case '\\':
              if (*++yyp != '\\')
                goto do_not_strip_quotes;
              else
                goto append;

            append:
            default:
              yyr += *yyp;
              break;

            case '"':
              return yyr;
            }
      do_not_strip_quotes: ;
      }

    return yystr;
  }

  std::string
  Parser::symbol_name (symbol_kind_type yysymbol)
  {
    return yytnamerr_ (yytname_[yysymbol]);
  }



  // Parser::context.
  Parser::context::context (const Parser& yyparser, const symbol_type& yyla)
    : yyparser_ (yyparser)
    , yyla_ (yyla)
  {}

  int
  Parser::context::expected_tokens (symbol_kind_type yyarg[], int yyargn) const
  {
    // Actual number of expected tokens
    int yycount = 0;

    const int yyn = yypact_[+yyparser_.yystack_[0].state];
    if (!yy_pact_value_is_default_ (yyn))
      {
        /* Start YYX at -YYN if negative to avoid negative indexes in
           YYCHECK.  In other words, skip the first -YYN actions for
           this state because they are default actions.  */
        const int yyxbegin = yyn < 0 ? -yyn : 0;
        // Stay within bounds of both yycheck and yytname.
        const int yychecklim = yylast_ - yyn + 1;
        const int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
        for (int yyx = yyxbegin; yyx < yyxend; ++yyx)
          if (yycheck_[yyx + yyn] == yyx && yyx != symbol_kind::S_YYerror
              && !yy_table_value_is_error_ (yytable_[yyx + yyn]))
            {
              if (!yyarg)
                ++yycount;
              else if (yycount == yyargn)
                return 0;
              else
                yyarg[yycount++] = YY_CAST (symbol_kind_type, yyx);
            }
      }

    if (yyarg && yycount == 0 && 0 < yyargn)
      yyarg[0] = symbol_kind::S_YYEMPTY;
    return yycount;
  }






  int
  Parser::yy_syntax_error_arguments_ (const context& yyctx,
                                                 symbol_kind_type yyarg[], int yyargn) const
  {
    /* There are many possibilities here to consider:
       - If this state is a consistent state with a default action, then
         the only way this function was invoked is if the default action
         is an error action.  In that case, don't check for expected
         tokens because there are none.
       - The only way there can be no lookahead present (in yyla) is
         if this state is a consistent state with a default action.
         Thus, detecting the absence of a lookahead is sufficient to
         determine that there is no unexpected or expected token to
         report.  In that case, just report a simple "syntax error".
       - Don't assume there isn't a lookahead just because this state is
         a consistent state with a default action.  There might have
         been a previous inconsistent state, consistent state with a
         non-default action, or user semantic action that manipulated
         yyla.  (However, yyla is currently not documented for users.)
       - Of course, the expected token list depends on states to have
         correct lookahead information, and it depends on the parser not
         to perform extra reductions after fetching a lookahead from the
         scanner and before detecting a syntax error.  Thus, state merging
         (from LALR or IELR) and default reductions corrupt the expected
         token list.  However, the list is correct for canonical LR with
         one exception: it will still contain any token that will not be
         accepted due to an error action in a later state.
    */

    if (!yyctx.lookahead ().empty ())
      {
        if (yyarg)
          yyarg[0] = yyctx.token ();
        int yyn = yyctx.expected_tokens (yyarg ? yyarg + 1 : yyarg, yyargn - 1);
        return yyn + 1;
      }
    return 0;
  }

  // Generate an error message.
  std::string
  Parser::yysyntax_error_ (const context& yyctx) const
  {
    // Its maximum.
    enum { YYARGS_MAX = 5 };
    // Arguments of yyformat.
    symbol_kind_type yyarg[YYARGS_MAX];
    int yycount = yy_syntax_error_arguments_ (yyctx, yyarg, YYARGS_MAX);

    char const* yyformat = YY_NULLPTR;
    switch (yycount)
      {
#define YYCASE_(N, S)                         \
        case N:                               \
          yyformat = S;                       \
        break
      default: // Avoid compiler warnings.
        YYCASE_ (0, YY_("syntax error"));
        YYCASE_ (1, YY_("syntax error, unexpected %s"));
        YYCASE_ (2, YY_("syntax error, unexpected %s, expecting %s"));
        YYCASE_ (3, YY_("syntax error, unexpected %s, expecting %s or %s"));
        YYCASE_ (4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
        YYCASE_ (5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
      }

    std::string yyres;
    // Argument number.
    std::ptrdiff_t yyi = 0;
    for (char const* yyp = yyformat; *yyp; ++yyp)
      if (yyp[0] == '%' && yyp[1] == 's' && yyi < yycount)
        {
          yyres += symbol_name (yyarg[yyi++]);
          ++yyp;
        }
      else
        yyres += *yyp;
    return yyres;
  }


  const signed char Parser::yypact_ninf_ = -56;

  const signed char Parser::yytable_ninf_ = -1;

  const short
  Parser::yypact_[] =
  {
     -36,    24,    46,   -28,   -36,    37,    57,   -56,    57,   -56,
     -56,   -56,    55,   -56,    48,    52,   -56,    57,    75,   -56,
     -56,    76,    94,    57,   -56,   -56,    90,     3,   -56,   110,
     -56,   106,   140,   -56,   -56,   -56,    57,    57,    10,    37,
     166,   167,    22,   153,   120,    37,    22,    31,   -56,   -56,
     -56,   -56,   154,    29,    37,   158,   160,    50,    22,    22,
      57,    22,    22,    57,   168,   169,   165,   161,   -56,   -56,
     -56,     1,    13,   170,   173,   -56,   163,   171,    57,    57,
     172,    37,   181,   -56,   -56,   174,   175,   -56,   -56,   -16,
     -56,   -56,   188,   183,   184,   178,   177,   185,   -56,   -56,
     -56,    22,    57,    23,   -56,   -56,   -56,    62,   182,    57,
      57,    57,   129,   -56,   192,   186,    -9,    57,    57,    57,
      57,    57,   179,   194,   196,   176,   180,    57,   190,   193,
     197,   198,   187,   189,   179,   177,   177,    57,    57,    57,
     201,   203,   208,   209,   177,   -56,   -56,    32,    44,   202,
     204,   205,   177,   177,   177,   177,   177,   195,   199,   210,
     212,   215,    47,    61,    67,    68,   216,   218,   177,   177,
     177,   200,   206,   207,   211,   177,   177,    69,    70,    78,
     219,   220,   223,   224,    79,   104,   213,   214,   217,   177,
     177,   177,   177,   -56,   -56,   225,   226,   227,   126,   132,
     143,   144,   177,   177,   177,   -56,   -56,   -56,   -56,   145,
     146,   147,   -56,   -56,   -56
  };

  const signed char
  Parser::yydefact_[] =
  {
       5,     0,     0,     0,     5,     0,     0,     1,     0,     2,
       4,    56,     0,    59,     9,     0,     7,     0,     0,     3,
       8,    11,     0,     0,    15,    10,     0,     0,     6,     0,
      45,     0,     0,    14,    13,    12,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    50,    52,
      54,    55,    57,     0,    23,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    22,    18,    19,
      53,    47,    46,     0,     0,    48,    49,     0,     0,     0,
       0,    23,     0,    51,    58,     0,     0,    20,    21,     0,
      16,    17,     0,     0,     0,     0,    28,     0,    29,    30,
      27,     0,     0,     0,    24,    26,    25,     0,     0,     0,
       0,     0,     0,    44,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    42,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    40,    41,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    43,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    31,    36,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    32,    33,    34,    35,     0,
       0,     0,    37,    38,    39
  };

  const short
  Parser::yypgoto_[] =
  {
     -56,   -56,   -56,   234,   -56,   -56,   -56,   222,   -56,   -56,
     -56,   221,   159,   150,   -18,   -56,   -56,   -56,   108,   -56,
     -55,   228,   -40,   -56,   -56,   -56,    -2,   191,    -6
  };

  const unsigned char
  Parser::yydefgoto_[] =
  {
       0,     2,     9,     3,     4,     6,    18,    20,    26,    27,
      33,    34,    66,    35,    96,    97,    98,    99,   133,   134,
     100,    36,    47,    73,    48,    49,    50,    51,    52
  };

  const unsigned char
  Parser::yytable_[] =
  {
      14,     1,    15,    12,    31,    92,    57,    29,   124,    30,
       8,    21,    93,    94,    29,    59,    30,    21,    71,    72,
      61,    75,    76,    31,   125,   126,    62,    13,    13,    11,
      40,    41,    61,     5,    13,    46,    11,    43,    62,    32,
      58,   105,    55,    56,    11,    59,     7,    65,   157,    60,
      61,    64,    67,    92,   109,   110,    62,    77,   111,    58,
     158,   107,    13,   171,    59,    92,    16,    70,    92,    61,
      19,    58,    85,    86,    17,    62,    59,   172,    22,    67,
     113,    61,    92,   173,   174,   186,   187,    62,    92,    92,
      92,    92,   105,   105,   188,   193,   108,   112,    23,    92,
      92,   105,    24,   115,   116,   117,    28,   105,   105,   105,
     105,   127,   128,   129,   130,   131,    30,   147,   148,    38,
     194,   139,   105,   105,   105,    92,   156,    11,    54,   105,
     105,   149,   150,   151,   162,   163,   164,   165,   118,   119,
     120,   121,   205,   105,   105,   105,   105,    92,   206,    39,
     177,   178,   179,    92,   105,   105,   105,   184,   185,   207,
     208,   212,   213,   214,    92,    92,    92,    92,    92,    44,
      45,   198,   199,   200,   201,    53,    68,    63,    69,    78,
      79,    80,    61,    81,   209,   210,   211,    82,    83,    89,
      87,   101,    90,    91,   104,    84,   102,   103,    92,   114,
     122,   106,   135,   123,   136,   145,   132,   140,   137,   152,
     141,   153,   138,   144,   142,   143,   154,   155,   168,   159,
     169,   160,   161,   170,   175,   166,   176,   189,   190,   167,
     180,   191,   192,   202,   203,   204,   181,   182,    10,    95,
      88,   183,   146,   195,   196,    25,     0,   197,     0,     0,
       0,    74,     0,     0,     0,     0,     0,    37,     0,    42
  };

  const short
  Parser::yycheck_[] =
  {
       6,    37,     8,     5,    20,    21,    46,     4,    17,     6,
      38,    17,    28,    29,     4,    14,     6,    23,    58,    59,
      19,    61,    62,    20,    33,    34,    25,     5,     5,     7,
      36,    37,    19,     9,     5,    13,     7,    39,    25,    36,
       9,    96,    44,    45,     7,    14,     0,    53,    16,    18,
      19,    53,    54,    21,    31,    32,    25,    63,    35,     9,
      16,   101,     5,    16,    14,    21,    11,    17,    21,    19,
      18,     9,    78,    79,    26,    25,    14,    16,     3,    81,
      18,    19,    21,    16,    16,    16,    16,    25,    21,    21,
      21,    21,   147,   148,    16,    16,   102,   103,    22,    21,
      21,   156,     8,   109,   110,   111,    16,   162,   163,   164,
     165,   117,   118,   119,   120,   121,     6,   135,   136,    13,
      16,   127,   177,   178,   179,    21,   144,     7,     8,   184,
     185,   137,   138,   139,   152,   153,   154,   155,     9,    10,
      11,    12,    16,   198,   199,   200,   201,    21,    16,     9,
     168,   169,   170,    21,   209,   210,   211,   175,   176,    16,
      16,    16,    16,    16,    21,    21,    21,    21,    21,     3,
       3,   189,   190,   191,   192,    22,    18,    23,    18,    11,
      11,    16,    19,    22,   202,   203,   204,    17,    15,     8,
      18,     3,    18,    18,    16,    24,    13,    13,    21,    17,
       8,    16,     8,    17,     8,    16,    27,    17,    32,     8,
      17,     8,    32,    26,    17,    17,     8,     8,     8,    17,
       8,    17,    17,     8,     8,    30,     8,     8,     8,    30,
      30,     8,     8,     8,     8,     8,    30,    30,     4,    89,
      81,    30,   134,    30,    30,    23,    -1,    30,    -1,    -1,
      -1,    60,    -1,    -1,    -1,    -1,    -1,    29,    -1,    38
  };

  const signed char
  Parser::yystos_[] =
  {
       0,    37,    40,    42,    43,     9,    44,     0,    38,    41,
      42,     7,    65,     5,    67,    67,    11,    26,    45,    18,
      46,    67,     3,    22,     8,    46,    47,    48,    16,     4,
       6,    20,    36,    49,    50,    52,    60,    60,    13,     9,
      67,    67,    50,    65,     3,     3,    13,    61,    63,    64,
      65,    66,    67,    22,     8,    65,    65,    61,     9,    14,
      18,    19,    25,    23,    65,    67,    51,    65,    18,    18,
      17,    61,    61,    62,    66,    61,    61,    67,    11,    11,
      16,    22,    17,    15,    24,    67,    67,    18,    51,     8,
      18,    18,    21,    28,    29,    52,    53,    54,    55,    56,
      59,     3,    13,    13,    16,    59,    16,    61,    67,    31,
      32,    35,    67,    18,    17,    67,    67,    67,     9,    10,
      11,    12,     8,    17,    17,    33,    34,    67,    67,    67,
      67,    67,    27,    57,    58,     8,     8,    32,    32,    67,
      17,    17,    17,    17,    26,    16,    57,    53,    53,    67,
      67,    67,     8,     8,     8,     8,    53,    16,    16,    17,
      17,    17,    53,    53,    53,    53,    30,    30,     8,     8,
       8,    16,    16,    16,    16,     8,     8,    53,    53,    53,
      30,    30,    30,    30,    53,    53,    16,    16,    16,     8,
       8,     8,     8,    16,    16,    30,    30,    30,    53,    53,
      53,    53,     8,     8,     8,    16,    16,    16,    16,    53,
      53,    53,    16,    16,    16
  };

  const signed char
  Parser::yyr1_[] =
  {
       0,    39,    40,    41,    42,    42,    43,    44,    45,    45,
      46,    46,    47,    48,    48,    48,    49,    49,    50,    50,
      50,    51,    51,    51,    52,    52,    53,    53,    54,    54,
      54,    55,    55,    55,    55,    55,    55,    55,    55,    55,
      56,    57,    57,    58,    59,    60,    61,    61,    61,    61,
      61,    62,    63,    63,    64,    64,    65,    66,    66,    67
  };

  const signed char
  Parser::yyr2_[] =
  {
       0,     2,     2,     3,     2,     0,     8,     3,     2,     0,
       3,     1,     2,     2,     2,     0,     8,     8,     5,     6,
       7,     3,     1,     0,    10,    10,     2,     1,     1,     1,
       1,    12,    13,    13,    13,    13,    12,    15,    15,    15,
       7,     2,     1,     3,     4,     1,     3,     3,     3,     3,
       1,     2,     1,     3,     1,     1,     1,     1,     4,     1
  };


#if YYDEBUG || 1
  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a YYNTOKENS, nonterminals.
  const char*
  const Parser::yytname_[] =
  {
  "\"end file\"", "error", "\"invalid token\"", "ASSIGN", "NOPT", "ID",
  "INT", "INTLITERAL", "LCURLY", "LESS", "LESSEQUAL", "GREATER",
  "GREATEREQUAL", "LPAREN", "CROSS", "POSTINC", "RCURLY", "RPAREN",
  "SEMICOL", "STAR", "FOR", "OUT", "COMMA", "LBRACKET", "RBRACKET",
  "MINUS", "COLON", "CASE", "SWITCH", "IF", "ELSE", "ISEVEN", "ISEDGE",
  "OR", "AND", "PAD", "METADATASTREAM", "DTL", "ACTIVE", "$accept",
  "transformgraph", "activenode", "kernellist", "kernel",
  "backingphyssize", "inputlistwrapper", "inputlist", "program",
  "constdecls", "metadatastreamdecl", "constdecl", "intlist",
  "forstatement", "outstatements", "innernest", "ifstatement",
  "switchstatement", "casestatements", "casestatement", "outstatement",
  "type", "expr", "unarystmt", "term", "factor", "intlit", "loc", "id", YY_NULLPTR
  };
#endif


#if YYDEBUG
  const short
  Parser::yyrline_[] =
  {
       0,   134,   134,   140,   145,   152,   157,   162,   167,   172,
     176,   182,   189,   195,   200,   206,   211,   216,   222,   227,
     234,   241,   247,   253,   259,   267,   272,   277,   285,   289,
     293,   298,   302,   306,   310,   314,   318,   322,   326,   330,
     342,   349,   354,   359,   366,   372,   376,   381,   386,   391,
     396,   401,   409,   413,   417,   421,   425,   430,   434,   439
  };

  void
  Parser::yy_stack_print_ () const
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << int (i->state);
    *yycdebug_ << '\n';
  }

  void
  Parser::yy_reduce_print_ (int yyrule) const
  {
    int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):\n";
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG

  Parser::symbol_kind_type
  Parser::yytranslate_ (int t) YY_NOEXCEPT
  {
    // YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to
    // TOKEN-NUM as returned by yylex.
    static
    const signed char
    translate_table[] =
    {
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38
    };
    // Last valid token kind.
    const int code_max = 293;

    if (t <= 0)
      return symbol_kind::S_YYEOF;
    else if (t <= code_max)
      return static_cast <symbol_kind_type> (translate_table[t]);
    else
      return symbol_kind::S_YYUNDEF;
  }

#line 5 "parser.yy"
} // DTL
#line 2612 "parser.cc"

#line 447 "parser.yy"



void DTL::Parser::error(const std::string& msg) {

	std::cout << msg << std::endl;
	std::cerr << "syntax error" << std::endl;
}

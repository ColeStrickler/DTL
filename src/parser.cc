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
  Parser::Parser (DTL::Scanner &scanner_yyarg, DTL::ProgramNode** root_yyarg)
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
      case symbol_kind::S_expr: // expr
      case symbol_kind::S_term: // term
      case symbol_kind::S_factor: // factor
        value.copy< DTL::ExpNode* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_forstatement: // forstatement
        value.copy< DTL::ForStmtNode* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_id: // id
        value.copy< DTL::IDNode* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_ID: // ID
        value.copy< DTL::IDToken * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_intlit: // intlit
        value.copy< DTL::IntLitNode* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_INTLITERAL: // INTLITERAL
        value.copy< DTL::IntLitToken * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_loc: // loc
        value.copy< DTL::LocNode* > (YY_MOVE (that.value));
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
        value.copy< DTL::Token * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_type: // type
        value.copy< DTL::TypeNode* > (YY_MOVE (that.value));
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
      case symbol_kind::S_expr: // expr
      case symbol_kind::S_term: // term
      case symbol_kind::S_factor: // factor
        value.move< DTL::ExpNode* > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_forstatement: // forstatement
        value.move< DTL::ForStmtNode* > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_id: // id
        value.move< DTL::IDNode* > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_ID: // ID
        value.move< DTL::IDToken * > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_intlit: // intlit
        value.move< DTL::IntLitNode* > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_INTLITERAL: // INTLITERAL
        value.move< DTL::IntLitToken * > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_loc: // loc
        value.move< DTL::LocNode* > (YY_MOVE (s.value));
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
        value.move< DTL::Token * > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_type: // type
        value.move< DTL::TypeNode* > (YY_MOVE (s.value));
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
      case symbol_kind::S_expr: // expr
      case symbol_kind::S_term: // term
      case symbol_kind::S_factor: // factor
        value.YY_MOVE_OR_COPY< DTL::ExpNode* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_forstatement: // forstatement
        value.YY_MOVE_OR_COPY< DTL::ForStmtNode* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_id: // id
        value.YY_MOVE_OR_COPY< DTL::IDNode* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_ID: // ID
        value.YY_MOVE_OR_COPY< DTL::IDToken * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_intlit: // intlit
        value.YY_MOVE_OR_COPY< DTL::IntLitNode* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_INTLITERAL: // INTLITERAL
        value.YY_MOVE_OR_COPY< DTL::IntLitToken * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_loc: // loc
        value.YY_MOVE_OR_COPY< DTL::LocNode* > (YY_MOVE (that.value));
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
        value.YY_MOVE_OR_COPY< DTL::Token * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_type: // type
        value.YY_MOVE_OR_COPY< DTL::TypeNode* > (YY_MOVE (that.value));
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
      case symbol_kind::S_expr: // expr
      case symbol_kind::S_term: // term
      case symbol_kind::S_factor: // factor
        value.move< DTL::ExpNode* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_forstatement: // forstatement
        value.move< DTL::ForStmtNode* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_id: // id
        value.move< DTL::IDNode* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_ID: // ID
        value.move< DTL::IDToken * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_intlit: // intlit
        value.move< DTL::IntLitNode* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_INTLITERAL: // INTLITERAL
        value.move< DTL::IntLitToken * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_loc: // loc
        value.move< DTL::LocNode* > (YY_MOVE (that.value));
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
        value.move< DTL::Token * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_type: // type
        value.move< DTL::TypeNode* > (YY_MOVE (that.value));
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
      case symbol_kind::S_expr: // expr
      case symbol_kind::S_term: // term
      case symbol_kind::S_factor: // factor
        value.copy< DTL::ExpNode* > (that.value);
        break;

      case symbol_kind::S_forstatement: // forstatement
        value.copy< DTL::ForStmtNode* > (that.value);
        break;

      case symbol_kind::S_id: // id
        value.copy< DTL::IDNode* > (that.value);
        break;

      case symbol_kind::S_ID: // ID
        value.copy< DTL::IDToken * > (that.value);
        break;

      case symbol_kind::S_intlit: // intlit
        value.copy< DTL::IntLitNode* > (that.value);
        break;

      case symbol_kind::S_INTLITERAL: // INTLITERAL
        value.copy< DTL::IntLitToken * > (that.value);
        break;

      case symbol_kind::S_loc: // loc
        value.copy< DTL::LocNode* > (that.value);
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
        value.copy< DTL::Token * > (that.value);
        break;

      case symbol_kind::S_type: // type
        value.copy< DTL::TypeNode* > (that.value);
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
      case symbol_kind::S_expr: // expr
      case symbol_kind::S_term: // term
      case symbol_kind::S_factor: // factor
        value.move< DTL::ExpNode* > (that.value);
        break;

      case symbol_kind::S_forstatement: // forstatement
        value.move< DTL::ForStmtNode* > (that.value);
        break;

      case symbol_kind::S_id: // id
        value.move< DTL::IDNode* > (that.value);
        break;

      case symbol_kind::S_ID: // ID
        value.move< DTL::IDToken * > (that.value);
        break;

      case symbol_kind::S_intlit: // intlit
        value.move< DTL::IntLitNode* > (that.value);
        break;

      case symbol_kind::S_INTLITERAL: // INTLITERAL
        value.move< DTL::IntLitToken * > (that.value);
        break;

      case symbol_kind::S_loc: // loc
        value.move< DTL::LocNode* > (that.value);
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
        value.move< DTL::Token * > (that.value);
        break;

      case symbol_kind::S_type: // type
        value.move< DTL::TypeNode* > (that.value);
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
      case symbol_kind::S_expr: // expr
      case symbol_kind::S_term: // term
      case symbol_kind::S_factor: // factor
        yylhs.value.emplace< DTL::ExpNode* > ();
        break;

      case symbol_kind::S_forstatement: // forstatement
        yylhs.value.emplace< DTL::ForStmtNode* > ();
        break;

      case symbol_kind::S_id: // id
        yylhs.value.emplace< DTL::IDNode* > ();
        break;

      case symbol_kind::S_ID: // ID
        yylhs.value.emplace< DTL::IDToken * > ();
        break;

      case symbol_kind::S_intlit: // intlit
        yylhs.value.emplace< DTL::IntLitNode* > ();
        break;

      case symbol_kind::S_INTLITERAL: // INTLITERAL
        yylhs.value.emplace< DTL::IntLitToken * > ();
        break;

      case symbol_kind::S_loc: // loc
        yylhs.value.emplace< DTL::LocNode* > ();
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
        yylhs.value.emplace< DTL::Token * > ();
        break;

      case symbol_kind::S_type: // type
        yylhs.value.emplace< DTL::TypeNode* > ();
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
  case 2: // program: constdecls forstatement
#line 124 "parser.yy"
        {
            yystack_[1].value.as < std::vector<DTL::StmtNode*> > ().push_back(yystack_[0].value.as < DTL::ForStmtNode* > ());
            *root = new ProgramNode(yystack_[1].value.as < std::vector<DTL::StmtNode*> > ());
            yylhs.value.as < DTL::ProgramNode* > () = *root;
        }
#line 1279 "parser.cc"
    break;

  case 3: // constdecls: constdecls constdecl
#line 130 "parser.yy"
        {
            yystack_[1].value.as < std::vector<DTL::StmtNode*> > ().push_back(yystack_[0].value.as < DTL::StmtNode* > ());
            yylhs.value.as < std::vector<DTL::StmtNode*> > () = yystack_[1].value.as < std::vector<DTL::StmtNode*> > ();
        }
#line 1288 "parser.cc"
    break;

  case 4: // constdecls: %empty
#line 135 "parser.yy"
        {
            auto ret = std::vector<DTL::StmtNode*>();
            yylhs.value.as < std::vector<DTL::StmtNode*> > () = ret;
        }
#line 1297 "parser.cc"
    break;

  case 5: // constdecl: type id ASSIGN intlit SEMICOL
#line 140 "parser.yy"
        {
            const Position * p = new Position(yystack_[4].value.as < DTL::TypeNode* > ()->pos(), yystack_[0].value.as < DTL::Token * > ()->pos());
            yylhs.value.as < DTL::StmtNode* > () = new ConstDeclNode(p, yystack_[4].value.as < DTL::TypeNode* > (), yystack_[3].value.as < DTL::IDNode* > (), yystack_[1].value.as < DTL::IntLitNode* > ());
        }
#line 1306 "parser.cc"
    break;

  case 6: // constdecl: NOPT type id ASSIGN intlit SEMICOL
#line 145 "parser.yy"
        {
            const Position * p = new Position(yystack_[4].value.as < DTL::TypeNode* > ()->pos(), yystack_[0].value.as < DTL::Token * > ()->pos());
            auto decl = new ConstDeclNode(p, yystack_[4].value.as < DTL::TypeNode* > (), yystack_[3].value.as < DTL::IDNode* > (), yystack_[1].value.as < DTL::IntLitNode* > ());
            decl->SetOpt(false);
            yylhs.value.as < DTL::StmtNode* > () = decl;
        }
#line 1317 "parser.cc"
    break;

  case 7: // constdecl: type id ASSIGN LCURLY intlist RCURLY SEMICOL
#line 152 "parser.yy"
        {
             const Position * p = new Position(yystack_[6].value.as < DTL::TypeNode* > ()->pos(), yystack_[1].value.as < DTL::Token * > ()->pos());
            yylhs.value.as < DTL::StmtNode* > () = new ConstArrayDeclNode(yystack_[6].value.as < DTL::TypeNode* > ()->pos(), yystack_[6].value.as < DTL::TypeNode* > (), yystack_[5].value.as < DTL::IDNode* > (), yystack_[2].value.as < std::vector<IntLitNode*> > ());
        }
#line 1326 "parser.cc"
    break;

  case 8: // intlist: intlit COMMA intlist
#line 159 "parser.yy"
        {
            yylhs.value.as < std::vector<IntLitNode*> > () = std::vector<DTL::IntLitNode*>();
            yylhs.value.as < std::vector<IntLitNode*> > ().push_back(yystack_[2].value.as < DTL::IntLitNode* > ());
            yylhs.value.as < std::vector<IntLitNode*> > ().insert(yylhs.value.as < std::vector<IntLitNode*> > ().end(), yystack_[0].value.as < std::vector<IntLitNode*> > ().begin(), yystack_[0].value.as < std::vector<IntLitNode*> > ().end());
        }
#line 1336 "parser.cc"
    break;

  case 9: // intlist: intlit
#line 165 "parser.yy"
        {
            yylhs.value.as < std::vector<IntLitNode*> > () = std::vector<DTL::IntLitNode*>();
            yylhs.value.as < std::vector<IntLitNode*> > ().push_back(yystack_[0].value.as < DTL::IntLitNode* > ());
        }
#line 1345 "parser.cc"
    break;

  case 10: // intlist: %empty
#line 170 "parser.yy"
        {
            yylhs.value.as < std::vector<IntLitNode*> > () = std::vector<DTL::IntLitNode*>();
        }
#line 1353 "parser.cc"
    break;

  case 11: // forstatement: FOR LPAREN constdecl expr SEMICOL unarystmt RPAREN LCURLY forstatement RCURLY
#line 177 "parser.yy"
        {
            const Position * p = new Position(yystack_[9].value.as < DTL::Token * > ()->pos(), yystack_[0].value.as < DTL::Token * > ()->pos());
            std::vector<StmtNode*> stmt_vec;
            stmt_vec.push_back(yystack_[1].value.as < DTL::ForStmtNode* > ());
            yylhs.value.as < DTL::ForStmtNode* > () = new ForStmtNode(p, yystack_[7].value.as < DTL::StmtNode* > (), yystack_[6].value.as < DTL::ExpNode* > (), yystack_[4].value.as < DTL::StmtNode* > (), stmt_vec);

        }
#line 1365 "parser.cc"
    break;

  case 12: // forstatement: FOR LPAREN constdecl expr SEMICOL unarystmt RPAREN LCURLY innernest RCURLY
#line 185 "parser.yy"
        {
            const Position * p = new Position(yystack_[9].value.as < DTL::Token * > ()->pos(), yystack_[0].value.as < DTL::Token * > ()->pos());
            yylhs.value.as < DTL::ForStmtNode* > () = new ForStmtNode(p, yystack_[7].value.as < DTL::StmtNode* > (), yystack_[6].value.as < DTL::ExpNode* > (), yystack_[4].value.as < DTL::StmtNode* > (), yystack_[1].value.as < std::vector<DTL::StmtNode*> > ());
        }
#line 1374 "parser.cc"
    break;

  case 13: // outstatements: outstatements outstatement
#line 190 "parser.yy"
        {
            yystack_[1].value.as < std::vector<DTL::StmtNode*> > ().push_back(yystack_[0].value.as < DTL::StmtNode* > ());
            yylhs.value.as < std::vector<DTL::StmtNode*> > () = yystack_[1].value.as < std::vector<DTL::StmtNode*> > ();
        }
#line 1383 "parser.cc"
    break;

  case 14: // outstatements: outstatement
#line 195 "parser.yy"
        {
            std::vector<StmtNode*> stmt_vec;
            stmt_vec.push_back(yystack_[0].value.as < DTL::StmtNode* > ());
            yylhs.value.as < std::vector<DTL::StmtNode*> > () = stmt_vec;
        }
#line 1393 "parser.cc"
    break;

  case 15: // innernest: outstatements
#line 203 "parser.yy"
    {
        yylhs.value.as < std::vector<DTL::StmtNode*> > () = yystack_[0].value.as < std::vector<DTL::StmtNode*> > ();
    }
#line 1401 "parser.cc"
    break;

  case 16: // innernest: ifstatement
#line 207 "parser.yy"
    {
        yylhs.value.as < std::vector<DTL::StmtNode*> > () = {yystack_[0].value.as < DTL::StmtNode* > ()};
    }
#line 1409 "parser.cc"
    break;

  case 17: // innernest: switchstatement
#line 211 "parser.yy"
    {
        yylhs.value.as < std::vector<DTL::StmtNode*> > () = {yystack_[0].value.as < DTL::StmtNode* > ()};
    }
#line 1417 "parser.cc"
    break;

  case 18: // ifstatement: IF LPAREN ISEVEN id RPAREN LCURLY outstatements RCURLY ELSE LCURLY outstatements RCURLY
#line 216 "parser.yy"
        {
            yylhs.value.as < DTL::StmtNode* > () = new IfStmtNode(yystack_[11].value.as < DTL::Token * > ()->pos(), yystack_[8].value.as < DTL::IDNode* > (), yystack_[5].value.as < std::vector<DTL::StmtNode*> > (), yystack_[1].value.as < std::vector<DTL::StmtNode*> > (), IFSTMTTYPE::IS_EVEN);
        }
#line 1425 "parser.cc"
    break;

  case 19: // ifstatement: IF LPAREN id LESS id RPAREN LCURLY outstatements RCURLY ELSE LCURLY outstatements RCURLY
#line 220 "parser.yy"
        {
            yylhs.value.as < DTL::StmtNode* > () = new IfStmtNode(yystack_[12].value.as < DTL::Token * > ()->pos(), yystack_[10].value.as < DTL::IDNode* > (), yystack_[5].value.as < std::vector<DTL::StmtNode*> > (), yystack_[1].value.as < std::vector<DTL::StmtNode*> > (), IFSTMTTYPE::LT, yystack_[8].value.as < DTL::IDNode* > ());
        }
#line 1433 "parser.cc"
    break;

  case 20: // ifstatement: IF LPAREN id LESSEQUAL id RPAREN LCURLY outstatements RCURLY ELSE LCURLY outstatements RCURLY
#line 224 "parser.yy"
        {
            yylhs.value.as < DTL::StmtNode* > () = new IfStmtNode(yystack_[12].value.as < DTL::Token * > ()->pos(), yystack_[10].value.as < DTL::IDNode* > (), yystack_[5].value.as < std::vector<DTL::StmtNode*> > (), yystack_[1].value.as < std::vector<DTL::StmtNode*> > (), IFSTMTTYPE::LTE, yystack_[8].value.as < DTL::IDNode* > ());
        }
#line 1441 "parser.cc"
    break;

  case 21: // ifstatement: IF LPAREN id GREATER id RPAREN LCURLY outstatements RCURLY ELSE LCURLY outstatements RCURLY
#line 228 "parser.yy"
        {
            yylhs.value.as < DTL::StmtNode* > () = new IfStmtNode(yystack_[12].value.as < DTL::Token * > ()->pos(), yystack_[10].value.as < DTL::IDNode* > (), yystack_[5].value.as < std::vector<DTL::StmtNode*> > (), yystack_[1].value.as < std::vector<DTL::StmtNode*> > (), IFSTMTTYPE::GT, yystack_[8].value.as < DTL::IDNode* > ());
        }
#line 1449 "parser.cc"
    break;

  case 22: // ifstatement: IF LPAREN id GREATEREQUAL id RPAREN LCURLY outstatements RCURLY ELSE LCURLY outstatements RCURLY
#line 232 "parser.yy"
        {
            yylhs.value.as < DTL::StmtNode* > () = new IfStmtNode(yystack_[12].value.as < DTL::Token * > ()->pos(), yystack_[10].value.as < DTL::IDNode* > (), yystack_[5].value.as < std::vector<DTL::StmtNode*> > (), yystack_[1].value.as < std::vector<DTL::StmtNode*> > (), IFSTMTTYPE::GTE, yystack_[8].value.as < DTL::IDNode* > ());
        }
#line 1457 "parser.cc"
    break;

  case 23: // ifstatement: IF LPAREN ISEDGE id RPAREN LCURLY outstatements RCURLY ELSE LCURLY outstatements RCURLY
#line 236 "parser.yy"
        {
            yylhs.value.as < DTL::StmtNode* > () = new IfStmtNode(yystack_[11].value.as < DTL::Token * > ()->pos(), yystack_[8].value.as < DTL::IDNode* > (), yystack_[5].value.as < std::vector<DTL::StmtNode*> > (),  yystack_[1].value.as < std::vector<DTL::StmtNode*> > (), IFSTMTTYPE::EDGE);
        }
#line 1465 "parser.cc"
    break;

  case 24: // ifstatement: IF LPAREN ISEDGE id OR ISEDGE id RPAREN LCURLY outstatements RCURLY ELSE LCURLY outstatements RCURLY
#line 240 "parser.yy"
        {
            yylhs.value.as < DTL::StmtNode* > () = new IfStmtNode(yystack_[14].value.as < DTL::Token * > ()->pos(), yystack_[11].value.as < DTL::IDNode* > (), yystack_[5].value.as < std::vector<DTL::StmtNode*> > (), yystack_[1].value.as < std::vector<DTL::StmtNode*> > (), IFSTMTTYPE::EDGE2OR, yystack_[8].value.as < DTL::IDNode* > ());
        }
#line 1473 "parser.cc"
    break;

  case 25: // ifstatement: IF LPAREN ISEDGE id AND ISEDGE id RPAREN LCURLY outstatements RCURLY ELSE LCURLY outstatements RCURLY
#line 244 "parser.yy"
        {
            yylhs.value.as < DTL::StmtNode* > () = new IfStmtNode(yystack_[14].value.as < DTL::Token * > ()->pos(), yystack_[11].value.as < DTL::IDNode* > (), yystack_[5].value.as < std::vector<DTL::StmtNode*> > (), yystack_[1].value.as < std::vector<DTL::StmtNode*> > (), IFSTMTTYPE::EDGE2AND, yystack_[8].value.as < DTL::IDNode* > ());
        }
#line 1481 "parser.cc"
    break;

  case 26: // switchstatement: SWITCH LPAREN id RPAREN LCURLY casestatements RCURLY
#line 256 "parser.yy"
        {
            std::reverse(yystack_[1].value.as < std::vector<std::vector<DTL::StmtNode*>> > ().begin(), yystack_[1].value.as < std::vector<std::vector<DTL::StmtNode*>> > ().end());
            yylhs.value.as < DTL::StmtNode* > () = new SwitchStmtNode(yystack_[6].value.as < DTL::Token * > ()->pos(), yystack_[4].value.as < DTL::IDNode* > (), yystack_[1].value.as < std::vector<std::vector<DTL::StmtNode*>> > ());
        }
#line 1490 "parser.cc"
    break;

  case 27: // casestatements: casestatement casestatements
#line 263 "parser.yy"
    {    
        yystack_[0].value.as < std::vector<std::vector<DTL::StmtNode*>> > ().push_back(yystack_[1].value.as < std::vector<DTL::StmtNode*> > ());
        yylhs.value.as < std::vector<std::vector<DTL::StmtNode*>> > () = yystack_[0].value.as < std::vector<std::vector<DTL::StmtNode*>> > ();
    }
#line 1499 "parser.cc"
    break;

  case 28: // casestatements: casestatement
#line 268 "parser.yy"
    {
        yylhs.value.as < std::vector<std::vector<DTL::StmtNode*>> > () = {yystack_[0].value.as < std::vector<DTL::StmtNode*> > ()};
    }
#line 1507 "parser.cc"
    break;

  case 29: // casestatement: CASE COLON outstatements
#line 273 "parser.yy"
    {
        yylhs.value.as < std::vector<DTL::StmtNode*> > () = yystack_[0].value.as < std::vector<DTL::StmtNode*> > ();
    }
#line 1515 "parser.cc"
    break;

  case 30: // outstatement: OUT ASSIGN expr SEMICOL
#line 280 "parser.yy"
            {
                const Position * p = new Position(yystack_[3].value.as < DTL::Token * > ()->pos(), yystack_[0].value.as < DTL::Token * > ()->pos());
                yylhs.value.as < DTL::StmtNode* > () = new OutStmtNode(p, yystack_[1].value.as < DTL::ExpNode* > ());
            }
#line 1524 "parser.cc"
    break;

  case 31: // type: INT
#line 286 "parser.yy"
    {
        yylhs.value.as < DTL::TypeNode* > () = new IntTypeNode(yystack_[0].value.as < DTL::Token * > ()->pos());
    }
#line 1532 "parser.cc"
    break;

  case 32: // expr: expr CROSS expr
#line 290 "parser.yy"
    {
        const Position * p = new Position(yystack_[2].value.as < DTL::ExpNode* > ()->pos(), yystack_[0].value.as < DTL::ExpNode* > ()->pos());
        yylhs.value.as < DTL::ExpNode* > () = new PlusNode(p, yystack_[2].value.as < DTL::ExpNode* > (), yystack_[0].value.as < DTL::ExpNode* > ());
    }
#line 1541 "parser.cc"
    break;

  case 33: // expr: expr LESS expr
#line 295 "parser.yy"
    {
        const Position * p = new Position(yystack_[2].value.as < DTL::ExpNode* > ()->pos(), yystack_[0].value.as < DTL::ExpNode* > ()->pos());
        yylhs.value.as < DTL::ExpNode* > () = new LessNode(p, yystack_[2].value.as < DTL::ExpNode* > (), yystack_[0].value.as < DTL::ExpNode* > ());
    }
#line 1550 "parser.cc"
    break;

  case 34: // expr: expr STAR expr
#line 300 "parser.yy"
    {
        const Position * p = new Position(yystack_[2].value.as < DTL::ExpNode* > ()->pos(), yystack_[0].value.as < DTL::ExpNode* > ()->pos());
        yylhs.value.as < DTL::ExpNode* > () = new TimesNode(p, yystack_[2].value.as < DTL::ExpNode* > (), yystack_[0].value.as < DTL::ExpNode* > ());
    }
#line 1559 "parser.cc"
    break;

  case 35: // expr: expr MINUS expr
#line 305 "parser.yy"
    {
        const Position * p = new Position(yystack_[2].value.as < DTL::ExpNode* > ()->pos(), yystack_[0].value.as < DTL::ExpNode* > ()->pos());
        yylhs.value.as < DTL::ExpNode* > () = new MinusNode(p, yystack_[2].value.as < DTL::ExpNode* > (), yystack_[0].value.as < DTL::ExpNode* > ());
    }
#line 1568 "parser.cc"
    break;

  case 36: // expr: term
#line 310 "parser.yy"
    {
        yylhs.value.as < DTL::ExpNode* > () = yystack_[0].value.as < DTL::ExpNode* > ();
    }
#line 1576 "parser.cc"
    break;

  case 37: // unarystmt: loc POSTINC
#line 315 "parser.yy"
        {
            const Position* p = new Position(yystack_[1].value.as < DTL::LocNode* > ()->pos(), yystack_[0].value.as < DTL::Token * > ()->pos());
            yylhs.value.as < DTL::StmtNode* > () = new PostIncStmtNode(p, yystack_[1].value.as < DTL::LocNode* > ());
        }
#line 1585 "parser.cc"
    break;

  case 38: // term: factor
#line 323 "parser.yy"
    {
        yylhs.value.as < DTL::ExpNode* > () = yystack_[0].value.as < DTL::ExpNode* > ();
    }
#line 1593 "parser.cc"
    break;

  case 39: // term: LPAREN expr RPAREN
#line 327 "parser.yy"
    {
        yylhs.value.as < DTL::ExpNode* > () = yystack_[1].value.as < DTL::ExpNode* > ();
    }
#line 1601 "parser.cc"
    break;

  case 40: // factor: intlit
#line 331 "parser.yy"
    {
        yylhs.value.as < DTL::ExpNode* > () = yystack_[0].value.as < DTL::IntLitNode* > ();
    }
#line 1609 "parser.cc"
    break;

  case 41: // factor: loc
#line 335 "parser.yy"
    {
        yylhs.value.as < DTL::ExpNode* > () = yystack_[0].value.as < DTL::LocNode* > ();
    }
#line 1617 "parser.cc"
    break;

  case 42: // intlit: INTLITERAL
#line 339 "parser.yy"
    {
        yylhs.value.as < DTL::IntLitNode* > () = new IntLitNode(yystack_[0].value.as < DTL::IntLitToken * > ()->pos(), yystack_[0].value.as < DTL::IntLitToken * > ()->num());
    }
#line 1625 "parser.cc"
    break;

  case 43: // loc: id
#line 344 "parser.yy"
    {
        yylhs.value.as < DTL::LocNode* > () = yystack_[0].value.as < DTL::IDNode* > ();
    }
#line 1633 "parser.cc"
    break;

  case 44: // loc: id LBRACKET id RBRACKET
#line 348 "parser.yy"
    {
        yylhs.value.as < DTL::LocNode* > () = new ArrayIndexNode(yystack_[3].value.as < DTL::IDNode* > ()->pos(), yystack_[3].value.as < DTL::IDNode* > (), yystack_[1].value.as < DTL::IDNode* > ());
    }
#line 1641 "parser.cc"
    break;

  case 45: // id: ID
#line 353 "parser.yy"
    {
        yylhs.value.as < DTL::IDNode* > () = new IDNode(yystack_[0].value.as < DTL::IDToken * > ()->pos(), yystack_[0].value.as < DTL::IDToken * > ()->value());
    }
#line 1649 "parser.cc"
    break;


#line 1653 "parser.cc"

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


  const signed char Parser::yypact_ninf_ = -61;

  const signed char Parser::yytable_ninf_ = -1;

  const short
  Parser::yypact_[] =
  {
     -61,    20,     3,   -61,     4,   -61,    53,   -61,   -61,    11,
      11,   144,   -61,    30,    47,    32,    35,    33,   -61,    32,
      10,   -61,   -61,   -61,   -61,    46,    33,    58,    59,    27,
      32,    32,    11,    32,    32,    11,    75,    90,   -61,   -61,
     -61,    13,   -13,   125,   109,   -61,   106,   115,   131,    33,
     143,   -61,   -61,   -61,   -61,    36,   149,   140,   141,   139,
     136,   142,   -61,   -61,   -61,    32,    11,    -1,   -61,   -61,
     -61,   108,   145,    11,    11,   135,   -61,   148,   146,   -12,
      11,    11,    11,    11,   132,   152,   153,   133,   134,   147,
     150,   151,   154,   155,   156,   132,   136,   136,    11,    11,
     161,   162,   165,   166,   136,   -61,   -61,    -8,    37,   158,
     159,   136,   136,   136,   136,   136,   157,   160,   169,   170,
      38,    51,    52,    63,   171,   172,   136,   136,   163,   164,
     167,   168,   136,   136,    88,    89,   174,   175,   176,   177,
      92,    95,   173,   178,   136,   136,   136,   136,   -61,   -61,
     180,   181,   107,   113,   116,   119,   136,   136,   -61,   -61,
     -61,   -61,   120,   122,   -61,   -61
  };

  const signed char
  Parser::yydefact_[] =
  {
       4,     0,     0,     1,     0,    31,     0,     3,     2,     0,
       0,     0,    45,     0,     0,     0,     0,     0,    42,     0,
       0,    36,    38,    40,    41,    43,    10,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     9,     5,     6,
      39,    33,    32,     0,     0,    34,    35,     0,     0,    10,
       0,    37,    44,     7,     8,     0,     0,     0,     0,     0,
      15,     0,    16,    17,    14,     0,     0,     0,    11,    13,
      12,     0,     0,     0,     0,     0,    30,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    28,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    26,    27,     0,     0,     0,
       0,     0,     0,     0,     0,    29,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    18,    23,
       0,     0,     0,     0,     0,     0,     0,     0,    19,    20,
      21,    22,     0,     0,    24,    25
  };

  const short
  Parser::yypgoto_[] =
  {
     -61,   -61,   -61,   184,   137,   179,   -26,   -61,   -61,   -61,
      96,   -61,   -60,   188,   -16,   -61,   -61,   -61,   -15,   182,
      16
  };

  const signed char
  Parser::yydefgoto_[] =
  {
       0,     1,     2,     7,    36,     8,    60,    61,    62,    63,
      94,    95,    64,     9,    20,    43,    21,    22,    23,    24,
      25
  };

  const unsigned char
  Parser::yytable_[] =
  {
      69,    27,    28,    29,    12,    86,    33,     4,   116,     5,
       5,    37,    34,    56,    41,    42,    12,    45,    46,    30,
       3,    87,    88,     6,    31,    13,    14,    31,    32,    33,
      73,    74,    33,    16,    37,    34,    30,    12,    34,    18,
      18,    31,    18,    26,    40,    19,    33,    69,    69,    71,
      17,    47,    34,   117,   128,    69,     6,    56,    56,    56,
      69,    69,    69,    69,    57,    58,    11,   129,   130,    35,
     107,   108,    56,    56,    69,    69,    38,    39,   115,   131,
      69,    69,    72,    75,    56,   120,   121,   122,   123,    78,
      79,    48,    69,    69,    69,    69,    89,    90,    91,    92,
     134,   135,    69,    69,   142,   143,   140,   141,   148,    56,
      56,   149,    49,    56,   109,   110,    56,    30,   152,   153,
     154,   155,    31,   158,    51,    33,    76,    33,    56,   159,
     162,   163,   160,    34,    56,   161,   164,    56,   165,    52,
      56,    56,    50,    56,    80,    81,    82,    83,     4,    53,
       5,    55,    65,    66,    67,    68,    84,    56,    70,    93,
      96,    97,    77,    85,   100,    98,    99,   101,   102,   111,
     112,   103,   105,   113,   114,   118,   119,   126,   127,   132,
     133,   104,   144,   145,   146,   147,    54,   124,   156,   157,
     125,   106,    10,   136,   137,    15,     0,   138,   139,     0,
       0,     0,     0,   150,     0,     0,     0,     0,   151,     0,
       0,     0,     0,     0,    44,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    59
  };

  const short
  Parser::yycheck_[] =
  {
      60,    16,    17,    19,     5,    17,    19,     4,    16,     6,
       6,    26,    25,    21,    30,    31,     5,    33,    34,     9,
       0,    33,    34,    20,    14,     9,    10,    14,    18,    19,
      31,    32,    19,     3,    49,    25,     9,     5,    25,     7,
       7,    14,     7,     8,    17,    13,    19,   107,   108,    65,
       3,    35,    25,    16,    16,   115,    20,    21,    21,    21,
     120,   121,   122,   123,    28,    29,    13,    16,    16,    23,
      96,    97,    21,    21,   134,   135,    18,    18,   104,    16,
     140,   141,    66,    67,    21,   111,   112,   113,   114,    73,
      74,    16,   152,   153,   154,   155,    80,    81,    82,    83,
     126,   127,   162,   163,    16,    16,   132,   133,    16,    21,
      21,    16,    22,    21,    98,    99,    21,     9,   144,   145,
     146,   147,    14,    16,    15,    19,    18,    19,    21,    16,
     156,   157,    16,    25,    21,    16,    16,    21,    16,    24,
      21,    21,    17,    21,     9,    10,    11,    12,     4,    18,
       6,     8,     3,    13,    13,    16,     8,    21,    16,    27,
       8,     8,    17,    17,    17,    32,    32,    17,    17,     8,
       8,    17,    16,     8,     8,    17,    17,     8,     8,     8,
       8,    26,     8,     8,     8,     8,    49,    30,     8,     8,
      30,    95,     4,    30,    30,    11,    -1,    30,    30,    -1,
      -1,    -1,    -1,    30,    -1,    -1,    -1,    -1,    30,    -1,
      -1,    -1,    -1,    -1,    32,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    55
  };

  const signed char
  Parser::yystos_[] =
  {
       0,    36,    37,     0,     4,     6,    20,    38,    40,    48,
      48,    13,     5,    55,    55,    38,     3,     3,     7,    13,
      49,    51,    52,    53,    54,    55,     8,    53,    53,    49,
       9,    14,    18,    19,    25,    23,    39,    53,    18,    18,
      17,    49,    49,    50,    54,    49,    49,    55,    16,    22,
      17,    15,    24,    18,    39,     8,    21,    28,    29,    40,
      41,    42,    43,    44,    47,     3,    13,    13,    16,    47,
      16,    49,    55,    31,    32,    55,    18,    17,    55,    55,
       9,    10,    11,    12,     8,    17,    17,    33,    34,    55,
      55,    55,    55,    27,    45,    46,     8,     8,    32,    32,
      17,    17,    17,    17,    26,    16,    45,    41,    41,    55,
      55,     8,     8,     8,     8,    41,    16,    16,    17,    17,
      41,    41,    41,    41,    30,    30,     8,     8,    16,    16,
      16,    16,     8,     8,    41,    41,    30,    30,    30,    30,
      41,    41,    16,    16,     8,     8,     8,     8,    16,    16,
      30,    30,    41,    41,    41,    41,     8,     8,    16,    16,
      16,    16,    41,    41,    16,    16
  };

  const signed char
  Parser::yyr1_[] =
  {
       0,    35,    36,    37,    37,    38,    38,    38,    39,    39,
      39,    40,    40,    41,    41,    42,    42,    42,    43,    43,
      43,    43,    43,    43,    43,    43,    44,    45,    45,    46,
      47,    48,    49,    49,    49,    49,    49,    50,    51,    51,
      52,    52,    53,    54,    54,    55
  };

  const signed char
  Parser::yyr2_[] =
  {
       0,     2,     2,     2,     0,     5,     6,     7,     3,     1,
       0,    10,    10,     2,     1,     1,     1,     1,    12,    13,
      13,    13,    13,    12,    15,    15,     7,     2,     1,     3,
       4,     1,     3,     3,     3,     3,     1,     2,     1,     3,
       1,     1,     1,     1,     4,     1
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
  "OR", "AND", "$accept", "program", "constdecls", "constdecl", "intlist",
  "forstatement", "outstatements", "innernest", "ifstatement",
  "switchstatement", "casestatements", "casestatement", "outstatement",
  "type", "expr", "unarystmt", "term", "factor", "intlit", "loc", "id", YY_NULLPTR
  };
#endif


#if YYDEBUG
  const short
  Parser::yyrline_[] =
  {
       0,   123,   123,   129,   135,   139,   144,   151,   158,   164,
     170,   176,   184,   189,   194,   202,   206,   210,   215,   219,
     223,   227,   231,   235,   239,   243,   255,   262,   267,   272,
     279,   285,   289,   294,   299,   304,   309,   314,   322,   326,
     330,   334,   338,   343,   347,   352
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
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34
    };
    // Last valid token kind.
    const int code_max = 289;

    if (t <= 0)
      return symbol_kind::S_YYEOF;
    else if (t <= code_max)
      return static_cast <symbol_kind_type> (translate_table[t]);
    else
      return symbol_kind::S_YYUNDEF;
  }

#line 5 "parser.yy"
} // DTL
#line 2275 "parser.cc"

#line 360 "parser.yy"



void DTL::Parser::error(const std::string& msg) {

	std::cout << msg << std::endl;
	std::cerr << "syntax error" << std::endl;
}

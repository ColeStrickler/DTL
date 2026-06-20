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
#line 127 "parser.yy"
        {
            yystack_[1].value.as < std::vector<DTL::StmtNode*> > ().push_back(yystack_[0].value.as < DTL::ForStmtNode* > ());
            *root = new ProgramNode(yystack_[1].value.as < std::vector<DTL::StmtNode*> > ());
            yylhs.value.as < DTL::ProgramNode* > () = *root;
        }
#line 1321 "parser.cc"
    break;

  case 3: // constdecls: constdecls constdecl
#line 133 "parser.yy"
        {
            yystack_[1].value.as < std::vector<DTL::StmtNode*> > ().push_back(yystack_[0].value.as < DTL::StmtNode* > ());
            yylhs.value.as < std::vector<DTL::StmtNode*> > () = yystack_[1].value.as < std::vector<DTL::StmtNode*> > ();
        }
#line 1330 "parser.cc"
    break;

  case 4: // constdecls: constdecls metadatastreamdecl
#line 138 "parser.yy"
        {
            yystack_[1].value.as < std::vector<DTL::StmtNode*> > ().push_back(yystack_[0].value.as < DTL::MetadataStreamDeclNode* > ());
            yylhs.value.as < std::vector<DTL::StmtNode*> > () = yystack_[1].value.as < std::vector<DTL::StmtNode*> > ();
        }
#line 1339 "parser.cc"
    break;

  case 5: // constdecls: %empty
#line 143 "parser.yy"
        {
            auto ret = std::vector<DTL::StmtNode*>();
            yylhs.value.as < std::vector<DTL::StmtNode*> > () = ret;
        }
#line 1348 "parser.cc"
    break;

  case 6: // metadatastreamdecl: METADATASTREAM LESS intlit COMMA intlit GREATER id SEMICOL
#line 149 "parser.yy"
        {
            const Position * p = new Position(yystack_[7].value.as < DTL::Token * > ()->pos(), yystack_[0].value.as < DTL::Token * > ()->pos());
            yylhs.value.as < DTL::MetadataStreamDeclNode* > () = new MetadataStreamDeclNode(p, new MetadataStreamTypeNode(yystack_[7].value.as < DTL::Token * > ()->pos()), yystack_[1].value.as < DTL::IDNode* > (), yystack_[5].value.as < DTL::IntLitNode* > (), yystack_[3].value.as < DTL::IntLitNode* > ());
        }
#line 1357 "parser.cc"
    break;

  case 7: // constdecl: type id ASSIGN intlit SEMICOL
#line 155 "parser.yy"
        {
            const Position * p = new Position(yystack_[4].value.as < DTL::TypeNode* > ()->pos(), yystack_[0].value.as < DTL::Token * > ()->pos());
            yylhs.value.as < DTL::StmtNode* > () = new ConstDeclNode(p, yystack_[4].value.as < DTL::TypeNode* > (), yystack_[3].value.as < DTL::IDNode* > (), yystack_[1].value.as < DTL::IntLitNode* > ());
        }
#line 1366 "parser.cc"
    break;

  case 8: // constdecl: NOPT type id ASSIGN intlit SEMICOL
#line 160 "parser.yy"
        {
            const Position * p = new Position(yystack_[4].value.as < DTL::TypeNode* > ()->pos(), yystack_[0].value.as < DTL::Token * > ()->pos());
            auto decl = new ConstDeclNode(p, yystack_[4].value.as < DTL::TypeNode* > (), yystack_[3].value.as < DTL::IDNode* > (), yystack_[1].value.as < DTL::IntLitNode* > ());
            decl->SetOpt(false);
            yylhs.value.as < DTL::StmtNode* > () = decl;
        }
#line 1377 "parser.cc"
    break;

  case 9: // constdecl: type id ASSIGN LCURLY intlist RCURLY SEMICOL
#line 167 "parser.yy"
        {
             const Position * p = new Position(yystack_[6].value.as < DTL::TypeNode* > ()->pos(), yystack_[1].value.as < DTL::Token * > ()->pos());
            yylhs.value.as < DTL::StmtNode* > () = new ConstArrayDeclNode(yystack_[6].value.as < DTL::TypeNode* > ()->pos(), yystack_[6].value.as < DTL::TypeNode* > (), yystack_[5].value.as < DTL::IDNode* > (), yystack_[2].value.as < std::vector<IntLitNode*> > ());
        }
#line 1386 "parser.cc"
    break;

  case 10: // intlist: intlit COMMA intlist
#line 174 "parser.yy"
        {
            yylhs.value.as < std::vector<IntLitNode*> > () = std::vector<DTL::IntLitNode*>();
            yylhs.value.as < std::vector<IntLitNode*> > ().push_back(yystack_[2].value.as < DTL::IntLitNode* > ());
            yylhs.value.as < std::vector<IntLitNode*> > ().insert(yylhs.value.as < std::vector<IntLitNode*> > ().end(), yystack_[0].value.as < std::vector<IntLitNode*> > ().begin(), yystack_[0].value.as < std::vector<IntLitNode*> > ().end());
        }
#line 1396 "parser.cc"
    break;

  case 11: // intlist: intlit
#line 180 "parser.yy"
        {
            yylhs.value.as < std::vector<IntLitNode*> > () = std::vector<DTL::IntLitNode*>();
            yylhs.value.as < std::vector<IntLitNode*> > ().push_back(yystack_[0].value.as < DTL::IntLitNode* > ());
        }
#line 1405 "parser.cc"
    break;

  case 12: // intlist: %empty
#line 185 "parser.yy"
        {
            yylhs.value.as < std::vector<IntLitNode*> > () = std::vector<DTL::IntLitNode*>();
        }
#line 1413 "parser.cc"
    break;

  case 13: // forstatement: FOR LPAREN constdecl expr SEMICOL unarystmt RPAREN LCURLY forstatement RCURLY
#line 192 "parser.yy"
        {
            const Position * p = new Position(yystack_[9].value.as < DTL::Token * > ()->pos(), yystack_[0].value.as < DTL::Token * > ()->pos());
            std::vector<StmtNode*> stmt_vec;
            stmt_vec.push_back(yystack_[1].value.as < DTL::ForStmtNode* > ());
            yylhs.value.as < DTL::ForStmtNode* > () = new ForStmtNode(p, yystack_[7].value.as < DTL::StmtNode* > (), yystack_[6].value.as < DTL::ExpNode* > (), yystack_[4].value.as < DTL::StmtNode* > (), stmt_vec);

        }
#line 1425 "parser.cc"
    break;

  case 14: // forstatement: FOR LPAREN constdecl expr SEMICOL unarystmt RPAREN LCURLY innernest RCURLY
#line 200 "parser.yy"
        {
            const Position * p = new Position(yystack_[9].value.as < DTL::Token * > ()->pos(), yystack_[0].value.as < DTL::Token * > ()->pos());
            yylhs.value.as < DTL::ForStmtNode* > () = new ForStmtNode(p, yystack_[7].value.as < DTL::StmtNode* > (), yystack_[6].value.as < DTL::ExpNode* > (), yystack_[4].value.as < DTL::StmtNode* > (), yystack_[1].value.as < std::vector<DTL::StmtNode*> > ());
        }
#line 1434 "parser.cc"
    break;

  case 15: // outstatements: outstatements outstatement
#line 205 "parser.yy"
        {
            yystack_[1].value.as < std::vector<DTL::StmtNode*> > ().push_back(yystack_[0].value.as < DTL::StmtNode* > ());
            yylhs.value.as < std::vector<DTL::StmtNode*> > () = yystack_[1].value.as < std::vector<DTL::StmtNode*> > ();
        }
#line 1443 "parser.cc"
    break;

  case 16: // outstatements: outstatement
#line 210 "parser.yy"
        {
            std::vector<StmtNode*> stmt_vec;
            stmt_vec.push_back(yystack_[0].value.as < DTL::StmtNode* > ());
            yylhs.value.as < std::vector<DTL::StmtNode*> > () = stmt_vec;
        }
#line 1453 "parser.cc"
    break;

  case 17: // innernest: outstatements
#line 218 "parser.yy"
    {
        yylhs.value.as < std::vector<DTL::StmtNode*> > () = yystack_[0].value.as < std::vector<DTL::StmtNode*> > ();
    }
#line 1461 "parser.cc"
    break;

  case 18: // innernest: ifstatement
#line 222 "parser.yy"
    {
        yylhs.value.as < std::vector<DTL::StmtNode*> > () = {yystack_[0].value.as < DTL::StmtNode* > ()};
    }
#line 1469 "parser.cc"
    break;

  case 19: // innernest: switchstatement
#line 226 "parser.yy"
    {
        yylhs.value.as < std::vector<DTL::StmtNode*> > () = {yystack_[0].value.as < DTL::StmtNode* > ()};
    }
#line 1477 "parser.cc"
    break;

  case 20: // ifstatement: IF LPAREN ISEVEN id RPAREN LCURLY outstatements RCURLY ELSE LCURLY outstatements RCURLY
#line 231 "parser.yy"
        {
            yylhs.value.as < DTL::StmtNode* > () = new IfStmtNode(yystack_[11].value.as < DTL::Token * > ()->pos(), std::vector<IDNode*>{yystack_[8].value.as < DTL::IDNode* > ()}, yystack_[5].value.as < std::vector<DTL::StmtNode*> > (), yystack_[1].value.as < std::vector<DTL::StmtNode*> > (), IFSTMTTYPE::IS_EVEN);
        }
#line 1485 "parser.cc"
    break;

  case 21: // ifstatement: IF LPAREN id LESS id RPAREN LCURLY outstatements RCURLY ELSE LCURLY outstatements RCURLY
#line 235 "parser.yy"
        {
            yylhs.value.as < DTL::StmtNode* > () = new IfStmtNode(yystack_[12].value.as < DTL::Token * > ()->pos(), std::vector<IDNode*>{yystack_[10].value.as < DTL::IDNode* > (),yystack_[8].value.as < DTL::IDNode* > ()}, yystack_[5].value.as < std::vector<DTL::StmtNode*> > (), yystack_[1].value.as < std::vector<DTL::StmtNode*> > (), IFSTMTTYPE::LT);
        }
#line 1493 "parser.cc"
    break;

  case 22: // ifstatement: IF LPAREN id LESSEQUAL id RPAREN LCURLY outstatements RCURLY ELSE LCURLY outstatements RCURLY
#line 239 "parser.yy"
        {
            yylhs.value.as < DTL::StmtNode* > () = new IfStmtNode(yystack_[12].value.as < DTL::Token * > ()->pos(), std::vector<IDNode*>{yystack_[10].value.as < DTL::IDNode* > (),yystack_[8].value.as < DTL::IDNode* > ()}, yystack_[5].value.as < std::vector<DTL::StmtNode*> > (), yystack_[1].value.as < std::vector<DTL::StmtNode*> > (), IFSTMTTYPE::LTE);
        }
#line 1501 "parser.cc"
    break;

  case 23: // ifstatement: IF LPAREN id GREATER id RPAREN LCURLY outstatements RCURLY ELSE LCURLY outstatements RCURLY
#line 243 "parser.yy"
        {
            yylhs.value.as < DTL::StmtNode* > () = new IfStmtNode(yystack_[12].value.as < DTL::Token * > ()->pos(), std::vector<IDNode*>{yystack_[10].value.as < DTL::IDNode* > (),yystack_[8].value.as < DTL::IDNode* > ()}, yystack_[5].value.as < std::vector<DTL::StmtNode*> > (), yystack_[1].value.as < std::vector<DTL::StmtNode*> > (), IFSTMTTYPE::GT);
        }
#line 1509 "parser.cc"
    break;

  case 24: // ifstatement: IF LPAREN id GREATEREQUAL id RPAREN LCURLY outstatements RCURLY ELSE LCURLY outstatements RCURLY
#line 247 "parser.yy"
        {
            yylhs.value.as < DTL::StmtNode* > () = new IfStmtNode(yystack_[12].value.as < DTL::Token * > ()->pos(), std::vector<IDNode*>{yystack_[10].value.as < DTL::IDNode* > (),yystack_[8].value.as < DTL::IDNode* > ()}, yystack_[5].value.as < std::vector<DTL::StmtNode*> > (), yystack_[1].value.as < std::vector<DTL::StmtNode*> > (), IFSTMTTYPE::GTE);
        }
#line 1517 "parser.cc"
    break;

  case 25: // ifstatement: IF LPAREN ISEDGE id RPAREN LCURLY outstatements RCURLY ELSE LCURLY outstatements RCURLY
#line 251 "parser.yy"
        {
            yylhs.value.as < DTL::StmtNode* > () = new IfStmtNode(yystack_[11].value.as < DTL::Token * > ()->pos(), std::vector<IDNode*>{yystack_[8].value.as < DTL::IDNode* > ()}, yystack_[5].value.as < std::vector<DTL::StmtNode*> > (),  yystack_[1].value.as < std::vector<DTL::StmtNode*> > (), IFSTMTTYPE::EDGE);
        }
#line 1525 "parser.cc"
    break;

  case 26: // ifstatement: IF LPAREN ISEDGE id OR ISEDGE id RPAREN LCURLY outstatements RCURLY ELSE LCURLY outstatements RCURLY
#line 255 "parser.yy"
        {
            yylhs.value.as < DTL::StmtNode* > () = new IfStmtNode(yystack_[14].value.as < DTL::Token * > ()->pos(), std::vector<IDNode*>{yystack_[11].value.as < DTL::IDNode* > (),yystack_[8].value.as < DTL::IDNode* > ()}, yystack_[5].value.as < std::vector<DTL::StmtNode*> > (), yystack_[1].value.as < std::vector<DTL::StmtNode*> > (), IFSTMTTYPE::EDGE2OR);
        }
#line 1533 "parser.cc"
    break;

  case 27: // ifstatement: IF LPAREN ISEDGE id AND ISEDGE id RPAREN LCURLY outstatements RCURLY ELSE LCURLY outstatements RCURLY
#line 259 "parser.yy"
        {
            yylhs.value.as < DTL::StmtNode* > () = new IfStmtNode(yystack_[14].value.as < DTL::Token * > ()->pos(), std::vector<IDNode*>{yystack_[11].value.as < DTL::IDNode* > (),yystack_[8].value.as < DTL::IDNode* > ()}, yystack_[5].value.as < std::vector<DTL::StmtNode*> > (), yystack_[1].value.as < std::vector<DTL::StmtNode*> > (), IFSTMTTYPE::EDGE2AND);
        }
#line 1541 "parser.cc"
    break;

  case 28: // ifstatement: IF LPAREN PAD id id id id RPAREN LCURLY outstatements RCURLY ELSE LCURLY outstatements RCURLY
#line 263 "parser.yy"
        {
            std::vector<IDNode*> ids = {yystack_[11].value.as < DTL::IDNode* > (), yystack_[10].value.as < DTL::IDNode* > (), yystack_[9].value.as < DTL::IDNode* > (), yystack_[8].value.as < DTL::IDNode* > ()};
            yylhs.value.as < DTL::StmtNode* > () = new IfStmtNode(yystack_[14].value.as < DTL::Token * > ()->pos(), ids, yystack_[5].value.as < std::vector<DTL::StmtNode*> > (), yystack_[1].value.as < std::vector<DTL::StmtNode*> > (), IFSTMTTYPE::PAD);
        }
#line 1550 "parser.cc"
    break;

  case 29: // switchstatement: SWITCH LPAREN id RPAREN LCURLY casestatements RCURLY
#line 275 "parser.yy"
        {
            std::reverse(yystack_[1].value.as < std::vector<std::vector<DTL::StmtNode*>> > ().begin(), yystack_[1].value.as < std::vector<std::vector<DTL::StmtNode*>> > ().end());
            yylhs.value.as < DTL::StmtNode* > () = new SwitchStmtNode(yystack_[6].value.as < DTL::Token * > ()->pos(), yystack_[4].value.as < DTL::IDNode* > (), yystack_[1].value.as < std::vector<std::vector<DTL::StmtNode*>> > ());
        }
#line 1559 "parser.cc"
    break;

  case 30: // casestatements: casestatement casestatements
#line 282 "parser.yy"
    {    
        yystack_[0].value.as < std::vector<std::vector<DTL::StmtNode*>> > ().push_back(yystack_[1].value.as < std::vector<DTL::StmtNode*> > ());
        yylhs.value.as < std::vector<std::vector<DTL::StmtNode*>> > () = yystack_[0].value.as < std::vector<std::vector<DTL::StmtNode*>> > ();
    }
#line 1568 "parser.cc"
    break;

  case 31: // casestatements: casestatement
#line 287 "parser.yy"
    {
        yylhs.value.as < std::vector<std::vector<DTL::StmtNode*>> > () = {yystack_[0].value.as < std::vector<DTL::StmtNode*> > ()};
    }
#line 1576 "parser.cc"
    break;

  case 32: // casestatement: CASE COLON outstatements
#line 292 "parser.yy"
    {
        yylhs.value.as < std::vector<DTL::StmtNode*> > () = yystack_[0].value.as < std::vector<DTL::StmtNode*> > ();
    }
#line 1584 "parser.cc"
    break;

  case 33: // outstatement: OUT ASSIGN expr SEMICOL
#line 299 "parser.yy"
            {
                const Position * p = new Position(yystack_[3].value.as < DTL::Token * > ()->pos(), yystack_[0].value.as < DTL::Token * > ()->pos());
                yylhs.value.as < DTL::StmtNode* > () = new OutStmtNode(p, yystack_[1].value.as < DTL::ExpNode* > ());
            }
#line 1593 "parser.cc"
    break;

  case 34: // type: INT
#line 305 "parser.yy"
    {
        yylhs.value.as < DTL::TypeNode* > () = new IntTypeNode(yystack_[0].value.as < DTL::Token * > ()->pos());
    }
#line 1601 "parser.cc"
    break;

  case 35: // expr: expr CROSS expr
#line 309 "parser.yy"
    {
        const Position * p = new Position(yystack_[2].value.as < DTL::ExpNode* > ()->pos(), yystack_[0].value.as < DTL::ExpNode* > ()->pos());
        yylhs.value.as < DTL::ExpNode* > () = new PlusNode(p, yystack_[2].value.as < DTL::ExpNode* > (), yystack_[0].value.as < DTL::ExpNode* > ());
    }
#line 1610 "parser.cc"
    break;

  case 36: // expr: expr LESS expr
#line 314 "parser.yy"
    {
        const Position * p = new Position(yystack_[2].value.as < DTL::ExpNode* > ()->pos(), yystack_[0].value.as < DTL::ExpNode* > ()->pos());
        yylhs.value.as < DTL::ExpNode* > () = new LessNode(p, yystack_[2].value.as < DTL::ExpNode* > (), yystack_[0].value.as < DTL::ExpNode* > ());
    }
#line 1619 "parser.cc"
    break;

  case 37: // expr: expr STAR expr
#line 319 "parser.yy"
    {
        const Position * p = new Position(yystack_[2].value.as < DTL::ExpNode* > ()->pos(), yystack_[0].value.as < DTL::ExpNode* > ()->pos());
        yylhs.value.as < DTL::ExpNode* > () = new TimesNode(p, yystack_[2].value.as < DTL::ExpNode* > (), yystack_[0].value.as < DTL::ExpNode* > ());
    }
#line 1628 "parser.cc"
    break;

  case 38: // expr: expr MINUS expr
#line 324 "parser.yy"
    {
        const Position * p = new Position(yystack_[2].value.as < DTL::ExpNode* > ()->pos(), yystack_[0].value.as < DTL::ExpNode* > ()->pos());
        yylhs.value.as < DTL::ExpNode* > () = new MinusNode(p, yystack_[2].value.as < DTL::ExpNode* > (), yystack_[0].value.as < DTL::ExpNode* > ());
    }
#line 1637 "parser.cc"
    break;

  case 39: // expr: term
#line 329 "parser.yy"
    {
        yylhs.value.as < DTL::ExpNode* > () = yystack_[0].value.as < DTL::ExpNode* > ();
    }
#line 1645 "parser.cc"
    break;

  case 40: // unarystmt: loc POSTINC
#line 334 "parser.yy"
        {
            const Position* p = new Position(yystack_[1].value.as < DTL::LocNode* > ()->pos(), yystack_[0].value.as < DTL::Token * > ()->pos());
            yylhs.value.as < DTL::StmtNode* > () = new PostIncStmtNode(p, yystack_[1].value.as < DTL::LocNode* > ());
        }
#line 1654 "parser.cc"
    break;

  case 41: // term: factor
#line 342 "parser.yy"
    {
        yylhs.value.as < DTL::ExpNode* > () = yystack_[0].value.as < DTL::ExpNode* > ();
    }
#line 1662 "parser.cc"
    break;

  case 42: // term: LPAREN expr RPAREN
#line 346 "parser.yy"
    {
        yylhs.value.as < DTL::ExpNode* > () = yystack_[1].value.as < DTL::ExpNode* > ();
    }
#line 1670 "parser.cc"
    break;

  case 43: // factor: intlit
#line 350 "parser.yy"
    {
        yylhs.value.as < DTL::ExpNode* > () = yystack_[0].value.as < DTL::IntLitNode* > ();
    }
#line 1678 "parser.cc"
    break;

  case 44: // factor: loc
#line 354 "parser.yy"
    {
        yylhs.value.as < DTL::ExpNode* > () = yystack_[0].value.as < DTL::LocNode* > ();
    }
#line 1686 "parser.cc"
    break;

  case 45: // intlit: INTLITERAL
#line 358 "parser.yy"
    {
        yylhs.value.as < DTL::IntLitNode* > () = new IntLitNode(yystack_[0].value.as < DTL::IntLitToken * > ()->pos(), yystack_[0].value.as < DTL::IntLitToken * > ()->num());
    }
#line 1694 "parser.cc"
    break;

  case 46: // loc: id
#line 363 "parser.yy"
    {
        yylhs.value.as < DTL::LocNode* > () = yystack_[0].value.as < DTL::IDNode* > ();
    }
#line 1702 "parser.cc"
    break;

  case 47: // loc: id LBRACKET id RBRACKET
#line 367 "parser.yy"
    {
        yylhs.value.as < DTL::LocNode* > () = new ArrayIndexNode(yystack_[3].value.as < DTL::IDNode* > ()->pos(), yystack_[3].value.as < DTL::IDNode* > (), yystack_[1].value.as < DTL::IDNode* > ());
    }
#line 1710 "parser.cc"
    break;

  case 48: // id: ID
#line 372 "parser.yy"
    {
        yylhs.value.as < DTL::IDNode* > () = new IDNode(yystack_[0].value.as < DTL::IDToken * > ()->pos(), yystack_[0].value.as < DTL::IDToken * > ()->value());
    }
#line 1718 "parser.cc"
    break;


#line 1722 "parser.cc"

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


  const signed char Parser::yypact_ninf_ = -70;

  const signed char Parser::yytable_ninf_ = -1;

  const short
  Parser::yypact_[] =
  {
     -70,     9,     1,   -70,     7,   -70,    10,    17,   -70,   -70,
     -70,    27,    27,    40,    22,   -70,    32,    47,    50,   -70,
      36,    54,    22,    50,    24,   -70,   -70,   -70,   -70,    41,
      22,    22,    66,    68,    76,    50,    50,    27,    50,    50,
      27,    83,    49,    65,   -70,   -70,   -70,   -13,    -3,    79,
      82,   -70,    92,    98,    27,   114,    22,   125,   -70,   -70,
     138,   -70,   -70,    19,   -70,   156,   149,   157,   152,   148,
     162,   -70,   -70,   -70,    50,    27,    -1,   -70,   -70,   -70,
     116,   154,    27,    27,    27,   155,   -70,   164,   163,    -9,
      27,    27,    27,    27,    27,   146,   171,   173,   150,   151,
      27,   167,   168,   169,   174,   166,   177,   146,   148,   148,
      27,    27,    27,   182,   186,   187,   188,   148,   -70,   -70,
      20,    38,   180,   181,   183,   148,   148,   148,   148,   148,
     172,   175,   191,   193,   195,    55,    56,    57,    58,   196,
     198,   148,   148,   148,   178,   179,   184,   185,   148,   148,
      59,    96,   102,   199,   202,   203,   204,   103,   115,   189,
     190,   192,   148,   148,   148,   148,   -70,   -70,   205,   208,
     209,   126,   127,   128,   129,   148,   148,   148,   -70,   -70,
     -70,   -70,   130,   136,   142,   -70,   -70,   -70
  };

  const signed char
  Parser::yydefact_[] =
  {
       5,     0,     0,     1,     0,    34,     0,     0,     4,     3,
       2,     0,     0,     0,     0,    48,     0,     0,     0,    45,
       0,     0,     0,     0,     0,    39,    41,    43,    44,    46,
       0,    12,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    11,     7,     8,    42,    36,    35,     0,
       0,    37,    38,     0,     0,     0,    12,     0,    40,    47,
       0,     9,    10,     0,     6,     0,     0,     0,     0,    17,
       0,    18,    19,    16,     0,     0,     0,    13,    15,    14,
       0,     0,     0,     0,     0,     0,    33,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    31,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    29,    30,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    32,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    20,    25,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    21,    22,
      23,    24,     0,     0,     0,    26,    27,    28
  };

  const short
  Parser::yypgoto_[] =
  {
     -70,   -70,   -70,   -70,   210,   165,   161,    12,   -70,   -70,
     -70,   111,   -70,   -69,   221,   -21,   -70,   -70,   -70,   -11,
     194,    16
  };

  const signed char
  Parser::yydefgoto_[] =
  {
       0,     1,     2,     8,     9,    42,    10,    69,    70,    71,
      72,   106,   107,    73,    11,    24,    49,    25,    26,    27,
      28,    29
  };

  const unsigned char
  Parser::yytable_[] =
  {
      78,    36,    34,    20,    15,     4,    38,     5,    97,     3,
      32,    33,    39,     5,    47,    48,    38,    51,    52,    41,
      43,     6,    39,    13,    98,    99,    14,    16,    17,    19,
      82,    83,    15,    35,    84,    21,   130,     7,    36,     6,
      65,    65,    37,    38,     4,    43,     5,    66,    67,    39,
      22,    78,    78,    80,   131,    15,    53,    19,    30,    65,
      78,    19,    31,    23,    40,    55,    78,    78,    78,    78,
      60,   144,   145,   146,   147,   159,    65,    65,    65,    65,
      65,    78,    78,    78,    44,    35,    45,    56,    78,    78,
      36,    81,    85,    46,    54,    38,    57,    58,    88,    89,
      90,    39,    78,    78,    78,    78,   100,   101,   102,   103,
     104,    38,   160,    78,    78,    78,   112,    65,   161,   166,
     120,   121,    59,    65,    65,    35,   122,   123,   124,   129,
      36,   167,    61,    63,    86,    38,    65,   135,   136,   137,
     138,    39,   178,   179,   180,   181,   185,    65,    65,    65,
      65,    65,   186,   150,   151,   152,    64,    65,   187,    74,
     157,   158,    75,    65,    91,    92,    93,    94,    77,    65,
      76,    87,    95,   105,   171,   172,   173,   174,    79,   108,
      96,   109,   110,   111,   113,   114,   115,   182,   183,   184,
     125,   116,   117,   118,   126,   127,   128,   132,   133,   141,
     134,   142,   139,   143,   148,   140,   149,   162,   153,   154,
     163,   164,   165,   175,   155,   156,   176,   177,   119,   168,
     169,    62,   170,    18,    68,    12,     0,     0,     0,     0,
       0,    50
  };

  const short
  Parser::yycheck_[] =
  {
      69,    14,    23,    14,     5,     4,    19,     6,    17,     0,
      21,    22,    25,     6,    35,    36,    19,    38,    39,    30,
      31,    20,    25,    13,    33,    34,     9,    11,    12,     7,
      31,    32,     5,     9,    35,     3,    16,    36,    14,    20,
      21,    21,    18,    19,     4,    56,     6,    28,    29,    25,
       3,   120,   121,    74,    16,     5,    40,     7,    22,    21,
     129,     7,     8,    13,    23,    16,   135,   136,   137,   138,
      54,    16,    16,    16,    16,    16,    21,    21,    21,    21,
      21,   150,   151,   152,    18,     9,    18,    22,   157,   158,
      14,    75,    76,    17,    11,    19,    17,    15,    82,    83,
      84,    25,   171,   172,   173,   174,    90,    91,    92,    93,
      94,    19,    16,   182,   183,   184,   100,    21,    16,    16,
     108,   109,    24,    21,    21,     9,   110,   111,   112,   117,
      14,    16,    18,     8,    18,    19,    21,   125,   126,   127,
     128,    25,    16,    16,    16,    16,    16,    21,    21,    21,
      21,    21,    16,   141,   142,   143,    18,    21,    16,     3,
     148,   149,    13,    21,     9,    10,    11,    12,    16,    21,
      13,    17,     8,    27,   162,   163,   164,   165,    16,     8,
      17,     8,    32,    32,    17,    17,    17,   175,   176,   177,
       8,    17,    26,    16,     8,     8,     8,    17,    17,     8,
      17,     8,    30,     8,     8,    30,     8,     8,    30,    30,
       8,     8,     8,     8,    30,    30,     8,     8,   107,    30,
      30,    56,    30,    13,    63,     4,    -1,    -1,    -1,    -1,
      -1,    37
  };

  const signed char
  Parser::yystos_[] =
  {
       0,    38,    39,     0,     4,     6,    20,    36,    40,    41,
      43,    51,    51,    13,     9,     5,    58,    58,    41,     7,
      56,     3,     3,    13,    52,    54,    55,    56,    57,    58,
      22,     8,    56,    56,    52,     9,    14,    18,    19,    25,
      23,    56,    42,    56,    18,    18,    17,    52,    52,    53,
      57,    52,    52,    58,    11,    16,    22,    17,    15,    24,
      58,    18,    42,     8,    18,    21,    28,    29,    43,    44,
      45,    46,    47,    50,     3,    13,    13,    16,    50,    16,
      52,    58,    31,    32,    35,    58,    18,    17,    58,    58,
      58,     9,    10,    11,    12,     8,    17,    17,    33,    34,
      58,    58,    58,    58,    58,    27,    48,    49,     8,     8,
      32,    32,    58,    17,    17,    17,    17,    26,    16,    48,
      44,    44,    58,    58,    58,     8,     8,     8,     8,    44,
      16,    16,    17,    17,    17,    44,    44,    44,    44,    30,
      30,     8,     8,     8,    16,    16,    16,    16,     8,     8,
      44,    44,    44,    30,    30,    30,    30,    44,    44,    16,
      16,    16,     8,     8,     8,     8,    16,    16,    30,    30,
      30,    44,    44,    44,    44,     8,     8,     8,    16,    16,
      16,    16,    44,    44,    44,    16,    16,    16
  };

  const signed char
  Parser::yyr1_[] =
  {
       0,    37,    38,    39,    39,    39,    40,    41,    41,    41,
      42,    42,    42,    43,    43,    44,    44,    45,    45,    45,
      46,    46,    46,    46,    46,    46,    46,    46,    46,    47,
      48,    48,    49,    50,    51,    52,    52,    52,    52,    52,
      53,    54,    54,    55,    55,    56,    57,    57,    58
  };

  const signed char
  Parser::yyr2_[] =
  {
       0,     2,     2,     2,     2,     0,     8,     5,     6,     7,
       3,     1,     0,    10,    10,     2,     1,     1,     1,     1,
      12,    13,    13,    13,    13,    12,    15,    15,    15,     7,
       2,     1,     3,     4,     1,     3,     3,     3,     3,     1,
       2,     1,     3,     1,     1,     1,     1,     4,     1
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
  "OR", "AND", "PAD", "METADATASTREAM", "$accept", "program", "constdecls",
  "metadatastreamdecl", "constdecl", "intlist", "forstatement",
  "outstatements", "innernest", "ifstatement", "switchstatement",
  "casestatements", "casestatement", "outstatement", "type", "expr",
  "unarystmt", "term", "factor", "intlit", "loc", "id", YY_NULLPTR
  };
#endif


#if YYDEBUG
  const short
  Parser::yyrline_[] =
  {
       0,   126,   126,   132,   137,   143,   148,   154,   159,   166,
     173,   179,   185,   191,   199,   204,   209,   217,   221,   225,
     230,   234,   238,   242,   246,   250,   254,   258,   262,   274,
     281,   286,   291,   298,   304,   308,   313,   318,   323,   328,
     333,   341,   345,   349,   353,   357,   362,   366,   371
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
      35,    36
    };
    // Last valid token kind.
    const int code_max = 291;

    if (t <= 0)
      return symbol_kind::S_YYEOF;
    else if (t <= code_max)
      return static_cast <symbol_kind_type> (translate_table[t]);
    else
      return symbol_kind::S_YYUNDEF;
  }

#line 5 "parser.yy"
} // DTL
#line 2352 "parser.cc"

#line 379 "parser.yy"



void DTL::Parser::error(const std::string& msg) {

	std::cout << msg << std::endl;
	std::cerr << "syntax error" << std::endl;
}

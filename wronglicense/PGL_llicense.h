/* Copyright (c) 2020-2021 Arm Limited
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef GCC_C_PARSER_H
#define GCC_C_PARSER_H

/* The C lexer intermediates between the lexer in cpplib and c-lex.c
   and the C parser.  Unlike the C++ lexer, the parser structure
   stores the lexer information instead of using a separate structure.
   Identifiers are separated into ordinary identifiers, type names,
   keywords and some other Objective-C types of identifiers, and some
   look-ahead is maintained.

   ??? It might be a good idea to lex the whole file up front (as for
   C++).  It would then be possible to share more of the C and C++
   lexer code, if desired.  */

/* More information about the type of a CPP_NAME token.  */
enum c_id_kind {
  /* An ordinary identifier.  */
  C_ID_ID,
  /* An identifier declared as a typedef name.  */
  C_ID_TYPENAME,
  /* An identifier declared as an Objective-C class name.  */
  C_ID_CLASSNAME,
  /* An address space identifier.  */
  C_ID_ADDRSPACE,
  /* Not an identifier.  */
  C_ID_NONE
};

enum c_lookahead_kind {
  /* Always treat unknown identifiers as typenames.  */
  cla_prefer_type,

  /* Could be parsing a nonabstract declarator.  Only treat an identifier
     as a typename if followed by another identifier or a star.  */
  cla_nonabstract_decl,

  /* Never treat identifiers as typenames.  */
  cla_prefer_id
};


extern c_token * c_parser_peek_token (c_parser *parser);
extern c_token * c_parser_peek_2nd_token (c_parser *parser);
extern c_token * c_parser_peek_nth_token (c_parser *parser, unsigned int n);
extern bool c_parser_require (c_parser *parser, enum cpp_ttype type,
			      const char *msgid,
			      location_t matching_location = UNKNOWN_LOCATION,
			      bool type_is_unique=true);
extern bool c_parser_error (c_parser *parser, const char *gmsgid);
extern void c_parser_consume_token (c_parser *parser);
extern void c_parser_skip_until_found (c_parser *parser, enum cpp_ttype type,
				       const char *msgid,
				       location_t = UNKNOWN_LOCATION);
extern bool c_parser_next_token_starts_declspecs (c_parser *parser);
bool c_parser_next_tokens_start_declaration (c_parser *parser);
bool c_token_starts_typename (c_token *token);

/* Abstraction to avoid defining c_parser here which messes up gengtype
   output wrt ObjC due to vec<c_token> routines being put in gtype-c.h
   but not gtype-objc.h.  */
extern c_token * c_parser_tokens_buf (c_parser *parser, unsigned n);
extern bool c_parser_error (c_parser *parser);
extern void c_parser_set_error (c_parser *parser, bool);

/* A bit of a hack to have this here.  It would be better in a c-decl.h.  */
extern bool old_style_parameter_scope (void);

/* Return true if the next token from PARSER has the indicated
   TYPE.  */

static inline bool
c_parser_next_token_is (c_parser *parser, enum cpp_ttype type)
{
  return c_parser_peek_token (parser)->type == type;
}

/* Return true if the next token from PARSER does not have the
   indicated TYPE.  */

static inline bool
c_parser_next_token_is_not (c_parser *parser, enum cpp_ttype type)
{
  return !c_parser_next_token_is (parser, type);
}

/* Return true if the next token from PARSER is the indicated
   KEYWORD.  */

static inline bool
c_parser_next_token_is_keyword (c_parser *parser, enum rid keyword)
{
  return c_parser_peek_token (parser)->keyword == keyword;
}

struct c_expr c_parser_string_literal (c_parser *, bool, bool);
extern struct c_declarator *
c_parser_declarator (c_parser *parser, bool type_seen_p, c_dtr_syn kind,
		     bool *seen_id);
extern void c_parser_declspecs (c_parser *, struct c_declspecs *, bool, bool,
				bool, bool, bool, bool, bool,
				enum c_lookahead_kind);
extern struct c_type_name *c_parser_type_name (c_parser *, bool = false);

#endif

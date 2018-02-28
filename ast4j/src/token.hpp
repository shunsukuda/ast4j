// #pragma once
#ifndef AST4J_TOKEN_HPP_
#define AST4J_TOKEN_HPP_

namespace ast4j {
	enum Token {
		token_eof,

		// 3.9. keywords
		token_ABSTRACT,
		token_ASSERT,
		token_BOOLEAN,
		token_BREAK,
		token_BYTE,
		token_CASE,
		token_CATCH,
		token_CHAR,
		token_CLASS,
		token_CONST,
		token_CONTINUE,
		token_DEFAULT,
		token_DO,
		token_DOUBLE,
		token_ELSE,
		token_ENUM,
		token_EXTENDS,
		token_FINAL,
		token_FINALLY,
		token_FLOAT,
		token_FOR,
		token_IF,
		token_GOTO,
		token_IMPLEMENTS,
		token_IMPORT,
		token_INSTANCEOF,
		token_INSTANCEOF,
		token_INTERFACE,
		token_LONG,
		token_NATIVE,
		token_NEW,
		token_PACKAGE,
		token_PRIVATE,
		token_PROTECTED,
		token_PUBLIC,
		token_RETURN,
		token_SHORT,
		token_STATIC,
		token_STRICTFP,
		token_SUPPER,
		token_SWITCH,
		token_SYNCHRONIZED,
		token_THIS,
		token_THROW,
		token_THROWS,
		token_TRANSIENT,
		token_TRY,
		token_VOID,
		token_VOLATILE,
		token_WHILE,

		// 3.10. Literals
		token_INTLIT,
		token_FLOATLIT,
		token_BOOLLIT,
		token_CHARLIT,
		token_STRINGLIT,
		token_NULLLIT,

		// 3.11. Separators
		token_LPAREN,     // (
		token_RPAREN,     // )
		token_LBRACE,     // {
		token_RBRACE,     // }
		token_LBRACK,     // [
		tokne_RBRACK,     // ]
		token_SEMI,       // ;
		token_COMMA,      // ,
		token_DOT,        // .
		token_ELLIPSIS,   // ...
		token_AT,         // @
		token_COLONCOLON, // ::

		// 3.12. Operators
		token_ASSIGN,         // =
		token_GT,             // >
		token_LT,             // <
		token_BANG,           // !
		token_TILDE,          // ~
		token_QUESTION,       // ?
		token_COLON,          // :
		token_ARROW,          // ->
		token_EQUAL,          // ==
		token_GE,             // >=
		token_LE,             // <=
		token_NOTEQUAL,       // !=
		token_AND,            // &&
		token_OR,             // ||
		token_INC,            // ++
		token_DEC,            // --
		token_ADD,            // +
		token_SUB,            // -
		token_MUL,            // *
		token_DIV,            // /
		token_BITAND,         // &
		token_BITOR,          // |
		token_CARET,          // ^
		token_MOD,            // %
		token_LSHIFT,         // <<
		token_RSHIFT,         // >>
		token_URSHIFT,        // >>>
		token_ADD_ASSIGN,     // +=
		token_SUB_ASSIGN,     // -=
		token_MUL_ASSIGN,     // *=
		token_DIV_ASSIGN,     // /=
		token_AND_ASSIGN,     // &=
		token_OR_ASSIGN,      // |=
		token_XOR_ASSIGN,     // ^=
		token_MOD_ASSIGN,     // %=
		token_LSHIFT_ASSIGN,  // <<=
		token_RSHIFT_ASSIGN,  // >>=
		token_URSHIFT_ASSIGN, // >>>=
	};
}

#endif
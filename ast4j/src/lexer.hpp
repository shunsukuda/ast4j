// #pragma once

// https://docs.oracle.com/javase/specs/jls/se8/html/index.html
#ifndef AST4J_LEXER_HPP_
#define AST4J_LEXER_HPP_

// https://github.com/BenHanson/lexertl 
#include "lexertl/lexertl/generator.hpp"
#include "lexertl/lexertl/iterator.hpp"
#include "token.hpp"

namespace ast4j {
	typedef struct macro_pair {
		const char *_name;
		const char *_regex;
	} macro_pair;

	typedef struct rule_pair {
		const char *_regex;
		std::size_t _id;
	} rule_pair;

	static macro_pair g_macros_[] = {
		{ "any", "[\t\v\f\r\n\040-\377]" }, // 0x20-0xFF
		{ "anyctrl", "[\001-\037]" },       // 0x01-0x1F
		
		// 3.3. Unicode Escapes
		{"UnicodeInputCharacter",
			"{UnicodeEscape}|"
			"{RawInputCharacter}"},
		{"UnicodeEscape", "\\{UnicodeMarker}{HexDigit}{4}"},
		{"UnicodeMarker", "u[u]?"},
		{"RawInputCharacter", " "}, /* any Unicode character */

		// 3.4. LineTerminators
		{"LineTerminator", "[\n\r]|\r\n"}, /* LF CR CRLF */
		{"InputCharacter", "{UnicodeInputCharacter}"}, /* but not CR LF */

		// 3.5. Input Elements and Tokens
		{"Input", "{InputElement}*{Sub}?"},
		{"InputElement",
			"{WhiteSpace}|"
			"{Comment}"
			/* "{Token}" */
		},
		/*
		{"Token",
			"{Identifier}|"
			"{Keyword}|"
			"{Literal}|"
			"{Separator}|"
			"{Operator}"},
		*/
		{"Sub", "\x1A"}, /* SUB(Ctrl-Z) */

		// 3.6. White Space
		{"WhiteSpace",
			"[ \t\f]|" /* SP HT FF */
			"{LineTerminator}"},

		// 3.7. Comments
		{"Comment", 
			"{TraditionalComment}|"
			"{EndOfLineComment}"},
		{"TraditionalCOmment", "[/][*]{CommentTail}"},
		{"CommentTail", 
			"[*]{CommentTailStar}|"
			"{NotStar}{CommentTail}"},
		{"CommentTailStar",
			"[/]|"
			"[*]{CommentTailStar}|"
			"{NotStarNotSlash}{CommentTail}"},
		{"NotStar",
			"{InputCharacter}|" /* but not * */
			"{LineTerminator}"},
		{"NotStartNotSlash",
			"{InputCharacter}|" /* but not * or | */
			"[/]|"
			"{LineTerminator}"},
		{"EndOfLineComment", "[/][/]{InputCharacter}"},

		// 3.8. Identifier
		{"Identifier",
			"{IdentifierCharas}"}, /* but not a {Keyword} or {BooleanLiteral} or {NullLiteral} */
		{"IdentifierChars",
			"{JavaLetter}|"
			"{JavaLetterOrDigit}*|",},
		{"JavaLetter",
			" "}, /* any Unicode character that is a "Java letter" */
		{"JavaLetterOrDigit",
			" "}, /* any Unicode character that is a "Java letter-or-digit" */

		// 3.10. Literals
		// 3.10.1. Integer Literals
		{"IntegerLiteral", 
			"{DecimalIntegerLiteral}|"
			"{HexIntegerLiteral}|"
			"{OctalIntegerLiteral}|"
			"{BinaryIntegerLiteral}"},
		{"DecimalIntegerLiteral","{DecimalNumeral}{IntegerTypeSuffix}?"},
		{"HexIntegerLiteral", "{HexNumeral}{IntegerTypeSuffix}?"},
		{"OctalIntegerLiteral", "{OctalNumeral}{IntegerTypeSuffix}?"},
		{"BinaryIntegerLiteral", "{BinaryNumeral}{IntegerTypeSuffix}?"},
		{"IntegerTypeSuffix", "[lL]"},

		{"DecimalNumeral",
			"0|"
			"{NonZeroDigit}{Digits}?|"
			"{NonZeroDigit}{Underscores}{Digits}"},
		{"NonZeroDigit", "[1-9]"},
		{"Digits",
			"{Digit}|"
			"{Digit}|{DigitsAndUnderscores}?{Digit}"},
		{"Digit",
			"0|"
			"{NonZeroDigit}"},
		{"DigitsAndUnderscores","{DigitOrUnderscore}{DigitOrUnderscore}*"},
		{"DigitOrUnderscore",
			"{Digit}|"
			"_"},
		{"Underscores", "_[_]*"},

		{"HexNumeral", "0[xX]{HexDigits}"},
		{"HexDigits",
			"{HexDigit}|"
			"{HexDigit}{HexDigitsAndUnderscores}?{HexDigit}"},
		{"HexDigit", "[0-9a-fA-F]"},
		{"HexDigitsAndUnderscores","{HexDigitOrUnderscore}{HexDigitOrUnderscore}*"},
		{"HexDigitOrUnderscore",
			"{HexDigit}|"
			"_"},

		{"OctalNumeral",
			"0{OctalDigits}|"
			"0{{Underscores}{OctalDigits}"},
		{"OctalDigits",
			"{OctalDigit}|"
			"{OctalDigit}{OctalDigitsAndUnderscores}?{OctalDigit}"},
		{"OctalDigit", "[0-7]"},
		{"OctalDigitsAndUnderscores","{OctalDigitOrUnderscore}{OctalDigitOrUnderscore}*"},
		{"OctalDigitOrUnderscore",
			"{OctalDigit}|"
			"_"},

		{"BinaryNumeral", "0[bB]{BinaryDigits}"},
		{"BinaryDigits",
			"{BinaryDigit}|"
			"{BinaryDigit}{BinaryDigitsAndUnderscores}?{BinaryDigit}"},
		{"BinaryDigit", "[0-1]"},
		{"BinaryDigitsAndUnderscores","{BinaryDigitOrUnderscore}{BinaryDigitOrUnderscore}*"},
		{"BinaryDigitOrUnderscore",
			"{BinaryDigit}|"
			"_"},

		// 3.10.2. Floating-Point Literals
		{"FloatingPointLiteral",
			"{DecimalFloatingPointLiteral}|"
			"{HexadecimalFloatingPointLiteral}"},
		{"DecimalFloatingPointLiteral",
			"{Digits}[.]{Digits}?{ExponentPart}?{FloatTypeSuffix}?|"
			"[.]{Digits}{ExponentPart}?{FloatTypeSuffix}?|"
			"{Digits}{ExponentPart}{FloatTypeSuffix}?|"
			"{Digits}{ExponentPart}?{FloatTypeSuffix}"
		},
		{"ExponentPart", "{ExponentIndicator}{SignedInteger}"},
		{"ExponentIndicator", "[eE]"},
		{"SignedInteger", "{Sign}?{Digits}"},
		{"Sign", "[+-]"},
		{"FloatTypeSuffix", "[fFdD]"},

		{"HexadecimalFloatingPointLiteral", "{HexSignificand}{BinaryExponent}{FloatTypeSuffix}?"},
		{"HexSignificand",  "{HexNumeral}[.]?|0[xX]{HexDigits}?[.]{HexDigits}"},
		{"BinaryExponent","{BinaryExponentIndicator}{SignedInteger}"},
		{"BinaryExponentIndicator", "[pP]"},

		// 3.10.3. Boolean Literals
		{"BooleanLiteral", "true|false"},

		// 3.10.4. Character Literals
		{"CharacterLiteral",
			"'{SingleCharacter}'|"
			"'{EscapeSequence}'"},
		{"SingleCharacter", "[{InputCharacter}[^'\\]]"}, /* bat not ' \ */

		// 3.10.5. String Literals
		{"StringLiteral", "\"{StringCharacter}\""},
		{"StringCharacter",
			"{InputCharacter}|" /* bat not  " \ */
			"{EscapeSequence}"},

		// 3.10.6. Escape Sequences for Character and String Literals.
		{"EscapeSequence",
			"\\[btnfr\"'\\]|" /* BS HT LF FF CR " '\ */
			"{OctalEscape}"}, /* Unicode \u0000 to \u00ff */
		{"OctalEscape",
			"\\{OctalDigit}|"
			"\\{OctalDigit}{2}|"
			"\\{ZeroToThree}{OctalDigit}{2}"},
		{"ZeroToThree", "[0-3]"},

		// 3.10.7. THe Null Literal
		{"NullLiteral", "null"},
		
	{0,0}
	};

	static rule_pair g_regexes_[] = {

		// 3.9. keywords
		{"abstract", token_ABSTRACT},
		{"assert", token_ASSERT},
		{"boolean", token_BOOLEAN},
		{"break", token_BREAK},
		{"byte", token_BYTE},
		{"case", token_CASE},
		{"catch", token_CATCH},
		{"char", token_CHAR},
		{"class", token_CLASS},
		{"const", token_CONST},
		{"continue", token_CONTINUE},
		{"default", token_DEFAULT},
		{"do", token_DO},
		{"double", token_DOUBLE},
		{"else", token_ELSE},
		{"enum", token_ENUM},
		{"extends", token_EXTENDS},
		{"final", token_FINAL},
		{"finally", token_FINALLY},
		{"float", token_FLOAT},
		{"for", token_FOR},
		{"if", token_IF},
		{"goto", token_GOTO},
		{"implements", token_IMPLEMENTS},
		{"import", token_IMPORT},
		{"instanceof", token_INSTANCEOF},
		{"instanceofinterface", token_INSTANCEOF},
		{"interface", token_INTERFACE},
		{"long", token_LONG},
		{"native", token_NATIVE},
		{"new", token_NEW},
		{"package", token_PACKAGE},
		{"private", token_PRIVATE},
		{"protected", token_PROTECTED},
		{"public", token_PUBLIC},
		{"return", token_RETURN},
		{"short", token_SHORT},
		{"static", token_STATIC},
		{"strictfp", token_STRICTFP},
		{"supper", token_SUPPER},
		{"switch", token_SWITCH},
		{"synchronized", token_SYNCHRONIZED},
		{"THiS", token_THIS},
		{"throw", token_THROW},
		{"throws", token_THROWS},
		{"transient", token_TRANSIENT},
		{"try", token_TRY},
		{"void", token_VOID},
		{"volatile", token_VOLATILE},
		{"while", token_WHILE},

		// 3.10. Literals
		{"{IntegerLiteral}", token_INTLIT},
		{"{FloatingPointLiteral}", token_FLOATLIT},
		{"{BooleanLiteral}", token_BOOLLIT},
		{"{CharacterLiteral}", token_CHARLIT},
		{"{StringLiteral}", token_STRINGLIT},
		{"{NullLiteral}", token_NULLLIT},

		// 3.11. Separators
		{"[(]", token_LPAREN},
		{"[)]", token_RPAREN},
		{"[{]", token_LBRACE},
		{"[}]", token_RBRACE},
		{"[[]", token_LBRACK},
		{"[]]", tokne_RBRACK},
		{";", token_SEMI},
		{",", token_COMMA},
		{"[.]", token_DOT},
		{"[.]{3}", token_ELLIPSIS},
		{"@", token_AT},
		{"::", token_COLONCOLON}, 

		// 3.12. Operators
		{"=", token_ASSIGN},
		{">", token_GT},
		{"<", token_LT},
		{"!", token_BANG},
		{"~", token_TILDE},
		{"[?]", token_QUESTION},
		{":", token_COLON},
		{"[-]>", token_ARROW},
		{"==", token_EQUAL},
		{">=", token_GE},
		{"<=", token_LE},
		{"!=", token_NOTEQUAL},
		{"&&", token_AND},
		{"[|]{2}", token_OR},
		{"[+}{2}", token_INC},
		{"[-]{2}", token_SUB},
		{"[+]", token_ADD},
		{"[-]", token_SUB},
		{"[*]", token_MUL},
		{"[/]", token_DIV},
		{"&", token_BITAND},
		{"[|]", token_BITOR},
		{"[^]", token_CARET},
		{"%", token_MOD},
		{"<<", token_LSHIFT},
		{">>", token_RSHIFT},
		{">>>", token_URSHIFT},
		{"[+]=", token_ADD_ASSIGN},
		{"[-]=", token_SUB_ASSIGN},
		{"[*]=", token_MUL_ASSIGN},
		{"[/]=", token_DIV_ASSIGN},
		{"&=", token_AND_ASSIGN},
		{"[|]=", token_OR_ASSIGN},
		{"[^]=", token_XOR_ASSIGN},
		{"%=", token_MOD_ASSIGN},
		{"<<=", token_LSHIFT_ASSIGN},
		{">>=", token_RSHIFT_ASSIGN},
		{">>>=", token_URSHIFT_ASSIGN},

		{ 0,0 }
	};

	void push_lexertl_rules(lexertl::rules);
}

#endif
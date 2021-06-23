Parsing with # Boost :: Spirit
## What is Boost :: Spirit?
  A library for writing parsing in C ++. You can parse only in C ++ without using yacc, lex, etc.
It can be widely used for JSON parser, calculator, config loading, oleore script, protocol parser, etc.

## Purpose of writing this guide
  This library is very interesting and exciting. I want to convey this fun. At the same time, it also has a delicate aspect, and you may encounter compilation errors that can be daunting, or you may be annoyed by the behavior. Time has passed since the Spirit was announced. Most of the information in the streets is old versions, and I think that more and more information sources are useless. Since there is little information dealing with Japanese character string processing, there is a high threshold for full-scale adoption of this library. There may be fewer people in a position to write such a guide than I think. I wrote this in the hope that more interesting things will come out in the world by writing this.

## How to proceed with this guide
We will deepen our understanding based on a small sample. I started to play working code, and it's a style of something. There are Qi, Pheonix, Karma, Lex as the composition of Spirit, but only Qi and Pheonix are handled.

## Parser

 * [Basic](parser_basic.md)
 * [Numeric parser](parser_numeric.md)
 * [Character parser](parser_char.md)
 * [bool parser](parser_bool.md)
 * [symbols parser](symbols.md)
 * [Parser Operators](parser_operators.md)
 * [Auxiliary parser](parser_auxiliary.md)
 * [Parser Directive](parser_directive.md)
 * [Semantic Action (+ Phoenix)](semantic_action.md)
 
## Rules

 * [Write a rule](rule.md)
 * [Processing Nbyte characters](rule_nbytechars.md)
 * [Comment syntax (Skipper)](skipper.md)
 * [Read Structure (Fusion)](fusion.md)
 * [Use std :: pair (Fusion)](fusion2.md)
 * [Display error location (Position Iterator)](position_iterator.md)
 * [Numeric parser 2](parser_numeric2.md)
 * [Phoenix and Placeholder](phoenix2.md)

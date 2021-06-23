# Character parser

## Basic
 
### char type

  The rule will be char_, but the namespace will be different depending on the expected character code. (namespace qi = boost :: spirit :: qi)
 * qi :: ascii
 * qi :: iso8859_1
 * qi :: standard
 * qi :: standard_wide
 
  The design of this area is fluid, so there is no problem if you keep the two, standard and standard_wide.
  ascii and [iso8859_1] (https://en.wikipedia.org/wiki/ISO/IEC_8859-1) are included in standard.
  The namespaces shift_jis and euc_jp do not exist, but they are included in standard.
  utf-8 is included in standard. However, if utf-8 is processed by wchar_t via iostream codecvt, it is included in standard_wide.
 
| Character type (attribute) | Rule | Description |
|:--|:--|:--|
| char | qi :: standard :: char_ | Matches one character. |
| wchar_t | qi :: standard_wide :: char_ | Matches 1-character wide characters. |


Read one character (char version)
```cpp
//c ++: char example
#include <boost / spirit / include / qi.hpp>
#include <iostream>
#include <string>

namespace qi = boost :: spirit :: qi;

int main () {
  std :: string input = "a";
  char n;
  qi :: parse (input.begin (), input.end (), qi :: standard :: char_, n);
  std :: cout << n << std :: endl;
  return 0;
}
```


Read one character (wchar_t version)
```cpp
//c ++: wchar example
#include <boost / spirit / include / qi.hpp>
#include <iostream>
#include <string>

namespace qi = boost :: spirit :: qi;

int main () {
  std :: wstring input = L "day";
  wchar_t n;
  qi :: parse (input.begin (), input.end (), qi :: standard_wide :: char_, n);
  std :: wcout.imbue (std :: locale (""));
  std :: wcout << n << std :: endl;
  return 0;
}
```

### char literal

| Character type (attribute) | Rule | Sample | Description |
|:--|:--|:--|:--|
| qi :: unused_type | qi :: lit (1 character character value) | qi :: lit ('X') | Matches 1 character value. |
| qi :: unused_type | qi :: lit (1 character wide character value) | qi :: lit (L'X') | Matches 1 character wide character literal. |

  qi :: unused_type indicates a type that is not retrieved as a value in an attribute.

### String literal

| Character type (attribute) | Rule | Sample | Description |
|:--|:--|:--|:--|
| qi :: unused_type | qi :: lit (string) | qi :: lit ("fixed string") | Matches the specified string. |
| qi :: unused_type | qi :: lit (wide character string) | qi :: lit (L "fixed character string") | Matches the specified wide character string. |

Check if it is the same as the string constant (char version)
```cpp
//c ++: String constant example
#include <boost / spirit / include / qi.hpp>
#include <iostream>
#include <string>

namespace qi = boost :: spirit :: qi;

int main () {
  std :: string input = "Hello"; // SJIS interpretation on Windows, UTF-8 interpretation on others
  auto s = input.begin ();
  auto e = input.end ();
  qi :: parse (s, e, qi :: lit ("hello"));
  // qi :: parse (s, e, qi :: lit ("hello"));
  std :: cout << ((s == e)? "Match": "Error") << std :: endl;
  return 0;
}
```
  The iterator passed to qi :: parse indicates the parsing range of the input value.
  The start position of the argument is passed by reference, which is the position where the match can be completed after parsing.
  If s == e, it indicates a full match, and if s! = E, it indicates that there was no match.
  Parsing on the commented out line changes the result from match to error.

### string

| Character type (attribute) | Rule | Sample |
|:--|:--|:--|
| std :: string | + (qi :: standard :: char_) ||
| std :: wstring | + (qi :: standard_wide :: char_) ||

  _ Here comes the + sign in the rules. _ An operator that can be adapted to a rule and indicates one or more iterations.
  Some similar operators indicate * 0 or more iterations.
  In regular expressions, + *, which has the same meaning, is a postfix operator, but it is implemented as a prefix operator for implementation in the C ++ grammar.
  It is clever that the repetition of char type can be extracted as string type.

Extract character string (wchar_t version)
```cpp
//c ++: 2 string constants
#include <boost / spirit / include / qi.hpp>
#include <iostream>
#include <string>

namespace qi = boost :: spirit :: qi;

int main () {
  std :: wstring input = L "Hello";
  std :: wstring n;
  qi :: parse (input.begin (), input.end (), + qi :: standard_wide :: char_, n);
  std :: wcout.imbue (std :: locale (""));
  std :: wcout << n << std :: endl;
  return 0;
}
```


## Character condition specification
  It is possible to specify matching characters for qi :: standard :: char_, qi :: standard_wide :: char_.
 There are two ways to specify

### Specifying the range from start to end

| Arguments | Description | Example |
|:--|:--|:--|
qi :: standard :: char_ (char arg1, char arg2) | arg1: start character, arg2: end character, match characters from start character to end character | qi :: standard :: char_ ('A','A', 'Z'); |
qi :: standard_wide :: char_ (wchar_t arg1, wchar_t arg2) | arg1: start character, arg2: end character, match characters from start character to end character | qi :: standard_wide :: char_ (L'A' , L'Z'); |


Character range Extracts the specified character string
```cpp
//c ++: Range specification example
#include <boost / spirit / include / qi.hpp>
#include <iostream>
#include <string>

namespace qi = boost :: spirit :: qi;

int main () {
  std :: string input = "FBIJHCBFIJXXX";
  std :: string n;
  qi :: parse (input.begin (), input.end (), + qi :: standard :: char_ ('A','J'), n);
  std :: cout << n << std :: endl; // X does not match the rule, so it will be displayed up to FBIJHCBFIJ
  return 0;
}
```
  SJIS and UTF-8 (characters other than ASCII) cannot be specified in the character range specification.
  Then, can it be specified by wchar_t of qi :: standard_wide?
  "The answer is half that can be solved, but not fundamentally."
  The definition of UNICODE such as variant characters is complicated and is not something that simply comes within the range.

  The handling of non-ASCII characters will be explained later. _

### Character specification by format

| Arguments | Description | Example |
|:--|:--|:--|
| qi :: standard :: char_ (const char * arg) | arg: character specification | qi :: standard :: char_ ("A-Z"); |
| qi :: standard_wide :: char_ (const wchar_t * arg) | arg: character specification | qi :: standard_wide :: char_ (L "a-fA-F0-9"); |

  In character specification, list the characters you want to specify. However, --characters must be specified at the beginning, and if they appear after the second character, the character range before and after --- is specified.
  In the case of "A-Z", it means that the character in the range of A to Z is specified.


Character Extracts the specified character string
```cpp
c ++: Character specification (specify characters individually) Example
#include <boost / spirit / include / qi.hpp>
#include <iostream>
#include <string>

namespace qi = boost :: spirit :: qi;

int main () {
  std :: wstring input = L "FBIJHABFIJXXX";
  std :: wstring n;
  qi :: parse (input.begin (), input.end (), + qi :: standard_wide :: char_ (L "ABFHIJ"), n);
  std :: wcout.imbue (std :: locale (""));
  std :: wcout << n << std :: endl;
  return 0;
}
```

## Character classification parser

  It is a rule of classified characters such as alphabets, numbers, white space, and newline characters.
  Like the character parser, the namespace differs depending on the expected character code. (namespace qi = boost :: spirit :: qi)

* qi :: ascii
 * qi :: iso8859_1
 * qi :: standard
 * qi :: standard_wide
 
The namespace ns is one of the following:
 
 * namespace ns = qi :: ascii;
 * namespace ns = qi :: iso8859_1;
 * namespace ns = qi :: standard;
 * namespace ns = qi :: standard_wide;

| Character classification | Rules | Examples |
|:--|:--|:--|
| Alphabet | ns :: alpha | a-zA-Z |
| Alphabet or numbers | ns :: alnum | a-zA-Z0-9 |
| Numbers | ns :: digit | 0-9 |
| Displayable characters | ns :: graph | Space! "# $% &'() = ~ ^ \\\\ | {} [] @` * +-/?> <, .A-zA-Z0-9 |
| Lowercase alphabet | ns :: lower | a-z |
| Uppercase alphabet | ns :: upper | A-Z |
| Phrase | ns :: punct |! "# $% &'() * +,-./ :; <=>? @ [\\] ^ _` {\ |} ~ |
| Blank | ns :: blank | Spaces, tabs |
| Space | ns :: space | Space, tab, CR, LF |
Hexadecimal characters | ns :: xdigit | 0-9a-fA-F |

  The implementation of character judgment differs depending on the namespace specification. The decision code depends on the locale code, such as std :: isalpha.
  The implementation of locale depends on the libraries provided by each platform.
  In his DEBUG version of Visual C ++, the ASSERT macro causes a range check error when an isalpha function call is passed through utf-8 code with qi :: standard.
  With this delicate implementation, he might want to write the necessary classifications himself, except for ns :: blank and ns :: space.

  If you want to specify Kanji, these character classification parsers are not enough and you need to write a special rule.

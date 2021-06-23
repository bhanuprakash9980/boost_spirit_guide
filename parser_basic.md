# Parser basic

  The rule consists of Iterator (input), Skipper (rule that skips input such as comments), and the type (attribute) of the parsed value.
  I will not touch on the explanation of Skipper in the basics, but will deal with it after I start to build rules.

  First, let's take a look at the basic rules for retrieving a value from a string input. To check the basic rules, use the code below.
  Inputs that do not match the rule will fail parsing (qi :: parse returns false).

```cpp
c ++: basic code
#include <boost / spirit / include / qi.hpp> // Use boost :: spirit :: qi
#include <iostream>
#include <string>

namespace qi = boost :: spirit :: qi; // Since the namespace is long, set it to qi

int main () {
  std :: string input = "12345"; // Input to parse. Please rewrite the value and play
  int n; // Variable to store the parsed result. This part depends on the rules you write.
  qi :: parse (// The body of the function to parse
    input.begin (), input.end (), // Specify the input to be parsed
    qi :: int_, // rules to parse
    n // Variable to store the parsed result
  );
  std :: cout << n << std :: endl; // Check the parsed result.
  return 0;
}
```
The rule to parse is equivalent to qi :: int_ and the input string is "12345".

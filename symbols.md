# Symbols

  You can associate a combination of strings with a value of your favorite type.
  namespace qi = boost :: spirit :: qi;

The definition is below
```cpp
template <typename Char, typename T, typename Lookup>
struct symbols;
```
  Char = char type
  T = attribute (value type)
  Lookup = string search class (default is tst_map <char, T>)
  However, T must meet the requirements of Primitive Type.

```cpp
C ++: char enum
#include <boost / spirit / include / qi.hpp>
#include <iostream>
#include <string>

namespace qi = boost :: spirit :: qi;

enum class Color {red, green, blue};

std :: ostream & operator << (std :: ostream & os, Color c) {
  if (c == Color :: red) os << "red";
  else if (c == Color :: green) os << "green";
  else if (c == Color :: blue) os << "blue";
  else os << "unknown";
  return os;
}

qi :: symbols <char, Color> color_;

int main () {

  // Add at runtime. It is also possible to add analysis results
  color_.add
    ("red", Color :: red)
    ("green", Color :: green)
    ("blue", Color :: blue)
  ;

  std :: string input = "green";
  Color c;
  qi :: parse (input.begin (), input.end (), color_, c);
  std :: cout << c << std :: endl;
  return 0;
}
```

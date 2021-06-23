# bool parser
   A bool parser is available. (namespace qi = boost :: spirit :: qi)
   Since it is prepared as a built-in type, let's use this for the bool type.

| Type (attribute) | Rule |
|:--|:--|
| bool | qi :: bool_ |

```cpp
c ++: qi :: bool_ example
#include <boost / spirit / include / qi.hpp>
#include <iostream>

namespace qi = boost :: spirit :: qi;

int main () {
   std :: string input = "true false";
   bool a, b;
   qi :: parse (input.begin (), input.end (), qi :: bool_ >>''>> qi :: bool_, a, b);
   std :: cout << a << "," << b << std :: endl;
   return 0;
}
```

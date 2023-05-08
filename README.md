# Header-only C++ library that implements a statically allocated circular buffer

The main purpose of this data-structure is to efficiently store last N incoming measurements (a typical requirement in 
embedded systems).

`.at()` returns the added items in recently-added first (e.g. at(0) returns the element which was just added)

Example:

```c++
#include "StaticCircularBuffer.hpp"
#include <iostream>

std::cout << "Allocating static circular buffer for 3 elements" << std::endl;
StaticCircularBuffer<uint32_t, 3> buf;
buf.fill(0); // zero-initialize buffer
std::cout << "buf.size() == " << buf.size() << std::endl;

std::cout << "Adding 3 elements" << std::endl;
buf.add(1);
buf.add(2);
buf.add(3);

std::cout << "buf.size() == " << buf.size() << std::endl;
// at returns last-added elements first
std::cout << "buf.at(0) == " << buf.at(0) << std::endl;

std:: cout << "Adding next element- the oldest element is overwritten" << std::endl;
buf.add(4);
// size has reached maximum
std::cout << "buf.size() == " << buf.size() << std::endl;

std::cout << "Buffer contents: ";
for (auto val: buf) {
    std::cout << val << ", ";
}
std::cout << std::endl;
```

Output:
```
Allocating static circular buffer for 3 elements
buf.size() == 0
Adding 3 elements
buf.size() == 3
buf.at(0) == 3
Adding next element- the oldest element is overwritten
buf.size() == 3
Buffer contents: 4, 3, 2,
```
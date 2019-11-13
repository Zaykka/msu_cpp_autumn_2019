#include <iostream>
#include "serializer.h"
#include <sstream>

struct Data
{
    uint64_t a;
    bool b;
    uint64_t c;

    template <class Serializer>
    Error serialize(Serializer& serializer)
    {
        return serializer(a, b, c);
    }
    template<class Deserizlizer>
    Error deserialize(Deserizlizer& deserizlizer) {
        return deserizlizer(a, b, c);
    }
};



int main() {
    Data x { 1, true, 2 };

    std::stringstream stream;

    Serializer serializer(stream);
    assert(serializer.save(x) == Error::NoError);

    Data y { 0, false, 0 };

    Deserializer deserializer(stream);
    const Error err = deserializer.load(y);

    assert(err == Error::NoError);

    assert(x.a == y.a);
    assert(x.b == y.b);
    assert(x.c == y.c);

    std::stringstream stream2("1 1 1");
    Deserializer des2(stream2);
    assert(des2.load(y) == Error::CorruptedArchive);

    std::stringstream stream3("true 34");
    Deserializer des3(stream3);
    assert(des3.load(y) == Error::CorruptedArchive);
}

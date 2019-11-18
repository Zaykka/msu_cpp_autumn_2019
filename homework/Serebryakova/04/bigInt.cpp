#include <iostream>
#include "bigInt.h"


BigInt::BigInt() : num(new char[1]),size(0), sign(true) {}
BigInt::BigInt(int val) {
    if (!val) {
        size = 1;
        sign = true;
        num  = new char[1];
        num[0] = 0;
    } else {
        size = 0;
        sign = true;
        int valC = val;
        while (valC) {
            ++size;
            valC /= 10;
        }
        num = new char[size];
        for (int i = 0; i < size; ++i) {
            num[i] = val % 10;
            val /= 10;
        }
    }
}
BigInt::BigInt(const BigInt& copied) : num(new char[copied.size]), size(copied.size) {
    sign = copied.sign;
    std::copy(copied.num, copied.num + size, num);
}

BigInt& BigInt::operator=(const BigInt& copied) {
    if (this == &copied) {
        return *this;
    }
    char * ptr = new char[copied.size];
    delete [] num;
    num = ptr;
    sign = copied.sign;
    size = copied.size;
    std::copy(copied.num, copied.num + size, num);
    return *this;
}

BigInt BigInt::plus(const BigInt& right) const {
    if (size >= right.size) {
        BigInt res;
        bool fl = false;
        for (int i = 0; i < size; ++i) {
            int r = i < right.size ? right.num[i] : 0;
            fl = (num[i] + r + fl) > 9;
        }
        res.size = size + fl;
        res.sign = true;
        res.num = new char[res.size];
        fl = false;
        for (int i = 0; i < res.size; ++i) {
            int a = i < right.size ? right.num[i] : 0;
            int b = i < size ? num[i] : 0;
            res.num[i] = (a + b + fl) % 10;
            fl = (a + b + fl) > 9;
        }
        return res;
    }
    return right.plus(*this);
}

BigInt BigInt::minus(const BigInt& right) const{
    BigInt res;
    res.size = 0;
    res.sign = true;
    bool add = false;
    for (int i = 0; i < size; ++i) {
        int a = i < size ? right.num[i] : 0;
        int digit = num[i] - add - a;
        add = digit < 0;
        if (digit) {
            res.size = i + 1;
        }
    }
    if (!res.size) {
        return BigInt(0);
    }
    res.num = new char[res.size];
    add = false;
    for (int i = 0; i < res.size; ++i) {
        int b = i < right.size ? right.num[i] : 0;
        int digit = num[i] - add - b;
        add = digit < 0;
        res.num[i] =  add ? 10 + digit : digit;
    }
    return res;
}

bool BigInt::bigAbs(const BigInt& right) const {
if (size < right.size) {
    return true;
} else if (size > right.size)
    return false;
for (int i = size - 1; i >= 0; --i) {
    if (num[i] < right.num[i]) {
        return true;
    } else if (num[i] > right.num[i]) {
        return false;
    }
}
return false;
}

BigInt BigInt::operator+(const BigInt& right) {
    BigInt left(*this);
    if (left.sign == right.sign) {
        return left.sign ? left.plus(right) : -left.plus(right);
    } else if (left.sign) {

        return !left.bigAbs(right) ? left.minus(right) : -right.minus(left);
    }
    return !left.bigAbs(right) ? -left.minus(right) : right.minus(left);
}
BigInt BigInt::operator-() const {
    BigInt res(*this);
    if (res.size == 1 && res.num[0] == 0) {
        return res;
    }
    res.sign = !sign;
    return res;
}
BigInt BigInt::operator-(const BigInt& right) {
    return BigInt(*this) + (-right);
}
std::ostream& operator<<(std::ostream &out, const BigInt &val) {
    if (!val.sign) {
        out << '-';
    }
    for (int i = val.size - 1; i >= 0; --i) {
        out << static_cast<char>(val.num[i] + '0');
    }
    return out;
}

bool operator==(const BigInt& right, const BigInt& left) {
    if (left.sign == right.sign && left.size == right.size) {
        for (int i = 0; i < right.size; ++i) {
            if (right.num[i] != left.num[i]) {
                return false;
            }
        }
        return true;
    }
    return false;
}

bool operator!=(const BigInt& right, const BigInt& left) {
    return !(right==left);
}

bool operator>(const BigInt& right, const BigInt& left) {
    if (right.sign > left.sign) {
        return true;
    } else if (right.sign < left.sign) {
        return false;
    }
    if (right.sign) {
        return left.bigAbs(right);
    }
    return !left.bigAbs(right);
}

bool operator<(const BigInt& right, const BigInt& left) {
    return left > right;
}

bool operator<=(const BigInt& right, const BigInt& left) {
    return right == left || right < left;
}
bool operator>=(const BigInt& right, const BigInt& left) {
    return right == left || right > left;
}

BigInt::~BigInt() {
    delete [] num;
}



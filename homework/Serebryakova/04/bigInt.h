#pragma once
#include <iostream>


class BigInt {
    char* num;
    int size;
    bool sign;
public:
    BigInt();

    BigInt(int);

    BigInt(const BigInt&);

    BigInt plus(const BigInt& right) const;

    BigInt minus(const BigInt& right) const;

    bool bigAbs(const BigInt& right) const;

    BigInt& operator=(const BigInt&);

    BigInt operator+(const BigInt&);

    BigInt operator-() const;

    BigInt operator-(const BigInt&);

    friend std::ostream& operator<<(std::ostream& , const BigInt&);

    friend bool operator==(const BigInt&, const BigInt&);

    friend bool operator!=(const BigInt&, const BigInt&);

    friend bool operator>(const BigInt&, const BigInt&);

    friend bool operator<(const BigInt&, const BigInt&);

    friend bool operator>=(const BigInt&, const BigInt&);

    friend bool operator<=(const BigInt&, const BigInt&);
};


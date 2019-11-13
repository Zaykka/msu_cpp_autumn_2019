#pragma once
#include <iostream>

enum class Error
{
    NoError,
    CorruptedArchive
};

class Serializer
{
    static constexpr char Separator = ' ';
    std::ostream &out;
public:
    explicit Serializer(std::ostream& out) : out(out) {}

    template <class T>
    Error save(T& object) {
        return object.serialize(*this);
    }

    template <class... ArgsT>
    Error operator()(ArgsT... args) {
        return process(args...);
    }

private:
    // process использует variadic templates
    template <class T, class... ArgsT>
    Error process(T& p, ArgsT&... args) {
        put(p);
        return process(args...);
    }
    template <class T>
    Error process(T& last) {
        put(last);
        return Error::NoError;
    }
    void put(bool b) {
        out << (b ? "true" : "false") << Separator;
    }
    void put(uint64_t val) {
        out << val << Separator;
    }
};

class Deserializer {
    std::istream &in;
public:
    explicit Deserializer(std::istream& in) : in(in) {}
    template <class T>
    Error load(T &object) {
        return object.deserialize(*this);
    }
    template <class... ArgsT>
    Error operator()(ArgsT&... args) {
        return process(args...);
    }
private:
    template<class T, class... ArgsT>
    Error process(T& p, ArgsT&... args) {
        if (get(p) == Error::CorruptedArchive) {
            return Error::CorruptedArchive;
        }
        return process(args...);
    }
    template<class T>
    Error process(T& last) {
        return get(last);
    }
    Error get(bool& a) {
        std::string s;
        in >> s;
        if (s == "true") {
            a = true;
        } else if (s == "false") {
            a = false;
        } else {
            return Error::CorruptedArchive;
        }
        return Error::NoError;
    }
    Error get(uint64_t& val) {
        std::string s;
        in >> s;
        if (!isdigit(s[0])) {
            return Error::CorruptedArchive;
        }
        val = std::stoull(s);
        return Error::NoError;
    }
};

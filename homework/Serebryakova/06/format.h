#include <iostream>
#include<vector>
#include<sstream>
#include <string>

template <class T>
std::string to_str(T&& x) {
    std::stringstream s;
    s << x;
    return s.str();
}

template<class... argsT>
std::string format(const std::string& st, argsT&&... args) {
    std::stringstream out;
    if (st.find("{}") != std::string::npos) {
        throw std::runtime_error("");
    }
    std::vector<std::string> param = {to_str(std::forward<argsT>(args))... };
    for (int i = 0; i < st.size(); ++i) {
        if (st[i] == '{') {
            ++i;
            int r = 0;
            while(st[i] != '}') {
                if (i > st.size() - 1  || !isdigit(st[i])) {
                    throw std::runtime_error("ff");
                }
                r *= 10;
                r += st[i] - '0';
                ++i;
            }
            ++i;
            if (r >= param.size()) {
                throw std::runtime_error("");
            }
            out << param[r];
        }
        if (st[i] == '}') {
            throw std::runtime_error("");
        } else if (st[i] != '\0'){
            out << st[i];
        }
    }
    return out.str();
}

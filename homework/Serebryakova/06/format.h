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
    std::string str(st);
    using std::to_string;
    if (str.find("{}") != std::string::npos) {
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
            if (r >= param.size()) {
                throw std::runtime_error("");
            }
            std::string repl = "{" + std::to_string(r) + "}";
            std::size_t pos = str.find(repl);
            str.replace(pos, repl.length(), param[r]);
        }
    }
    if (str.find('}') != std::string::npos) {
        throw std::runtime_error("tt");
    }
    return str;
}


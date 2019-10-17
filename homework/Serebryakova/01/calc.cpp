#include <iostream>
#include <vector>
#include <string>


struct Expression {
    std::string token;
    std::vector<Expression> args;
    explicit Expression(const std::string &token) : token(token) {}
    Expression(const std::string &token, Expression a) : token(token), args{a} {}
    Expression(const std::string &token, Expression a, Expression b) : token(token), args{a, b} {}
};

class Parser {
    std::string parse_token();
    Expression parse_simple_expression();
    Expression parse_binary_expression(int min_priority);
public:
    std::string str;
    std::string::const_iterator curr_token;
    explicit Parser(const std::string &str) : str(str), curr_token(str.begin()) {}
    Expression parse();
};

std::string Parser::parse_token() {
    for (; isspace(*curr_token); ++curr_token) {}
    if (isdigit(*curr_token)) {
        std::string number;
        for(; isdigit(*curr_token); ++curr_token) {
            number.push_back(*curr_token);
        }
        return number;
    }
    std::vector<std::string> ch = {"+", "-", "*", "/"};
    std::string t = "+-*/";
    auto symb = t.find(*curr_token);
    if (symb != std::string::npos) {
        ++curr_token;
        return ch[symb];
    }
    return "";
}

Expression Parser::parse_simple_expression() {
    auto token = parse_token();
    if (token.empty()) {
        throw std::runtime_error("invalid input");
    }
    if (isdigit(token[0])) {
        return Expression(token);
    }
    return Expression(token, parse_simple_expression());
}

int get_priority(const std::string& op) {
    switch (*op.c_str()) {
        case '+':
            return 1;
        case '-':
            return 1;
        case '*':
            return 2;
        case '/':
            return 2;
        default:
            return 0;
    }
}

Expression Parser::parse_binary_expression(int min_priority) {
    auto left = parse_simple_expression();
    while (1) {
        auto op =  parse_token();
        auto priority = get_priority(op);
        if (priority <= min_priority) {
            --curr_token;
            return left;
        }
        auto right = parse_binary_expression(priority);
        left = Expression(op, left, right);
    }
}

Expression Parser::parse() {
    return parse_binary_expression(0);
}
int eval(const Expression& expr) {
    switch(expr.args.size()) {
        case 2: {
            auto a = eval(expr.args[0]);
            auto b = eval(expr.args[1]);
            switch (expr.token[0]) {
                case '+':
                    return a + b;
                case '-':
                    return a - b;
                case '*':
                    return a * b;
                case '/':
                    return a / b;
                default:
                    throw std::runtime_error("Unknown binary operator");
            }
        }
        case 1: {
            auto a = eval(expr.args[0]);
            if (expr.token == "-") {
                return -a;
            }
            throw std::runtime_error("Unknown binary operator");
        }
        case 0: {
            return std::strtol(expr.token.c_str(), nullptr, 10);
        }
        default:
            throw std::runtime_error("Unknown expression");
    }
}

int main(int argc, char* argv[]) {
    try {
        std::string str(argv[1]);
        Parser p(str);
        auto res = eval(p.parse());
        std::cout << res;
    }
    catch (std::exception& e) {
        std::cout << e.what() << std::endl;
        return 2;
    }
    return 0;
}



cmake_minimum_required(VERSION 3.12)
project(simplex_method)

set(CMAKE_CXX_STANDARD 14)

add_executable(simplex_method calc.cpp)

#
##include <iostream>
##include <vector>
##include <string>
#
#
#struct Expression {
#std::string token; // + - * /
#std::vector<Expression> args; // один или два числа
#Expression(std::string token) : token(token) {}
#Expression(std::string token, Expression a) : token(token), args{a} {}
#Expression(std::string token, Expression a, Expression b) : token(token), args{a, b} {}
#};
#
#class Parser {
#std::string parse_token();
#Expression parse_simple_expression();
#Expression parse_binary_expression(int min_priority);
#public:
#const char *str;
#explicit Parser(const char* str) : str(str) {}
#Expression parse();
#};
#
#std::string Parser::parse_token() {
#while (isspace(*str)) {
#++str;
#}
#if (isdigit(*str)) {
#std::string number;
#while(isdigit(*str)) {
#number.push_back(*str);
#str++;
#}
#return number;
#}
#static const std::vector<std::string> ch = {"+", "-", "*", "/"};
#for (auto &t : ch) {
#if (*str == *t.c_str()) {
#str++;
#return t;
#}
#}
#return "";
#}
#
#Expression Parser::parse_simple_expression() {
#auto token = parse_token();
#if (token.empty()) {
#std::cout << "Invalid input" << std::endl;
#exit(1);
#}
#if (isdigit(token[0])) {
#return Expression(token);
#}
#return Expression(token, parse_simple_expression()); // ?????
#}
#
#int get_priority(const std::string& op) {
#switch (*op.c_str()) {
#case '+':
#return 1;
#case '-':
#return 1;
#case '*':
#return 2;
#case '/':
#return 2; // default 2+3*4
#default:
#return 0;
#}
#}
#
#Expression Parser::parse_binary_expression(int min_priority) {
#auto left = parse_simple_expression();
#while (1) {
#auto op =  parse_token();
#auto priority = get_priority(op);
#if (priority <= min_priority) {
#str--;
#return left;
#}
#auto right = parse_binary_expression(priority);
#left = Expression(op, left, right);
#}
#}
#
#Expression Parser::parse() {
#return parse_binary_expression(0);
#}
#int eval(const Expression& expr) {
#switch(expr.args.size()) {
#case 2: {
#auto a = eval(expr.args[0]);
#auto b = eval(expr.args[1]);
#switch (expr.token[0]) {
#case '+':
#return a + b;
#case '-':
#return a - b;
#case '*':
#return a * b;
#case '/':
#return a / b;
#default:
#std::cout << "Unknown binary operator" << std::endl;
#exit(1);
#}
#}
#case 1: {
#auto a = eval(expr.args[0]);
#if (expr.token == "-") {
#return -a;
#} else {
#std::cout << "Unknown unary operator" << std::endl;
#exit(1);
#}
#}
#case 0: {
#return std::strtod(expr.token.c_str(), nullptr);
#}
#
#}
#}
#
#
#int main() {
#Parser p("-2+3*4");
#auto res = eval(p.parse());
#std::cout << res << std::endl;
#return 0;
#}



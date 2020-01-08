#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <thread>
#include <exception>
#include <algorithm>


const std::string COPY = "copy";
const size_t MAXSIZE = 1024 * 1024;


void create_bin_file(std::ofstream &out) {
    for (int i = 0; i < 1024 * 1023; ++i) {
        uint64_t rand_num = rand() % 113;
        out.write((char *) &rand_num, sizeof(rand_num));
    }
}


void copy(const std::string& name1, const std::string& name2){
    auto *buf = new uint64_t [MAXSIZE];
    std::ifstream in(name1, std::ios::binary);
    std::ofstream out(name2, std::ios::binary);

    while (!in.eof()) {
        in.read((char*) buf, 1024 * 1024);
        if (in.gcount()) {
            out.write((char*) buf, in.gcount());
        }
    }
    out.close();
    in.close();
    delete[] buf;
}

void merge(std::vector<std::string>& f_names){
    copy(f_names[0], "output");
    std::ifstream in(COPY, std::ios::binary);
    std::ofstream out("output", std::ios::binary);
    uint64_t c1, c2;
    
    for (size_t i = 1; i < f_names.size(); ++i) {
        copy("output", COPY);
        std::ifstream tmp(f_names[i], std::ios::binary);

        in.read((char*) &c1, sizeof(c1));
        tmp.read((char*) &c2, sizeof(c2));

        while (!tmp.eof()) {
            if(!in.gcount()) {
                while (!tmp.eof()) {
                    out.write((char*) &c2, sizeof(c2));
                    tmp.read((char*) &c2, sizeof(c2));
                }
            } else if (c2 <=  c1) {
                out.write((char*) &c2, sizeof(c2));
                tmp.read((char*) &c2, sizeof(c2));
            } else {
                out.write((char*) &c1, sizeof(c1));
                in.read((char*) &c1, sizeof(c1));
            }
        }

        if (in.gcount()) {
            out.write((char*) &c1, sizeof(c1));
            auto *buf = new uint64_t[MAXSIZE];

            while (!in.eof()) {
                in.read((char*) buf, MAXSIZE);
                out.write((char*) buf, in.gcount());
            }
            delete[] buf;
        }
    }
}

void clean_files(std::vector<std::string>& names) {
    for (auto &name: names) {
        if (remove(name.c_str())) {
            throw std::runtime_error("Can't remove file");
        }
    }
    
    if (remove(COPY.c_str())) {
        throw std::runtime_error("Can't remove file");
    }
}

void file_sort(std::ofstream& out) {
    std::ifstream in("input", std::ios::binary);
    
    if (!in) {
        throw std::runtime_error("Can't open file: input");
    }

    std::vector<std::string> names;
    auto *buf = new uint64_t [MAXSIZE];
    
    for (int i = 0; !in.eof(); ++i) {
        std::string name = "output" + std::to_string(i) + ".bin";
        names.push_back(name);

        in.read((char*) buf, MAXSIZE);
        size_t cnt = in.gcount();

        if(cnt){
            size_t read_ = cnt / (2 * sizeof(uint64_t));

            std::thread th1([buf, read_]() {
                std::sort(buf, buf + read_);
            });

            std::thread th2([buf, read_]() {
                std::sort(buf + read_, buf + 2 * read_);
            });

            th1.join();
            th2.join();

            out.open(name, std::ios::binary);
            if(!out.is_open()) {
                delete[] buf;
                throw std::runtime_error("Can't open file: " + name);
            }
            out.write((char*) buf, read_ * sizeof(uint64_t));
            out.close();
            ++i;

            name = "output" + std::to_string(i) + ".bin";
            names.push_back(name);
            out.open(name, std::ios::binary);
            if(!out.is_open()){
                delete[] buf;
                throw std::runtime_error("Can't open file: " + name);
            }
            out.write((char*) (buf + read_), cnt - read_ * sizeof(uint64_t));
            out.close();
        }
    }
    
    delete[] buf;
    merge(names);
    clean_files(names);
    in.close();
}

int main(){
    std::ofstream out("input", std::ios::binary);
    
    if (!out) {
        std::cerr << "Can't open file: input" << std::endl;
        return 1;
    }

    create_bin_file(out);
    out.close();
    
    try {
        file_sort(out);
        
    } catch(const std::runtime_error &err) {
        std::cerr << err.what() << std::endl;
        return 1;
    }
    return 0;
}


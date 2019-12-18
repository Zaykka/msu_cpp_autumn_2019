#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <thread>


const std::string COPY = "copy";


void copy(const std::string& name1, const std::string& name2){
    auto *buf = new uint64_t [1024 * 1024];
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
            auto *buf = new uint64_t[1024 * 1024];

            while (!in.eof()) {
                in.read((char*) buf, 1024 * 1024);
                out.write((char*) buf, in.gcount());
            }
            delete[] buf;
        }
    }
}

int main(){
    std::ofstream out("input", std::ios::binary);
    
    for (int i = 0; i < 1024 * 1023; ++i) {
        uint64_t rand_num = rand() % 113;
        out.write((char *) &rand_num, sizeof(rand_num));
    }
    out.close();
    
    std::vector<std::string> names;
    auto *buf = new uint64_t [1024 * 1024];
    std::ifstream in("input", std::ios::binary);

    for (int i = 0; !in.eof(); ++i){
        std::string name = "output" + std::to_string(i) + ".bin";
        names.push_back(name);

        in.read((char*) buf, 1024 * 1024);
        size_t cnt = in.gcount();

        if(cnt){
            size_t read_ = cnt / (2 * sizeof(uint64_t));

            std::thread th1([buf, read_]() {
                std::sort(buf, buf + read_);
            });

            std::thread th2([buf, read_]() {
                std::sort(buf +read_,
                    buf + 2 * read_);
            });

            th1.join();
            th2.join();

            out.open(name, std::ios::binary);
            if(!out.is_open()){
                delete[] buf;
                return 1;
            }
            out.write((char*) buf, read_ * sizeof(uint64_t));
            out.close();
            ++i;

            name = "output" + std::to_string(i) + ".bin";
            names.push_back(name);
            out.open(name, std::ios::binary);
            if(!out.is_open()){
                delete[] buf;
                return 1;
            }
            out.write((char*) (buf + read_), cnt - read_ * sizeof(uint64_t));
            out.close();
        }
    }
    merge(names);
    
    for (auto &name: names) {
        remove(name.c_str());
    }
    remove(COPY.c_str());
    
    in.close();
    delete[] buf;
    return 0;
}



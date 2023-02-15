#include <iostream>

#include "common.h"
#include "DimacsParser.h"
#include "DPLL.h"

int main(int argc, char **argv) {
//    argc = 11;
    if (argc < 2){
        std::cerr<<"error: no input files"<<std::endl;
        return 1;
    }
//    argv = "/test.dimacs";
    for (int i = 1; i<argc; i++) {
        std::string f(argv[i]);
        std::cout<<f<<std::endl;
        formula phi = DimacsParser::parse(f);

        //timer start
        auto start = std::chrono::steady_clock::now();
        //solve
        DPLL solver(phi);
        bool sat = solver.check_sat();
        model m;
        if(sat){
            m = solver.get_model();
        }
        //timer end
        auto end = std::chrono::steady_clock::now();

        if(sat) {
            std::cout<<" sat"<<std::endl;
            for (const auto &p:m){
                std::cout<<"   "<<p.first<<" -> "<<p.second<<std::endl;
            }
        }else{
            std::cout<<" unsat"<<std::endl;
        }

        auto duration = std::chrono::duration_cast<std::chrono::duration<double>>(end - start);
        std::cout<<" time: "<<duration.count()<<std::endl;
    }
    return 0;
}

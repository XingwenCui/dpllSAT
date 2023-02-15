//
// Created by Xingwen Cui on 15/2/2023.
//
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cassert>
#include "common.h"

#ifndef DPLLSAT_DIMACSPARSER_H
#define DPLLSAT_DIMACSPARSER_H

class DimacsParser{
public:
    /**
     * Parse a dimacs file, static type wont change members
     * @param file_name dimacs file name
     * @return a parsed formula
     */
    static formula parse(const std::string &file_name) {
        std :: ifstream fin(file_name);
        if (!fin){
            std::cerr <<"file not found: "<<file_name<<"'"<<std::endl;
            std::exit((1));
        }

        int n = 0, m = 0;
        while (!fin.eof()) {
            char ch;
            fin >> ch;

            if (ch == 'c') { //c-line: comment
                char buf[1024];
                fin.getline(buf, 1024);
            } else if (ch == 'p') { //p-line: clause will begin
                std::string buf;
                fin >> buf;
                assert(buf == "cnf");
                fin >> n >> m;
                break;
            } else{ //unexpected line
                std::cerr << "parse error at char"<<ch<<"'"<<std::endl;
                std::exit(1);
            }
        }

        //clause begin
        std::vector<clause> clauses;
        for (int i = 0; i < m; i++){
            clause c;
            while (!fin.eof()) {
                int v;
                fin>>v;
                if(v == 0){
                    clauses.push_back(c);
                    break;
                }
                assert(VAR(v)<=n);
                c.push_back(v);
            }
        }
        assert(clauses.size() == m);

        return formula(n,clauses);
    }

};

#endif //DPLLSAT_DIMACSPARSER_H

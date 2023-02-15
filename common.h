

#include "vector"
#include "unordered_map"
#include "string"
#include "sstream"

#ifndef DPLLSAT_COMMON_H
#define DPLLSAT_COMMON_H

/**
 * A literal is an atomic formula (contains one variable)
 * In dimacs, + positive number denote the corresponding variables;
 *            - negative number denote the negations of the corresponding variables
 * Varibales are numbered from 1
 */
typedef int literal;
#define POSITIVE(x) ((x)>0)
#define NEGATIVE(x) ((x)<0)
#define VAR(x) (((x)>0) ? (x):(-(x)))

//A clause is a list of literals (their disjunction)
typedef std::vector<literal> clause;

//A formula is a list of clauses (their conjunction)
struct formula{
    int num_variable;
    std::vector<clause> clauses;
    //formula function to assign initial formula
    formula(int n, const std::vector<clause>& clauses): num_variable(n),clauses(clauses) {}
};

//A satisfying model (interpretation)
// e.g. model[i] = false: variable i is assigned to false.
typedef std::unordered_map<int,bool> model;

#endif //DPLLSAT_COMMON_H

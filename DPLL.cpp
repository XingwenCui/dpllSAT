
#include "DPLL.h"

bool DPLL::check_sat() {
    std::unordered_map<int, int> atomStatus; //record node status 0,1,2
    int clause_num = phi.clauses.size(); //clause number
    int atomNum = phi.num_variable; //number of variables;

    for (int i=1; i<=atomNum; i++)
        result.insert(std::make_pair(i,true)); //insert the initial assignemnts to model (all true)

    int* nodeStatus = new int[atomNum];
    for (int i=0; i<atomNum; i++)
        nodeStatus[i] = 0; //set all node status 0 initially

    int ptr = 0; //point current node

    while (true){
        if (nodeStatus[ptr] == 2)
            break;
        else if(nodeStatus[ptr] == 0){
            nodeStatus[ptr]++;
            result[ptr + 1] = false;
        }
        else{
            nodeStatus[ptr]++;
            result[ptr+1] = true;
        }
        int solveStatus = 2; //0->not solution; 1->solution; 2->not confirm
        //check whether is solution
        bool wholeValue = true; // the whole formula's truth value
        for (int i=0; i<clause_num; i++){ //check each clause
            bool currValue=false; //this current clause value
            bool any_notsure=false; //Is there unsure lit?
            int len = phi.clauses[i].size();  //the lit number in this clause

            for (int j=0; j<len; j++){
                int currvar = phi.clauses[i][j]; //current value
                if(VAR(currvar)<=ptr+1){
                    if((POSITIVE(currvar)&&result[currvar]) || (NEGATIVE(currvar)&&!result[VAR(currvar)])){
                        //one lit is true, the clause is true
                        currValue=true;
                        break;
                    }
                }else{
                    any_notsure=true; //There has not sure lit
                }
            }

            wholeValue=wholeValue&&currValue;
            if(currValue||any_notsure){
                continue;
            } else{
                solveStatus=0; //not soltion
                break;
            }
        }
        if(wholeValue)
            solveStatus=1;
        //finish check
        if(solveStatus==0) { //not solution backtrack
            while (ptr > 0 && nodeStatus[ptr] == 2) //back to not confirm status
                ptr--;
            for (int i = ptr + 1; i < atomNum; i++)
                nodeStatus[i] = 0;
        } else if(solveStatus==1)
            return true;
        else ptr++;
    }
    return false;
}

model DPLL::get_model() {
    return this->result;
}
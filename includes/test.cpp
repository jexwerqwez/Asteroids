#include "base.h"

#define NB -125
#define NM -90
#define NS -55
#define ZN -20
#define Z 0
#define ZP 20
#define PS 55
#define PM 90
#define PB 125
#define MIN(A, B) (((A) < (B)) ? (A) : (B))
#define MAX(A, B) (((A) > (B)) ? (A) : (B))
#define AND 1
#define OR 2

class Rule {
    int current_state;
    int operation;
    int delta_state;
    int previous_state;
public:
    Rule(int cur, int op, int del, int prev) : 
    current_state(cur), operation(op), delta_state(del), previous_state(prev) {};
    void setRules(int cur_st, int delta_st, int prev_st);
    int getCurr() {return current_state;};
    int getOper() {return operation;};
    int getDelta() {return delta_state;};
    int getPrev() {return previous_state;};
};

class Fuzzy_Controller {
    vector<Rule*> all_rules;
    int basis;
public:
    Fuzzy_Controller(int b) : basis(b) {};
    int getBasis() {return basis;};
    vector<Rule*> getRules() {return all_rules;};
    void rules_manager();
    double rules_processing(int e, int de);
    double membership_function(int x, int mu, int basis) {
        return exp(-pow(x - mu, 2) / (2 * pow(basis, 2)));
    }
};

void Rule::setRules(int cur_st, int delta_st, int prev_st) {
    current_state = cur_st;
    delta_state = delta_st;
    previous_state = prev_st;
}

void Fuzzy_Controller::rules_manager() {
    all_rules.push_back(new Rule(Z, AND, Z, Z));
    all_rules.push_back(new Rule(PB, OR, PB, NB));
    all_rules.push_back(new Rule(NB, OR, NB, PB));
    all_rules.push_back(new Rule(NM, AND, ZN, PB));
    all_rules.push_back(new Rule(PM, AND, ZP, NB));
    all_rules.push_back(new Rule(ZN, AND, ZN, ZP));
    all_rules.push_back(new Rule(ZP, AND, ZP, ZN));

    all_rules.push_back(new Rule(NS, AND, PS, ZP));
    all_rules.push_back(new Rule(NS, AND, NS, PM));
    all_rules.push_back(new Rule(PS, AND, NS, ZN));
    all_rules.push_back(new Rule(PS, AND, PS, NM));
}

double Fuzzy_Controller::rules_processing(int e, int de) {
    double num = 0, den = 0;
    for (int i = 0; i < all_rules.size(); i++) {
        double alpha = 0, mf_cur = 0, mf_delt = 0;
        mf_cur = membership_function(e, all_rules[i]->getCurr(), getBasis());
        mf_delt = membership_function(de, all_rules[i]->getDelta(), getBasis());
        alpha = (all_rules[i]->getOper() == 1) ? MIN(mf_cur, mf_delt) : MAX(mf_cur, mf_delt);
        num += (alpha * all_rules[i]->getPrev());
        den += alpha;
    }
    return num / den;
}

int main() {
    Fuzzy_Controller fuz(30);
    fuz.rules_manager();
    int e = 50;
    int de = -70;
    fuz.rules_processing(e,de);
    std::cout << e << ' ' << de << ' ' << fuz.rules_processing(e, de) << std::endl;
    return 0;
}

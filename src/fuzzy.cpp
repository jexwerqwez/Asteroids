#include "../includes/fuzzy.h"

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
    for (long unsigned int i = 0; i < all_rules.size(); i++) {
        double alpha = 0, mf_cur = 0, mf_delt = 0;
        mf_cur = membership_function(e, all_rules[i]->getCurr(), getBasis());
        mf_delt = membership_function(de, all_rules[i]->getDelta(), getBasis());
        alpha = (all_rules[i]->getOper() == 1) ? MIN(mf_cur, mf_delt) : MAX(mf_cur, mf_delt);
        num += (alpha * all_rules[i]->getPrev());
        den += alpha;
    }
    return num / den;
}

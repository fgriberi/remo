#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "../../mili/mili/mili.h"

using namespace std;

int main()
{
    stringstream ss("gi|221214|dbj|D00627.1|CXA9CG Human coxsackievirus A9 genomic RNA, complete genome, strain: Griggs");
    vector<string> result;
    ss >> mili::Separator(result, '|');
    cout << result[3] << endl;
    return 0;
}


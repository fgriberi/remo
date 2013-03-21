#include <assert.h>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

#include <mili/mili.h>
using namespace mili;

class Results
{
    string lastMicro;
    size_t negatives;
    size_t zeroes;
    size_t positives;

    void outData() const
    {
        if (!lastMicro.empty())
        {
            cout << lastMicro << ", " << negatives << ", " << zeroes << ", " << positives << endl;
        }
    }

    void clear()
    {
        negatives = zeroes = positives = 0;
    }
public:
    Results()
    {
        clear();
    }

    void add(const string& micro, int delta)
    {
        if (lastMicro != micro)
        {
            outData();
            lastMicro = micro;
            clear();
        }

        if (delta < 0)
            ++negatives;
        else if (delta == 0)
            ++zeroes;
        else
            ++positives;
    }

    void end()
    {
        outData();
    }
};

enum Columns
{
    ColMicro = 0,
    ColUpperCaseCountOrig = 5,
    ColMCountOrig = 6,
    ColUpperCaseCountHum = 10,
    ColMCountHum = 11,
    MaxCol
};

int main()
{
    string line;
    vector<string> fields;
    Results r;

    int upperCaseCountOrig;
    int mCountOrig;
    int upperCaseCountHum;
    int mCountHum;

    while (cin >> Separator(fields, ','))
    {
        assert(fields.size() >= MaxCol);

        assert(from_string(fields[ColUpperCaseCountOrig], upperCaseCountOrig));
        assert(from_string(fields[ColMCountOrig], mCountOrig));
        assert(from_string(fields[ColUpperCaseCountHum], upperCaseCountHum));
        assert(from_string(fields[ColMCountHum], mCountHum));

        r.add(fields[ColMicro], ((upperCaseCountOrig - mCountOrig) - (upperCaseCountHum - mCountHum)));
        fields.clear();
    }
    r.end();

    return EXIT_SUCCESS;
}


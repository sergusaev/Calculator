#ifndef ARGUMENT_H
#define ARGUMENT_H

#include <QString>

static const int MAX_RADIX_COUNT = 25;

class Argument
{

public:
    Argument();
    Argument(double value);
    ~Argument();

    long double m_value;
    int m_radixCount;
    QString toString() const;

    void addDigit(int value);
    void addDot();
    void reset();

    int m_exp = 0;
    bool m_expectRightArg = false;



};

#endif // ARGUMENT_H

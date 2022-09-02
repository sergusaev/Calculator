#ifndef ARGUMENT_H
#define ARGUMENT_H

#include <QString>

static const int MAX_RADIX_COUNT = 15;

class Argument
{

public:
    Argument();
    Argument(long double value);
    ~Argument();

    QString toString();

    void addDigit(int value);
    void addPoint();
    void reset();
    void update();

    long double m_value;    // type up to 20 meaning signs
    int m_signsCount;
    int m_exponent;
    bool m_expectRightArg;



};

#endif // ARGUMENT_H

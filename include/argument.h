#ifndef ARGUMENT_H
#define ARGUMENT_H

#include <QString>
#include <ttmath/ttmath.h>

static const int MAX_RADIX_COUNT = 25;

class Argument
{

public:
    Argument();
    Argument(ttmath::Big<1,2> value);
    ~Argument();

    QString toString();

    void addDigit(int value);
    void addPoint();
    void reset();
    void update();

    ttmath::Big<1,2> m_value;    // type up to 20 meaning signs
    int m_signsCount;
    int m_exponent;
    bool m_expectRightArg;



};

#endif // ARGUMENT_H

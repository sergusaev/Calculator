#ifndef ARGUMENT_H
#define ARGUMENT_H

#include <QString>
#include <ttmath/ttmath.h>

static const int MAX_RADIX_COUNT = 26;

class Argument
{

public:
    Argument();
    Argument(ttmath::Big<1,2> value);
    ~Argument();

    QString toString();

    void addDigit(char value);
    void addPoint();
    void reset();
    void update();

    ttmath::Big<1,2> m_value;
    std::string m_valueString;
    bool m_expectRightArg;



};

#endif // ARGUMENT_H

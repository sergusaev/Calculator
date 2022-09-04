#include "argument.h"
#include <sstream>
#include <cmath>
#include <iomanip>

inline ttmath::Big<1,2> fractional(ttmath::Big<1,2> value)
{
    return value - (ttmath::Big<1,2>)value;
}

inline int decimalsFromVal(ttmath::Big<1,2> value)
{
    int d = 1;
    ttmath::Big<1,2> mul = 10;
    ttmath::Big<1,2> tolerance = "1000000000000000000000000";
    for (; d < 25 && static_cast<ttmath::Big<1,2>>(fractional(value * mul) * tolerance) != 0; ++d) {
        mul *= 10;
        tolerance /= 10;
    }
    return d;
}


Argument::Argument()
{
    reset();
}

Argument::Argument(ttmath::Big<1, 2> value)

{
    reset();
    m_value = value;

}

Argument::~Argument()
{

}

QString Argument::toString()
{
    std::stringstream ss;
    if(m_exponent >= 0) {
        ss << std::fixed << std::setprecision(0);
    } else {
        ss <<  std::fixed << std::setprecision(-m_exponent - 1);
    }
    ss <<  m_value;
    if(m_exponent == -1) {
        ss<< ".";
    }
     return QString::fromStdString(ss.str());
}


void Argument::addDigit(int value)
{

    if(m_expectRightArg) {
        reset();
    }

    if(m_signsCount >= MAX_RADIX_COUNT) {
        return;
    }
    ++m_signsCount;
    if(m_value >= 0){
        if(m_exponent >= 0) {
            m_value = m_value * 10 + value;
        } else {
            m_value = m_value + value * std::pow(10, m_exponent);
            --m_exponent;
        }
    } else {
        if(m_exponent >= 0) {
            m_value = m_value * 10 - value;
        } else {
            m_value = m_value - value * std::pow(10, m_exponent);
            --m_exponent;
        }
    }
}

void Argument::addPoint()
{
    if(m_expectRightArg) {
        reset();
    }
    if(m_signsCount > MAX_RADIX_COUNT || m_exponent < 0) {
        return;
    }
    ++m_signsCount;
    m_exponent = -1;

}

void Argument::reset()
{
    m_exponent = 0;
    m_value = 0;
    m_signsCount = 0;
    m_expectRightArg = false;
}

void Argument::update()
{
    if((m_value - (ttmath::Big<1,2>)m_value) == 0) {
        m_exponent = 0;
    } else {
        m_exponent = fractional(m_value) == 0 ? 0 : -1 - decimalsFromVal(m_value);
    }
    std::stringstream ss;
    ss << m_value;
    m_signsCount = ss.str().size();
    if(m_exponent < 0) {
        m_signsCount -= m_exponent;
    }
}

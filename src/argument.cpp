#include "argument.h"
#include <sstream>
#include <cmath>
#include <iomanip>

inline long double fractional(long double value)
{
    return value - (long long)value;
}

inline int decimalsFromVal(long double value)
{
    int d = 1;
    long long mul = 10;
    long long tolerance = 1000000000000000;
    for (; d < 15 && (long long)(fractional(value * mul) * tolerance); ++d) {
        mul *= 10;
        tolerance /= 10;
    }
    return d;
}


Argument::Argument()
{
    reset();
}

Argument::Argument(long double value)

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
    if((m_value - (long long)m_value) == 0) {
        m_exponent = 0;
    } else {
        m_exponent = fractional(m_value) == 0 ? 0 : -1 - decimalsFromVal(m_value);
    }
    m_signsCount = (int)std::log10((int)m_value + 1);
    if(m_exponent < 0) {
        m_signsCount -= m_exponent;
    }
}

#include "argument.h"
#include <sstream>
#include <cmath>
#include <iomanip>

Argument::Argument()
{
    reset();
}

Argument::Argument(double value)

{
    reset();
    m_value = value;

}

Argument::~Argument()
{

}

QString Argument::toString() const
{
    std::stringstream ss;
    if(m_exp >= 0) {
        ss << std::fixed << std::setprecision(0);
    } else {
        ss <<  std::fixed << std::setprecision(-m_exp - 1);
    }
    ss <<  m_value;
    if(m_exp == -1) {
        ss<< ".";
    }
    return QString::fromStdString(ss.str());
}

void Argument::addDigit(int value)
{
    if(m_expectRightArg) {
        reset();
    }
    if(m_radixCount >= MAX_RADIX_COUNT) {
        return;
    }
    if(m_value != 0 || value != 0 || m_exp < 0) {
        m_radixCount++;
    }
    if(m_value >= 0){
        if(m_exp >= 0) {
            m_value = m_value * 10 + value;
        } else {
            m_value = m_value + value * std::pow(10, m_exp);
            --m_exp;
        }
    } else {
        if(m_exp >= 0) {
            m_value = m_value * 10 - value;
        } else {
            m_value = m_value - value * std::pow(10, m_exp);
            --m_exp;
        }
    }
}

void Argument::addDot()
{
    if(m_expectRightArg) {
        reset();
    }
    if(m_radixCount >= MAX_RADIX_COUNT || m_exp < 0) {
        return;
    }
    m_radixCount++;
    m_exp = -1;

}

void Argument::reset()
{
    m_exp = 0;
    m_radixCount = 0;
    m_value = 0;
    m_expectRightArg = false;
}

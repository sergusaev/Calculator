#include "argument.h"
#include <sstream>
#include <cmath>
#include <iomanip>


Argument::Argument()
{
    reset();
}

Argument::Argument(ttmath::Big<1, 2> value)

{
    reset();
    m_value = value;
    m_valueString = m_value.ToString();

}

Argument::~Argument()
{

}

QString Argument::toString()
{
    std::string tmp = m_valueString.substr(0,MAX_RADIX_COUNT);
    return QString::fromStdString(tmp);
}


void Argument::addDigit(char value)
{
    if(m_expectRightArg) {
        reset();
    }
    if(m_valueString.size() >= MAX_RADIX_COUNT) {
        return;
    }
    if(m_valueString.size() == 1 && m_valueString[0] == '0') {
        m_valueString[0] = value;
    } else {
        m_valueString.push_back(value);
    }
    update();

}

void Argument::addPoint()
{
    if(m_expectRightArg) {
        reset();
    }
    if(m_valueString.size() > MAX_RADIX_COUNT || m_valueString.find('.') != std::string::npos) {
        return;
    }
    m_valueString.push_back('.');
}

void Argument::reset()
{
    m_value = 0;
    m_valueString = "0";
    m_expectRightArg = false;
}

void Argument::update()
{
    m_value = m_valueString;
}

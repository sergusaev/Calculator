#include "argument.h"
#include <sstream>
#include <cmath>


Argument::Argument()
{
    reset();
}

Argument::Argument(ttmath::Big<1, 2> value)

{
    static const ttmath::Big<1, 2> max_value = std::string(MAX_RADIX_COUNT, '9');
    reset();
    m_value = value;
    ttmath::Conv conv;
    conv.base = 10;
    conv.scient_from = std::numeric_limits<decltype(conv.scient_from)>::max();
    conv.round = MAX_RADIX_COUNT;

    if (m_value > max_value)
    {
        m_value.SkipFraction();
        m_valueString = m_value.ToString(conv);
        m_valueString = m_valueString.substr(m_valueString.size() - MAX_RADIX_COUNT);
        m_value = m_valueString;
        m_valueString = m_value.ToString(conv);
    }
    else
    {
        m_valueString = m_value.ToString(conv);
        if (m_valueString.size() > MAX_RADIX_COUNT)
        {
            m_valueString = m_valueString.substr(0, MAX_RADIX_COUNT);
            m_value = m_valueString;
        }
    }

}

Argument::~Argument()
{

}

QString Argument::toString()
{
    return QString::fromStdString(m_valueString);
}


void Argument::addDigit(char value)
{
    if(!m_digitsEnteringInProgress) {
        reset();
        m_digitsEnteringInProgress = true;
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
    if(!m_digitsEnteringInProgress) {
        reset();
        m_digitsEnteringInProgress = true;
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
    m_digitsEnteringInProgress = false;
}

void Argument::update()
{
    m_value = m_valueString;
}

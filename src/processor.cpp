#include "processor.h"
#include <cmath>


Processor *Processor::instance()
{
    static Processor *instance = new Processor;
    return instance;
}

void Processor::evaluate(Button::ButtonType type)
{
    switch(type) {
    case Button::ButtonType::DigitZero:
        m_rightValue.addDigit(0);
        break;
    case Button::ButtonType::DigitOne:
        m_rightValue.addDigit(1);
        break;
    case Button::ButtonType::DigitTwo:
        m_rightValue.addDigit(2);
        break;
    case Button::ButtonType::DigitThree:
        m_rightValue.addDigit(3);
        break;
    case Button::ButtonType::DigitFour:
        m_rightValue.addDigit(4);
        break;
    case Button::ButtonType::DigitFive:
        m_rightValue.addDigit(5);
        break;
    case Button::ButtonType::DigitSix:
        m_rightValue.addDigit(6);
        break;
    case Button::ButtonType::DigitSeven:
        m_rightValue.addDigit(7);
        break;
    case Button::ButtonType::DigitEight:
        m_rightValue.addDigit(8);
        break;
    case Button::ButtonType::DigitNine:
        m_rightValue.addDigit(9);
        break;
    case Button::ButtonType::Cancel:
        m_rightValue = Argument();
        m_leftValue = Argument();
        m_operation = Button::ButtonType::Plus;
        break;
    case Button::ButtonType::Back:
        m_rightValue.m_value = (m_rightValue.m_value) / 10;
        m_rightValue.m_radixCount--;
        break;
    case Button::ButtonType::Percent:
        m_rightValue.m_value = m_rightValue.m_value  / 100;
        m_rightValue.m_radixCount = m_rightValue.m_radixCount - 10;
        break;
    case Button::ButtonType::Dot:
        m_rightValue.addDot();
        break;
    case Button::ButtonType::Negative:
        m_rightValue.m_value = -m_rightValue.m_value;
        break;
    case Button::ButtonType::Plus:
    case Button::ButtonType::Minus:
    case Button::ButtonType::Equal:
    case Button::ButtonType::Multiplication:
    case Button::ButtonType::Division:
        doOperation();
        m_operation = (type == Button::ButtonType::Equal) ? m_operation : type;
        m_rightValue = m_leftValue;
        m_rightValue.m_expectRightArg = true;
        break;


    }
    emit rightValueChanged(m_rightValue.toString(), m_rightValue.m_radixCount);
}

void Processor::doOperation()
{
    switch(m_operation) {
    case Button::ButtonType::Plus:

        m_leftValue.m_value = m_leftValue.m_value + m_rightValue.m_value;

        break;
    case Button::ButtonType::Minus:
        m_leftValue.m_value = m_leftValue.m_value - m_rightValue.m_value;

        break;
    case Button::ButtonType::Multiplication:
        m_leftValue.m_value = m_leftValue.m_value * m_rightValue.m_value;

        break;

    }

    if((m_leftValue.m_value - (int)m_leftValue.m_value) == 0) {
        m_leftValue.m_exp = 0;
    } else {
        m_leftValue.m_exp = -1 - std::ceil(-std::log10(m_leftValue.m_value - (int)m_leftValue.m_value));
    }
    m_leftValue.m_radixCount = (int)std::log10((int)m_leftValue.m_value + 1);
    if(m_leftValue.m_exp < 0) {
        m_leftValue.m_radixCount-= m_leftValue.m_exp;
    }
}



Processor::Processor()
    : m_operation(Button::ButtonType::Plus)
{

}


Processor::~Processor()
{

}




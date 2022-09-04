#include "processor.h"
#include "secretmenuhandler.h"
#include <cmath>

Processor *Processor::instance()
{
    static Processor *instance = new Processor;
    return instance;
}

inline QString getStringOp(Button::ButtonType type) {
    QString op;
    switch(type){
    case Button::ButtonType::Plus:
        op = " + ";
        break;
    case Button::ButtonType::Minus:
        op = " - ";
        break;
    case Button::ButtonType::Division:
        op = " / ";
        break;
    case Button::ButtonType::Multiplication:
        op = " * ";
        break;
    default:
        break;
    }
    return op;
}

void Processor::evaluate(Button::ButtonType type)
{
    SecretMenuHandler::instance()->onButtonClicked(type);
    Argument tempDisplay;
    Argument *displayValue = &m_rightValue;
    switch(type) {
    case Button::ButtonType::DigitZero:
        m_rightValue.addDigit('0');

        break;
    case Button::ButtonType::DigitOne:
        m_rightValue.addDigit('1');

        break;
    case Button::ButtonType::DigitTwo:
        m_rightValue.addDigit('2');

        break;
    case Button::ButtonType::DigitThree:
        m_rightValue.addDigit('3');

        break;
    case Button::ButtonType::DigitFour:
        m_rightValue.addDigit('4');

        break;
    case Button::ButtonType::DigitFive: {
        m_rightValue.addDigit('5');

        break;
    }
    case Button::ButtonType::DigitSix:
        m_rightValue.addDigit('6');

        break;
    case Button::ButtonType::DigitSeven:
        m_rightValue.addDigit('7');

        break;
    case Button::ButtonType::DigitEight:
        m_rightValue.addDigit('8');

        break;
    case Button::ButtonType::DigitNine:
        m_rightValue.addDigit('9');

        break;
    case Button::ButtonType::Clean:
        m_rightValue = Argument();
        m_leftValue = Argument(1);
        m_operation = Button::ButtonType::Multiplication;
        m_bracketOpened = false;


        break;
    case Button::ButtonType::Brackets:
        if(!m_rightValue.m_digitsEnteringInProgress && !m_bracketOpened) {
            m_memValue = m_leftValue;
            m_memOperation = m_operation;
            m_leftValue = Argument(1);
            m_operation = Button::ButtonType::Multiplication;
            m_bracketOpened = !m_bracketOpened;
        }
        else if(m_rightValue.m_digitsEnteringInProgress && m_bracketOpened){
            doOperation();
            m_rightValue = m_leftValue;
            m_leftValue = m_memValue;
            m_operation = m_memOperation;
            m_bracketOpened = !m_bracketOpened;
        }
        break;
    case Button::ButtonType::Point:
        m_rightValue.addPoint();

        break;
    case Button::ButtonType::Negative:
        m_rightValue.m_value = -m_rightValue.m_value;

        break;
    case Button::ButtonType::Plus:
    case Button::ButtonType::Minus:
    case Button::ButtonType::Multiplication:
    case Button::ButtonType::Division:
        if (m_rightValue.m_digitsEnteringInProgress)
        {
            doOperation();
            m_operation = type;
            m_rightValue = m_leftValue;
        }
        else
        {
            m_operation = type;
            displayValue = nullptr;
        }

        break;
    case Button::ButtonType::Percent:
        if(m_rightValue.m_value != 0 && m_rightValue.m_valueString.size() < MAX_RADIX_COUNT - 2)
        {
            m_rightValue = Argument(m_rightValue.m_value * m_leftValue.m_value / 100) ;

        }
        break;
    case Button::ButtonType::Equal:
        doOperation();
        tempDisplay = m_leftValue;
        displayValue = &tempDisplay;
        m_rightValue.m_digitsEnteringInProgress = false;
        m_leftValue.m_digitsEnteringInProgress = true;

        break;
    }
    if(displayValue){
        emit rightValueChanged(displayValue->toString());
        updateExpression(type);
    }
}


void Processor::doOperation()
{
    switch(m_operation) {
    case Button::ButtonType::Plus:
        m_leftValue = Argument(m_leftValue.m_value + m_rightValue.m_value);
        break;
    case Button::ButtonType::Minus:
        m_leftValue = Argument(m_leftValue.m_value - m_rightValue.m_value);
        break;
    case Button::ButtonType::Multiplication:
        m_leftValue = Argument(m_leftValue.m_value * m_rightValue.m_value);
        break;
    case Button::ButtonType::Division:
        m_leftValue = Argument(m_leftValue.m_value / m_rightValue.m_value);
        break;
    default:
        break;
    }

}

void Processor::updateExpression(Button::ButtonType type)
{
    if(!m_bracketOpened && type == Button::ButtonType::Brackets) {
        type = m_operation;
    }
    switch(type) {
    case Button::ButtonType::Negative:
    case Button::ButtonType::Percent:
        if(!m_rightValue.m_digitsEnteringInProgress && m_rightValue.m_value < 0) {
            m_expression = m_leftValue.toString() + getStringOp(m_operation) + "(" + m_rightValue.toString() +")";
        } else {
            m_expression = m_leftValue.toString() + getStringOp(m_operation) + m_rightValue.toString();
        }
        break;
    case Button::ButtonType::Plus:
    case Button::ButtonType::Minus:
    case Button::ButtonType::Division:
    case Button::ButtonType::Multiplication:
        if(m_rightValue.m_digitsEnteringInProgress) {
            m_expression += m_rightValue.toString();
        } else {
            m_expression = m_leftValue.toString() + getStringOp(type);
        }
        break;

    case Button::ButtonType::Equal:
        if(m_rightValue.m_value < 0) {
            m_expression = getStringOp(m_operation) + "(" + m_rightValue.toString() + ")";
        } else {
            m_expression = getStringOp(m_operation) + m_rightValue.toString();
        }
        break;
    case Button::ButtonType::Brackets:
        break;
    case Button::ButtonType::Clean:
        m_expression = "0";
        break;
    default:
        if(m_leftValue.m_digitsEnteringInProgress) {
            m_expression = m_rightValue.toString();
        } else {
            m_expression = m_leftValue.toString() + getStringOp(m_operation) + m_rightValue.toString();
        }
        break;
    }
    if(m_bracketOpened) {
        m_expression = m_memValue.toString() + getStringOp(m_memOperation) + "(" + m_expression + ")";
    }
    emit expressionChanged(m_expression);
}



Processor::Processor()
    : m_leftValue(1)
    , m_memOperation(Button::ButtonType::Plus)
    , m_operation(Button::ButtonType::Multiplication)
    , m_bracketOpened(false)
{

}


Processor::~Processor()
{

}




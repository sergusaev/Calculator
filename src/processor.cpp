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
    Argument tempDisplay;
    Argument *displayValue = &m_rightValue;
    switch(type) {
    case Button::ButtonType::DigitZero:
        m_rightValue.addDigit('0');
        if(!(SecretMenuHandler::instance()->openingState() == OpeningState::InactiveState)) {
            emit wrongButtonClicked();
        }
        break;
    case Button::ButtonType::DigitOne:
        m_rightValue.addDigit('1');
        if(!(SecretMenuHandler::instance()->openingState() == OpeningState::InactiveState)) {
            emit digitOneClicked();
        }
        break;
    case Button::ButtonType::DigitTwo:
        m_rightValue.addDigit('2');
        if(!(SecretMenuHandler::instance()->openingState() == OpeningState::InactiveState)) {
            emit digitTwoClicked();
        }
        break;
    case Button::ButtonType::DigitThree:
        m_rightValue.addDigit('3');
        if(!(SecretMenuHandler::instance()->openingState() == OpeningState::InactiveState)) {
            emit digitThreeClicked();
        }
        break;
    case Button::ButtonType::DigitFour:
        m_rightValue.addDigit('4');
        if(!(SecretMenuHandler::instance()->openingState() == OpeningState::InactiveState)) {
            emit wrongButtonClicked();
        }
        break;
    case Button::ButtonType::DigitFive: {
        m_rightValue.addDigit('5');
        if(!(SecretMenuHandler::instance()->openingState() == OpeningState::InactiveState)) {
            emit wrongButtonClicked();
        }
        break;
    }
    case Button::ButtonType::DigitSix:
        m_rightValue.addDigit('6');
        if(!(SecretMenuHandler::instance()->openingState() == OpeningState::InactiveState)) {
            emit wrongButtonClicked();
        }
        break;
    case Button::ButtonType::DigitSeven:
        m_rightValue.addDigit('7');
        if(!(SecretMenuHandler::instance()->openingState() == OpeningState::InactiveState)) {
            emit wrongButtonClicked();
        }
        break;
    case Button::ButtonType::DigitEight:
        m_rightValue.addDigit('8');
        if(!(SecretMenuHandler::instance()->openingState() == OpeningState::InactiveState)) {
            emit wrongButtonClicked();
        }
        break;
    case Button::ButtonType::DigitNine:
        m_rightValue.addDigit('9');
        if(!(SecretMenuHandler::instance()->openingState() == OpeningState::InactiveState)) {
            emit wrongButtonClicked();
        }
        break;
    case Button::ButtonType::Clean:
        m_rightValue = Argument();
        if(!(SecretMenuHandler::instance()->openingState() == OpeningState::InactiveState)) {
            emit wrongButtonClicked();
        }
        break;
    case Button::ButtonType::AllClean:
        m_rightValue = Argument();
        m_leftValue = Argument();
        m_operation = Button::ButtonType::Plus;
        if(!(SecretMenuHandler::instance()->openingState() == OpeningState::InactiveState)) {
            emit wrongButtonClicked();
        }
        break;
    case Button::ButtonType::Point:
        m_rightValue.addPoint();
        if(!(SecretMenuHandler::instance()->openingState() == OpeningState::InactiveState)) {
            emit wrongButtonClicked();
        }
        break;
    case Button::ButtonType::Negative:
        m_rightValue.m_value = -m_rightValue.m_value;
        if(!(SecretMenuHandler::instance()->openingState() == OpeningState::InactiveState)) {
            emit wrongButtonClicked();
        }
        break;
    case Button::ButtonType::Plus:
    case Button::ButtonType::Minus:
    case Button::ButtonType::Multiplication:
    case Button::ButtonType::Division:
        if (!m_rightValue.m_expectRightArg)
        {
            doOperation();
            m_operation = type;
            m_rightValue = m_leftValue;
            m_rightValue.m_expectRightArg = true;
            m_leftValue.m_expectRightArg = true;
        }
        else
        {
            m_operation = type;
            displayValue = nullptr;
        }
        emit wrongButtonClicked();
        break;
    case Button::ButtonType::Percent:
        if (!m_rightValue.m_expectRightArg &&  m_rightValue.m_value != 0 && m_rightValue.m_valueString.size() < MAX_RADIX_COUNT)
        {
            switch(m_operation) {
            case Button::ButtonType::Plus:
            case Button::ButtonType::Minus:
                tempDisplay = m_rightValue;
//                tempDisplay.m_value = tempDisplay.m_value / 100;
                tempDisplay = Argument(tempDisplay.m_value /= 100);
                displayValue = &tempDisplay;
//                m_rightValue.m_value = tempDisplay.m_value;
                m_rightValue = Argument(tempDisplay.m_value) ;
//                m_rightValue.update();
                if(!(SecretMenuHandler::instance()->openingState() == OpeningState::InactiveState)) {
                    emit wrongButtonClicked();
                }
                break;
            default:
                m_rightValue.m_value = m_rightValue.m_value  / 100;
                m_rightValue.update();
                if(!(SecretMenuHandler::instance()->openingState() == OpeningState::InactiveState)) {
                    emit wrongButtonClicked();
                }
                break;
            }
        }
        else
        {
            displayValue = nullptr;
        }

        break;
    case Button::ButtonType::Equal:
        doOperation();
        tempDisplay = m_leftValue;
        displayValue = &tempDisplay;
        m_rightValue.m_expectRightArg = true;
        m_leftValue.m_expectRightArg = false;
        if(!(SecretMenuHandler::instance()->openingState() == OpeningState::InactiveState)) {
            emit wrongButtonClicked();
        }
        break;
    }
    if(displayValue){
        emit rightValueChanged(displayValue->toString());
        updateExpression(type);
    }
}

void Processor::doOperation()
{
    double leftVal = (&m_leftValue.m_value)->ToDouble();
    double rightVal = (&m_rightValue.m_value)->ToDouble();
    switch(m_operation) {
    case Button::ButtonType::DigitZero:
    case Button::ButtonType::DigitOne:
    case Button::ButtonType::DigitTwo:
    case Button::ButtonType::DigitThree:
    case Button::ButtonType::DigitFour:
    case Button::ButtonType::DigitFive:
    case Button::ButtonType::DigitSix:
    case Button::ButtonType::DigitSeven:
    case Button::ButtonType::DigitEight:
    case Button::ButtonType::DigitNine:
    case Button::ButtonType::Point:
    case Button::ButtonType::AllClean:
    case Button::ButtonType::Clean:
    case Button::ButtonType::Negative:
    case Button::ButtonType::Equal:
        break;
    case Button::ButtonType::Plus:
//        m_leftValue.m_value = m_leftValue.m_value + m_rightValue.m_value;
        m_leftValue = Argument(m_leftValue.m_value + m_rightValue.m_value);
        break;
    case Button::ButtonType::Minus:
//        m_leftValue.m_value = m_leftValue.m_value - m_rightValue.m_value;
        m_leftValue = Argument(m_leftValue.m_value - m_rightValue.m_value);
        break;
    case Button::ButtonType::Multiplication:
//        m_leftValue.m_value = m_leftValue.m_value * m_rightValue.m_value;
        m_leftValue = Argument(m_leftValue.m_value * m_rightValue.m_value);
        break;
    case Button::ButtonType::Division:
//        m_leftValue.m_value = m_leftValue.m_value / m_rightValue.m_value;
        m_leftValue = Argument(m_leftValue.m_value / m_rightValue.m_value);
        break;
    case Button::ButtonType::Percent:
//        m_leftValue.m_value = m_rightValue.m_value;
        m_leftValue = m_rightValue;
        break;
    }

}

void Processor::updateExpression(Button::ButtonType type)
{
    switch(type) {
    case Button::ButtonType::Negative:
    case Button::ButtonType::Percent:
        if(m_leftValue.m_expectRightArg && m_rightValue.m_value < 0) {
            m_expression = m_leftValue.toString() + getStringOp(m_operation) + "(" + m_rightValue.toString() +")";
        }
        break;
    case Button::ButtonType::Plus:
    case Button::ButtonType::Minus:
    case Button::ButtonType::Division:
    case Button::ButtonType::Multiplication:
        if(!m_rightValue.m_expectRightArg) {
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
    case Button::ButtonType::AllClean:
        m_expression = "0";
        break;
    case Button::ButtonType::Clean:
        break;
    default:
        if(!m_leftValue.m_expectRightArg) {
            m_expression = m_rightValue.toString();
        } else {
            m_expression = m_leftValue.toString() + getStringOp(m_operation) + m_rightValue.toString();
        }
        break;
    }
    emit expressionChanged(m_expression);
}



Processor::Processor()
    : m_operation(Button::ButtonType::Plus)
{

}


Processor::~Processor()
{

}




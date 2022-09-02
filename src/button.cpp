#include "button.h"


Button::Button()
    :m_type(ButtonType::CommonType)
{

}

Button::Button(ButtonType type, QObject *parent)
    : m_type(type)
{
    Q_UNUSED(parent)
    switch(m_type) {
    case ButtonType::Back:
        setColor("#0889A6");
        setColorActive("#F7E425");
        setIconPath("../icons/chevron_left.png");
        break;
    case ButtonType::Negative:
        setColor("#0889A6");
        setColorActive("#F7E425");
        setIconPath("../icons/plus_minus.png");
        break;
    case ButtonType::Percent:
        setColor("#0889A6");
        setColorActive("#F7E425");
        setIconPath("../icons/percent.png");
        break;
    case ButtonType::Division:
        setColor("#0889A6");
        setColorActive("#F7E425");
        setIconPath("../icons/division.png");
        break;
    case ButtonType::DigitSeven:
        setColor("#B0D1D8");
        setColorActive("#04BFAD");
        setText("7");
        break;
    case ButtonType::DigitEight:
        setColor("#B0D1D8");
        setColorActive("#04BFAD");
        setText("8");
        break;
    case ButtonType::DigitNine:
        setColor("#B0D1D8");
        setColorActive("#04BFAD");
        setText("9");
        break;
    case ButtonType::Multiplication:
        setColor("#0889A6");
        setColorActive("#F7E425");
        setIconPath("../icons/multiplication.png");
        break;
    case ButtonType::DigitFour:
        setColor("#B0D1D8");
        setColorActive("#04BFAD");
        setText("4");
        break;
    case ButtonType::DigitFive:
        setColor("#B0D1D8");
        setColorActive("#04BFAD");
        setText("5");
        break;
    case ButtonType::DigitSix:
        setColor("#B0D1D8");
        setColorActive("#04BFAD");
        setText("6");
        break;
    case ButtonType::Minus:
        setColor("#0889A6");
        setColorActive("#F7E425");
        setIconPath("../icons/minus.png");
        break;
    case ButtonType::DigitOne:
        setColor("#B0D1D8");
        setColorActive("#04BFAD");
        setText("1");
        break;
    case ButtonType::DigitTwo:
        setColor("#B0D1D8");
        setColorActive("#04BFAD");
        setText("2");
        break;
    case ButtonType::DigitThree:
        setColor("#B0D1D8");
        setColorActive("#04BFAD");
        setText("3");
        break;
    case ButtonType::Plus:
        setColor("#0889A6");
        setColorActive("#F7E425");
        setIconPath("../icons/plus.png");
        break;
    case ButtonType::Cancel:
        setColor("#F25E5E");
        setColorActive("#FFA07A");
        setIconPath("../icons/text_button.png");
        break;
    case ButtonType::DigitZero:
        setColor("#B0D1D8");
        setColorActive("#04BFAD");
        setText("0");
        break;
    case ButtonType::Dot:
        setColor("#B0D1D8");
        setColorActive("#04BFAD");
        setText(".");
        break;
    case ButtonType::Equal:
        setColor("#0889A6");
        setColorActive("#F7E425");
        setIconPath("../icons/equal.png");
        break;
    case ButtonType::CommonType:
    default:
        break;
    }
}


Button::ButtonType Button::type() const
{
    return m_type;
}

void Button::setType(ButtonType newButtonType)
{
    if (m_type == newButtonType)
        return;
    m_type = newButtonType;

}


const QString &Button::text() const
{
    return m_text;
}

void Button::setText(const QString &newButtonText)
{
    m_text = newButtonText;
}

const QString &Button::iconPath() const
{
    return m_iconPath;
}

void Button::setIconPath(const QString &newButtonIconPath)
{
    m_iconPath = newButtonIconPath;
}


const QString &Button::color() const
{
    return m_color;
}

void Button::setColor(const QString &newButtonColor)
{
    m_color = newButtonColor;
}


const QString &Button::colorActive() const
{
    return m_colorActive;
}

void Button::setColorActive(const QString &newColorActive)
{
    if (m_colorActive == newColorActive)
        return;
    m_colorActive = newColorActive;

}


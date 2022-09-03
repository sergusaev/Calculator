#ifndef BUTTON_H
#define BUTTON_H

#include <QObject>

class Button : public QObject
{
    Q_OBJECT
public:

    enum ButtonType {
        AllClean = Qt::UserRole + 2,
        Negative,
        Percent,
        Division,
        DigitSeven,
        DigitEight,
        DigitNine,
        Multiplication,
        DigitFour,
        DigitFive,
        DigitSix,
        Minus,
        DigitOne,
        DigitTwo,
        DigitThree,
        Plus,
        Clean,
        DigitZero,
        Point,
        Equal
    };
    Q_ENUM(ButtonType)

    Button();

    Button(ButtonType type, QObject *parent = nullptr);
    ~Button() = default;

    const QString &text() const;
    void setText(const QString &newButtonText);

    const QString &color() const;
    void setColor(const QString &newButtonColor);

    const QString &iconPath() const;
    void setIconPath(const QString &newButtonIconPath);

    ButtonType type() const;
    void setType(ButtonType newButtonType);

    const QString &colorActive() const;
    void setColorActive(const QString &newColorActive);




private:
    ButtonType m_type;
    QString m_text;
    QString m_iconPath;
    QString m_color;
    QString m_colorActive;


};

Q_DECLARE_METATYPE(Button::ButtonType)

#endif // BUTTON_H

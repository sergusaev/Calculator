#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <QObject>
#include <memory>
#include "argument.h"
#include "button.h"



class Processor : public QObject
{
    Q_OBJECT

public:
    virtual ~Processor();
    static Processor *instance();
    Q_INVOKABLE void evaluate(Button::ButtonType type);
    void doOperation();
    void updateExpression(Button::ButtonType type);

    Argument m_rightValue;
    Argument m_leftValue;
    Argument m_memValue;
    QString m_expression;
    Button::ButtonType m_memOperation;
    Button::ButtonType m_operation;
    bool m_bracketOpened;

signals:
    void leftValueChanged(const QString& strValue);
    void rightValueChanged(const QString& strValue);
    void expressionChanged(const QString& expression);
    void digitOneClicked();
    void digitTwoClicked();
    void digitThreeClicked();
    void wrongButtonClicked();
    Q_INVOKABLE void equalButtonLongPressed();

private:
    Processor();
};

#endif // PROCESSOR_H

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
    QString m_expression;
    Button::ButtonType m_operation;

signals:
    void leftValueChanged(const QString& strValue);
    void rightValueChanged(const QString& strValue);
    void expressionChanged(const QString& expression);

private:
    Processor();
};

#endif // PROCESSOR_H

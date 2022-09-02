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

    Argument m_rightValue;
    Argument m_leftValue;
    Button::ButtonType m_operation;
    void doOperation();
signals:
    void leftValueChanged(const QString& strValue, int radixCount);
    void rightValueChanged(const QString& strValue, int radixCount);

private:
    Processor();
};

#endif // PROCESSOR_H

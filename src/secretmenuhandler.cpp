#include "secretmenuhandler.h"
#include "processor.h"
#include <QDebug>

SecretMenuHandler::~SecretMenuHandler()
{

}

SecretMenuHandler *SecretMenuHandler::instance()
{
    static SecretMenuHandler *instance = new SecretMenuHandler;
    return instance;
}

SecretMenuHandler::SecretMenuHandler(QObject *parent)
    : QObject{parent}
    , m_beginOpeningTimestamp(0)
    , m_openingState(OpeningState::InactiveState)
{

}

quint64 SecretMenuHandler::equalButtonTimeHeld() const
{
    return m_equalButtonTimeHeld;
}

void SecretMenuHandler::setEqualButtonTimeHeld(quint64 newEqualButtonTimeHeld)
{
    m_equalButtonTimeHeld = newEqualButtonTimeHeld;
}

OpeningState SecretMenuHandler::openingState() const
{
    return m_openingState;
}

void SecretMenuHandler::setOpeningState(OpeningState newOpeningState)
{
    m_openingState = newOpeningState;
    qDebug() << "Opening state = " << newOpeningState;
}

quint64 SecretMenuHandler::beginOpeningTimestamp() const
{
    return m_beginOpeningTimestamp;
}

void SecretMenuHandler::setBeginOpeningTimestamp(quint64 newBeginOpeningTimestamp)
{
    m_beginOpeningTimestamp = newBeginOpeningTimestamp;
    emit beginOpeningTimestampChanged();
}

//void SecretMenuHandler::equalButtonPressAndHold()
//{
//    setOpeningState(OpeningState::InitialState);
//    setBeginOpeningTimestamp(QDateTime::currentMSecsSinceEpoch());
//}

void SecretMenuHandler::resetOpening()
{
    setBeginOpeningTimestamp(0);
    setOpeningState(OpeningState::InactiveState);
}

void SecretMenuHandler::equalButtonPressed()
{
    setEqualButtonTimeHeld(QDateTime::currentMSecsSinceEpoch());
}

void SecretMenuHandler::buttonPressed(Button::ButtonType type)
{
    if(type == Button::ButtonType::Equal) {
        equalButtonPressed();
    }
}

void SecretMenuHandler::equalButtonReleased()
{
    quint64 currentTimeStamp = QDateTime::currentMSecsSinceEpoch();
    quint64 interval = currentTimeStamp - equalButtonTimeHeld();
    qDebug() << "Interval = " << interval;

    if(interval >= 4000) {
        setOpeningState(OpeningState::InitialState);
        setBeginOpeningTimestamp(currentTimeStamp);
    }
}

void SecretMenuHandler::buttonReleased(Button::ButtonType type)
{
    if(type == Button::ButtonType::Equal) {
        equalButtonReleased();
    }
}


void SecretMenuHandler::onButtonClicked(Button::ButtonType type)
{
    quint64 currentTimeElapsed = QDateTime::currentMSecsSinceEpoch() - beginOpeningTimestamp();
    if(currentTimeElapsed > 5000)  {
        resetOpening();
        return;
    }
    switch(type) {
    case Button::ButtonType::DigitOne:
        if(m_openingState == OpeningState::InitialState) {
            setOpeningState(OpeningState::PressedOneState);
        } else {
            resetOpening();
        }
        break;
    case Button::ButtonType::DigitTwo:
        if(m_openingState == OpeningState::PressedOneState) {
            setOpeningState(OpeningState::PressedTwoState);
        } else {
            resetOpening();
        }
        break;
    case Button::ButtonType::DigitThree:
        if(m_openingState == OpeningState::PressedTwoState) {
            setOpeningState(OpeningState::PressedThreeState);
            emit openMenu();
        } else {
            resetOpening();
        }
        break;
    default:
        resetOpening();
        break;
    }
}

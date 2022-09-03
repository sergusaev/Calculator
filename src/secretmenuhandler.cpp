#include "secretmenuhandler.h"
#include "processor.h"

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
    QObject::connect(Processor::instance(), &Processor::digitOneClicked, this, &SecretMenuHandler::onDigitOneClicked);
    QObject::connect(Processor::instance(), &Processor::digitTwoClicked, this, &SecretMenuHandler::onDigitTwoClicked);
    QObject::connect(Processor::instance(), &Processor::digitThreeClicked, this, &SecretMenuHandler::onDigitThreeClicked);
    QObject::connect(Processor::instance(), &Processor::wrongButtonClicked, this, &SecretMenuHandler::onWrongButtonClicked);
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

void SecretMenuHandler::equalButtonReleased()
{
    quint64 currentTimeStamp = QDateTime::currentMSecsSinceEpoch();
    setEqualButtonTimeHeld(currentTimeStamp - equalButtonTimeHeld());
    if(equalButtonTimeHeld() >= 4000) {
        setOpeningState(OpeningState::InitialState);
        setBeginOpeningTimestamp(currentTimeStamp);
    }
}

void SecretMenuHandler::onDigitOneClicked()
{
    if(m_openingState == OpeningState::InactiveState) {
        return;
    }
    if(m_openingState == OpeningState::InitialState) {
        quint64 currentTimeElapsed = QDateTime::currentMSecsSinceEpoch() - beginOpeningTimestamp();
        if(currentTimeElapsed <= 5000)  {
            setOpeningState(OpeningState::PressedOneState);
        } else {
            resetOpening();
        }
    }
}

void SecretMenuHandler::onDigitTwoClicked()
{
    if(m_openingState & (OpeningState::InactiveState | OpeningState::InitialState)) {
        return;
    }
    if(m_openingState == OpeningState::PressedOneState) {
        quint64 currentTimeElapsed = QDateTime::currentMSecsSinceEpoch() - beginOpeningTimestamp();
        if(currentTimeElapsed <= 5000)  {
            setOpeningState(OpeningState::PressedTwoState);
        } else {
            resetOpening();
        }
    }
}

void SecretMenuHandler::onDigitThreeClicked()
{
    if(m_openingState & (OpeningState::InactiveState | OpeningState::InitialState | OpeningState::PressedOneState)) {
        return;
    }
    if(m_openingState == OpeningState::PressedTwoState) {
        quint64 currentTimeElapsed = QDateTime::currentMSecsSinceEpoch() - beginOpeningTimestamp();
        if(currentTimeElapsed <= 5000)  {
            setOpeningState(OpeningState::PressedThreeState);
            emit openMenu();
        } else {
            resetOpening();
        }
    }
}

void SecretMenuHandler::onWrongButtonClicked()
{
    resetOpening();
}

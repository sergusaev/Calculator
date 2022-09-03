#ifndef SECRETMENUHANDLER_H
#define SECRETMENUHANDLER_H

#include <QObject>
#include <QDateTime>

enum OpeningState{
    InactiveState,
    InitialState,
    PressedOneState,
    PressedTwoState,
    PressedThreeState

};

class SecretMenuHandler : public QObject
{
    Q_OBJECT
    Q_PROPERTY(qint64 beginOpeningTimestamp READ beginOpeningTimestamp WRITE setBeginOpeningTimestamp NOTIFY beginOpeningTimestampChanged)
public:
    ~SecretMenuHandler();
    static SecretMenuHandler *instance();

//    Q_INVOKABLE void equalButtonPressAndHold();
    Q_INVOKABLE void resetOpening();

    Q_INVOKABLE void equalButtonPressed();
    Q_INVOKABLE void equalButtonReleased();

    quint64 beginOpeningTimestamp() const;
    void setBeginOpeningTimestamp(quint64 newBeginOpeningTimestamp);

    OpeningState openingState() const;
    void setOpeningState(OpeningState newOpeningState);

    quint64 equalButtonTimeHeld() const;
    void setEqualButtonTimeHeld(quint64 newEqualButtonTimeHeld);

signals:
    void openMenu();
    void beginOpeningTimestampChanged();

public slots:
    void onDigitOneClicked();
    void onDigitTwoClicked();
    void onDigitThreeClicked();
    void onWrongButtonClicked();

private:
    SecretMenuHandler(QObject *parent = nullptr);
    quint64 m_equalButtonTimeHeld;
    quint64 m_beginOpeningTimestamp;
    OpeningState m_openingState;


};

#endif // SECRETMENUHANDLER_H

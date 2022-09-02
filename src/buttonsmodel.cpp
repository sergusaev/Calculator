#include "buttonsmodel.h"



ButtonsModel::ButtonsModel(QObject *parent) :
    QAbstractListModel{parent}
{
    for(Button::ButtonType i = Button::ButtonType::Back; (int)i < (int)Button::ButtonType::Equal + 1; i = (Button::ButtonType)((int)i + 1)) {
        m_buttons.push_back(std::make_shared<Button>(i));
    }
}

ButtonsModel::~ButtonsModel()
{

}



QHash<int, QByteArray> ButtonsModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[ButtonRoles::ButtonTypeRole] = "buttonType";
    roles[ButtonRoles::ButtonTextRole] = "buttonText";
    roles[ButtonRoles::ButtonIconPathRole] = "buttonIconPath";
    roles[ButtonRoles::ButtonColorRole] = "buttonColor";
    roles[ButtonRoles::ButtonColorActiveRole] = "buttonColorActive";
    return roles;
}

int ButtonsModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return static_cast<int>(m_buttons.size());
}

QVariant ButtonsModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid() || index.row() > rowCount(index)) {
        return {};
    }
    const Button& button {*m_buttons.at(index.row())};
    switch (role) {
        case ButtonRoles::ButtonTypeRole: {
            return QVariant::fromValue(button.type());
        }
    case ButtonRoles::ButtonTextRole: {
        return QVariant::fromValue(button.text());
    }
    case ButtonRoles::ButtonIconPathRole: {
        return QVariant::fromValue(button.iconPath());
    }
    case ButtonRoles::ButtonColorRole: {
        return QVariant::fromValue(button.color());
    }
    case ButtonRoles::ButtonColorActiveRole: {
        return QVariant::fromValue(button.colorActive());
    }
        default: {
            return true;
        }
    }
}



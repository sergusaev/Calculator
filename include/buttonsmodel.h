#ifndef BUTTONSMODEL_H
#define BUTTONSMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include <vector>
#include <memory>
#include "button.h"
#include "secretmenuhandler.h"

class ButtonsModel : public QAbstractListModel
{
    Q_OBJECT
public:
    ButtonsModel(QObject *parent = nullptr);

    ~ButtonsModel();

    QHash<int, QByteArray> roleNames() const override;

    int rowCount(const QModelIndex &parent = {}) const override;

    QVariant data(const QModelIndex &index = {}, int role = Qt::DisplayRole) const override;

private:
    enum ButtonRoles {
        ButtonTypeRole = Qt::UserRole + 1,
        ButtonTextRole,
        ButtonIconPathRole,
        ButtonColorRole,
        ButtonColorActiveRole
    };
    std::vector<std::shared_ptr<Button>> m_buttons;
};

#endif // BUTTONSMODEL_H

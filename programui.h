#ifndef PROGRAMUI_H
#define PROGRAMUI_H

#include <QColor>
#include <QDebug>
#include <QAbstractListModel>
#include "uibind.hpp"

class ProgramUI : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(UIBind uiBind WRITE setUIBind NOTIFY uiBindChanged)

public:
    enum Types {
        NameRole = Qt::UserRole,
        HueRole = Qt::UserRole+2,
        SaturationRole = Qt::UserRole+3,
        BrightnessRole = Qt::UserRole+4
    };

    explicit ProgramUI(QObject *parent = 0);

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role) const override;

    UIBind uiBind(void);

    void setUIBind(UIBind & ui);
protected:
    // return the roles mapping to be used by QML
    virtual QHash<int, QByteArray> roleNames() const override;
private:
    UIBind * uiBind_;
    QList<QColor> m_data;
    QHash<int, QByteArray> m_roleNames;
signals:
    void uiBindChanged(void);
};

#endif // PROGRAMUI_H

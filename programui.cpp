#include "programui.h"

ProgramUI::ProgramUI(QObject *parent)
    : QAbstractListModel(parent),
      uiBind_(NULL)
{
    m_roleNames[NameRole] = "name";
    m_roleNames[HueRole] = "hue";
    m_roleNames[SaturationRole] = "saturation";
    m_roleNames[BrightnessRole] = "brightness";

    // Append the color names as QColor to the data list (QList<QColor>)
    for(const QString& name : QColor::colorNames()) {
        m_data.append(QColor(name));
    }
}

int ProgramUI::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_data.count();

//    if (!parent.isValid())
//        return 0;
//    else if (uiBind_ == NULL)
//        return 5;
//    else
//        return uiBind_->lenghtInput();
}

QVariant ProgramUI::data(const QModelIndex &index, int role) const
{
    int row = index.row();
     if(row < 0 || row >= m_data.count()) {
         return QVariant();
     }
     const QColor& color = m_data.at(row);
     qDebug() << row << role << color;
     switch(role) {
     case NameRole:
         // return the color name as hex string (model.name)
         return color.name();
     case HueRole:
         // return the hue of the color (model.hue)
         return color.hueF();
     case SaturationRole:
         // return the saturation of the color (model.saturation)
         return color.saturationF();
     case BrightnessRole:
         // return the brightness of the color (model.brightness)
         return color.lightnessF();
     }
     return QVariant();

    //    if (!index.isValid())
//        return QVariant();

//    int row = index.row();

//    switch(role) {
//        case Qt::DisplayRole:
//            return 5;
//        //return uiBind_->getInput(row);
//    }

//    return QVariant();
}

QHash<int, QByteArray> ProgramUI::roleNames() const
{
    return m_roleNames;
}

UIBind ProgramUI::uiBind(void) {}

void ProgramUI::setUIBind(UIBind & ui) {
    uiBind_ = &ui;
}

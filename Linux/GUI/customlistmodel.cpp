#include "customlistmodel.h"
#include<string>
using namespace std;
CustomListModel::CustomListModel(QObject *parent):
    QStringListModel(parent){
}

CustomListModel::CustomListModel(const QStringList &strings, QObject *parent):
    QStringListModel(strings, parent){
}

Qt::ItemFlags CustomListModel::flags (const QModelIndex & index) const {
    Qt::ItemFlags defaultFlags = QStringListModel::flags(index);
    if (index.isValid()){
        return defaultFlags | Qt::ItemIsUserCheckable;
    }
    return defaultFlags;
}

QVariant CustomListModel::data(const QModelIndex &index,
                                 int role) const {
    if (!index.isValid())
        return QVariant();

    if(role == Qt::CheckStateRole)
        return checkedItems.contains(index) ?
                    Qt::Checked : Qt::Unchecked;

    else if(role == Qt::BackgroundColorRole)
        return checkedItems.contains(index) ?
                    QColor("#ffffb2") : QColor("#ffffff");

    return QStringListModel::data(index, role);
}

bool CustomListModel::setData(const QModelIndex &index,
                                const QVariant &value, int role){

    if(!index.isValid() || role != Qt::CheckStateRole)
        return false;

    if(value == Qt::Checked)
        checkedItems.insert(index);
    else
        checkedItems.remove(index);

    emit dataChanged(index, index);
    return true;
}
QString datastr="";
void CustomListModel::save(){
    datastr="";
    QFile file("required_components.txt");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream out(&file);
    out << "Required components:" << "\n";
    foreach(QPersistentModelIndex index, checkedItems){
        out << index.data().toString() << "\n";
    datastr.append(QString::fromStdString(index.data().toString().toStdString().substr(0,index.data().toString().length()-4))+",");
    }

}

QString CustomListModel::get_data()
{
      return datastr.mid(0,datastr.length()-1);
}

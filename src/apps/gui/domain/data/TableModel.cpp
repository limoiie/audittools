#include <domain/data/TableModel.h>

#include <qbrush.h>

#include <domain/data/convert/gui_converter.h>

TableModel::
TableModel(std::shared_ptr<table::TableInterface> table_interface,
           QObject* parent)
  : QAbstractTableModel(parent)
  , model(std::move(table_interface))
  , show_seq_no_(true) {
}

int TableModel::rowCount(const QModelIndex&) const {
  return model->rows();
}

int TableModel::columnCount(const QModelIndex&) const {
  return model->cols() + (show_seq_no_ ? 1 : 0);
}

QVariant TableModel::data(const QModelIndex& index, int const role) const {
  if (!index.isValid()) return QVariant();
  auto const row = index.row();
  auto const col = index.column();
  switch (role) {
    case Qt::DisplayRole:
      return data(row, col);
    case Qt::BackgroundRole:
      return QBrush(0 == (row & 1) ? "#F8F6F4" : "#F4F6F8");
      /*case Qt::TextColorRole:
        if (model->is_out_of_rule(row)) return QBrush("#FF0000");
        return QVariant();*/
    default: break;
  }
  return QVariant();
}

QVariant TableModel::
headerData(int const section, Qt::Orientation const orientation,
           int const role) const {

  if (orientation == Qt::Horizontal && Qt::DisplayRole == role) {
    auto related_section = section;
    if (show_seq_no_) {
      if (0 == section)
        return QString("No.");
      --related_section;
    }

    if (0 <= related_section && related_section < columnCount({})) {
      return QString::fromStdString(model->field_labels()[related_section].name);
    }
  }
  return QAbstractTableModel::headerData(section, orientation, role);
}

QVariant TableModel::data(size_t const row, size_t col) const {
  if (show_seq_no_) {
    if (0 == col) return row + 1;
    --col;
  }

  if (col >= 0 && static_cast<int>(col) < columnCount({}))
    return QString::fromStdString(convert_dynamic<GuiTag, std::string>()(model->item(row, col)));
  return QVariant();
}

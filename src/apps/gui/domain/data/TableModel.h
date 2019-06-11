#ifndef DOMAIN_DATA_TABLEMODEL_H
#define DOMAIN_DATA_TABLEMODEL_H

#include <qabstractitemmodel.h>

#include <base/model/table.h>

class TableModel : public QAbstractTableModel {
  Q_OBJECT

public:
  explicit TableModel(std::shared_ptr<table::TableInterface> table_interface, QObject* parent = nullptr);

  int rowCount(const QModelIndex& parent) const override;
  int columnCount(const QModelIndex& parent) const override;
  QVariant data(const QModelIndex& index, int role) const override;
  QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

  bool show_seq_no() const { return show_seq_no_; }
  void set_show_seq_no(bool const show) { show_seq_no_ = show; }

  std::shared_ptr<table::TableInterface> model;

protected:
  QVariant data(size_t row, size_t col) const;

  bool show_seq_no_;

};

#endif // DOMAIN_DATA_TABLEMODEL_H
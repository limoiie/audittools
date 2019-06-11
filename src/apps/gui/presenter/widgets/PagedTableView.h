#ifndef PRESENTER_TABLE_PAGEDTABLEVIEW_H
#define PRESENTER_TABLE_PAGEDTABLEVIEW_H

#include <QWidget>
#include <base/model/table.h>

namespace Ui
{
  class PagedTableView;
}

struct PagedTableModel;

class PagedTableView : public QWidget {
  Q_OBJECT

public:
  explicit PagedTableView(QWidget *parent = nullptr);

  void setup_model(std::shared_ptr<table::TableInterface> const& table);

  bool show_seq_no() const;
  void set_show_seq_no(bool show) const;

  void update_ui() const;

public slots:
  void up_page() const;
  void down_page() const;
  void goto_page() const;

protected:
  void paintEvent(QPaintEvent*) override;

private:
  std::shared_ptr<Ui::PagedTableView> ui_;
  std::shared_ptr<PagedTableModel> model_;

};

#endif // !PRESENTER_TABLE_PAGEDTABLEVIEW_H

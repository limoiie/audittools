#ifndef PAGEDTABLEBAR_H
#define PAGEDTABLEBAR_H

#include <QWidget>


namespace Ui
{
  class PagedTableBar;
}

class PagedTableBar : public QWidget {
  Q_OBJECT

public:
  explicit PagedTableBar(QWidget *parent = nullptr);

  size_t get_goto_page() const;

public slots:
  void update_ui(size_t max_page, size_t curr_page);

protected:
  void paintEvent(QPaintEvent* ) override;

private:
  std::shared_ptr<Ui::PagedTableBar> ui_;
};

#endif // PAGEDTABLEBAR_H

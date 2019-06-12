#ifndef PRESENTER_VIEW_MAINWINDOW_H
#define PRESENTER_VIEW_MAINWINDOW_H

#include <QWidget>

#include <base/model/table.h>
#include <domain/data/CpuData.h>

namespace Ui
{
  class MainWindow;
}

class MainWindow final : public QWidget {
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = nullptr);

public slots:
  void append_data() const;
  void reset_data() const;
  void fresh_data() const;

private:
  std::shared_ptr<Ui::MainWindow> ui_;
  std::shared_ptr<table::Table<CpuData>> model_;

};

#endif // PRESENTER_VIEW_MAINWINDOW_H

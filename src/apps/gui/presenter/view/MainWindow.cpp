#include <presenter/view/MainWindow.h>

#include "ui_mainwindow.h"

#include <presenter/widgets/PagedTableView.h>

MainWindow::MainWindow(QWidget *parent)
  : QWidget(parent)
  , ui_(new Ui::MainWindow) {
  ui_->setupUi(this);

  setLayout(ui_->mainLayout);

  ui_->body->setLayout(ui_->bodyLayout);

  ui_->controlBar->setLayout(ui_->controlBarLayout);
  ui_->controlBar->setFixedHeight(42);

  model_ = std::make_shared<table::InMemTable<CpuData>>();
  ui_->tableView->setup_model(model_);

  setStyleSheet("PagedTableView {background: #000000;} QLabel {color: #FFFFFF}");

  connect(ui_->startButton, SIGNAL(clicked()), this, SLOT(append_data()));
  connect(ui_->resetButton, SIGNAL(clicked()), this, SLOT(reset_data()));
  connect(ui_->freshButton, SIGNAL(clicked()), this, SLOT(fresh_data()));
}

void MainWindow::append_data() const {
  CpuData obj;
  obj.name.val = "Intel";
  obj.type.val = "Corei7";
  model_->append(obj);

  auto const message = QString("Append, now has %1 items.").arg(model_->rows());
  ui_->statusBar->showMessage(message);
}

void MainWindow::reset_data() const {
  model_->clear();

  auto const message = QString("Reset, now has %1 items.").arg(model_->rows());
  ui_->statusBar->showMessage(message);
}

void MainWindow::fresh_data() const {
  ui_->tableView->update_ui();

  auto const message = QString("Fresh, now has %1 items.").arg(model_->rows());
  ui_->statusBar->showMessage(message);
}

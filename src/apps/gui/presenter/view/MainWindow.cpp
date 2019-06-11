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

  setStyleSheet("PagedTableView {background: #000000;} QLable {color: #FFFFFF}");
}

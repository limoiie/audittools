#include <presenter/widgets/PagedTableView.h>

#include "ui_pagedtableview.h"

#include <qstyleoption.h>
#include <qpainter.h>

#include <domain/data/TableModel.h>
#include <presenter/widgets/PagedTableBar.h>

// TODO: creake a tmp container with the same as page_size, fill in data when up/down/goto pages
// TODO: create a function to update ui according to model
struct PagedTableModel : TableModel {

  size_t page_size;
  mutable size_t page_num;

  explicit PagedTableModel(std::shared_ptr<table::TableInterface> table_interface, 
                  QObject* parent = nullptr)
    : TableModel(std::move(table_interface), parent)
    , page_size(50)
    , page_num(0) {
  }

  int rowCount(const QModelIndex&) const override {
    update_page_num();
    if (pages() == page_num) {
      auto const cnt = model->rows() % page_size;
      return 0 == cnt ? page_size : cnt;
    }
    return page_size;
  }
  
  QVariant data(const QModelIndex& index, int const role) const override {
    update_page_num();
    auto const row = index.row() + page_num * page_size - page_size;
    auto const col = index.column();

    if (0 == pages() || !index.isValid()) 
      return QVariant();
    
    if (Qt::DisplayRole == role)
      return TableModel::data(row, col);
    return TableModel::data(index, role);
  }

  QVariant headerData(int const section, 
                      Qt::Orientation const orientation, 
                      const int role) const override {
    update_page_num();
    return TableModel::headerData(section, orientation, role);
  }

  size_t pages() const {
    return model->rows() / page_size + (model->rows() % page_size ? 1 : 0);
  }

  void up_page() const {
    page_num += 1;
    update_page_num();
  }

  void down_page() const {
    page_num -= 1;
    update_page_num();
  }

  void goto_page(size_t const page) const {
    page_num = page;
    update_page_num();
  }

private:
  void update_page_num() const {
    page_num = max(page_num, static_cast<size_t>(1));
    page_num = min(page_num, pages());
  }

};

void PagedTableView::up_page() const {
  model_->up_page();
  update_ui();
}

void PagedTableView::down_page() const {
  model_->down_page();
  update_ui();
}

void PagedTableView::goto_page() const {
  model_->goto_page(ui_->controlBar->get_goto_page());
  update_ui();
}

PagedTableView::PagedTableView(QWidget* parent)
  : QWidget(parent)
  , ui_(new Ui::PagedTableView) {
  ui_->setupUi(this);
  setLayout(ui_->mainLayout);
  ui_->controlBar->setFixedHeight(42);

  ui_->tableView->sortByColumn(0, Qt::AscendingOrder);
  ui_->tableView->horizontalHeader()->setStretchLastSection(true);
  ui_->tableView->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft | Qt::AlignVCenter);
  ui_->tableView->verticalHeader()->setDefaultSectionSize(30);
  ui_->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
  ui_->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
  ui_->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void PagedTableView::setup_model(std::shared_ptr<table::TableInterface> const& table) {
  model_ = std::make_shared<PagedTableModel>(table);
  ui_->tableView->setModel(model_.get());
}

bool PagedTableView::show_seq_no() const {
  return model_->show_seq_no();
}

void PagedTableView::set_show_seq_no(bool const show) const {
  model_->set_show_seq_no(show);
}

void PagedTableView::update_ui() const {
  ui_->controlBar->update_ui(model_->page_num, model_->pages());
}

void PagedTableView::paintEvent(QPaintEvent*) {
  QStyleOption option;
  option.init(this);
  QPainter painter(this);
  style()->drawPrimitive(QStyle::PE_Widget, &option, &painter, this);
}

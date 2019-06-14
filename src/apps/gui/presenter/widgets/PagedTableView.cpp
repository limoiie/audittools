#include <presenter/widgets/PagedTableView.h>

#include "ui_pagedtableview.h"

#include <qstyleoption.h>
#include <qpainter.h>

#include <domain/data/TableModel.h>
#include <presenter/widgets/PagedTableBar.h>
#include <domain/data/convert/gui_converter.h>

struct CacheTableWrapper : table::TableInterface {
  explicit CacheTableWrapper(std::shared_ptr<TableInterface> const& core)
    : core(core) {
  }

  table::Label const& label() const override {
    return core->label();
  }

  std::vector<table::Label> const& field_labels() const override {
    return core->field_labels();
  }

  size_t rows() const override {
    return cache.size();
  }
  size_t cols() const override {
    return core->cols();
  }
  table::row_const_t row(size_t const r) const override {
    if (r < cache.size())
      return cache[r];
    return {};
  }

  std::vector<table::row_const_t> row(size_t const s, size_t const e) const override {
    if (s < e && e <= cache.size()) {
      std::vector<table::row_const_t> row_list;
      for (auto i = s; i < e; ++i)
        row_list.emplace_back(std::move(row(i)));
      return std::move(row_list);
    }
    return {};
  }

  table::item_const_t item(size_t const r, size_t const c) const override {
    return row(r)[c];
  }

  std::shared_ptr<TableInterface> core;

  std::vector<table::row_const_t> cache;

};

// TODO: creake a tmp container with the same as page_size, fill in data when up/down/goto pages
// TODO: create a function to update ui according to model
struct PagedTableModel : TableModel {
  size_t page_max_size;
  mutable size_t page_num;

  explicit PagedTableModel(std::shared_ptr<table::TableInterface> const& table_interface,
                  QObject* parent = nullptr)
    : TableModel(std::make_shared<CacheTableWrapper>(table_interface), parent)
    , page_max_size(20)
    , page_num(0)
    , page_size_(0)
    , valid_(false) {
    wrapper_ = std::dynamic_pointer_cast<CacheTableWrapper>(model);
  }

  QVariant data(const QModelIndex& index, int const role) const override {
    if (0 == pages()) return QVariant();
    return TableModel::data(index, role);
  }

  size_t pages() const {
    return wrapper_->core->rows() / page_max_size +
      (wrapper_->core->rows() % page_max_size ? 1 : 0);
  }

  void update_page() {
    update_page_num(page_num);
  }

  void up_page() {
    update_page_num(page_num - 1);
  }

  void down_page() {
    update_page_num(page_num + 1);
  }

  void goto_page(size_t const page) {
    update_page_num(page);
  }

private:
  void update_page_num(size_t const target_page) {
    page_num = max(target_page, static_cast<size_t>(1));
    page_num = min(page_num, pages());

    // force reloading data
    valid_ = false;
    update_data();
  }

  void update_data() {
    if (valid_) return;

    auto target_data = std::vector<table::row_const_t>();
    if (page_num != 0) {  // load from database
      auto const s = page_num * page_max_size - page_max_size;
      auto const e = min(s + page_max_size, wrapper_->core->rows());
      target_data = wrapper_->core->row(s, e);
    }

    auto const new_page_size = static_cast<int>(target_data.size());
    if (new_page_size < page_size_) {  // become less
      beginRemoveRows({}, new_page_size, page_size_ - 1);
      wrapper_->cache.swap(target_data);
      endRemoveRows();
    } else if (new_page_size > page_size_) {  // become more
      beginInsertRows({}, page_size_, new_page_size - 1);
      wrapper_->cache.swap(target_data);
      endInsertRows();
    }
    page_size_ = new_page_size;
    valid_ = true;
  }

  std::shared_ptr<CacheTableWrapper> wrapper_;
  mutable int page_size_;
  mutable bool valid_;

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
  ui_->tableView->verticalHeader()->hide();
  ui_->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
  ui_->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
  ui_->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void PagedTableView::setup_model(std::shared_ptr<table::TableInterface> const& table) {
  model_ = std::make_shared<PagedTableModel>(table);
  ui_->tableView->setModel(model_.get());

  connect(ui_->controlBar->up_button(), SIGNAL(clicked()), this, SLOT(up_page()));
  connect(ui_->controlBar->down_button(), SIGNAL(clicked()), this, SLOT(down_page()));
}

bool PagedTableView::show_seq_no() const {
  return model_->show_seq_no();
}

void PagedTableView::set_show_seq_no(bool const show) const {
  model_->set_show_seq_no(show);
}

void PagedTableView::update_ui() const {
  model_->update_page();
  ui_->controlBar->update_ui(model_->pages(), model_->page_num);
}

void PagedTableView::paintEvent(QPaintEvent*) {
  QStyleOption option;
  option.init(this);
  QPainter painter(this);
  style()->drawPrimitive(QStyle::PE_Widget, &option, &painter, this);
}

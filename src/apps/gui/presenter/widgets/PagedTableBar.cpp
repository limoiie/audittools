#include <presenter/widgets/PagedTableBar.h>
#include "ui_PagedTableBar.h"

#include <qstyleoption.h>
#include <qpainter.h>

PagedTableBar::PagedTableBar(QWidget *parent) :
  QWidget(parent),
  ui_(new Ui::PagedTableBar) {
  ui_->setupUi(this);
  setLayout(ui_->horizontalLayout);
}

size_t PagedTableBar::get_goto_page() const {
  return ui_->gotoLineEdit->text().toUInt();
}

void PagedTableBar::update_ui(size_t const max_page, size_t const curr_page) {
  printf("%d%d", max_page, curr_page);
}

void PagedTableBar::paintEvent(QPaintEvent*) {
  QStyleOption option;
  option.init(this);
  QPainter painter(this);
  style()->drawPrimitive(QStyle::PE_Widget, &option, &painter, this);
}

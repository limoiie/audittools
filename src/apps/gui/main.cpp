#include <iostream>
#include <string>
#include <chrono>

#include <QApplication>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>

#include <rxqt.hpp>

#include <domain/launch/LoadMod.h>
#include <log/log.h>

// TODO: Move to Presenter
void load_mod_chain() {
  auto const on_result = [](std::shared_ptr<OutMessage> const& msg) {
    std::cout << msg->step << ": " << msg->message << std::endl;
  };

  auto const on_complete = []() {
    std::cout << "Complete sub load mod" << std::endl;
  };

  auto const on_error = [](std::exception_ptr const& exp) {
    try {
      std::rethrow_exception(exp);
    } catch (std::exception const& e) {
      std::cerr << "Error: " << e.what() << std::endl;
    }
  };

  for (auto& mod : LoadMod::load_chain()) {
    mod->invoke(on_result, on_complete, on_error);
  }

  LoadMod::load_chain();
}

int test_rxqt(int argc, char *argv[]) {
  QApplication app(argc, argv);

  rxqt::run_loop rxqt_run_loop;

  auto widget = std::make_unique<QWidget>();
  auto layout = new QVBoxLayout;
  widget->setLayout(layout);

  auto const button = new QPushButton("Click me");
  auto label = new QLabel;

  layout->addWidget(button);
  layout->addWidget(label);

  auto const count = std::make_shared<int>(0);

  rxqt::from_signal(button, &QPushButton::clicked)
    .map([=](const auto&) { return (*count) += 1; })
    .debounce(std::chrono::milliseconds(QApplication::doubleClickInterval()))
    .tap([=](int) { (*count) = 0; })
    .subscribe([label](int const x) { label->setText(QString("%1-ple click.").arg(x)); });

  rxqt::from_signal(button, &QPushButton::pressed)
    .subscribe([=](const auto&) { label->setText(QString()); });

  widget->show();
  return QApplication::exec();
}

int main() {
  load_mod_chain();
  return 0;
  // return test_rxqt(argc, argv);
}
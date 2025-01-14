#include <QApplication>
#include <QMainWindow>
#include <QDockWidget>
#include <QStackedWidget>
#include <QAction>
#include <QWidget>
#include <QLabel>
#include <QListWidget>
#include <QStyledItemDelegate>
#include <QSize>
#include "cryptPage.h"
#include "decryptPage.h"
#include "safeMessagesPage.h"

class CustomDelegate : public QStyledItemDelegate {
public:
    CustomDelegate(QObject *parent = nullptr) : QStyledItemDelegate(parent) {}

    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override {
        QSize size = QStyledItemDelegate::sizeHint(option, index);
        size.setHeight(size.height() + 30);
        return size;
    }
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QMainWindow mainWindow;
    mainWindow.setWindowTitle("CryptedMessenger");

    QStackedWidget *stackedWidget = new QStackedWidget(&mainWindow);

    CryptPage *cryptPage = new CryptPage();
    DecryptPage *decryptPage = new DecryptPage();
    SafeMessagesPage *safeMessagesPage = new SafeMessagesPage();


    stackedWidget->addWidget(cryptPage);
    stackedWidget->addWidget(decryptPage);
    stackedWidget->addWidget(safeMessagesPage);

    QDockWidget *dockWidget = new QDockWidget("Opcije", &mainWindow);
    dockWidget->setMaximumWidth(120);
    dockWidget->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    dockWidget->setFeatures(QDockWidget::NoDockWidgetFeatures);

    QListWidget *listWidget = new QListWidget(dockWidget);
    listWidget->addItem("Kriptiraj");
    listWidget->addItem("Dekriptiraj");
    listWidget->addItem("Safe Messaging");

    listWidget->setItemDelegate(new CustomDelegate(listWidget));

    dockWidget->setWidget(listWidget);
    mainWindow.addDockWidget(Qt::LeftDockWidgetArea, dockWidget);

    QObject::connect(listWidget, &QListWidget::currentRowChanged, [=](int index) {
        stackedWidget->setCurrentIndex(index);
    });

    mainWindow.setCentralWidget(stackedWidget);

    mainWindow.resize(800, 600);
    mainWindow.show();

    return app.exec();
}
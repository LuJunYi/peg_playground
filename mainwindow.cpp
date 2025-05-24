#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 动态连接 grammarEditTextEdit 的 textChanged 信号
    connect(ui->grammarEditTextEdit, &QTextEdit::textChanged, this, &MainWindow::onGrammarTextChanged);

    // 动态连接 parsePushButton 的 clicked 信号
    connect(ui->parsePushButton, &QPushButton::clicked, this, &MainWindow::onParseButtonClicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onGrammarTextChanged()
{
    // 获取 grammarEditTextEdit 的内容
    QString grammarText = ui->grammarEditTextEdit->toPlainText();
}

void MainWindow::onParseButtonClicked()
{
}

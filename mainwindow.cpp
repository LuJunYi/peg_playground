#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    _pegParser.reset(new peg::parser());

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
    if (!ui->autoRefreshCheckBox->isChecked())
    {
        return; // 如果未选中自动刷新，则不处理
    }

    parseCode();
}

void MainWindow::onParseButtonClicked()
{
    parseCode();
}

void MainWindow::parseCode()
{
    peg::parser parser(R"(
        START <-  ~HELLO WORLD
        HELLO <- 'Hello' _
        WORLD <- 'World' _
        _     <- [ \t\r\n]*
     )");

    parser.enable_ast();

    std::shared_ptr<peg::Ast> ast;
    auto ret = parser.parse("Hello World", ast);
    if (ret)
    {
        qDebug() << "Parsing Ok.";
    }
    else
    {
        qDebug() << "Parsing failed.";
    }
    // QString peg_grammar = ui->grammarEditTextEdit->toPlainText();

    // _pegParser->load_grammar(R"(
    //    START <-  ~HELLO WORLD
    //    HELLO <- 'Hello' _
    //    WORLD <- 'World' _
    //    _     <- [ \t\r\n]*
    // )");
    // _pegParser->enable_packrat_parsing();
    // _pegParser->enable_ast();

    // std::shared_ptr<peg::Ast> ast;
    // if (_pegParser->parse("Hello World.", ast))
    // {
    //     auto dd = ast->nodes.size();
    //     qDebug() << "Parsing Ok.";
    // }
    // else
    // {
    //     qDebug() << "Parsing failed.";
    // }
}

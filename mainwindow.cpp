#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QDebug>
#include <QString>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    _pegParser.reset(new peg::parser());

    // 动态连接 grammarEditTextEdit 的 textChanged 信号
    connect(ui->grammarPlainTextEdit, &QPlainTextEdit::textChanged, this, &MainWindow::onGrammarTextChanged);
    // 动态连接 parsePushButton 的 clicked 信号
    connect(ui->parsePushButton, &QPushButton::clicked, this, &MainWindow::onParseButtonClicked);

    connect(ui->codeEditorPlainTextEdit, &QPlainTextEdit::textChanged, this, &MainWindow::onGrammarTextChanged);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onGrammarTextChanged()
{
    QString peg_grammar = ui->grammarPlainTextEdit->toPlainText();
    // qDebug() << peg_grammar;
    ui->grammarInfoPlainTextEdit->clear();

    _pegParser->set_logger([&](size_t ln, size_t col, const std::string &msg)
                           { 
                                QString logMessage = QString("Line %1, Column %2: %3")
                                            .arg(ln + 1)
                                            .arg(col + 1)
                                            .arg(QString::fromStdString(msg));
                                ui->grammarInfoPlainTextEdit->appendPlainText(logMessage); });

    if (_pegParser->load_grammar(peg_grammar.toLocal8Bit().data()))
    {
        if (ui->packratCheckBox->isChecked())
        {
            _pegParser->enable_packrat_parsing();
        }
        _pegParser->enable_ast();

        _grammarValid = true;
        parseCode();
    }
    else
    {
        _grammarValid = false;

        qDebug() << "Grammar is invalid.";
    }
}

void MainWindow::onParseButtonClicked()
{
    if (_grammarValid)
    {
        parseCode();
    }
}

void MainWindow::onCodeEditorTextChanged()
{
    if (!ui->autoRefreshCheckBox->isChecked())
    {
        return; // 如果未选中自动刷新，则不处理
    }

    if (_grammarValid)
    {
        parseCode();
    }
}

void MainWindow::parseCode()
{
    QString codeText = ui->codeEditorPlainTextEdit->toPlainText();
    QStringList codeLines = codeText.split('\n');

    _pegParser->set_logger([&](size_t ln, size_t col, const std::string &msg)
                           { 
         QString logMessage = QString("Line %1, Column %2: %3")
                     .arg(ln + 1)
                     .arg(col + 1)
                     .arg(QString::fromStdString(msg));
         ui->codeResultPlainTextEdit->appendPlainText(logMessage); });

    for (const QString &line : codeLines)
    {
        qDebug() << line; // 输出每一行代码

        // 这里可以添加对每一行代码的处理逻
        std::string codeLine = line.toStdString();
        std::shared_ptr<peg::Ast> ast;
        if (_pegParser->parse(codeLine, ast))
        {
            // auto dd = ast->nodes.size();

            QString astStr = QString::fromStdString(peg::ast_to_s(ast));
            ui->codeAstPlainTextEdit->setPlainText(astStr);

            qDebug() << "Parsing Ok.";
        }
        else
        {
            qDebug() << "Parsing failed.";
        }
    }
}

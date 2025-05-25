#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <memory>

#include "peglib.h"

QT_BEGIN_NAMESPACE

namespace Ui
{
    class MainWindow;
}

QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

private slots:
    void onGrammarTextChanged();    // 处理 grammarEditTextEdit 的文本更改
    void onParseButtonClicked();    // 处理 parsePushButton 的点击
    void onCodeEditorTextChanged(); // 处理 codeEditorPlainTextEdit 的文本更改

private:
    void parseCode();

private:
    Ui::MainWindow *ui;

    std::shared_ptr<peg::parser> _pegParser;
    bool _grammarValid = false;
};
#endif // MAINWINDOW_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
    void onGrammarTextChanged(); // 处理 grammarEditTextEdit 的文本更改
    void onParseButtonClicked(); // 处理 parsePushButton 的点击

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H

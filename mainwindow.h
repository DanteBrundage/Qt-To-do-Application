#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "task.h"
#include <QVector>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void updateStatus();

public slots:
    void addTask();
    void removeTask(Task* task);
    void taskStatusChanged(Task* task);
    void DarkModeToggle(bool dark);

private:
    Ui::MainWindow *ui;
    QVector<Task*>  mTasks;
    void keyPressEvent(QKeyEvent* event);
    bool darkMode;
    void darkToggle(bool* off);
    void generateIcons();
};
#endif // MAINWINDOW_H

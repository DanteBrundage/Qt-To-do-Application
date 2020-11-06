#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QDebug"
#include "QInputDialog"
#include "QKeyEvent"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow), mTasks()
{
    //set stylesheeet
    QFile file(":/light.qss");
    file.open(QFile::ReadOnly | QFile::Text);
    QTextStream stream(&file);
    this->setStyleSheet(stream.readAll());

    ui->setupUi(this);

    connect(ui->addTaskButton, &QPushButton::clicked, this, &MainWindow::addTask);
    updateStatus();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::addTask() {

    bool ok = !ui->taskCreator->text().isEmpty();
    QString name  = ui->taskCreator->text();

    if(ok && !name.isEmpty()){
        qDebug() << "Adding task ";
        Task* task = new Task(name);

        connect(task, &Task::removed, this, &MainWindow::removeTask);

        mTasks.append(task);
        ui->tasksLayout->addWidget(task);
        updateStatus();
    }

}

void MainWindow::removeTask(Task* task){
    mTasks.removeOne(task);
    ui->tasksLayout->removeWidget(task);
    delete task;
    updateStatus();
}

void MainWindow::taskStatusChanged(Task*){
    updateStatus();
}

void MainWindow::updateStatus() {
    int completedCount = 0;

    for(auto& task: mTasks){
        if(task->isComplete()){
            completedCount++;
        }

    }

    int remainingTasks = mTasks.size() - completedCount;

    ui->statusLabel->setText(
                QString("Status: %1 todo / %2 completed").arg(remainingTasks).arg(completedCount)
                );
}

void MainWindow::keyPressEvent(QKeyEvent *event){
    if(event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter){
        qDebug() << "Enter Key Pressed";
        MainWindow::addTask();
        ui->taskCreator->clear();
    }
}

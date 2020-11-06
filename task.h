#ifndef TASK_H
#define TASK_H

#include <QWidget>
#include <QString>

namespace Ui {
class Task;
}

class Task : public QWidget
{
    Q_OBJECT

public:
    explicit Task(const QString &name, QWidget *parent = nullptr);
    ~Task();

    void setName(const QString &name);
    QString name() const;
    bool isComplete() const;

signals:
    void removed(Task* task);
    void statusChanged(Task* task);

private slots:
    void checked(bool checked);
    void editTask();
    void generateIcons();

private:
    Ui::Task *ui;
};

#endif // TASK_H

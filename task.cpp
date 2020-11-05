#include "task.h"
#include "ui_task.h"
#include "QInputDialog"
#include "QDebug"

Task::Task(const QString &name, QWidget *parent) : QWidget(parent), ui(new Ui::Task)
{
    ui->setupUi(this);
    setName(name);

    connect(ui->removeButton, &QPushButton::clicked, [this]{
        emit removed(this);
    });

    connect(ui->checkBox, &QCheckBox::toggled, this, &Task::checked);

    connect(ui->editButton, &QPushButton::clicked, this, &Task::editTask);
}


void Task::setName(const QString &name){
    ui->checkBox->setText(name);
}

QString Task::name()const{
    return ui->checkBox->text();
}

bool Task::isComplete() const{
    return ui->checkBox->isChecked();
}

void Task::checked(bool checked){
    QFont font(ui->checkBox->font());
    font.setStrikeOut(checked);
    ui->checkBox->setFont(font);
    emit statusChanged(this);
}

void Task::editTask(){
    bool ok;
    QString _name = QInputDialog::getText(this,
                                         tr("Add task"),
                                         tr("Task name"),
                                         QLineEdit::Normal,
                                         name(),
                                         &ok);
    if(ok && !_name.isEmpty()){
        qDebug() << "Changing task name";
        setName(_name);
    }
}

Task::~Task()
{
    delete ui;
}

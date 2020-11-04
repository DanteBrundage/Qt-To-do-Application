#include "task.h"
#include "ui_task.h"

Task::Task(const QString &name, QWidget *parent) : QWidget(parent), ui(new Ui::Task)
{
    ui->setupUi(this);
    setName(name);

    connect(ui->removeButton, &QPushButton::clicked, [this]{
        emit removed(this);
    });

    connect(ui->checkBox, &QCheckBox::toggled, this, &Task::checked);
}


void Task::setName(const QString &name){
    ui->checkBox->setText(name);
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

Task::~Task()
{
    delete ui;
}

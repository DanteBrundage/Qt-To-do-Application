#include "task.h"
#include "ui_task.h"
#include "QInputDialog"
#include "QDebug"
#include "QFontDatabase"

Task::Task(const QString &name, QWidget *parent) : QWidget(parent), ui(new Ui::Task)
{
    ui->setupUi(this);
    generateIcons();

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

void Task::generateIcons(){
    if (QFontDatabase::addApplicationFont(":/FontAwesome.otf") < 0)
        qWarning() << "FontAwesome cannot be loaded !";

    QFont font;
    font.setFamily("FontAwesome");
    font.setPixelSize(32);

    ui->editButton->setFont(font); //this helps control the size, but not needed for icon necessarily
    ui->editButton->setText("\uf044");

    ui->removeButton->setFont(font);
    ui->removeButton->setText("\uf1f8");
    //ui->darkModeToggle->setText("\uf186");

}
Task::~Task()
{
    delete ui;
}

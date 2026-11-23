#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QTableWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QSpinBox>
#include <QComboBox>
#include <QLineEdit>
#include <QDebug>
#include <vector>
#include <memory>

#include "Enemy.h"
#include "PlayerCharacter.h"
#include "Combatant.h"

#define TYEP_COLUMN 0
#define NAME_COLUMN 1
#define CURRENT_HP_COLUMN 2
#define MAX_HP_COLUMN 3
#define AC_COLUMN 4
#define INITIATIVE_COLUMN 5
#define LEVEL_COLUMN 6
#define CLASS_COLUMN 7
#define CHALL_RATE_COLUMN 8
#define EXP_RATE_COLUMN 9

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QWidget* window = new QWidget;
    QTableWidget* table = new QTableWidget(0, 10);
    QPushButton* addRowButton = new QPushButton("+ Add row");
    QPushButton* readValuesOfRow = new QPushButton("Read values");

    QVBoxLayout* layout = new QVBoxLayout(window);

    table->setHorizontalHeaderLabels({"Type", "Name", "Current HP","Maximum HP", "AC", "Initiative", "Level", "Class", "CR", "XP"});

    QObject::connect(addRowButton, &QPushButton::clicked, [table](){
        int row = table->rowCount();
        QComboBox* type = new QComboBox;
        type->addItems({"Player", "Enemy"});
        table->insertRow(row);

        QComboBox* chall_rate = new QComboBox;
        chall_rate->addItem("0", 0);
        chall_rate->addItem("1/8", 0.125);
        chall_rate->addItem("1/4", 0.25);
        chall_rate->addItem("1/2", 0.5);

        QString s = "";
        for (int i = 1; i <= 30; i++)
        {
            s = QString::number(i);
            chall_rate->addItem(s, i);
        }       
        table->setCellWidget(row, TYEP_COLUMN, type);
        table->setCellWidget(row, CURRENT_HP_COLUMN, new QSpinBox);
        table->setCellWidget(row, MAX_HP_COLUMN, new QSpinBox);
        table->setCellWidget(row, AC_COLUMN, new QSpinBox);
        table->setCellWidget(row, INITIATIVE_COLUMN, new QSpinBox);

        QSpinBox* lvl = new QSpinBox;
        QLineEdit* cls = new QLineEdit;
        lvl->setEnabled(true);
        cls->setEnabled(true);
        lvl->setStyleSheet("QSpinBox:disabled { border: 1px solid red; }");
        cls->setStyleSheet("QLineEdit:disabled { border: 1px solid red; }");
        table->setCellWidget(row, LEVEL_COLUMN, lvl);
        table->setCellWidget(row, CLASS_COLUMN, cls);
        QSpinBox* xp = new QSpinBox;  
        chall_rate->setEnabled(false);
        xp->setEnabled(false);
        chall_rate->setStyleSheet("QComboBox:disabled { border: 1px solid red; }");
        chall_rate->setToolTip("Only usable for Enemy character type");
        xp->setStyleSheet("QSpinBox:disabled { border: 1px solid red; }");
        xp->setToolTip("Only usable for Enemy character type");
        table->setCellWidget(row, CHALL_RATE_COLUMN, chall_rate);       
        table->setCellWidget(row, EXP_RATE_COLUMN, xp);  


        QObject::connect(type, &QComboBox::currentTextChanged, [chall_rate, xp, lvl, cls](const QString& text) {
            if("Enemy" == text)
            {   
                chall_rate->setEnabled(true);
                xp->setEnabled(true);
                lvl->setEnabled(false);
                cls->setEnabled(false);
                chall_rate->setToolTip("");
                xp->setToolTip("");
                
                lvl->setToolTip("Only usable for Player character type");
                cls->setToolTip("Only usable for Player character type");
            }
            else
            {
                lvl->setEnabled(true);
                cls->setEnabled(true);
                chall_rate->setEnabled(false);
                xp->setEnabled(false);
                lvl->setToolTip("");
                cls->setToolTip("");
                
                chall_rate->setToolTip("Only usable for Enemy character type");
                xp->setToolTip("Only usable for Enemy character type");
            }
        });      
 
    
    });
    std::vector<std::unique_ptr<Combatant>> roster;
    QObject::connect(readValuesOfRow, &QPushButton::clicked, [table, &roster](){
               
        for(int i = 0; i < table->rowCount(); i++)
        {   
            QComboBox* type = qobject_cast<QComboBox*>(table->cellWidget(i, TYEP_COLUMN));

            QTableWidgetItem* name =  table->item(i, NAME_COLUMN);

            qDebug() << type->currentText();
            QSpinBox* curhp = qobject_cast<QSpinBox*>(table->cellWidget(i, CURRENT_HP_COLUMN));
            qDebug() << curhp->value();
            QSpinBox* maxhp = qobject_cast<QSpinBox*>(table->cellWidget(i, MAX_HP_COLUMN));
            qDebug() << maxhp->value();
            QSpinBox* init = qobject_cast<QSpinBox*>(table->cellWidget(i, INITIATIVE_COLUMN));
            qDebug() << init->value();
            QSpinBox* armor = qobject_cast<QSpinBox*>(table->cellWidget(i, AC_COLUMN));
            qDebug() << armor->value();

            std::string newname = "Unnamed";
            if(name != nullptr)
            {
                newname = name->text().toStdString(); 
            }
            qDebug() << newname;


            if(type->currentText() == "Player")
            {
                QSpinBox* levl = qobject_cast<QSpinBox*>(table->cellWidget(i, LEVEL_COLUMN));
                qDebug() << levl->value();
                QLineEdit* classe = qobject_cast<QLineEdit*>(table->cellWidget(i, CLASS_COLUMN));
                qDebug() << classe->text();
                
                std::unique_ptr<PlayerCharacter> playerchar =
                std::make_unique<PlayerCharacter>(newname, curhp->value(), maxhp->value(), armor->value(), init->value(), classe->text().toStdString(), levl->value());  
                qDebug() << playerchar->getCurrentHP();
                roster.push_back(std::move(playerchar));
            }
            else if(type->currentText() == "Enemy")
            {
                QComboBox* challrate = qobject_cast<QComboBox*>(table->cellWidget(i, CHALL_RATE_COLUMN));
                qDebug() << challrate->currentData();
                float crate = challrate->currentData().toFloat();
                QSpinBox* exp = qobject_cast<QSpinBox*>(table->cellWidget(i, EXP_RATE_COLUMN));
                qDebug() << exp->value();
                std::unique_ptr<Enemy> enemy = 
                std::make_unique<Enemy>(newname, curhp->value(), maxhp->value(), armor->value(), init->value(), crate);
                qDebug() << enemy->getCurrentHP();
                roster.push_back(std::move(enemy));
            }
        }

        table->setRowCount(0);

        for(int i = 0; i < roster.size(); i++)
        {
            qDebug() << roster[i]->getCurrentHP();
        }

    });

    layout->addWidget(table);
    layout->addWidget(addRowButton);
    layout->addWidget(readValuesOfRow);
    window->resize(900, 600);
    window->show();

    return app.exec();
}
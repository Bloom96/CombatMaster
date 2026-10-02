#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QTableWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QSpinBox>
#include <QComboBox>
#include <QLineEdit>

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
    QTableWidget* table = new QTableWidget(0, 9);
    QPushButton* addRowButton = new QPushButton("+ Add row");

    QVBoxLayout* layout = new QVBoxLayout(window);


    table->setHorizontalHeaderLabels({"Type", "Name", "Current HP","Maximum HP", "AC", "Initiative", "Level", "Class", "CR", "XP"});

    QObject::connect(addRowButton, &QPushButton::clicked, [table](){
        int row = table->rowCount();
        QComboBox* type = new QComboBox;
        type->addItems({"Player", "Enemy"});
        table->insertRow(row);


        
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
        QSpinBox* cr = new QSpinBox;
        QSpinBox* xp = new QSpinBox;  
        cr->setEnabled(false);
        xp->setEnabled(false);
        cr->setStyleSheet("QSpinBox:disabled { border: 1px solid red; }");
        cr->setToolTip("Only usable for Enemy character type");
        xp->setStyleSheet("QSpinBox:disabled { border: 1px solid red; }");
        xp->setToolTip("Only usable for Enemy character type");
        table->setCellWidget(row, CHALL_RATE_COLUMN, cr);       
        table->setCellWidget(row, EXP_RATE_COLUMN, xp);  

        QObject::connect(type, &QComboBox::currentTextChanged, [cr, xp, lvl, cls](const QString& text) {
            if("Enemy" == text)
            {   
                cr->setEnabled(true);
                xp->setEnabled(true);
                lvl->setEnabled(false);
                cls->setEnabled(false);
                cr->setToolTip("");
                xp->setToolTip("");
                
                lvl->setToolTip("Only usable for Player character type");
                cls->setToolTip("Only usable for Player character type");
            }
            else
            {
                lvl->setEnabled(true);
                cls->setEnabled(true);
                cr->setEnabled(false);
                xp->setEnabled(false);
                lvl->setToolTip("");
                cls->setToolTip("");
                
                cr->setToolTip("Only usable for Enemy character type");
                xp->setToolTip("Only usable for Enemy character type");
            }
        });      
 
    
    });

    layout->addWidget(table);
    layout->addWidget(addRowButton);
    window->resize(900, 600);
    window->show();

    return app.exec();
}
#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QWidget>
#include<QGridLayout>
#include <QPushButton>
#include <QLCDNumber>

class Calculator : public QWidget
{
    Q_OBJECT
public:
    Calculator(QWidget *parent = nullptr);
    ~Calculator();
  public  slots:
    void   newDigit();
void changeOperation();
void showresult();
void reset();


 // Add you custom slots here
protected:
    void createWidgets();        //Function to create the widgets
    void placeWidget();         // Function to place the widgets
    void makeConnexions();     // Create all the connectivity

private:

    QGridLayout *btnLayout; // layout for the buttons
    QVBoxLayout *layouts;        //main layout for the button
    QVector<QPushButton*> digit;  //Vector for the digits
    QPushButton *enter;            // enter button
    QPushButton *clear;            // enter button

    QVector<QPushButton*> operate; //operation buttons
    QLCDNumber *display;// Where to display the numbers
private:
    int * left=nullptr;  //left operand
    int * right=nullptr;         // right operand
    QString *operation=nullptr;  // Pointer on the current operation
};
#endif // CALCULATOR_H

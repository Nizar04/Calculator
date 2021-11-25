/* Nizar El Mouaquit */
#include "calculator.h"

Calculator::Calculator(QWidget *parent): QWidget(parent)
{
    createWidgets();
    placeWidget();
    makeConnexions();

}
Calculator::~Calculator()
{
    delete display;
    delete layouts;
    delete btnLayout;
}
void Calculator::createWidgets()
{
    //Creating the layouts
    layouts = new QVBoxLayout();
    layouts->setSpacing(2);
    //grid layout
    btnLayout = new QGridLayout;
    //creating the buttons
    for(int i=0; i < 10; i++)
    {
        digit.push_back(new QPushButton(QString::number(i)));
        digit.back()->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        digit.back()->resize(sizeHint().width(), sizeHint().height());

    }
    //enter button
    enter = new QPushButton("Enter",this);
    enter->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    enter->resize(sizeHint().width(), sizeHint().height());

    clear = new QPushButton("Clear All",this);
    clear->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    clear->resize(sizeHint().width(), sizeHint().height());

    //operatiosn buttons
    operate.push_back(new QPushButton("+"));

    operate.push_back(new QPushButton("-"));

    operate.push_back(new QPushButton("x"));

    operate.push_back(new QPushButton("/"));

    //creating the lcd
    display = new QLCDNumber(this);
    display->setDigitCount(6);
}

void Calculator::placeWidget()
{
    layouts->addWidget(display);
    layouts->addLayout(btnLayout);
    //adding the buttons
    for(int i=1; i <10; i++)
        btnLayout->addWidget(digit[i], (i-1)/3, (i-1)%3);
    //Adding the operations
    for(int i=0; i < 4; i++)
    btnLayout->addWidget(operate[ i], i, 4);
    //Adding the 0 button
    btnLayout->addWidget(digit[0], 3, 2);
    // adding button egual
    btnLayout->addWidget(enter, 4, 0, 1,5);
    //adding button clear
    btnLayout->addWidget(clear, 3, 0, 1,2);
    setLayout(layouts);
}
void Calculator::makeConnexions()
{
    for(int i=0; i <10; i++)
        connect(digit[i], &QPushButton::clicked,
                this, &Calculator::newDigit);
    for(int i=0; i <4; i++)
        connect(operate[i], &QPushButton::clicked,
                this, &Calculator::changeOperation);
    connect(enter,&QPushButton::clicked,this,&Calculator::showresult);
    connect(clear,&QPushButton::clicked,this,&Calculator::reset);
}


void Calculator::newDigit()
{
//getting the sender
auto button = dynamic_cast<QPushButton*>(sender());
//getting the value
int value = button->text().toInt();
//Check if we have an operation defined
  if(operation)
    {
      //check if we have a value or not
        if(!right)
           right = new int{value};
        else
           *right = 10 * (*right) + value;
           display->display(*right);
     }
   else
    {
    if(!left)
    left = new int{value};
    else
    *left = 10 * (*left) + value;
    display->display(*left);
     }
}
void Calculator::changeOperation()
{
    //Getting the sender button
    auto button = dynamic_cast<QPushButton*>(sender());
    //Storing the operation
    operation = new QString{button->text()};
    //Initiating the right button
    right = new int{0};
    //reseting the display
    display->display(" ");
}
void Calculator::showresult(){
    //Getting the sender button
    auto button = dynamic_cast<QPushButton*>(sender());
    //Storing the operation
   enter = new QPushButton{button};
 if(*operation=="+")
 {

     *left+= *left+(*right);
 }
 if(*operation=="-")
 {*left+= *left-(*right);
 }

 if(*operation=="*")
 {   *left+= *left*(*right);
 }

 if(*operation=="/")
 {
     if(*right==0)
     {display->display("DIVIDING_BY_0");
}
     else
     *left= *left/(*right);
 }

else
     display->display(*left);
}
void Calculator::reset()
{
    right = new int{0};
    left = new int{0};
    operation =nullptr;
    display->display(0);
}


#include "g-header.h"

///This file includes constructor, destructor and member fxns for FIO_Dialog class

///Constructor
FIO_Dialog::FIO_Dialog()
{
    //Add box to parent container
    add(p_box);

    //Add button to box
    p_box.pack_start(but_1);
    p_box.pack_start(but_2);
    but_1.set_label("Okay");
    but_2.set_label("Error Message");
}

///Destructor
FIO_Dialog::~FIO_Dialog()
{
}

///Function to define confirm button signal
void FIO_Dialog::on_confirm_button_clicked()
{
    std::cout <<"Confirm Test"<<std::endl;
}

///Function to define question button signal
void FIO_Dialog::on_question_button_clicked()
{
    std::cout<<"Question Test"<<std::endl;
}

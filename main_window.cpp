#include "g-header.h"
#include "dialog-main.h"
#include "buttons-main.h"
#include "architecture-main.h"
#include "actions-main.h"

//This file will define constructor & destructor of the MWindow class

MWindow::MWindow()
{
    //Call functions to construct architechture
    set_window_properties();
    init_architecture();
    stage_position_setup();
    x_axis_setup();
    y_axis_setup();
    predefined_fxns_setup();
    shutter_control_setup();
    button_signals();

    //Show everything
    show_all_children();
}

//Destructor
MWindow::~MWindow()
{
}









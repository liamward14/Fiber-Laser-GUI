#include <gtkmm-3.0/gtkmm.h>
#include <cstdio>
#include <iostream>

///Class definitions
//Define Main Window class
class MWindow : public Gtk::Window
{
public:
    MWindow(); //constructor
    ~MWindow(); //destructor
protected:

    ///Gtk Widget Members

    //Top-level frames
    Gtk::Grid p_grid;
    Gtk::Frame f_1_1_1,f_1_1_2,f_1_1_3,f_1_1_4,f_1_1_5;
    //Top-level Boxes
    Gtk::Box b_2_1_1,b_2_2_1,b_2_3_1,b_2_4_1,b_2_5_1;

    ///Stage Position Members
    Gtk::Grid p_grid_3_1;
    Gtk::Label lab_4_1_1,lab_4_1_2,lab_4_1_3,lab_4_1_4,lab_4_pad_1;
    Gtk::Entry ent_4_1_1,ent_4_1_2,ent_4_1_3,ent_4_1_4,ent_4_1_5,ent_4_1_6;
    Gtk::Button but_4_1_1,but_4_1_2,but_4_1_3,but_4_1_4;
    Gtk::Button but_5_1_1,but_5_1_2,but_5_2_1,but_5_2_2;
    Gtk::Button but_5_3_1,but_5_3_2,but_5_4_1,but_5_4_2;
    Gtk::Box b_4_1_1,b_4_1_2,b_4_1_3,b_4_1_4;

    ///x_axis_setup members
    Gtk::Grid p_grid_3_2;
    Gtk::Label lab_4_2_1,lab_4_2_2,lab_4_2_3,lab_4_2_4,lab_4_2_5;
    Gtk::Button but_4_2_1,but_4_2_2,but_4_2_3,but_4_2_4,but_4_2_5,but_4_2_6;
    Gtk::Label lab_4_2_6,lab_4_2_7;
    Gtk::SpinButton spb_4_2_1,spb_4_2_2;

    ///y_axis_setup members
    Gtk::Grid p_grid_3_3;
    Gtk::Label lab_4_3_1,lab_4_3_2,lab_4_3_3,lab_4_3_4,lab_4_3_5;
    Gtk::Button but_4_3_1,but_4_3_2,but_4_3_3,but_4_3_4,but_4_3_5,but_4_3_6;
    Gtk::Label lab_4_3_6,lab_4_3_7;
    Gtk::SpinButton spb_4_3_1,spb_4_3_2;

    ///predefined_fxn_setup members
    Gtk::Grid p_grid_3_4;
    Gtk::Label lab_3_4_1,lab_3_4_2,lab_3_4_3,lab_3_4_4;
    Gtk::TextView tv_3_4_1;
    Gtk::ComboBoxText cbt_3_4_1;
    Gtk::Entry ent_3_4_1,ent_3_4_2;
    Gtk::Button but_3_4_1,but_3_4_2,but_3_4_3,but_3_4_4;

    ///shutter_control_setup members
    Gtk::Grid p_grid_3_5;
    Gtk::Button but_3_5_1,but_3_5_2;
    Gtk::Label lab_3_5_1,lab_5_pad_1,lab_5_pad_2,lab_5_pad_3;
    Gtk::Label *lab_3_5_2 = new Gtk::Label("Open"); //Open label
    Glib::RefPtr<Gtk::CssProvider> css_provider_open = Gtk::CssProvider::create();
    Gtk::Label *lab_3_5_3 = new Gtk::Label("Closed"); //Close label
    Glib::RefPtr<Gtk::CssProvider> css_provider_close = Gtk::CssProvider::create();

    //Member functions
    void init_architecture();
    void stage_position_setup();
    void x_axis_setup();
    void y_axis_setup();
    void predefined_fxns_setup();
    void shutter_control_setup();
    void button_signals();
    void on_qbutton_clicked();
    void on_save_button_clicked();
    void on_open_button_clicked();
    void on_close_button_clicked();
    void on_load_button_clicked();
    int on_save_error();
    void on_save_success();
    void on_no_name();
    void on_load_error();
    int counter=0; //this is for the shutter status fxn (temporary soln.)
    bool open = false; //this is for saving shutter settings (find better soln??)

};


/*
//Class for dialog window corresponding to File IO error
class FIO_Dialog : public Gtk::Window
{
public:
    FIO_Dialog(); //constrcutor
    ~FIO_Dialog(); //destructor

protected:
    ///Gtk Widget members
    Gtk::ButtonBox p_box;
    Gtk::Button but_1; //confirm button
    Gtk::Button but_2; //question button

    ///Member functions
    void on_confirm_button_clicked();
    void on_question_button_clicked();
};*/

///Other important definitions
//Structure type def to hold settings data
typedef struct settings
{
    Glib::ustring name;
    float abs_x;
    float abs_y;
    float origin[2];
    int shutter_status;
}FL_settings;



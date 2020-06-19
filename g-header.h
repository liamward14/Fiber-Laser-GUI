#include <gtkmm-3.0/gtkmm.h>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <boost/algorithm/string.hpp>
using namespace std;

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
    Gtk::Button but_4_1_1,but_4_1_2,but_4_1_3,but_4_1_4,but_4_1_5;
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
    Gtk::Button but_3_4_1,but_3_4_2,but_3_4_3,but_3_4_4,but_3_4_5,but_3_4_6;

    ///shutter_control_setup members
    Gtk::Grid p_grid_3_5;
    Gtk::Button but_3_5_1,but_3_5_2;
    Gtk::Label lab_3_5_1,lab_5_pad_1,lab_5_pad_2,lab_5_pad_3;
    Gtk::Label *lab_3_5_2 = new Gtk::Label("Open"); //Open label
    Glib::RefPtr<Gtk::CssProvider> css_provider_open = Gtk::CssProvider::create();
    Gtk::Label *lab_3_5_3 = new Gtk::Label("Closed"); //Close label
    Glib::RefPtr<Gtk::CssProvider> css_provider_close = Gtk::CssProvider::create();

    ///Data storage
    //Structure type def to hold origin data
    typedef struct origin
    {
        float origin_x;
        float origin_y;
    }FL_origin;

    typedef struct position
    {
        float abs_x;
        float abs_y;
        float rel_x;
        float rel_y;
    }FL_position;

    FL_origin stored_origin;
    FL_position m1;
    FL_position m2;
    FL_position m3;
    FL_position m4;

    //Member functions
    void init_architecture();
    void stage_position_setup();
    void x_axis_setup();
    void y_axis_setup();
    void predefined_fxns_setup();
    void shutter_control_setup();
    void button_signals();
    void on_qbutton_clicked();
    void on_send_button_clicked();
    void on_clear_button_clicked();
    void on_save_button_clicked();
    void on_open_button_clicked();
    void on_close_button_clicked();
    void on_load_button_clicked();
    void on_set_origin_button_clicked();
    void on_go_to_button_clicked();
    void on_display_origin_button_clicked();
    void on_m1_button_clicked();
    void on_m1r_button_clicked();
    void on_m2_button_clicked();
    void on_m2r_button_clicked();
    void on_pos_stored_successfully();
    int on_save_error();
    void on_save_success();
    void on_no_name();
    void on_load_error();
    void on_load_success();
    void on_set_origin_success();
    void on_general_error();
    void on_internal_load_success();
    void on_send_success();
    int counter=0; //this is for the shutter status fxn (temporary soln.)
    bool open = false; //this is for saving shutter settings (find better soln??)

    ///Global Styling & Fonts
    Gdk::RGBA colour = Gdk::RGBA(Glib::ustring("rgb(19,206,13)"));
    Pango::FontDescription f = Pango::FontDescription(Glib::ustring("Sans Bold 10"));
    Pango::FontDescription f2 = Pango::FontDescription(Glib::ustring("Sans 9"));
};

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



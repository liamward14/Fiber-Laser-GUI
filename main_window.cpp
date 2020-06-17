#include "g-header.h"

//This file will define all member fxns of the MWindow class

MWindow::MWindow()
{
    //Call functions to construct architechture
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

///Architecture Functions
///Function to setup the base architecture
void MWindow::init_architecture()
{
    //Add parent grid
    add(p_grid);

    //Populate grid
    for(int j=0;j<4;j++)
    {
        if(j<3)
        {
            p_grid.insert_row(j);
            p_grid.insert_column(j);
        }
        else
        {
            p_grid.insert_column(j);
        }
    }

    //Add main frames and boxes
    p_grid.attach(f_1_1_1,0,0,3,1);
    p_grid.attach(f_1_1_2,0,1,3,1);
    p_grid.attach(f_1_1_3,0,2,2,1);
    p_grid.attach(f_1_1_4,3,0,1,2);
    p_grid.attach(f_1_1_5,2,2,2,1);

    f_1_1_1.add(b_2_1_1);
    f_1_1_2.add(b_2_2_1);
    f_1_1_3.add(b_2_3_1);
    f_1_1_4.add(b_2_4_1);
    f_1_1_5.add(b_2_5_1);

    //Labels & Styling
    f_1_1_1.set_label("Stage Position");
    f_1_1_2.set_label("Shutter Control");
    f_1_1_3.set_label("X-Axis");
    f_1_1_5.set_label("Y-Axis");
    f_1_1_4.set_label("Predefined Functions");

}

///Function to setup stage position box
void MWindow::stage_position_setup()
{
    b_2_1_1.add(p_grid_3_1);

    //Populate grid
    for (int j=0;j<5;j++)
    {
        p_grid_3_1.insert_row(j);
        p_grid_3_1.insert_column(j);
    }

    ///Row 0
    p_grid_3_1.attach(lab_4_1_1,0,0);
    p_grid_3_1.attach(ent_4_1_1,1,0);
    p_grid_3_1.attach(ent_4_1_2,2,0);
    p_grid_3_1.attach(lab_4_pad_1,3,0);
    p_grid_3_1.attach(but_4_1_2,4,0);

    //Labels & Styling
    lab_4_1_1.set_label("Absolute Position");
    lab_4_pad_1.set_hexpand(true);
    but_4_1_2.set_label("Set Origin");

    ///Row 1
    p_grid_3_1.attach(lab_4_1_2,0,1);
    p_grid_3_1.attach(ent_4_1_3,1,1);
    p_grid_3_1.attach(ent_4_1_4,2,1);

    //Labels & Styling
    lab_4_1_2.set_label("Relative Position");

    ///Row 2
    p_grid_3_1.attach(but_4_1_1,0,2);
    p_grid_3_1.attach(ent_4_1_5,1,2);
    p_grid_3_1.attach(ent_4_1_6,2,2);

    //Labels & Styling
    but_4_1_1.set_label("Go to Position");

    ///Row 3
    p_grid_3_1.attach(lab_4_1_3,0,3);
    p_grid_3_1.attach(b_4_1_1,1,3);
    p_grid_3_1.attach(b_4_1_2,2,3);
    p_grid_3_1.attach(but_4_1_4,4,3,1,2);
    b_4_1_1.pack_start(but_5_1_1,Gtk::PACK_EXPAND_WIDGET);
    b_4_1_1.pack_end(but_5_1_2,Gtk::PACK_EXPAND_WIDGET);
    b_4_1_2.pack_start(but_5_2_1,Gtk::PACK_EXPAND_WIDGET);
    b_4_1_2.pack_end(but_5_2_2,Gtk::PACK_EXPAND_WIDGET);

    //Labels & Styling
    lab_4_1_3.set_label("Save Position");
    but_5_1_1.set_label("M1 +");
    but_5_1_2.set_label("M2 +");
    but_5_2_1.set_label("M3 +");
    but_5_2_2.set_label("M4 +");
    but_4_1_4.set_label("Joystick Off");


    ///Row 4
    p_grid_3_1.attach(lab_4_1_4,0,4);
    p_grid_3_1.attach(b_4_1_3,1,4);
    b_4_1_3.pack_start(but_5_3_1,Gtk::PACK_EXPAND_WIDGET);
    b_4_1_3.pack_end(but_5_3_2,Gtk::PACK_EXPAND_WIDGET);
    b_4_1_4.pack_start(but_5_4_1,Gtk::PACK_EXPAND_WIDGET);
    b_4_1_4.pack_end(but_5_4_2,Gtk::PACK_EXPAND_WIDGET);
    p_grid_3_1.attach(b_4_1_4,2,4);
    p_grid_3_1.attach(but_4_1_3,3,4);

    //Labels & Styling
    lab_4_1_4.set_label("Recall Location");
    but_5_3_1.set_label("M1 R");
    but_5_3_2.set_label("M2 R");
    but_5_4_1.set_label("M3 R");
    but_5_4_2.set_label("M4 R");
    but_4_1_3.set_label("Relative Origin");

}

///Function to setup 'X-Axis' box
void MWindow::x_axis_setup()
{
    //Add grid to parent container
    b_2_3_1.add(p_grid_3_2);

    //Populate grid
    for(int j=0;j<5;j++)
    {
        if (j<4)
        {
            p_grid_3_2.insert_row(j);
            p_grid_3_2.insert_column(j);
        }
        else
        {
            p_grid_3_2.insert_column(j);
        }
    }
    ///Spin button settings (to be customized as necessary)
    int default_min = 1;
    int default_max = 100;
    int default_val = 1;
    int default_increment = 1;
    int default_pg_increment = 10;
    ///End of spin button settings

    ///Row 0
    p_grid_3_2.attach(lab_4_2_1,0,0);
    p_grid_3_2.attach(lab_4_2_2,1,0);
    p_grid_3_2.attach(lab_4_2_3,2,0);
    p_grid_3_2.attach(lab_4_2_4,3,0);
    p_grid_3_2.attach(lab_4_2_5,4,0);

    //Labels & Styling
    lab_4_2_1.set_label("Jog");
    lab_4_2_2.set_label("Step");
    lab_4_2_3.set_hexpand(true);
    lab_4_2_4.set_label("Step");
    lab_4_2_5.set_label("Jog");

    ///Row 1
    p_grid_3_2.attach(but_4_2_1,0,1);
    p_grid_3_2.attach(but_4_2_2,1,1);
    p_grid_3_2.attach(but_4_2_3,2,1);
    p_grid_3_2.attach(but_4_2_4,3,1);
    p_grid_3_2.attach(but_4_2_5,4,1);

    //Labels & Styling
    but_4_2_1.set_label("<<<<");
    but_4_2_2.set_label("<<");
    but_4_2_3.set_label("Stop");
    but_4_2_4.set_label(">>");
    but_4_2_5.set_label(">>>>");

    ///Row 2
    p_grid_3_2.attach(lab_4_2_6,0,2,2,1);
    p_grid_3_2.attach(spb_4_2_1,2,2);

    //Labels & Styling
    lab_4_2_6.set_label("Step Size (\u03BCm)");
    //spb_4_2_1
    spb_4_2_1.set_range(default_min,default_max);
    spb_4_2_1.set_value(default_val);
    spb_4_2_1.set_increments(default_increment,default_pg_increment);
    spb_4_2_1.set_wrap(true);

    ///Row 3
    p_grid_3_2.attach(lab_4_2_7,0,3,2,1);
    p_grid_3_2.attach(spb_4_2_2,2,3);
    p_grid_3_2.attach(but_4_2_6,3,3,2,1);

    //Labels & Styling
    lab_4_2_7.set_label("Velocity (\u03BCm/s)");
    but_4_2_6.set_label("Home X");
    //spb_4_2_2
    spb_4_2_2.set_range(default_min,default_max);
    spb_4_2_2.set_value(default_val);
    spb_4_2_2.set_increments(default_increment,default_pg_increment);
    spb_4_2_2.set_wrap(true);
}

///Function to setup 'Y-Axis' box
void MWindow::y_axis_setup()
{
    //Add grid to parent container
    b_2_5_1.add(p_grid_3_3);

    //Populate grid
    for(int j=0;j<5;j++)
    {
        if (j<4)
        {
            p_grid_3_3.insert_row(j);
            p_grid_3_3.insert_column(j);
        }
        else
        {
            p_grid_3_3.insert_column(j);
        }
    }
    ///Spin button settings (to be customized as necessary)
    int default_min = 1;
    int default_max = 100;
    int default_val = 1;
    int default_increment = 1;
    int default_pg_increment = 10;
    ///End of spin button settings

    ///Row 0
    p_grid_3_3.attach(lab_4_3_1,0,0);
    p_grid_3_3.attach(lab_4_3_2,1,0);
    p_grid_3_3.attach(lab_4_3_3,2,0);
    p_grid_3_3.attach(lab_4_3_4,3,0);
    p_grid_3_3.attach(lab_4_3_5,4,0);

    //Labels & Styling
    lab_4_3_1.set_label("Jog");
    lab_4_3_2.set_label("Step");
    lab_4_3_3.set_hexpand(true);
    lab_4_3_4.set_label("Step");
    lab_4_3_5.set_label("Jog");

    ///Row 1
    p_grid_3_3.attach(but_4_3_1,0,1);
    p_grid_3_3.attach(but_4_3_2,1,1);
    p_grid_3_3.attach(but_4_3_3,2,1);
    p_grid_3_3.attach(but_4_3_4,3,1);
    p_grid_3_3.attach(but_4_3_5,4,1);

    //Labels & Styling
    but_4_3_1.set_label("<<<<");
    but_4_3_2.set_label("<<");
    but_4_3_3.set_label("Stop");
    but_4_3_4.set_label(">>");
    but_4_3_5.set_label(">>>>");

    ///Row 2
    p_grid_3_3.attach(lab_4_3_6,0,2,2,1);
    p_grid_3_3.attach(spb_4_3_1,2,2);

    //Labels & Styling
    lab_4_3_6.set_label("Step Size (\u03BCm)");
    //spb_4_3_1
    spb_4_3_1.set_range(default_min,default_max);
    spb_4_3_1.set_value(default_val);
    spb_4_3_1.set_increments(default_increment,default_pg_increment);
    spb_4_3_1.set_wrap(true);

    ///Row 3
    p_grid_3_3.attach(lab_4_3_7,0,3,2,1);
    p_grid_3_3.attach(spb_4_3_2,2,3);
    p_grid_3_3.attach(but_4_3_6,3,3,2,1);

    //Labels & Styling
    lab_4_3_7.set_label("Velocity (\u03BCm/s)");
    but_4_3_6.set_label("Home Y");
    //spb_4_3_2
    spb_4_3_2.set_range(default_min,default_max);
    spb_4_3_2.set_value(default_val);
    spb_4_3_2.set_increments(default_increment,default_pg_increment);
    spb_4_3_2.set_wrap(true);
}

///Function to setup Predefined Functions box
void MWindow::predefined_fxns_setup()
{
    //Add grid to parent container
    b_2_4_1.add(p_grid_3_4);

    //Populate grid
    for(int j=0;j<10;j++)
    {
        if(j<3)
        {
            p_grid_3_4.insert_row(j);
            p_grid_3_4.insert_column(j);
        }
        else
        {
            p_grid_3_4.insert_row(j);
        }
    }

    ///Row 0
    p_grid_3_4.attach(lab_3_4_1,0,0);
    p_grid_3_4.attach(but_3_4_1,2,0);

    //Labels & Styling
    lab_3_4_1.set_label("Predefined Functions");
    but_3_4_1.set_label("Quit");

    ///Row 1/2/3
    p_grid_3_4.attach(tv_3_4_1,0,1,3,3);

    //Labels & Styling
    tv_3_4_1.set_size_request(20,100);

    ///Row 4
    p_grid_3_4.attach(lab_3_4_2,0,4,1,1);

    //Labels & Styling
    lab_3_4_2.set_label("Select Function Below");

    ///Row 5
    p_grid_3_4.attach(cbt_3_4_1,0,5,2,1);
    p_grid_3_4.attach(but_3_4_4,2,5);

    //Labels & Styling
    but_3_4_4.set_label("Begin");
    cbt_3_4_1.append("None");
    cbt_3_4_1.append("Sample Function 1");
    cbt_3_4_1.append("Sample Function 2");

    ///Row 6
    p_grid_3_4.attach(lab_3_4_3,0,6,2,1);

    //Labels & Styling
    lab_3_4_3.set_label("Save Parameters As:");

    ///Row 7
    p_grid_3_4.attach(ent_3_4_1,0,7,2,1);
    p_grid_3_4.attach(but_3_4_2,2,7);

    //Labels & Styling
    but_3_4_2.set_label("Save");

    ///Row 8
    p_grid_3_4.attach(lab_3_4_4,0,8,2,1);

    //Labels & Styling
    lab_3_4_4.set_label("Load Parameters");

    ///Row 9
    p_grid_3_4.attach(ent_3_4_2,0,9,2,1);
    p_grid_3_4.attach(but_3_4_3,2,9);

    //Labels & Styling
    but_3_4_3.set_label("Load");

}

///Function to setup Shutter Control Box
void MWindow::shutter_control_setup()
{
    //Add grid to parent container
    b_2_2_1.add(p_grid_3_5);

    //Populate grid
    for(int j=0;j<6;j++)
    {
        if (j<2)
        {
            p_grid_3_5.insert_row(j);
            p_grid_3_5.insert_column(j);
        }
        else
        {
            p_grid_3_5.insert_column(j);
        }
    }

    //Style Provider Construction (need to make Labels in a special way)
    //Open label
    Gtk::Label *lab_3_5_2 = new Gtk::Label("Open");
    Glib::RefPtr<Gtk::CssProvider> css_provider = Gtk::CssProvider::create();
    css_provider->load_from_data("label {background-image: image(lime);}");
    lab_3_5_2->get_style_context()->add_provider(
    css_provider, GTK_STYLE_PROVIDER_PRIORITY_USER);

    Gtk::Label *lab_3_5_3 = new Gtk::Label("Closed");
    Glib::RefPtr<Gtk::CssProvider> css_provider2 = Gtk::CssProvider::create();
    css_provider2->load_from_data("label {background-image: image(red);}");
    lab_3_5_3->get_style_context()->add_provider(
    css_provider2, GTK_STYLE_PROVIDER_PRIORITY_USER);

    ///Row 0
    p_grid_3_5.attach(but_3_5_1,0,0);
    p_grid_3_5.attach(lab_3_5_1,1,0,5,1);

    //Labels & Styling
    lab_3_5_1.set_label("Status");
    lab_3_5_1.set_hexpand(true);
    but_3_5_1.set_label("Open");
    but_3_5_1.set_label("Open");

    ///Row 1
    p_grid_3_5.attach(but_3_5_2,0,1);
    p_grid_3_5.attach(lab_5_pad_1,1,1);
    p_grid_3_5.attach(*lab_3_5_2,2,1);
    p_grid_3_5.attach(lab_5_pad_2,3,1);
    p_grid_3_5.attach(*lab_3_5_3,4,1);
    p_grid_3_5.attach(lab_5_pad_3,5,1);
//    p_grid_3_5.attach(lab_3_5_2,1,1);
//    p_grid_3_5.attach(lab_3_5_3,2,1);

    //Labels & Styling
    int padding_width=70;
    int padding_height=10;
    but_3_5_2.set_label("Close");
    lab_3_5_2->set_hexpand(true);
    lab_3_5_3->set_hexpand(true);
    lab_5_pad_1.set_size_request(padding_width,padding_height);
    lab_5_pad_2.set_size_request(padding_width,padding_height);
    lab_5_pad_3.set_size_request(padding_width,padding_height);
    //lab_3_5_2.set_label("Open");
    //lab_3_5_3.set_label("Closed");


}

///End of Architecture Functions

///Function to define button signals
void MWindow::button_signals()
{
    but_3_4_1.signal_clicked().connect(sigc::mem_fun(*this,&MWindow::on_qbutton_clicked));
    but_3_4_2.signal_clicked().connect(sigc::mem_fun(*this,&MWindow::on_save_button_clicked));
}

///Function to define button responses
void MWindow::on_qbutton_clicked()
{
    hide();
}

void MWindow::on_save_button_clicked()
{
    //Open settings file
    const char *f_name = "saved_settings.txt";
    FILE *fh;

    FL_settings user_settings;
    //Process: get from buffer, retrieve ustring, retrieve as const char *, convert to float
    user_settings.name = ent_3_4_1.get_buffer()->get_text();
    user_settings.abs_x = (float )atof((ent_4_1_1.get_buffer()->get_text()).data());
    user_settings.abs_y = (float )atof((ent_4_1_2.get_buffer()->get_text()).data());
    user_settings.origin[0] = 0;
    user_settings.origin[1] = 0; //need to figure out how to change these later??
    user_settings.shutter_status = 1; //need to configure (either 1 or 0)

    fh = fopen(f_name,"a");
    if (fh==NULL)
    {
        //Could not open file
        //Need to put some sort of indicator here (pop-up window)
        exit(1);
    }
    fprintf(fh,"%s\n%f\n%f\n%f\t%f\n%d\n\n",
                    (user_settings.name).c_str(),
                    user_settings.abs_x,
                    user_settings.abs_y,
                    user_settings.origin[0],
                    user_settings.origin[1],
                    user_settings.shutter_status);
    fclose(fh);

}


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

///ARCHITECTURE FXNS
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

    //Default:
    stored_origin.origin_x = 0;
    stored_origin.origin_y = 0;
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
    css_provider_open->load_from_data("label {background-image: image(lime);}");
    css_provider_close->load_from_data("label {background-image: image(red);}");

    ///Row 0
    p_grid_3_5.attach(but_3_5_1,0,0);
    p_grid_3_5.attach(lab_3_5_1,1,0,5,1);

    //Labels & Styling
    lab_3_5_1.set_label("Status");
    lab_3_5_1.set_hexpand(true);
    but_3_5_1.set_label("Open");
    but_3_5_1.set_label("Open");
    but_3_5_1.set_size_request(70,10);

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
    but_3_5_2.set_size_request(70,10);

    if (counter==0)
    {
         //Set color indiciator
        lab_3_5_3->get_style_context()->add_provider(
        css_provider_close, GTK_STYLE_PROVIDER_PRIORITY_USER);
        css_provider_close->load_from_data("label {background-image: image(red);}"); //set bkgrnd img
        counter++;
    }


    //lab_3_5_2.set_label("Open");
    //lab_3_5_3.set_label("Closed");


}
///END OF ARCHITECTURE FXNS

///BUTTON RESPONSE FXNS
///Function to define button signals
void MWindow::button_signals()
{
    but_3_4_1.signal_clicked().connect(sigc::mem_fun(*this,&MWindow::on_qbutton_clicked));
    but_3_4_2.signal_clicked().connect(sigc::mem_fun(*this,&MWindow::on_save_button_clicked));
    but_3_5_1.signal_clicked().connect(sigc::mem_fun(*this,&MWindow::on_open_button_clicked));
    but_3_5_2.signal_clicked().connect(sigc::mem_fun(*this,&MWindow::on_close_button_clicked));
    but_3_4_3.signal_clicked().connect(sigc::mem_fun(*this,&MWindow::on_load_button_clicked));
    but_4_1_2.signal_clicked().connect(sigc::mem_fun(*this,&MWindow::on_set_origin_button_clicked));
}

///Function to define quit button response
void MWindow::on_qbutton_clicked()
{
    hide();
}

///Function to define save button response
void MWindow::on_save_button_clicked()
{

    //Open settings file
    Glib::ustring name = ent_3_4_1.get_buffer()->get_text();
    Glib::ustring f_path = "user-saved-params\\";
    Glib::ustring f_end = ".txt";
    Glib::ustring f_name = f_path+name+f_end;//saved_settings.txt";
    FILE *fh;

    FL_settings user_settings;
    //Process: get from buffer, retrieve ustring, retrieve as const char *, convert to float
    //Glib::ustring name = ent_3_4_1.get_buffer()->get_text();
    if (name[0]=='\0')
    {
        on_no_name();
        return;
    }
    user_settings.name = name;
    user_settings.abs_x = (float )atof((ent_4_1_1.get_buffer()->get_text()).data());
    user_settings.abs_y = (float )atof((ent_4_1_2.get_buffer()->get_text()).data());
    user_settings.origin[0] = 0;
    user_settings.origin[1] = 0; //need to figure out how to change these later??
    int shutter_status;
    if (open)
    {
        shutter_status=1;//shutter open
    }
    else
    {
        shutter_status=0;//shutter closed
    }
    user_settings.shutter_status = shutter_status; //need to configure (either 1 or 0)

    fh = fopen(f_name.data(),"w");
    if (fh==NULL)
    {
        //Could not open file
        int result = on_save_error();
        switch(result)
        {
        case(Gtk::RESPONSE_OK):
            return;
        default:
            std::cout<<"Unexpected click"<<std::endl;
            break;
        }

    }
    fprintf(fh,"Name:%s,\nx:%f,\ny:%f,\noriginx:%f,\noriginy:%f,\nshutter:%d\n\n",
                    (user_settings.name).c_str(),
                    user_settings.abs_x,
                    user_settings.abs_y,
                    user_settings.origin[0],
                    user_settings.origin[1],
                    user_settings.shutter_status);
    fclose(fh);

    //Saved successfully
    on_save_success();
}

///Function to define 'load' button response
void MWindow::on_load_button_clicked()
{
    Glib::ustring f_path = "user-saved-params\\";
    Glib::ustring f_end = ".txt";
    Glib::ustring f_name = f_path+(ent_3_4_2.get_buffer()->get_text())+f_end;
    FL_settings load_settings; //define structure member to hold parsed loaded data
    std::string labels[5] = {"Name","x","y","origin","shutter"};
    int j=0; //keeping track of loaded members
    //Init structure members
    string name;
    float xf,yf,o_xf,o_yf,shutterf;

    //Use C++ method of reading files b/c it makes parsing data easier
    std::string line;
    std::ifstream fh (f_name.data());
    if (fh.is_open())
    {
        while (std::getline(fh,line,','))
        {
            //std::cout << line << std::endl;
            switch(j)
            {
            case 0:{ //Reading 'Name'
                name = line.string::substr(5,string::npos);
                //std::cout << name << std::endl;
                break;
                }
            case 1:{//Reading 'x'
                std::string x = line.string::substr(3,string::npos);
                //std::cout << x << std::endl;
                //printf("Line: %s\t",line);
                //printf("Abs x string: %s\n",x);
                xf = (float )atof(x.c_str()); //convert to float
                break;
                }
            case 2:{ //Reading 'y'
                std::string y = line.string::substr(3,string::npos);
                //std::cout << y << std::endl;
                //printf("Line: %s\t",line);
                //printf("Abs y string: %s\n",y);
                yf = atof(y.c_str());
                }
            case 3:{//Reading 'originx'
                std::string o_x = line.string::substr(9,string::npos);
                //std::cout << o_x << std::endl;
                o_xf = atof(o_x.c_str());
                break;
                }
            case 4:{
                std::string o_y = line.string::substr(9,string::npos);
                //std::cout << o_y << std::endl;
                o_yf = atof(o_y.c_str());
                break;
                }
            case 5:{ //Reading 'shutter'
                std::string shutter = line.string::substr(9,string::npos);
                //std::cout << shutter << std::endl;
                shutterf = atof(shutter.c_str());
                break;
                }
            }
            j++;
        }
        load_settings.abs_x = xf;
        load_settings.abs_y = yf;
        //printf("Absolute x: %f\n",xf);
        //printf("Absolute y: %f\n",yf);
        load_settings.name = name;
        load_settings.origin[0] = o_xf;
        load_settings.origin[1] = o_yf;
        load_settings.shutter_status = shutterf;
        fh.close();
        on_load_success(); //display dialog if file loaded correctly
    }
    else
    {
        //Could not open file
        on_load_error();
        return;
    }

    //Write loaded settings to appropriate buffers (will need to connect this to backend eventually)
    ent_4_1_1.get_buffer()->set_text(to_string(load_settings.abs_x));
    ent_4_1_2.get_buffer()->set_text(to_string(load_settings.abs_y));

    //Simulate open / close click based on loaded settings
    if (load_settings.shutter_status)
    {
        on_open_button_clicked();
    }
    else
    {
        on_close_button_clicked();
    }
}

///Function to define 'open' shutter button response
void MWindow::on_open_button_clicked()
{
    css_provider_open->load_from_data("label {background-image: image(lime);}"); //reset bkgrnd img

    //Set colour indicator
    lab_3_5_2->get_style_context()->add_provider(
    css_provider_open, GTK_STYLE_PROVIDER_PRIORITY_USER);

    //remove 'Close' color indicator
    css_provider_close->load_from_data("label {background-image: image(transparent);}");
    open = true; //set open indicator to true

}

///Function to define 'close' shutter button response
void MWindow::on_close_button_clicked()
{
    css_provider_close->load_from_data("label {background-image: image(red);}"); //reset bkgrnd img

    //Set color indiciator
    lab_3_5_3->get_style_context()->add_provider(
    css_provider_close, GTK_STYLE_PROVIDER_PRIORITY_USER);

    //remove 'Open' color indicator
    css_provider_open->load_from_data("label {background-image: image(transparent);}");
    open = false; //set open indiciator to false
}

///Function to define button response for Set Origin button
void MWindow::on_set_origin_button_clicked()
{
    stored_origin.origin_x = atof(((ent_4_1_1.get_buffer()->get_text()).data()));
    stored_origin.origin_y = atof(((ent_4_1_2.get_buffer()->get_text()).data()));
    on_set_origin_success();
}
///END OF BUTTON RESPONSE FXNS

///DIALOG FXNS
///Function to define error message for saving settings
int MWindow::on_save_error()
{
    Gtk::MessageDialog dialog(*this,
    "Error saving settings.\nPlease review the text file\nholding user-save settings.",
    false,Gtk::MESSAGE_QUESTION,Gtk::BUTTONS_OK);
    int result = dialog.run();
    return result;
}

///Function to prompt user for saved settings name
void MWindow::on_no_name()
{
    Gtk::MessageDialog dialog(*this,
    "Please enter a name to save the settings under.",
    false,Gtk::MESSAGE_QUESTION,Gtk::BUTTONS_OK);
    dialog.run();
}

///Function to display success dialog for saving settings
void MWindow::on_save_success()
{
    Gtk::MessageDialog dialog(*this,
    "Settings saved successfully!",
    false,Gtk::MESSAGE_QUESTION,Gtk::BUTTONS_OK);
    dialog.run();
    ent_3_4_1.get_buffer()->set_text("");
}

///Function to display failure dialog for loading settings
void MWindow::on_load_error()
{
    Glib::ustring f_end = ".txt";
    Glib::ustring f_name = (ent_3_4_2.get_buffer()->get_text())+f_end;
    Glib::ustring msg = "Error loading file: "+f_name+"\n"+"Please make sure the file exists and is not corrupted";
    Gtk::MessageDialog dialog(*this,
    msg.data(),
    false,Gtk::MESSAGE_QUESTION,Gtk::BUTTONS_OK);
    dialog.run();
    ent_3_4_2.get_buffer()->set_text("");
}

///Function to display success dialog for loading settings
void MWindow::on_load_success()
{
    Gtk::MessageDialog dialog(*this,
    "Settings loaded successfully!",
    false,Gtk::MESSAGE_QUESTION,Gtk::BUTTONS_OK);
    dialog.run();
    ent_3_4_2.get_buffer()->set_text("");
}

///Function to display success dialog for storing origin
void MWindow::on_set_origin_success()
{
    std::string msg;
    string x_pos = to_string(stored_origin.origin_x);
    string y_pos = to_string(stored_origin.origin_y);
    msg = "Origin set successfully!\nO:("+x_pos+","+y_pos+")";
    Gtk::MessageDialog dialog(*this,
    msg.c_str(),
    false,Gtk::MESSAGE_QUESTION,Gtk::BUTTONS_OK);
    dialog.run();
}
///END OF DIALOG FXNS
//Other stuff (including global vars needed) are defined below:
//static int counter=0;



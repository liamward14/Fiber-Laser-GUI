
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
    but_4_1_1.signal_clicked().connect(sigc::mem_fun(*this,&MWindow::on_go_to_button_clicked));
    but_4_1_5.signal_clicked().connect(sigc::mem_fun(*this,&MWindow::on_display_origin_button_clicked));
    but_5_1_1.signal_clicked().connect(sigc::mem_fun(*this,&MWindow::on_m1_button_clicked));
    but_5_3_1.signal_clicked().connect(sigc::mem_fun(*this,&MWindow::on_m1r_button_clicked));
    but_5_1_2.signal_clicked().connect(sigc::mem_fun(*this,&MWindow::on_m2_button_clicked));
    but_5_3_2.signal_clicked().connect(sigc::mem_fun(*this,&MWindow::on_m2r_button_clicked));
    but_3_4_5.signal_clicked().connect(sigc::mem_fun(*this,&MWindow::on_send_button_clicked));
    but_3_4_6.signal_clicked().connect(sigc::mem_fun(*this,&MWindow::on_clear_button_clicked));
    but_5_2_1.signal_clicked().connect(sigc::mem_fun(*this,&MWindow::on_m3_button_clicked));
    but_5_4_1.signal_clicked().connect(sigc::mem_fun(*this,&MWindow::on_m3r_button_clicked));
    but_5_2_2.signal_clicked().connect(sigc::mem_fun(*this,&MWindow::on_m4_button_clicked));
    but_5_4_2.signal_clicked().connect(sigc::mem_fun(*this,&MWindow::on_m4r_button_clicked));
    but_4_1_4.signal_clicked().connect(sigc::mem_fun(*this,&MWindow::on_joystick_off_button_clicked));
    but_4_2_2.signal_clicked().connect(sigc::mem_fun(*this,&MWindow::on_x_left_step_button_clicked));
    but_4_1_3.signal_clicked().connect(sigc::mem_fun(*this,&MWindow::on_relative_origin_button_clicked));
    but_4_2_4.signal_clicked().connect(sigc::mem_fun(*this,&MWindow::on_x_right_step_button_clicked));
    but_4_2_5.signal_clicked().connect(sigc::mem_fun(*this,&MWindow::on_x_right_jog_button_clicked));
    but_4_2_1.signal_clicked().connect(sigc::mem_fun(*this,&MWindow::on_x_left_jog_button_clicked));
    but_4_2_6.signal_clicked().connect(sigc::mem_fun(*this,&MWindow::on_home_x_button_clicked));
    but_4_2_3.signal_clicked().connect(sigc::mem_fun(*this,&MWindow::on_x_stop_button_clicked));
    but_4_3_2.signal_clicked().connect(sigc::mem_fun(*this,&MWindow::on_y_left_step_button_clicked));
    but_4_3_1.signal_clicked().connect(sigc::mem_fun(*this,&MWindow::on_y_left_jog_button_clicked));
    but_4_3_4.signal_clicked().connect(sigc::mem_fun(*this,&MWindow::on_y_right_step_button_clicked));
    but_4_3_5.signal_clicked().connect(sigc::mem_fun(*this,&MWindow::on_y_right_jog_button_clicked));
    but_4_3_6.signal_clicked().connect(sigc::mem_fun(*this,&MWindow::on_home_y_button_clicked));
    but_4_3_3.signal_clicked().connect(sigc::mem_fun(*this,&MWindow::on_y_stop_button_clicked));
    but_3_4_7.signal_clicked().connect(sigc::mem_fun(*this,&MWindow::on_enable_disable_button_clicked));
    but_3_4_4.signal_clicked().connect(sigc::mem_fun(*this,&MWindow::on_begin_button_clicked));
}

///Function to define quit button response
void MWindow::on_qbutton_clicked()
{
    int result = -1*(on_quit_request());
    switch(result)
    {
    case 5:
        hide();
        break;
    case 6:
        return;
    }
}

///Function to define Send button response
void MWindow::on_send_button_clicked()
{
    //Need to send info via serial communication
    //There will be a placeholder here for now
    on_send_success(); //display dialog
}

///Function to define Clear button response
void MWindow::on_clear_button_clicked()
{
    //Clear the textview buffer that sends commands
    tv_3_4_1.get_buffer()->set_text("");
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
            on_general_error();
            //std::cout<<"Unexpected click"<<std::endl;
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

///Function to define 'Enable / Disable' predefined fxns button response
void MWindow::on_enable_disable_button_clicked()
{
    std::string current_label = but_3_4_7.get_label();
    if(current_label=="Enable")
    {
        but_3_4_7.set_label("Disable");
        cbt_3_4_1.set_sensitive(true);
        on_pre_functions_enabled_disabled(current_label);
    }
    else if (current_label=="Disable")
    {
        but_3_4_7.set_label("Enable");
        cbt_3_4_1.set_sensitive(false);
        on_pre_functions_enabled_disabled(current_label);
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
    float ox = atof(((ent_4_1_1.get_buffer()->get_text()).data()));
    float oy = atof(((ent_4_1_2.get_buffer()->get_text()).data()));
    if(abs(ox)>25||abs(oy)>25)
    {
        //Display message dialog
        on_range_violated();

        //Set to max params for x
        if(ox<-25)
        {
            ent_4_1_1.get_buffer()->set_text("-25");
        }
        else if (ox>25)
        {
            ent_4_1_1.get_buffer()->set_text("25");
        }

        //Set to max params for y
        if(oy<-25)
        {
            ent_4_1_2.get_buffer()->set_text("-25");
        }
        else if (oy>25)
        {
            ent_4_1_2.get_buffer()->set_text("25");
        }
        on_abs_pos_change();
        return;
    }
    stored_origin.origin_x = ox;
    stored_origin.origin_y = oy;
    on_set_origin_success();
    on_abs_pos_change();
}

///Function to define Go To Position button response
void MWindow::on_go_to_button_clicked()
{
    //Only changes labels for now - will eventually need to connect with backend
    float current_x = atof((ent_4_1_5.get_buffer()->get_text()).data());
    float current_y = atof((ent_4_1_6.get_buffer()->get_text()).data());

    if (abs(current_x)>25 || abs(current_y)>25)
    {
        //Display message dialog
        on_range_violated();

        //Set to max params for x
        if(current_x<-25)
        {
            ent_4_1_1.get_buffer()->set_text("-25");
        }
        else if (current_x>25)
        {
            ent_4_1_1.get_buffer()->set_text("25");
        }

        //Set to max params for y
        if(current_y<-25)
        {
            ent_4_1_2.get_buffer()->set_text("-25");
        }
        else if (current_y>25)
        {
            ent_4_1_2.get_buffer()->set_text("25");
        }
        ent_4_1_5.get_buffer()->set_text("0.00000"); //reset go-to entries
        ent_4_1_6.get_buffer()->set_text("0.00000");
        on_abs_pos_change(); //adjust relative position
        return; //exit
    }

    //if no errors, execute go-to command(s)
    ent_4_1_1.get_buffer()->set_text(to_string(current_x));
    ent_4_1_2.get_buffer()->set_text(to_string(current_y));

    ent_4_1_5.get_buffer()->set_text("0.00000");
    ent_4_1_6.get_buffer()->set_text("0.00000");

    on_abs_pos_change();
}

///Function to define Display Origin button response
void MWindow::on_display_origin_button_clicked()
{
    std::string msg;
    string x_pos = to_string(stored_origin.origin_x);
    string y_pos = to_string(stored_origin.origin_y);
    msg = "Current Origin:("+x_pos+","+y_pos+")";
    Gtk::MessageDialog dialog(*this,
    msg.c_str(),
    false,Gtk::MESSAGE_QUESTION,Gtk::BUTTONS_OK);
    dialog.run();
}

///Function to define M1+ Save button response
void MWindow::on_m1_button_clicked()
{
    try
    {
        m1.abs_x = atof((ent_4_1_1.get_buffer()->get_text()).data());
        m1.abs_y = atof((ent_4_1_2.get_buffer()->get_text()).data());
        m1.rel_x = atof((ent_4_1_3.get_buffer()->get_text()).data());
        m1.rel_y = atof((ent_4_1_4.get_buffer()->get_text()).data());
    }
    catch(...)
    {
        on_general_error();
    }
    on_pos_stored_successfully();

}

///Function to define M1 R recall button response
void MWindow::on_m1r_button_clicked()
{
    //Need to connect to backend still
    ent_4_1_1.get_buffer()->set_text(to_string(m1.abs_x));
    ent_4_1_2.get_buffer()->set_text(to_string(m1.abs_y));
    ent_4_1_3.get_buffer()->set_text(to_string(m1.rel_x));
    ent_4_1_4.get_buffer()->set_text(to_string(m1.rel_y));
    on_internal_load_success();
}

///Function to define M2+ Save button response
void MWindow::on_m2_button_clicked()
{
    try
    {
        m2.abs_x = atof((ent_4_1_1.get_buffer()->get_text()).data());
        m2.abs_y = atof((ent_4_1_2.get_buffer()->get_text()).data());
        m2.rel_x = atof((ent_4_1_3.get_buffer()->get_text()).data());
        m2.rel_y = atof((ent_4_1_4.get_buffer()->get_text()).data());
    }
    catch(...)
    {
        on_general_error();
    }
    on_pos_stored_successfully();

}

///Function to define M2 R recall button response
void MWindow::on_m2r_button_clicked()
{
    //Need to connect to backend still
    ent_4_1_1.get_buffer()->set_text(to_string(m2.abs_x));
    ent_4_1_2.get_buffer()->set_text(to_string(m2.abs_y));
    ent_4_1_3.get_buffer()->set_text(to_string(m2.rel_x));
    ent_4_1_4.get_buffer()->set_text(to_string(m2.rel_y));
    on_internal_load_success();
}

///Function to define M3 + save button response
void MWindow::on_m3_button_clicked()
{
    try
    {
        m3.abs_x = atof((ent_4_1_1.get_buffer()->get_text()).data());
        m3.abs_y = atof((ent_4_1_2.get_buffer()->get_text()).data());
        m3.rel_x = atof((ent_4_1_3.get_buffer()->get_text()).data());
        m3.rel_y = atof((ent_4_1_4.get_buffer()->get_text()).data());
    }
    catch(...)
    {
        on_general_error(); //this may not be right...will have to check
    }
    on_pos_stored_successfully();
}

///Function to define M3 R recall button response
void MWindow::on_m3r_button_clicked()
{
    //Need to connect to backend still
    ent_4_1_1.get_buffer()->set_text(to_string(m3.abs_x));
    ent_4_1_2.get_buffer()->set_text(to_string(m3.abs_y));
    ent_4_1_3.get_buffer()->set_text(to_string(m3.rel_x));
    ent_4_1_4.get_buffer()->set_text(to_string(m3.rel_y));
    on_internal_load_success();
}

///Function to define M4 + save button response
void MWindow::on_m4_button_clicked()
{
    try
    {
        m4.abs_x = atof((ent_4_1_1.get_buffer()->get_text()).data());
        m4.abs_y = atof((ent_4_1_2.get_buffer()->get_text()).data());
        m4.rel_x = atof((ent_4_1_3.get_buffer()->get_text()).data());
        m4.rel_y = atof((ent_4_1_4.get_buffer()->get_text()).data());
    }
    catch(...)
    {
        on_general_error(); //this may not be right...will have to check
    }
    on_pos_stored_successfully();
}

///Function to define M4 R recall button response
void MWindow::on_m4r_button_clicked()
{
    //Need to connect to backend still
    ent_4_1_1.get_buffer()->set_text(to_string(m4.abs_x));
    ent_4_1_2.get_buffer()->set_text(to_string(m4.abs_y));
    ent_4_1_3.get_buffer()->set_text(to_string(m4.rel_x));
    ent_4_1_4.get_buffer()->set_text(to_string(m4.rel_y));
    on_internal_load_success();
}

///Function to define x-axis left step button response
void MWindow::on_x_left_step_button_clicked()
{
    float current_x = atof((ent_4_1_1.get_buffer()->get_text()).data());
    float step_size = atof((spb_4_2_1.get_buffer()->get_text()).data());
    float new_x = current_x - step_size;
    if (new_x<-25)
    {
        on_range_violated();
        float x_left_limit = -25;
        ent_4_1_1.get_buffer()->set_text(to_string(x_left_limit));
        on_abs_pos_change();
        return;
    }
    else if (new_x>25)
    {
        on_range_violated();
        float x_right_limit = 25; //NEED TO CHANGE THIS - ACTUAL SYSTEM IS MM not MICROMeters
        ent_4_1_1.get_buffer()->set_text(to_string(x_right_limit));
        on_abs_pos_change();
        return;
    }
    else
    {
    ent_4_1_1.get_buffer()->set_text(to_string(new_x));
    on_abs_pos_change();
    }
}

///Function to define x-axis left jog button response
void MWindow::on_x_left_jog_button_clicked()
{
    //nothing yet
    on_general_clicked();
}

///Fucntion to define x-axis right step button response
void MWindow::on_x_right_step_button_clicked()
{
    float current_x = atof((ent_4_1_1.get_buffer()->get_text()).data());
    float step_size = atof((spb_4_2_1.get_buffer()->get_text()).data());
    float new_x = current_x + step_size;
    if (new_x<-25)
    {
        on_range_violated();
        float x_left_limit = -25;
        ent_4_1_1.get_buffer()->set_text(to_string(x_left_limit));
        on_abs_pos_change();
        return;
    }
    else if (new_x>25)
    {
        on_range_violated();
        float x_right_limit = 25; //NEED TO CHANGE THIS - ACTUAL SYSTEM IS MM not MICROMeters
        ent_4_1_1.get_buffer()->set_text(to_string(x_right_limit));
        on_abs_pos_change();
        return;
    }
    else
    {
    ent_4_1_1.get_buffer()->set_text(to_string(new_x));
    on_abs_pos_change();
    }
}

///Function to define x-axis right jog button response
void MWindow::on_x_right_jog_button_clicked()
{
    //nothing yet
    on_general_clicked();
}

///Function to define x-axis 'Home X' button response
void MWindow::on_home_x_button_clicked()
{
    //Need to connect to backend still
    float hx = stored_origin.origin_x;
    ent_4_1_1.get_buffer()->set_text(to_string(hx));
    on_abs_pos_change();
}

///Function to define x-axis 'Stop' button response
void MWindow::on_x_stop_button_clicked()
{
    //Nothign yet - need to integrate with backend
    on_general_clicked();
}

///Function to define y-axis left step button response
void MWindow::on_y_left_step_button_clicked()
{
    float current_y = atof((ent_4_1_2.get_buffer()->get_text()).data());
    float step_size = atof((spb_4_3_1.get_buffer()->get_text()).data());
    float new_y = current_y - step_size;
    if (new_y<-25)
    {
        on_range_violated();
        float y_left_limit = -25;
        ent_4_1_2.get_buffer()->set_text(to_string(y_left_limit));
        on_abs_pos_change();
        return;
    }
    else if (new_y>25)
    {
        on_range_violated();
        float y_right_limit = 25; //NEED TO CHANGE THIS - ACTUAL SYSTEM IS MM not MICROMeters
        ent_4_1_2.get_buffer()->set_text(to_string(y_right_limit));
        on_abs_pos_change();
        return;
    }
    else
    {
    ent_4_1_2.get_buffer()->set_text(to_string(new_y));
    on_abs_pos_change();
    }
}

///Function to define y-axis left jog button response
void MWindow::on_y_left_jog_button_clicked()
{
    //nothing yet, need to connect w/ backend
    on_general_clicked();
}

///Function to define y-axis right step button response
void MWindow::on_y_right_step_button_clicked()
{
    float current_y = atof((ent_4_1_2.get_buffer()->get_text()).data());
    float step_size = atof((spb_4_3_1.get_buffer()->get_text()).data());
    float new_y = current_y + step_size;
    if (new_y<-25)
    {
        on_range_violated();
        float y_left_limit = -25;
        ent_4_1_2.get_buffer()->set_text(to_string(y_left_limit));
        on_abs_pos_change();
        return;
    }
    else if (new_y>25)
    {
        on_range_violated();
        float y_right_limit = 25; //NEED TO CHANGE THIS - ACTUAL SYSTEM IS MM not MICROMeters
        ent_4_1_2.get_buffer()->set_text(to_string(y_right_limit));
        on_abs_pos_change();
        return;
    }
    else
    {
    ent_4_1_2.get_buffer()->set_text(to_string(new_y));
    on_abs_pos_change();
    }
}

///Function to define y-axis right jog button response
void MWindow::on_y_right_jog_button_clicked()
{
    //nothing yet, need to connect w/ backend
    on_general_clicked();
}

///Function to define 'Home Y' button response
void MWindow::on_home_y_button_clicked()
{
    //need to connect w/ backend still
    float hy = stored_origin.origin_y;
    ent_4_1_2.get_buffer()->set_text(to_string(hy));
    on_abs_pos_change();
}

///Function to define Relative Origin button press
void MWindow::on_relative_origin_button_clicked()
{
    //Will go to current origin position
    float origin_x = stored_origin.origin_x;
    float origin_y = stored_origin.origin_y;

    ent_4_1_1.get_buffer()->set_text(to_string(origin_x));
    ent_4_1_2.get_buffer()->set_text(to_string(origin_y));

    on_abs_pos_change();
}

///Function to define y-axis stop button response
void MWindow::on_y_stop_button_clicked()
{
    //need to integrate w/ backend still
    on_general_clicked();
}

///Function to define response to 'Begin' button
void MWindow::on_begin_button_clicked()
{
    //Need to connect to backend still
    on_general_clicked();
}

///END OF BUTTON RESPONSE FXNS

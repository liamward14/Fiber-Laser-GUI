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

///Function to display success dialog for storing position
void MWindow::on_pos_stored_successfully()
{
    string msg = "Position stored successfully";
    Gtk::MessageDialog dialog(*this,
    msg.c_str(),
    false,Gtk::MESSAGE_QUESTION,Gtk::BUTTONS_OK);
    dialog.run();
}

///Function for undefined error
void MWindow::on_general_error()
{
    string msg = "Error Occurred";
    Gtk::MessageDialog dialog(*this,
    msg.c_str(),
    false,Gtk::MESSAGE_QUESTION,Gtk::BUTTONS_OK);
    dialog.run();
}

///Function to display success for loading saved settings correctly
void MWindow::on_internal_load_success()
{
    string msg = "Position loaded successfully";
    Gtk::MessageDialog dialog(*this,
    msg.c_str(),
    false,Gtk::MESSAGE_QUESTION,Gtk::BUTTONS_OK);
    dialog.run();
}
///END OF DIALOG FXNS
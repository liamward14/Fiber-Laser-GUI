///GENERAL ACTION FUNCTIONS
//These are defined in order to respond to other activites quielty

///Function to define relative pos change when abs changes

void MWindow::on_abs_pos_change()
{
    float ox = stored_origin.origin_x;
    float oy = stored_origin.origin_y;
    float absx = atof((ent_4_1_1.get_buffer()->get_text()).data());
    float absy = atof((ent_4_1_2.get_buffer()->get_text()).data());

    //Relative positions
    float rx = absx-ox;
    float ry = absy-oy;

    //set text buffers of realtive position
    ent_4_1_3.get_buffer()->set_text(to_string(rx));
    ent_4_1_4.get_buffer()->set_text(to_string(ry));
}

#include "ui.h"

void
cb (
  GtkWidget* self,
  GtkStateFlags flags,
  gpointer user_data
) {
    //~ printf ("[signal] %d\n", flags);
    if (flags == 128)
        g_application_quit ((GApplication *) user_data);
}


void change (GtkRange * range, const char * cmd) {
    char * run = g_strdup_printf (cmd, gtk_range_get_value (range));
    printf ("[command] %s\n", run);
    system (run);
    free (run);
}

void launch (const char * cmd, GtkWidget * w) {
    system (cmd);
}

UI::UI (GtkApplication* app) {
    window = gtk_application_window_new (app);
    brightness = gtk_scale_new_with_range (GTK_ORIENTATION_HORIZONTAL, 5, 100, 1);
    volume = gtk_scale_new_with_range (GTK_ORIENTATION_HORIZONTAL, 1, 100, 1);
    mic = gtk_scale_new_with_range (GTK_ORIENTATION_HORIZONTAL, 1, 100, 1);
    
    g_signal_connect (brightness, "value-changed", (GCallback) change, "brightnessctl s %f%%");
    
    GtkWidget * box = gtk_box_new (GTK_ORIENTATION_VERTICAL, 3);
    
    gtk_window_set_child ((GtkWindow *)window, box);
    
    gtk_box_append ((GtkBox *) box, brightness);
    gtk_box_append ((GtkBox *) box, gtk_label_new ("Brightness"));
    gtk_box_append ((GtkBox *) box, volume);
    gtk_box_append ((GtkBox *) box, gtk_label_new ("Volume"));
    gtk_box_append ((GtkBox *) box, mic);
    gtk_box_append ((GtkBox *) box, gtk_label_new ("Mic"));
    
    GtkWidget * label = gtk_label_new ("c");
    gtk_label_set_markup ((GtkLabel *)label, "<small><tt>Rock and roll will never die</tt></small>");
    GtkWidget * button_box = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 10);
    gtk_box_append ((GtkBox *) box, button_box);    
    
    GtkWidget   * settings = gtk_button_new_with_label ("Settings"),
                * mixer = gtk_button_new_with_label ("Mixer"),
                * router = gtk_button_new_with_label ("Audio Router");
    
    g_signal_connect_swapped (settings, "clicked", launch, "raspi-config");
    g_signal_connect_swapped (mixer, "clicked", launch, "pavucontrol");
    g_signal_connect_swapped (router, "clicked", launch, "qjackctl");
    
    gtk_box_append ((GtkBox *) button_box, settings);        
    gtk_box_append ((GtkBox *) button_box, mixer);        
    gtk_box_append ((GtkBox *) button_box, router);        
    
    gtk_box_set_homogeneous ((GtkBox *) button_box, true);
    gtk_widget_set_margin_top (button_box, 30);
    gtk_widget_set_margin_top (label, 20);
    
    gtk_box_append ((GtkBox *) box, label);

    gtk_widget_set_margin_top (box, 30);
    gtk_widget_set_margin_start (box, 30);
    gtk_widget_set_margin_end (box, 30);
    gtk_widget_set_margin_bottom (box, 30);
    
    gtk_widget_set_sensitive (label, false);
    gtk_window_set_decorated ((GtkWindow *) window, false);
    gtk_widget_set_size_request (window, 600, 200);
    gtk_window_set_title ((GtkWindow *) window, "Control Panel");
    gtk_window_present ((GtkWindow *)window);
    
    g_signal_connect (window, "state-flags-changed", (GCallback) cb, app);
}

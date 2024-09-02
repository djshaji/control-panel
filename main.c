#include <gtk/gtk.h>
#include "ui.h"

static void
activate (GtkApplication* app,
          gpointer        user_data)
{
    UI ui = UI (app);
}

int main (int argc, char ** argv) {
    GtkApplication *app;
    int status;

    app = gtk_application_new ("org.acoustixaudio.controlpanel", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
    status = g_application_run (G_APPLICATION (app), argc, argv);
    g_object_unref (app);

    printf ("status: %d\n", status);
}

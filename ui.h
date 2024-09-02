#ifndef UI_H
#define UI_H

#include <gtk/gtk.h>

class UI {
    public:
    GtkWidget * window, * brightness, * volume, * mic ;
    
    UI (GtkApplication* app);
};

#endif

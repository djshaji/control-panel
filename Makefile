GTK=`pkg-config gtk4 --libs --cflags`

all:
	c++ main.c ui.c $(GTK) -fpermissive -o control-panel

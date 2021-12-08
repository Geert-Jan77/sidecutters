/*
 Compile

    gcc main.c -o main `pkg-config --cflags --libs gtk+-3.0`

 Run
 
    ./main
*/

#include <gtk/gtk.h>

static void activate (GtkApplication *app, gpointer user_data)
{
    GtkWidget *window;
    window = gtk_application_window_new (app);
    gtk_window_set_title (GTK_WINDOW (window), "Side Cutters");
    GdkRectangle workarea = {0};
    gdk_monitor_get_workarea(gdk_display_get_primary_monitor(gdk_display_get_default()), &workarea);
    //printf ("W: %u x H:%u\n", workarea.width, workarea.height);
    gtk_window_set_default_size (GTK_WINDOW (window), workarea.width, workarea.height);
    gtk_widget_show_all (window);
}

int main (int argc, char **argv)
{
    GtkApplication *app;
    int status;
    app = gtk_application_new ("side.cutters", G_APPLICATION_FLAGS_NONE);
    g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
    status = g_application_run (G_APPLICATION (app), argc, argv);
    g_object_unref (app);
    return status;
}

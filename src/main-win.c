#include <gtk/gtk.h>

GdkPixbuf *create_pixbuf(const gchar * filename) 
{
   GdkPixbuf *pixbuf;
   GError *error = NULL;
   pixbuf = gdk_pixbuf_new_from_file(filename, &error);
   if (!pixbuf) 
   {
      fprintf(stderr, "%s\n", error->message);
      g_error_free(error);
   }
   return pixbuf;
}

int main(int argc, char *argv[]) {
    
  GtkWidget *window;
  GdkPixbuf *icon;
  gtk_init(&argc, &argv);
  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title(GTK_WINDOW(window), "Side Cutters");
  GdkRectangle workarea = {0};
  gdk_monitor_get_workarea(gdk_display_get_primary_monitor(gdk_display_get_default()), &workarea);
  gtk_window_set_default_size (GTK_WINDOW (window), workarea.width, workarea.height);
  icon = create_pixbuf("rsc/icon.png");  
  gtk_window_set_icon(GTK_WINDOW(window), icon);
  gtk_widget_show(window);
  gtk_widget_show_all (window);
  g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);
  g_object_unref(icon);    
  gtk_main();
  return 0;
}

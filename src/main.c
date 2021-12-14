#include <gtk/gtk.h>
#include "testpdf.c"

// menu 
void show_message_cb (GtkMenuItem *item, gpointer user_data) 
{
    g_print ("Debug Message\n");
}

void show_uri_cb (GtkMenuItem *item, gpointer user_data) 
{
	const char* uri = "https://github.com/Geert-Jan77/sidecutters/";
	guint32 timestamp = GDK_CURRENT_TIME;
	GError** error;
	gtk_show_uri_on_window (NULL, uri, timestamp, NULL);
}

void export_pdf_cb (GtkMenuItem *item, gpointer user_data) 
{
	char* arg[] = {"Test1","Test2"};
	int iRet = testpdf(arg);
	GtkWidget *dialog ;
    if (iRet == 0) dialog = gtk_message_dialog_new(NULL, 0, GTK_MESSAGE_INFO, GTK_BUTTONS_OK, "The bookmarked printable data file 'testpdf.pdf' was exported." );
    gtk_window_set_title(GTK_WINDOW(dialog), "TestPdf");
    gint result = gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy( GTK_WIDGET(dialog) );
}

// icon
GdkPixbuf *create_pixbuf(const gchar * filename ) 
{
	GdkPixbuf *pixbuf;
	GError *error = NULL;
	pixbuf = gdk_pixbuf_new_from_file(filename, &error );
	if (!pixbuf) 
	{
		fprintf(stderr, "%s\n", error->message );
		g_error_free(error );
	}
	return pixbuf;
}

// buttons
struct Icons
{
	GtkWidget *line;
	GtkWidget *polyline;
	GtkWidget *polygon;
	GtkWidget *exportpdf;
	GtkWidget *exportdxf;
};
static gboolean query_tooltip(GtkWidget* self, gint x, gint y, gboolean keyboard_mode, GtkTooltip* tooltip, gpointer user_data)
{
	return FALSE;
}
static void bLine_clicked(GtkWidget *button, struct Icons *icons )
{
	static gboolean bLine = TRUE;
	bLine = !bLine;
	if (bLine)
		gtk_button_set_image(GTK_BUTTON(button), icons -> line );
	else
		gtk_button_set_image(GTK_BUTTON(button), icons -> polygon );
}
static void bPolyline_clicked(GtkWidget *button)
{
}

int main(int argc, char *argv[] )
{
	// main window
	GtkWidget *window;
	GdkPixbuf *icon;
	gtk_init(&argc, &argv );
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL );
	gtk_window_set_title(GTK_WINDOW(window), "Side Cutters" );
	GdkRectangle workarea = {0 };
	gdk_monitor_get_workarea(gdk_display_get_primary_monitor(gdk_display_get_default()), &workarea );
	gtk_window_set_default_size (GTK_WINDOW (window), workarea.width, workarea.height );
	
	// icon
	icon = create_pixbuf("rsc/icon.png" ); 
	gtk_window_set_icon(GTK_WINDOW(window), icon );
	
	// menu
	GtkWidget *center_vbox;
    GtkWidget *menuBar;
    GtkWidget *menuItem1, *menuItem2;
    GtkWidget *submenu1, *submenu2;
    GtkWidget *item_message;
	GtkWidget *item_export_pdf;
    GtkWidget *item_quit;
	GtkWidget *item_opensource;
    center_vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    menuBar =gtk_menu_bar_new ();
    menuItem1 = gtk_menu_item_new_with_mnemonic ("_Application");
	submenu1 = gtk_menu_new ();
    item_message = gtk_menu_item_new_with_label ("Debug Message");
	item_export_pdf = gtk_menu_item_new_with_label ("Export Pdf");
    item_quit = gtk_menu_item_new_with_label ("Quit");
    gtk_menu_shell_append (GTK_MENU_SHELL (submenu1), item_message);
	gtk_menu_shell_append (GTK_MENU_SHELL (submenu1), item_export_pdf);
    gtk_menu_shell_append (GTK_MENU_SHELL (submenu1), item_quit);	
	gtk_menu_item_set_submenu (GTK_MENU_ITEM (menuItem1), submenu1);
	gtk_menu_shell_append (GTK_MENU_SHELL (menuBar), menuItem1);
    menuItem2 = gtk_menu_item_new_with_mnemonic ("_Help");
	submenu2 = gtk_menu_new ();	
	item_opensource = gtk_menu_item_new_with_label ("View sourcecode on web");
    gtk_menu_shell_append (GTK_MENU_SHELL (submenu2), item_opensource);
	gtk_menu_item_set_submenu (GTK_MENU_ITEM (menuItem2), submenu2);
	gtk_menu_shell_append (GTK_MENU_SHELL (menuBar), menuItem2);
    gtk_box_pack_start (GTK_BOX (center_vbox), menuBar, FALSE, FALSE, 0);
    gtk_container_add (GTK_CONTAINER (window), center_vbox);
    g_signal_connect (item_message, "activate", G_CALLBACK (show_message_cb), NULL);
	g_signal_connect (item_export_pdf, "activate", G_CALLBACK (export_pdf_cb), NULL);
	g_signal_connect_swapped (item_quit, "activate", G_CALLBACK (gtk_widget_destroy), window);
	g_signal_connect (item_opensource, "activate", G_CALLBACK (show_uri_cb), NULL);
	
	// buttons
	struct Icons icons;
	icons.line = gtk_image_new_from_file("rsc/line.xpm" );
	icons.polyline = gtk_image_new_from_file("rsc/polyline.xpm" );
	icons.polygon = gtk_image_new_from_file("rsc/polygon.xpm" );
	icons.exportpdf = gtk_image_new_from_file("rsc/exportpdf.xpm" );
	icons.exportdxf = gtk_image_new_from_file("rsc/exportdxf.xpm" );
	g_object_ref_sink(icons.line );
	g_object_ref_sink(icons.polyline );
	g_object_ref_sink(icons.polygon );
	g_object_ref_sink(icons.exportpdf );
	g_object_ref_sink(icons.exportdxf );
	GtkWidget *iLine = icons.line;
	GtkWidget *iPolyline = icons.polyline;
	GtkWidget *iPolygon = icons.polygon;
	GtkWidget *iExportpdf = icons.exportpdf;
	GtkWidget *iExportdxf = icons.exportdxf;
	GtkWidget *bLine = gtk_button_new();
	GtkWidget *bPolyline = gtk_button_new();
	GtkWidget *bPolygon = gtk_button_new();
	GtkWidget *bExportpdf = gtk_button_new();
	GtkWidget *bExportdxf = gtk_button_new();
	gtk_button_set_image (GTK_BUTTON(bLine), iLine );
	gtk_button_set_image (GTK_BUTTON(bPolyline), iPolyline );
	gtk_button_set_image (GTK_BUTTON(bPolygon), iPolygon );
	gtk_button_set_image (GTK_BUTTON(bExportpdf), iExportpdf );
	gtk_button_set_image (GTK_BUTTON(bExportdxf), iExportdxf );
	GtkWidget *vbox;
    vbox = gtk_box_new (FALSE, 0);
	gtk_container_add(GTK_CONTAINER(center_vbox), vbox );
	GtkWidget *hbox;
    hbox = gtk_box_new (TRUE, 0);
	gtk_container_add(GTK_CONTAINER(vbox), hbox );
	
	gtk_box_pack_start (GTK_BOX(hbox), bLine, FALSE, FALSE, 0);
	gchar *lLine = "<span font='10' background='#00000002' foreground='#AFAFFFFF'>Line</span>";
	gtk_widget_set_tooltip_markup(bLine, lLine);
	gtk_widget_show(bLine );
	g_signal_connect(bLine, "clicked", G_CALLBACK(bLine_clicked ), &icons );
	
	gtk_box_pack_start (GTK_BOX(hbox), bPolyline, FALSE, FALSE, 0);
	gchar *lPolyline = "<span font='10' background='#00000002' foreground='#AFAFFFFF'>Polyline</span>";
	gtk_widget_set_tooltip_markup(bPolyline, lPolyline);
	gtk_widget_show(bPolyline );
	g_signal_connect(bPolyline, "clicked", G_CALLBACK(bPolyline_clicked ), NULL );
	
	gtk_box_pack_start (GTK_BOX(hbox), bExportpdf, FALSE, FALSE, 0);
	gchar *lExportpdf = "<span font='10' background='#00000002' foreground='#AFAFFFFF'>Export Pdf</span>";
	gtk_widget_set_tooltip_markup(bExportpdf, lExportpdf);
	gtk_widget_show(bExportpdf );
	
	gtk_box_pack_start (GTK_BOX(hbox), bExportdxf, FALSE, FALSE, 0);
	gchar *lExportdxf = "<span font='10' background='#00000002' foreground='#AFAFFFFF'>Export Dxf</span>";
	gtk_widget_set_tooltip_markup(bExportdxf, lExportdxf);
	gtk_widget_show(bExportdxf );
	g_signal_connect(bExportdxf, "query-tooltip", G_CALLBACK(query_tooltip ), NULL);
	
	g_signal_connect(window, "delete-event", G_CALLBACK(gtk_main_quit ), NULL );
	gtk_widget_show(window );
	gtk_widget_show_all(window );
	g_signal_connect(G_OBJECT(window ), "destroy", G_CALLBACK(gtk_main_quit ), NULL );
	g_object_unref(icon ); 	
	gtk_main();
  
}


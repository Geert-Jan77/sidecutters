#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "testpdf.c"
#define MAX_LEN 256

static char *sFromConf(char *KeytoFind )
{
    char *ValueFound;
    char c;
    FILE *fp2;
    //char *line = NULL;
    size_t len = 0;
	char buffer[MAX_LEN];
    ssize_t read;
    fp2 = fopen("config", "r");
    if (fp2 == NULL)
    {
        g_print("Error file not found.\n");
		return "Error file not found.\n";
    }
	//while ((read = getline(&line, &len, fp2)) != -1)
    while (fgets(buffer, MAX_LEN, fp2))
    {
		read = strcspn(buffer, "\n");
        buffer[read + 1] = 0;
		g_print("read = %d\n", read);
		char *line = buffer;
        g_print("line %s\n", line);
		char *word = " = ";
        char *pch = strstr(line, word);
        if(pch)
        {
			g_print("strstr success \n");
            size_t leng = pch - line;
            char *key = malloc(leng + 1);
            if (key)
            {
                for(int i = 0; i < pch - line; i++)
                {
                    key[i] = *(line + i);
                }
                key[leng] = '\0';
                size_t leng2 = read + (size_t)(line - pch) - 3;
                char *value = malloc(leng2 + 1);
                if(value)
                {
                    int iStart = pch - line + 3;
                    for(int i = iStart; i < iStart + leng2; i++)
                    {
                        value[i - iStart] = *(line + i);
                    }
                    value[leng2] = '\0';
                    if (strcmp(KeytoFind,key)==0)
                    {
                        ValueFound = value;
                    }
                }
            }
        }
    }
    fclose(fp2);
    return ValueFound;
}

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
    char* sRes = sFromConf("Resource");
    char* sPicturefile = malloc(strlen(sRes) + strlen("side cutters.jpg") + 1);
    strcpy(sPicturefile, sRes);
    strcat(sPicturefile, "side cutters.jpg");
    char* sPdfFile = sFromConf("Filetest");
	char* arg[] = {sPdfFile, sPicturefile };
	int iRet = testpdf(arg);
	GtkWidget *dialog ;
    if (iRet == 0) dialog = gtk_message_dialog_new(NULL, 0, GTK_MESSAGE_INFO, GTK_BUTTONS_OK, "The bookmarked portable data file was exported." );
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
    char c;
    FILE *fp2;
	char buffer[MAX_LEN];
    size_t len = 0;
    ssize_t read;
    fp2 = fopen("config", "r");
    if (fp2 == NULL)
    {
        g_print("Error file not found.\n");
    }
    g_print("Key, Value\n");
    //while ((read = getline(&line, &len, fp2)) != -1)
	while (fgets(buffer, MAX_LEN, fp2))
    {
		read = strcspn(buffer, "\n");
        buffer[read+1] = 0;
		g_print("read = %d\n", read);
		char *line = buffer;
        g_print("line %s\n", line);
		char *word = " = ";
        char *pch = strstr(line, word);
        if(pch)
        {
            size_t leng = pch - line;
            char *key = malloc(leng + 1);
            if (key)
            {
                for(int i = 0; i < pch - line; i++)
                {
                    key[i] = *(line + i);
                }
                key[leng] = '\0';
                g_print("%s, ", key);
                size_t leng2 = read + (size_t)(line - pch) - 3;
                char *value = malloc(leng2 + 1);
                if(value)
                {
                    int iStart = pch - line + 3;
                    for(int i = iStart; i < iStart + leng2; i++)
                    {
                        value[i - iStart] = *(line + i);
                    }
                    value[leng2] = '\0';
                    g_print("%s", value);
                    g_print("\n");
                }
            }
        }
    }
}

static void bExportpdf_clicked(GtkWidget *button)
{
    /*
    float val;
    FILE *fp1;
    fp1 = fopen("config", "w");
    char buffer[12];
    int j = snprintf(buffer, 12, "%f", 3.141592653589f);
    g_print("%s\n", buffer);
    for (int i = 0; i < j; i++) { if (buffer[i] == ',') buffer[i]='.'; }
    g_print("%s\n", buffer);
    fprintf(fp1, "Pi = %s\n", buffer); // Read with scanf
    fprintf(fp1, "Resource = rsc/\n");
    fprintf(fp1, "Filetest = testpdf.pdf\n");
    fprintf(fp1, "Working = workingdirectory\n");
    fprintf(fp1, "Documents = documentfolder\n");
    fprintf(fp1, "Apps = appfolder\n");
    fprintf(fp1, "Pictures = picturefolder\n");
    fprintf(fp1, "Desktop = desktopfolder\n");
    fprintf(fp1, "Downloads = downloadfolder\n");
    fprintf(fp1, "Thrash = thrashfolder\n");
    fclose(fp1);
     */
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
    char *sRes = sFromConf("Resource");
	g_print("sFromConf =%s \n" ,sRes);
    char *sIconfile = malloc(strlen(sRes) + strlen("icon.png") + 1);
    strcpy(sIconfile, sRes);
    strcat(sIconfile, "icon.png");
	g_print("%s \n" ,sIconfile);
	icon = create_pixbuf(sIconfile );
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
    char *sLinefile = malloc(strlen(sRes) + strlen("line.xpm") + 1);
    char *sPolylinefile = malloc(strlen(sRes) + strlen("polyline.xpm") + 1);
    char *sPolygonfile = malloc(strlen(sRes) + strlen("polygon.xpm") + 1);
    char *sExportpdffile = malloc(strlen(sRes) + strlen("exportpdf.xpm") + 1);
    char *sExportdxffile = malloc(strlen(sRes) + strlen("exportdxf.xpm") + 1);
    strcpy(sLinefile, sRes);
    strcat(sLinefile, "line.xpm");
    strcpy(sPolylinefile, sRes);
    strcat(sPolylinefile, "polyline.xpm");
    strcpy(sPolygonfile, sRes);
    strcat(sPolygonfile, "polygon.xpm");
    strcpy(sExportpdffile, sRes);
    strcat(sExportpdffile, "exportpdf.xpm");
    strcpy(sExportdxffile, sRes);
    strcat(sExportdxffile, "exportdxf.xpm");
	icons.line = gtk_image_new_from_file(sLinefile );
	icons.polyline = gtk_image_new_from_file(sPolylinefile );
	icons.polygon = gtk_image_new_from_file(sPolygonfile );
	icons.exportpdf = gtk_image_new_from_file(sExportpdffile );
	icons.exportdxf = gtk_image_new_from_file(sExportdxffile );
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
	g_signal_connect(bExportpdf, "clicked", G_CALLBACK(bExportpdf_clicked ), NULL );
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


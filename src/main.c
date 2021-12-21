
/*
 This is the Entry point for MacOS.

 Compile

    gcc main.c -o main `pkg-config --cflags --libs gtk+-3.0`

 Run
 
    ./main
*/


#include <gtk/gtk.h>

static void
print_hello (GtkWidget *widget,
             gpointer   data)
{
  g_print ("Hello World\n");
}

static void
activate (GtkApplication *app,
          gpointer        user_data)
{
  GtkWidget *window;
  GtkWidget *button;
  GtkWidget *button_box;

  window = gtk_application_window_new (app);
  gtk_window_set_title (GTK_WINDOW (window), "Window");
  gtk_window_set_default_size (GTK_WINDOW (window), 200, 200);

  button_box = gtk_button_box_new (GTK_ORIENTATION_HORIZONTAL);
  gtk_container_add (GTK_CONTAINER (window), button_box);

  button = gtk_button_new_with_label ("Hello World");
  g_signal_connect (button, "clicked", G_CALLBACK (print_hello), NULL);
  // g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_widget_destroy), window);
  gtk_container_add (GTK_CONTAINER (button_box), button);

  gtk_widget_show_all (window);
}

int
main (int    argc,
      char **argv)
{
  GtkApplication *app;
  int status;

  app = gtk_application_new ("org.gtk.example", G_APPLICATION_FLAGS_NONE);
  g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
  status = g_application_run (G_APPLICATION (app), argc, argv);
  g_object_unref (app);

  return status;
}

#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cairo.h>
#include <cairo-pdf.h>
#include "testpdf.c"
#include "testcairo.c"
#define MAX_LEN 256

gint iWindowx, iWindowy;
gint iCairox, iCairoy;
gboolean bCairoinitialized=FALSE;
gboolean bCairoshown=FALSE;

gboolean callback_minimize(GtkWidget *widget, GdkEventWindowState *event, gpointer user_data)
{
    if(event->new_window_state & GDK_WINDOW_STATE_ICONIFIED)
	{
		if (bCairoinitialized && bCairoshown) {hidecairo(); bCairoshown = FALSE;}
	}
	if(event->new_window_state & GDK_WINDOW_STATE_FOCUSED)
	{	
		if (bCairoinitialized && !bCairoshown) {showcairo(); bCairoshown = TRUE; }
	}	
return TRUE;
}

void getsize(GtkWidget *widget, GtkAllocation *allocation, char *data ) 
{
	gint wix, wiy;
	gdk_window_get_origin (gtk_widget_get_window (widget), &wix, &wiy);
	g_print("%s x %d y %d width %d height %d \n", data, allocation->x + wix, allocation->y + wiy, allocation->width, allocation->height);
	iCairox = allocation->x + wix + allocation->width;
	iCairoy = allocation->y + wiy;
	if (!bCairoinitialized) testcairo(iCairox,iCairoy);
	bCairoinitialized = TRUE;
	bCairoshown = TRUE;
}

static char *sFromConf(char *KeytoFind )
{
	// read config file key-value strings
    char *ValueFound;
    char c;
    FILE *fp2;
    size_t len = 0;
	char buffer[MAX_LEN];
    ssize_t read;
    fp2 = fopen("config", "r");
    if (fp2 == NULL)
    {
        g_print("Error file not found.\n");
		return "Error file not found.\n";
    }
    while (fgets(buffer, MAX_LEN, fp2))
    {
		read = strcspn(buffer, "\n");
        buffer[read + 1] = 0;
		char *line = buffer;
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
	/* This dialogue is displayed under the cairo drawing
	GtkWidget *dialog ;
    if (iRet == 0) dialog = gtk_message_dialog_new(NULL, 0, GTK_MESSAGE_INFO, GTK_BUTTONS_OK, "The bookmarked portable data file was exported." );
    gtk_window_set_title(GTK_WINDOW(dialog), "TestPdf");
    gint result = gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy( GTK_WIDGET(dialog) );
	*/
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
	GtkWidget *line0;
	GtkWidget *polyline;
	GtkWidget *polyline0;
	GtkWidget *polygon;
	GtkWidget *polygon0;
	GtkWidget *rectangle;
	GtkWidget *rectangle0;
	GtkWidget *square;
	GtkWidget *square0;
	GtkWidget *circle;
	GtkWidget *circle0;
	GtkWidget *circlethree;
	GtkWidget *circlethree0;
	GtkWidget *arc;
	GtkWidget *arc0;
	GtkWidget *arcthree;
	GtkWidget *arcthree0;
	GtkWidget *ellipse;
	GtkWidget *ellipse0;
	GtkWidget *cubic;
	GtkWidget *cubic0;
	GtkWidget *quadratic;
	GtkWidget *quadratic0;
	GtkWidget *text;
	GtkWidget *text0;
	GtkWidget *image;
	GtkWidget *image0;
	GtkWidget *linear;
	GtkWidget *linear0;
	GtkWidget *aligned;
	GtkWidget *aligned0;
	GtkWidget *angular;
	GtkWidget *angular0;
	GtkWidget *radius;
	GtkWidget *radius0;
	GtkWidget *round;
	GtkWidget *round0;
	GtkWidget *chamfer;
	GtkWidget *chamfer0;
	GtkWidget *br3ak;
	GtkWidget *br3ak0;
	GtkWidget *shorten;
	GtkWidget *shorten0;
	GtkWidget *exportpdf;
	GtkWidget *exportpdf0;
	GtkWidget *importdxf;
	GtkWidget *importdxf0;
};
static gboolean query_tooltip(GtkWidget* self, gint x, gint y, gboolean keyboard_mode, GtkTooltip* tooltip, gpointer user_data)
{
	return FALSE;
}

static void bImage_clicked(GtkWidget *button, struct Icons *icons )
{
	static gboolean bImage = FALSE;
	bImage = !bImage;
	if (bImage)
		gtk_button_set_image(GTK_BUTTON(button), icons -> image );
	else
		gtk_button_set_image(GTK_BUTTON(button), icons -> image0 );
	animate();
}

static void bLine_clicked(GtkWidget *button, struct Icons *icons )
{
	static gboolean bLine = FALSE;
	bLine = !bLine;
	if (bLine)
		gtk_button_set_image(GTK_BUTTON(button), icons -> line );
	else
		gtk_button_set_image(GTK_BUTTON(button), icons -> line0 );
}

static void bPolyline_clicked(GtkWidget *button, struct Icons *icons)
{
	// Read Config file to debug window
	static gboolean bPolyline = FALSE;
	bPolyline = !bPolyline;
	if (bPolyline)
		gtk_button_set_image(GTK_BUTTON(button), icons -> polyline );
	else
		gtk_button_set_image(GTK_BUTTON(button), icons -> polyline0 );
	
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
		//g_print("read = %d\n", read);
		char *line = buffer;
        //g_print("line %s\n", line);
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

static void bExportpdf_clicked(GtkWidget *button, struct Icons *icons)
{
	static gboolean bExportpdf = FALSE;
	bExportpdf = !bExportpdf;
	if (bExportpdf)
		gtk_button_set_image(GTK_BUTTON(button), icons -> exportpdf );
	else
		gtk_button_set_image(GTK_BUTTON(button), icons -> exportpdf0 );

	char* sRes = sFromConf("Resource");
    char* sPicturefile = malloc(strlen(sRes) + strlen("side cutters.jpg") + 1);
    strcpy(sPicturefile, sRes);
    strcat(sPicturefile, "side cutters.jpg");
    char* sPdfFile = sFromConf("Filetest");
	char* arg[] = {sPdfFile, sPicturefile };
	//int iRet = testpdf(arg);
	int iRet = 0;
	cairo_surface_t *surface;
	cairo_t *cr;
	surface = cairo_pdf_surface_create(sPdfFile, 504, 648);
	cr = cairo_create(surface);
	
	cairo_set_source_rgb(cr, 0, 0, 0);
	cairo_select_font_face (cr, "Calibri", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
	cairo_set_font_size (cr, 14.17f);
	cairo_move_to(cr, 10.0, 50.0);
	cairo_show_text(cr, "5 mm Calibri lettertype.");  
	cairo_set_font_size (cr, 28.34f);
	cairo_move_to(cr, 10.0, 50.0f + 14.17f + 28.34f);
	cairo_show_text(cr, "10 mm Calibri lettertype.");  
	
	cairo_show_page(cr);
	cairo_surface_destroy(surface);
	cairo_destroy(cr);
	/* This dialog is painted below our cairo surface !!
	GtkWidget *dialog ;
    if (iRet == 0) dialog = gtk_message_dialog_new(NULL, 0, GTK_MESSAGE_INFO, GTK_BUTTONS_OK, "The cairo portable data file was exported." );
    gtk_window_set_title(GTK_WINDOW(dialog), "TestPdf");
    gint result = gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy( GTK_WIDGET(dialog) );
	*/
	
    /*
	  save config file
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

static void bImportdxf_clicked(GtkWidget *button, struct Icons *icons)
{
	static gboolean bImportdxf = FALSE;
	bImportdxf = !bImportdxf;
	if (bImportdxf)
		gtk_button_set_image(GTK_BUTTON(button), icons -> importdxf );
	else
		gtk_button_set_image(GTK_BUTTON(button), icons -> importdxf0 );
    
}

static void bText_clicked(GtkWidget *button, struct Icons *icons)
{
	static gboolean bText = FALSE;
	bText = !bText;
	if (bText)
		gtk_button_set_image(GTK_BUTTON(button), icons -> text );
	else
		gtk_button_set_image(GTK_BUTTON(button), icons -> text0 );
}

int main(int argc, char *argv[] )
{
	// main window
	GtkWidget *window;
	GdkPixbuf *icon;
	gtk_init(&argc, &argv );
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL );
	GdkRectangle workarea = {0 };
	gdk_monitor_get_workarea(gdk_display_get_primary_monitor(gdk_display_get_default()), &workarea );	
	g_print ("gdk_monitor_get_workarea(gdk_display_get_primary_monitor(gdk_display_get_default()), &workarea ); \nworkarea.width %d, workarea.height %d\n", workarea.width, workarea.height);
    GdkGeometry hints;
	/* MS windows taskbar should be done in windows api.
    hints.min_width = workarea.width - 15;
    hints.max_width = workarea.width - 15;
    hints.min_height = workarea.height - 36; // taskbar
    hints.max_height = workarea.height - 36;
    gtk_window_set_geometry_hints( GTK_WINDOW(window), window, &hints, (GdkWindowHints)(GDK_HINT_MIN_SIZE | GDK_HINT_MAX_SIZE));
	gtk_window_set_default_size (GTK_WINDOW (window), workarea.width - 15, workarea.height - 36);
	iWindowx = 5;
	iWindowy = 5;
	*/
	hints.min_width = workarea.width;
    hints.max_width = workarea.width;
    hints.min_height = workarea.height;
    hints.max_height = workarea.height;
    gtk_window_set_geometry_hints( GTK_WINDOW(window), window, &hints, (GdkWindowHints)(GDK_HINT_MIN_SIZE | GDK_HINT_MAX_SIZE));
	gtk_window_set_default_size (GTK_WINDOW (window), workarea.width, workarea.height);
	iWindowx = 0;
	iWindowy = 0;
	gtk_window_move (GTK_WINDOW(window), iWindowx, iWindowy);
	gtk_window_set_title(GTK_WINDOW(window), "Side Cutters" );

	// icon
    char *sRes = sFromConf("Resource");
	//g_print("sFromConf =%s \n" ,sRes);
    char *sIconfile = malloc(strlen(sRes) + strlen("icon.png") + 1);
    strcpy(sIconfile, sRes);
    strcat(sIconfile, "icon.png");
	//g_print("%s \n" ,sIconfile);
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
	char *sLinefile0 = malloc(strlen(sRes) + strlen("line0.xpm") + 1);
    char *sPolylinefile = malloc(strlen(sRes) + strlen("polyline.xpm") + 1);
	char *sPolylinefile0 = malloc(strlen(sRes) + strlen("polyline0.xpm") + 1);
    char *sPolygonfile = malloc(strlen(sRes) + strlen("polygon.xpm") + 1);
	char *sPolygonfile0 = malloc(strlen(sRes) + strlen("polygon0.xpm") + 1);
	char *sRectanglefile = malloc(strlen(sRes) + strlen("rectangle.xpm") + 1);
    char *sRectanglefile0 = malloc(strlen(sRes) + strlen("rectangle0.xpm") + 1);
	char *sSquarefile = malloc(strlen(sRes) + strlen("square.xpm") + 1);
	char *sSquarefile0 = malloc(strlen(sRes) + strlen("square0.xpm") + 1);
	char *sCirclefile = malloc(strlen(sRes) + strlen("circle.xpm") + 1);
	char *sCirclefile0 = malloc(strlen(sRes) + strlen("circle0.xpm") + 1);
	char *sCirclethreefile = malloc(strlen(sRes) + strlen("circlethree.xpm") + 1);
	char *sCirclethreefile0 = malloc(strlen(sRes) + strlen("circlethree0.xpm") + 1);
	char *sArcfile = malloc(strlen(sRes) + strlen("arc.xpm") + 1);
	char *sArcfile0 = malloc(strlen(sRes) + strlen("arc0.xpm") + 1);
	char *sArcthreefile = malloc(strlen(sRes) + strlen("arcthree.xpm") + 1);
	char *sArcthreefile0 = malloc(strlen(sRes) + strlen("arcthree0.xpm") + 1);
	char *sEllipsefile = malloc(strlen(sRes) + strlen("ellepse.xpm") + 1);
	char *sEllipsefile0 = malloc(strlen(sRes) + strlen("ellepse0.xpm") + 1);
	char *sCubicfile = malloc(strlen(sRes) + strlen("cubic.xpm") + 1);
	char *sCubicfile0 = malloc(strlen(sRes) + strlen("cubic0.xpm") + 1);
	char *sQuadraticfile = malloc(strlen(sRes) + strlen("quadratic.xpm") + 1);
	char *sQuadraticfile0 = malloc(strlen(sRes) + strlen("quadratic0.xpm") + 1);
	char *sTextfile = malloc(strlen(sRes) + strlen("text.xpm") + 1);
	char *sTextfile0 = malloc(strlen(sRes) + strlen("text0.xpm") + 1);
	char *sImagefile = malloc(strlen(sRes) + strlen("image.xpm") + 1);
	char *sImagefile0 = malloc(strlen(sRes) + strlen("image0.xpm") + 1);
	char *sLinearfile = malloc(strlen(sRes) + strlen("linear.xpm") + 1);
	char *sLinearfile0 = malloc(strlen(sRes) + strlen("linear0.xpm") + 1);
	char *sAlignedfile = malloc(strlen(sRes) + strlen("aligned.xpm") + 1);
	char *sAlignedfile0 = malloc(strlen(sRes) + strlen("aligned0.xpm") + 1);
	char *sAngularfile = malloc(strlen(sRes) + strlen("angular.xpm") + 1);
	char *sAngularfile0 = malloc(strlen(sRes) + strlen("angular0.xpm") + 1);
	char *sRadiusfile = malloc(strlen(sRes) + strlen("radius.xpm") + 1);
	char *sRadiusfile0 = malloc(strlen(sRes) + strlen("radius0.xpm") + 1);
	char *sRoundfile = malloc(strlen(sRes) + strlen("round.xpm") + 1);
	char *sRoundfile0 = malloc(strlen(sRes) + strlen("round0.xpm") + 1);
	char *sChamferfile = malloc(strlen(sRes) + strlen("chamfer.xpm") + 1);
	char *sChamferfile0 = malloc(strlen(sRes) + strlen("chamfer0.xpm") + 1);
	char *sBreakfile = malloc(strlen(sRes) + strlen("break.xpm") + 1);
	char *sBreakfile0 = malloc(strlen(sRes) + strlen("break0.xpm") + 1);
	char *sShortenfile = malloc(strlen(sRes) + strlen("shorten.xpm") + 1);
	char *sShortenfile0 = malloc(strlen(sRes) + strlen("shorten0.xpm") + 1);
	char *sExportpdffile = malloc(strlen(sRes) + strlen("exportpdf.xpm") + 1);
	char *sExportpdffile0 = malloc(strlen(sRes) + strlen("exportpdf0.xpm") + 1);
    char *sImportdxffile = malloc(strlen(sRes) + strlen("importdxf.xpm") + 1);
	char *sImportdxffile0 = malloc(strlen(sRes) + strlen("importdxf0.xpm") + 1);
    strcpy(sLinefile, sRes);
    strcat(sLinefile, "line.xpm");
	strcpy(sLinefile0, sRes);
    strcat(sLinefile0, "line0.xpm");
    strcpy(sPolylinefile, sRes);
    strcat(sPolylinefile, "polyline.xpm");
	strcpy(sPolylinefile0, sRes);
    strcat(sPolylinefile0, "polyline0.xpm");
    strcpy(sPolygonfile, sRes);
    strcat(sPolygonfile, "polygon.xpm");
	strcpy(sPolygonfile0, sRes);
    strcat(sPolygonfile0, "polygon0.xpm");
    strcpy(sRectanglefile, sRes);
    strcat(sRectanglefile, "rectangle.xpm");
	strcpy(sRectanglefile0, sRes);
    strcat(sRectanglefile0, "rectangle0.xpm");
	strcpy(sSquarefile, sRes);
    strcat(sSquarefile, "square.xpm");
	strcpy(sSquarefile0, sRes);
    strcat(sSquarefile0, "square0.xpm");
	strcpy(sCirclefile, sRes);
    strcat(sCirclefile, "circle.xpm");
	strcpy(sCirclefile0, sRes);
    strcat(sCirclefile0, "circle0.xpm");
	strcpy(sCirclethreefile, sRes);
    strcat(sCirclethreefile, "circlethree.xpm");
	strcpy(sCirclethreefile0, sRes);
    strcat(sCirclethreefile0, "circlethree0.xpm");
	strcpy(sArcfile, sRes);
    strcat(sArcfile, "arc.xpm");
	strcpy(sArcfile0, sRes);
    strcat(sArcfile0, "arc0.xpm");
	strcpy(sArcthreefile, sRes);
    strcat(sArcthreefile, "arcthree.xpm");
	strcpy(sArcthreefile0, sRes);
    strcat(sArcthreefile0, "arcthree0.xpm");
	strcpy(sEllipsefile, sRes);
    strcat(sEllipsefile, "ellipse.xpm");
	strcpy(sEllipsefile0, sRes);
    strcat(sEllipsefile0, "ellipse0.xpm");
	strcpy(sCubicfile, sRes);
    strcat(sCubicfile, "cubic.xpm");
	strcpy(sCubicfile0, sRes);
    strcat(sCubicfile0, "cubic0.xpm");
	strcpy(sQuadraticfile, sRes);
    strcat(sQuadraticfile, "quadratic.xpm");
	strcpy(sQuadraticfile0, sRes);
    strcat(sQuadraticfile0, "quadratic0.xpm");
	strcpy(sTextfile, sRes);
    strcat(sTextfile, "text.xpm");
	strcpy(sTextfile0, sRes);
    strcat(sTextfile0, "text0.xpm");
	strcpy(sImagefile, sRes);
    strcat(sImagefile, "image.xpm");
	strcpy(sImagefile0, sRes);
    strcat(sImagefile0, "image0.xpm");
	strcpy(sLinearfile, sRes);
    strcat(sLinearfile, "linear.xpm");
	strcpy(sLinearfile0, sRes);
    strcat(sLinearfile0, "linear0.xpm");
	strcpy(sAlignedfile, sRes);
    strcat(sAlignedfile, "aligned.xpm");
	strcpy(sAlignedfile0, sRes);
    strcat(sAlignedfile0, "aligned0.xpm");
	strcpy(sAngularfile, sRes);
    strcat(sAngularfile, "angular.xpm");
	strcpy(sAngularfile0, sRes);
    strcat(sAngularfile0, "angular0.xpm");
	strcpy(sRadiusfile, sRes);
    strcat(sRadiusfile, "radius.xpm");
	strcpy(sRadiusfile0, sRes);
    strcat(sRadiusfile0, "radius0.xpm");
	strcpy(sRoundfile, sRes);
    strcat(sRoundfile, "round.xpm");
	strcpy(sRoundfile0, sRes);
    strcat(sRoundfile0, "round0.xpm");
	strcpy(sChamferfile, sRes);
    strcat(sChamferfile, "chamfer.xpm");
	strcpy(sChamferfile0, sRes);
    strcat(sChamferfile0, "chamfer0.xpm");
	strcpy(sBreakfile, sRes);
    strcat(sBreakfile, "break.xpm");
	strcpy(sBreakfile0, sRes);
    strcat(sBreakfile0, "break0.xpm");
	strcpy(sShortenfile, sRes);
    strcat(sShortenfile, "shorten.xpm");
	strcpy(sShortenfile0, sRes);
    strcat(sShortenfile0, "shorten0.xpm");
	strcpy(sExportpdffile, sRes);
    strcat(sExportpdffile, "exportpdf.xpm");
	strcpy(sExportpdffile0, sRes);
    strcat(sExportpdffile0, "exportpdf0.xpm");
    strcpy(sImportdxffile, sRes);
    strcat(sImportdxffile, "importdxf.xpm");
	strcpy(sImportdxffile0, sRes);
    strcat(sImportdxffile0, "importdxf0.xpm");
	icons.line = gtk_image_new_from_file(sLinefile );
	icons.line0 = gtk_image_new_from_file(sLinefile0 );
	icons.polyline = gtk_image_new_from_file(sPolylinefile );
	icons.polyline0 = gtk_image_new_from_file(sPolylinefile0 );
	icons.polygon = gtk_image_new_from_file(sPolygonfile );
	icons.polygon0 = gtk_image_new_from_file(sPolygonfile0 );
	icons.rectangle = gtk_image_new_from_file(sRectanglefile );
	icons.rectangle0 = gtk_image_new_from_file(sRectanglefile0 );
	icons.square = gtk_image_new_from_file(sSquarefile );
	icons.square0 = gtk_image_new_from_file(sSquarefile0 );
	icons.circle = gtk_image_new_from_file(sCirclefile );
	icons.circle0 = gtk_image_new_from_file(sCirclefile0 );
	icons.circlethree = gtk_image_new_from_file(sCirclethreefile );
	icons.circlethree0 = gtk_image_new_from_file(sCirclethreefile0 );
	icons.arc = gtk_image_new_from_file(sArcfile );
	icons.arc0 = gtk_image_new_from_file(sArcfile0 );
	icons.arcthree = gtk_image_new_from_file(sArcthreefile );
	icons.arcthree0 = gtk_image_new_from_file(sArcthreefile0 );
	icons.ellipse = gtk_image_new_from_file(sEllipsefile );
	icons.ellipse0 = gtk_image_new_from_file(sEllipsefile0 );
	icons.cubic = gtk_image_new_from_file(sCubicfile );
	icons.cubic0 = gtk_image_new_from_file(sCubicfile0 );
	icons.quadratic = gtk_image_new_from_file(sQuadraticfile );
	icons.quadratic0 = gtk_image_new_from_file(sQuadraticfile0 );
	icons.text = gtk_image_new_from_file(sTextfile );
	icons.text0 = gtk_image_new_from_file(sTextfile0 );
	icons.image = gtk_image_new_from_file(sImagefile );
	icons.image0 = gtk_image_new_from_file(sImagefile0 );
	icons.linear = gtk_image_new_from_file(sLinearfile );
	icons.linear0 = gtk_image_new_from_file(sLinearfile0 );
	icons.aligned = gtk_image_new_from_file(sAlignedfile );
	icons.aligned0 = gtk_image_new_from_file(sAlignedfile0 );
	icons.angular = gtk_image_new_from_file(sAngularfile );
	icons.angular0 = gtk_image_new_from_file(sAngularfile0 );
	icons.radius = gtk_image_new_from_file(sRadiusfile );
	icons.radius0 = gtk_image_new_from_file(sRadiusfile0 );
	icons.round = gtk_image_new_from_file(sRoundfile );
	icons.round0 = gtk_image_new_from_file(sRoundfile0 );
	icons.chamfer = gtk_image_new_from_file(sChamferfile );
	icons.chamfer0 = gtk_image_new_from_file(sChamferfile0 );
	icons.br3ak = gtk_image_new_from_file(sBreakfile );
	icons.br3ak0 = gtk_image_new_from_file(sBreakfile0 );
	icons.shorten = gtk_image_new_from_file(sShortenfile );
	icons.shorten0 = gtk_image_new_from_file(sShortenfile0 );
	icons.exportpdf = gtk_image_new_from_file(sExportpdffile );
	icons.exportpdf0 = gtk_image_new_from_file(sExportpdffile0 );
	icons.importdxf = gtk_image_new_from_file(sImportdxffile );
	icons.importdxf0 = gtk_image_new_from_file(sImportdxffile0 );
	g_object_ref_sink(icons.line );
	g_object_ref_sink(icons.line0 );
	g_object_ref_sink(icons.polyline );
	g_object_ref_sink(icons.polyline0 );
	g_object_ref_sink(icons.polygon );
	g_object_ref_sink(icons.polygon0 );
	g_object_ref_sink(icons.rectangle );
	g_object_ref_sink(icons.rectangle0 );
	g_object_ref_sink(icons.square );
	g_object_ref_sink(icons.square0 );
	g_object_ref_sink(icons.circle );
	g_object_ref_sink(icons.circle0 );
	g_object_ref_sink(icons.circlethree );
	g_object_ref_sink(icons.circlethree0 );
	g_object_ref_sink(icons.arc );
	g_object_ref_sink(icons.arc0 );
	g_object_ref_sink(icons.arcthree );
	g_object_ref_sink(icons.arcthree0 );
	g_object_ref_sink(icons.ellipse );
	g_object_ref_sink(icons.ellipse0 );
	g_object_ref_sink(icons.cubic );
	g_object_ref_sink(icons.cubic0 );
	g_object_ref_sink(icons.quadratic );
	g_object_ref_sink(icons.quadratic0 );
	g_object_ref_sink(icons.text );
	g_object_ref_sink(icons.text0 );
	g_object_ref_sink(icons.image );
	g_object_ref_sink(icons.image0 );
	g_object_ref_sink(icons.linear );
	g_object_ref_sink(icons.linear0 );
	g_object_ref_sink(icons.aligned );
	g_object_ref_sink(icons.aligned0 );
	g_object_ref_sink(icons.angular );
	g_object_ref_sink(icons.angular0 );
	g_object_ref_sink(icons.radius );
	g_object_ref_sink(icons.radius0 );
	g_object_ref_sink(icons.round );
	g_object_ref_sink(icons.round0 );
	g_object_ref_sink(icons.chamfer);
	g_object_ref_sink(icons.chamfer0);
	g_object_ref_sink(icons.br3ak );
	g_object_ref_sink(icons.br3ak0 );
	g_object_ref_sink(icons.shorten );
	g_object_ref_sink(icons.shorten0 );
	g_object_ref_sink(icons.exportpdf );
	g_object_ref_sink(icons.exportpdf0 );
	g_object_ref_sink(icons.importdxf );
	g_object_ref_sink(icons.importdxf0 );
	GtkWidget *iLine = icons.line;
	GtkWidget *iLine0 = icons.line0;
	GtkWidget *iPolyline = icons.polyline;
	GtkWidget *iPolyline0 = icons.polyline0;
	GtkWidget *iPolygon = icons.polygon;
	GtkWidget *iPolygon0 = icons.polygon0;
	GtkWidget *iRectangle = icons.rectangle;
	GtkWidget *iRectangle0 = icons.rectangle0;
	GtkWidget *iSquare = icons.square;
	GtkWidget *iSquare0 = icons.square0;
	GtkWidget *iCircle = icons.circle;
	GtkWidget *iCircle0 = icons.circle0;
	GtkWidget *iCirclethree = icons.circlethree;
	GtkWidget *iCirclethree0 = icons.circlethree0;
	GtkWidget *iArc = icons.arc;
	GtkWidget *iArc0 = icons.arc0;
	GtkWidget *iArcthree = icons.arcthree;
	GtkWidget *iArcthree0 = icons.arcthree0;
	GtkWidget *iEllipse = icons.ellipse;
	GtkWidget *iEllipse0 = icons.ellipse0;
	GtkWidget *iCubic = icons.cubic;
	GtkWidget *iCubic0 = icons.cubic0;
	GtkWidget *iQuadratic = icons.quadratic;
	GtkWidget *iQuadratic0 = icons.quadratic0;
	GtkWidget *iText = icons.text;
	GtkWidget *iText0 = icons.text0;
	GtkWidget *iImage = icons.image;
	GtkWidget *iImage0 = icons.image0;
	GtkWidget *iLinear = icons.linear;
	GtkWidget *iLinear0 = icons.linear0;
	GtkWidget *iAligned = icons.aligned;
	GtkWidget *iAligned0 = icons.aligned0;
	GtkWidget *iAngular = icons.angular;
	GtkWidget *iAngular0 = icons.angular0;
	GtkWidget *iRadius = icons.radius;
	GtkWidget *iRadius0 = icons.radius0;
	GtkWidget *iRound = icons.round;
	GtkWidget *iRound0 = icons.round0;
	GtkWidget *iChamfer = icons.chamfer;
	GtkWidget *iChamfer0 = icons.chamfer0;
	GtkWidget *iBreak = icons.br3ak;
	GtkWidget *iBreak0 = icons.br3ak0;
	GtkWidget *iShorten = icons.shorten;
	GtkWidget *iShorten0 = icons.shorten0;
	GtkWidget *iExportpdf = icons.exportpdf;
	GtkWidget *iExportpdf0 = icons.exportpdf0;
	GtkWidget *iImportdxf = icons.importdxf;
	GtkWidget *iImportdxf0 = icons.importdxf0;
	GtkWidget *bLine = gtk_button_new();
	GtkWidget *bPolyline = gtk_button_new();
	GtkWidget *bPolygon = gtk_button_new();
	GtkWidget *bRectangle = gtk_button_new();
	GtkWidget *bSquare = gtk_button_new();
	GtkWidget *bCircle = gtk_button_new();
	GtkWidget *bCirclethree = gtk_button_new();
	GtkWidget *bArc = gtk_button_new();
	GtkWidget *bArcthree = gtk_button_new();
	GtkWidget *bEllipse = gtk_button_new();
	GtkWidget *bCubic = gtk_button_new();
	GtkWidget *bQuadratic = gtk_button_new();
	GtkWidget *bText = gtk_button_new();
	GtkWidget *bImage = gtk_button_new();
	GtkWidget *bLinear = gtk_button_new();
	GtkWidget *bAligned = gtk_button_new();
	GtkWidget *bAngular = gtk_button_new();
	GtkWidget *bRadius = gtk_button_new();
	GtkWidget *bRound = gtk_button_new();
	GtkWidget *bChamfer = gtk_button_new();
	GtkWidget *bBreak = gtk_button_new();
	GtkWidget *bShorten = gtk_button_new();
	GtkWidget *bExportpdf = gtk_button_new();
	GtkWidget *bImportdxf = gtk_button_new();
	gtk_button_set_image (GTK_BUTTON(bLine), iLine0 );
	gtk_button_set_image (GTK_BUTTON(bPolyline), iPolyline0 );
	gtk_button_set_image (GTK_BUTTON(bPolygon), iPolygon0 );
	gtk_button_set_image (GTK_BUTTON(bRectangle), iRectangle0 );
	gtk_button_set_image (GTK_BUTTON(bSquare), iSquare0 );
	gtk_button_set_image (GTK_BUTTON(bCircle), iCircle0 );
	gtk_button_set_image (GTK_BUTTON(bCirclethree), iCirclethree0 );
	gtk_button_set_image (GTK_BUTTON(bArc), iArc0 );
	gtk_button_set_image (GTK_BUTTON(bArcthree), iArcthree0 );
	gtk_button_set_image (GTK_BUTTON(bEllipse), iEllipse0 );
	gtk_button_set_image (GTK_BUTTON(bCubic), iCubic0 );
	gtk_button_set_image (GTK_BUTTON(bQuadratic), iQuadratic0 );
	gtk_button_set_image (GTK_BUTTON(bText), iText0 );
	gtk_button_set_image (GTK_BUTTON(bImage), iImage0 );
	gtk_button_set_image (GTK_BUTTON(bLinear), iLinear0 );
	gtk_button_set_image (GTK_BUTTON(bAligned), iAligned0 );
	gtk_button_set_image (GTK_BUTTON(bAngular), iAngular0 );
	gtk_button_set_image (GTK_BUTTON(bRadius), iRadius0 );
	gtk_button_set_image (GTK_BUTTON(bRound), iRound0 );
	gtk_button_set_image (GTK_BUTTON(bChamfer), iChamfer0 );
	gtk_button_set_image (GTK_BUTTON(bBreak), iBreak0 );
	gtk_button_set_image (GTK_BUTTON(bShorten), iShorten0 );
	gtk_button_set_image (GTK_BUTTON(bExportpdf), iExportpdf0 );
	gtk_button_set_image (GTK_BUTTON(bImportdxf), iImportdxf0 );
	GtkWidget *vbox;
    vbox = gtk_box_new (FALSE, 0);
	gtk_container_add(GTK_CONTAINER(center_vbox), vbox );
	GtkWidget *buttonbox;
    buttonbox = gtk_box_new (TRUE, 0);
	gtk_container_add(GTK_CONTAINER(vbox), buttonbox );
	GtkWidget *buttonbox2;
	buttonbox2 = gtk_box_new(TRUE, 0); 
	g_signal_connect(buttonbox2, "size-allocate", G_CALLBACK(getsize), "buttonbox2");
	gtk_container_add(GTK_CONTAINER(vbox), buttonbox2 );
	gtk_box_pack_start (GTK_BOX(buttonbox), bLine, FALSE, FALSE, 0);
	gchar *lLine = "<span font='10' background='#00000002' foreground='#AFAFFFFF'>Line</span>";
	gtk_widget_set_tooltip_markup(bLine, lLine);
	gtk_widget_show(bLine );
	g_signal_connect(bLine, "clicked", G_CALLBACK(bLine_clicked ), &icons );
	
	gtk_box_pack_start (GTK_BOX(buttonbox), bPolyline, FALSE, FALSE, 0);
	gchar *lPolyline = "<span font='10' background='#00000002' foreground='#AFAFFFFF'>Polyline</span>";
	gtk_widget_set_tooltip_markup(bPolyline, lPolyline);
	gtk_widget_show(bPolyline );
	g_signal_connect(bPolyline, "clicked", G_CALLBACK(bPolyline_clicked ), &icons );
	
	gtk_box_pack_start (GTK_BOX(buttonbox), bRectangle, FALSE, FALSE, 0);
	gchar *lRectangle = "<span font='10' background='#00000002' foreground='#AFAFFFFF'>Rectangle</span>";
	gtk_widget_set_tooltip_markup(bRectangle, lRectangle);
	gtk_widget_show(bRectangle );
	
	gtk_box_pack_start (GTK_BOX(buttonbox), bSquare, FALSE, FALSE, 0);
	gchar *lSquare = "<span font='10' background='#00000002' foreground='#AFAFFFFF'>Square</span>";
	gtk_widget_set_tooltip_markup(bSquare, lSquare);
	gtk_widget_show(bSquare );
	
	gtk_box_pack_start (GTK_BOX(buttonbox), bCircle, FALSE, FALSE, 0);
	gchar *lCircle = "<span font='10' background='#00000002' foreground='#AFAFFFFF'>Circle</span>";
	gtk_widget_set_tooltip_markup(bCircle, lCircle);
	gtk_widget_show(bCircle );
	
	gtk_box_pack_start (GTK_BOX(buttonbox), bCirclethree, FALSE, FALSE, 0);
	gchar *lCirclethree = "<span font='10' background='#00000002' foreground='#AFAFFFFF'>Circle through three points</span>";
	gtk_widget_set_tooltip_markup(bCirclethree, lCirclethree);
	gtk_widget_show(bCirclethree );
	
	gtk_box_pack_start (GTK_BOX(buttonbox), bArc, FALSE, FALSE, 0);
	gchar *lArc = "<span font='10' background='#00000002' foreground='#AFAFFFFF'>Arc</span>";
	gtk_widget_set_tooltip_markup(bArc, lArc);
	gtk_widget_show(bArc );
	
	gtk_box_pack_start (GTK_BOX(buttonbox), bArcthree, FALSE, FALSE, 0);
	gchar *lArcthree = "<span font='10' background='#00000002' foreground='#AFAFFFFF'>Arc through three points</span>";
	gtk_widget_set_tooltip_markup(bArcthree, lArcthree);
	gtk_widget_show(bArcthree );
	
	gtk_box_pack_start (GTK_BOX(buttonbox), bEllipse, FALSE, FALSE, 0);
	gchar *lEllipse = "<span font='10' background='#00000002' foreground='#AFAFFFFF'>Ellipse</span>";
	gtk_widget_set_tooltip_markup(bEllipse, lEllipse);
	gtk_widget_show(bEllipse );
	
	gtk_box_pack_start (GTK_BOX(buttonbox), bCubic, FALSE, FALSE, 0);
	gchar *lCubic = "<span font='10' background='#00000002' foreground='#AFAFFFFF'>Cubic bezier curve</span>";
	gtk_widget_set_tooltip_markup(bCubic, lCubic);
	gtk_widget_show(bCubic );
	
	gtk_box_pack_start (GTK_BOX(buttonbox), bQuadratic, FALSE, FALSE, 0);
	gchar *lQuadratic = "<span font='10' background='#00000002' foreground='#AFAFFFFF'>Quadratic bezier curve</span>";
	gtk_widget_set_tooltip_markup(bQuadratic, lQuadratic);
	gtk_widget_show(bQuadratic );
	
	gtk_box_pack_start (GTK_BOX(buttonbox), bText, FALSE, FALSE, 0);
	gchar *lText = "<span font='10' background='#00000002' foreground='#AFAFFFFF'>Text</span>";
	gtk_widget_set_tooltip_markup(bText, lText);
	gtk_widget_show(bText );
	g_signal_connect(bText, "clicked", G_CALLBACK(bText_clicked ), &icons);
	
	gtk_box_pack_start (GTK_BOX(buttonbox), bImage, FALSE, FALSE, 0);
	gchar *lImage = "<span font='10' background='#00000002' foreground='#AFAFFFFF'>Image</span>";
	gtk_widget_set_tooltip_markup(bImage, lImage);
	gtk_widget_show(bImage );
	g_signal_connect(bImage, "clicked", G_CALLBACK(bImage_clicked ), &icons );
	
	gtk_box_pack_start (GTK_BOX(buttonbox2), bLinear, FALSE, FALSE, 0);
	gchar *lLinear = "<span font='10' background='#00000002' foreground='#AFAFFFFF'>Linear dimension</span>";
	gtk_widget_set_tooltip_markup(bLinear, lLinear);
	gtk_widget_show(bLinear );
	
	gtk_box_pack_start (GTK_BOX(buttonbox2), bAligned, FALSE, FALSE, 0);
	gchar *lAligned = "<span font='10' background='#00000002' foreground='#AFAFFFFF'>Aligned dimension</span>";
	gtk_widget_set_tooltip_markup(bAligned, lAligned);
	gtk_widget_show(bAligned );
	
	gtk_box_pack_start (GTK_BOX(buttonbox2), bAngular, FALSE, FALSE, 0);
	gchar *lAngular = "<span font='10' background='#00000002' foreground='#AFAFFFFF'>Angular dimension</span>";
	gtk_widget_set_tooltip_markup(bAngular, lAngular);
	gtk_widget_show(bAngular );
	
	gtk_box_pack_start (GTK_BOX(buttonbox2), bRadius, FALSE, FALSE, 0);
	gchar *lRadius = "<span font='10' background='#00000002' foreground='#AFAFFFFF'>Radius dimension</span>";
	gtk_widget_set_tooltip_markup(bRadius, lRadius);
	gtk_widget_show(bRadius );
	
	gtk_box_pack_start (GTK_BOX(buttonbox), bRound, FALSE, FALSE, 0);
	gchar *lRound = "<span font='10' background='#00000002' foreground='#AFAFFFFF'>Round edges</span>";
	gtk_widget_set_tooltip_markup(bRound, lRound);
	gtk_widget_show(bRound );
	
	gtk_box_pack_start (GTK_BOX(buttonbox), bChamfer, FALSE, FALSE, 0);
	gchar *lChamfer = "<span font='10' background='#00000002' foreground='#AFAFFFFF'>Chamfer edges</span>";
	gtk_widget_set_tooltip_markup(bChamfer, lChamfer);
	gtk_widget_show(bChamfer );
	
	gtk_box_pack_start (GTK_BOX(buttonbox), bBreak, FALSE, FALSE, 0);
	gchar *lBreak = "<span font='10' background='#00000002' foreground='#AFAFFFFF'>Break at intersect</span>";
	gtk_widget_set_tooltip_markup(bBreak, lBreak);
	gtk_widget_show(bBreak );
	
	gtk_box_pack_start (GTK_BOX(buttonbox), bShorten, FALSE, FALSE, 0);
	gchar *lShorten = "<span font='10' background='#00000002' foreground='#AFAFFFFF'>Shorten to intersect</span>";
	gtk_widget_set_tooltip_markup(bShorten, lShorten);
	gtk_widget_show(bShorten );
	
	gtk_box_pack_start (GTK_BOX(buttonbox2), bExportpdf, FALSE, FALSE, 0);
	gchar *lExportpdf = "<span font='10' background='#00000002' foreground='#AFAFFFFF'>Export Pdf</span>";
	gtk_widget_set_tooltip_markup(bExportpdf, lExportpdf);
	gtk_widget_show(bExportpdf );
	g_signal_connect(bExportpdf, "clicked", G_CALLBACK(bExportpdf_clicked ), &icons );
    
	gtk_box_pack_start (GTK_BOX(buttonbox2), bImportdxf, FALSE, FALSE, 0);
	gchar *lImportdxf = "<span font='10' background='#00000002' foreground='#AFAFFFFF'>Import Dxf</span>";
	gtk_widget_set_tooltip_markup(bImportdxf, lImportdxf);
	gtk_widget_show(bImportdxf );
    g_signal_connect(bImportdxf, "query-tooltip", G_CALLBACK(query_tooltip ), NULL);
	g_signal_connect(bImportdxf, "clicked", G_CALLBACK(bImportdxf_clicked ), &icons );
	
	g_signal_connect(window, "delete-event", G_CALLBACK(gtk_main_quit ), NULL );
	gtk_widget_show(window );
	gtk_widget_show_all((GtkWidget*)window );
	
	gint iAllocatedheight = gtk_widget_get_allocated_height(window);
	gint iAllocatedwidth = gtk_widget_get_allocated_width(window);
	g_print("Window size x %d y %d width %d height %d \n",iWindowx, iWindowy, iAllocatedwidth, iAllocatedheight);
		
	g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit ), NULL );
	g_signal_connect(G_OBJECT(window), "window-state-event", G_CALLBACK(callback_minimize), NULL);

	g_object_unref(icon ); 	
	gtk_main();
  
}


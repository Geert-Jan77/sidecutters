#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cairo.h>
#include <cairo-pdf.h>
#include "testpdf.c"
#include "testcairo.c"
#define MAX_LEN 256

gboolean bCairoinitialized = FALSE;
gboolean bColorpickerinitialized = FALSE;
gboolean bCairoshown = FALSE;
GtkWidget *frame, *acibox, *icCol, *buttonbox2, *window, *icCol0;
gint iLeft, iTop;
guint iAciold;
gint iColorpickerLeft, iColorpickerTop;

gint calibratescreen(float *ppmm, float *fSize)
{
    gint width_mm, height_mm;
    gint width_pix, height_pix;
    GdkRectangle workarea = {0};
    GdkMonitor *monitor;
    monitor = gdk_display_get_primary_monitor(gdk_display_get_default());
    width_mm = gdk_monitor_get_width_mm (monitor);
    height_mm = gdk_monitor_get_height_mm (monitor);
    GdkRectangle r = {0};
    gdk_monitor_get_geometry(monitor, &r);
    width_pix = (gint)r.width;
    height_pix = (gint)r.height;
    gdk_monitor_get_workarea( monitor, &workarea);
    *fSize = sqrt((float)width_mm / 25.4f * (float)width_mm / 25.4f + (float)height_mm / 25.4f * (float)height_mm / 25.4f);
	*ppmm = (float) width_pix / (float)width_mm; 
	return 6;
}

void getsize(GtkWidget *widget, GtkAllocation *allocation, char *data ) 
{
	gint wix, wiy;
	gdk_window_get_origin (gtk_widget_get_window (widget), &wix, &wiy);
	if (!bCairoinitialized) 
	{
		g_print("Relative to client %s x %d y %d width %d height %d \n", data, allocation->x, allocation->y, allocation->width, allocation->height);
		g_print("Absolute coords %s x %d y %d width %d height %d \n", data, allocation->x + wix, allocation->y + wiy, allocation->width, allocation->height);
		bCairoinitialized = TRUE;
		iWindowx = allocation->x + allocation->width;
		iWindowy = allocation->y;
	}
}

void getsizecolorpicker(GtkWidget *widget, GtkAllocation *allocation, char *data ) 
{
	if (!bColorpickerinitialized)
	{
		g_print("Relative to client %s x %d y %d width %d height %d \n", data, allocation->x, allocation->y, allocation->width, allocation->height);
		iColorpickerLeft = allocation->x;
		iColorpickerTop = allocation->y;
		bColorpickerinitialized = TRUE;
	}
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
	// Read Config file to debug window
	
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
	while (fgets(buffer, MAX_LEN, fp2))
    {
		read = strcspn(buffer, "\n");
        buffer[read+1] = 0;
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
	animate(frame);
}

static void bLine_clicked(GtkWidget *button, struct Icons *icons )
{
	//static gboolean bLine = FALSE;
	boLine = !boLine;
	if (boLine)
		gtk_button_set_image(GTK_BUTTON(button), icons -> line );
	else
		gtk_button_set_image(GTK_BUTTON(button), icons -> line0 );
}

static void bPolyline_clicked(GtkWidget *button, struct Icons *icons)
{
	static gboolean bPolyline = FALSE;
	bPolyline = !bPolyline;
	if (bPolyline)
		gtk_button_set_image(GTK_BUTTON(button), icons -> polyline );
	else
		gtk_button_set_image(GTK_BUTTON(button), icons -> polyline0 );
	
}

static void bExportpdf_clicked(GtkWidget *button, struct Icons *icons)
{
	// export pdf with cairo
	cairo_text_extents_t extents1, extents2, extents3;
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
	int iRet = 0;
	cairo_surface_t *surface;
	cairo_t *Cairo;
	surface = cairo_pdf_surface_create(sPdfFile, 297.0 * fPPMM, 210.0 * fPPMM);
	Cairo = cairo_create(surface);
	

	// finished drawing objects (20, 5) -> (0, 0) 
	cairo_set_line_width (Cairo, 0.2 * MMPT ); //0.2 mm linewidth
	gboolean boRedrawBtn = FALSE;
	int iCounter = 1;
	while (iCounter <= Pages[0])
	{
		if (Pages[iCounter] == 6)
		{
			iDonex0 = (gint)Pages[iCounter + 1];
			iDoney0 = (gint)Pages[iCounter + 2];
			iDonex1 = (gint)Pages[iCounter + 3];
			iDoney1 = (gint)Pages[iCounter + 4];
			iCounter = iCounter + 5;
			cairo_move_to(Cairo, ((float)iDonex0) * fPPMM, (210.0 - (float)iDoney0) * fPPMM );
			cairo_line_to(Cairo, ((float)iDonex1) * fPPMM, (210.0 - (float)iDoney1) * fPPMM );
			cairo_stroke(Cairo);
		}
		if (Pages[iCounter] == 5)
		{
			iDonex0 = (gint)Pages[iCounter + 2];
			iCounter = iCounter + 3;
			cairo_set_source_rgb(Cairo,(float)dxfcolor[4 * iDonex0 + 1], (float)dxfcolor[4 * iDonex0 + 2], (float)dxfcolor[4 * iDonex0 + 3]/255);
		}
	}
	
	// textbox
	cairo_set_source_rgb(Cairo, 0, 0, 0);
	cairo_select_font_face(Cairo, "Calibri", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
    cairo_set_font_size(Cairo, 3.0 * fPPMM / PXPT);
	cairo_text_extents(Cairo, "A4 297 x 210 mm. Calibri 3 mm.", &extents1);
    if (!bMarker1) g_print("Target font height %f mm Realised fontheight %f mm\n", 3.0, extents1.height /fPPMM );
    fScalefont = 3.0 * fPPMM / extents1.height;
	if (!bMarker1) {g_print("Font Scaling %.2f \n", fScalefont); bMarker1=TRUE;}
    cairo_set_font_size(Cairo, 3.0 * fPPMM / PXPT);
	cairo_text_extents(Cairo, "A4 297 x 210 mm. Calibri 3 mm.", &extents1);
	cairo_move_to(Cairo, (297.0 * fPPMM) - extents1.width - extents1.x_bearing, (210.0 * fPPMM) - extents1.height - extents1.y_bearing  );   
	cairo_show_text(Cairo, "A4 297 x 210 mm. Calibri 3 mm.");
	// textbox
	cairo_set_source_rgb(Cairo, 0, 0, 0);
	cairo_select_font_face (Cairo, "Calibri", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL); 
    cairo_set_font_size (Cairo, 3.0 * fPPMM / PXPT);
	cairo_text_extents(Cairo, label, &extents2);
	cairo_move_to(Cairo, (297.0 * fPPMM) - extents2.width - extents2.x_bearing, (210.0 * fPPMM) - extents1.height - extents2.height - extents2.y_bearing  );   
	cairo_show_text(Cairo, label);  
	
	
	cairo_show_page(Cairo);
	cairo_surface_destroy(surface);
	cairo_destroy(Cairo);
	GtkWidget *dialog ;
    if (iRet == 0) dialog = gtk_message_dialog_new(NULL, 0, GTK_MESSAGE_INFO, GTK_BUTTONS_OK, "The cairo portable data file was exported." );
    gtk_window_set_title(GTK_WINDOW(dialog), "TestPdf");
    gint result = gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy( GTK_WIDGET(dialog) );
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

void boRedrawBtn(guint iDoneAci)
{
	GdkPixbuf* pix0 = gtk_image_get_pixbuf(GTK_IMAGE(icons.color0));
	guchar *pixels = gdk_pixbuf_get_pixels (pix0);
	int rowstride = gdk_pixbuf_get_rowstride (pix0);
	for (int j = 6; j < 34; j++)
	{
		for (int i = 6; i < 34; i++)
		{
			guchar *p = pixels + i * rowstride + j * 3;
			p[0] = (guchar)dxfcolor[4 * iDoneAci + 1];
			p[1] = (guchar)dxfcolor[4 * iDoneAci + 2];
			p[2] = (guchar)dxfcolor[4 * iDoneAci + 3];
		}
	}
	icCol0 = gtk_image_new_from_pixbuf ( pix0);		
	gtk_button_set_image (GTK_BUTTON(bColor), icCol0 );
	gtk_widget_show_all (window);
}

static void bUndo_clicked(GtkWidget *button, struct Icons *icons)
{
	if (Undo[0] < 1)
	{
		GtkWidget *dialog ;
		dialog = gtk_message_dialog_new(NULL, 0, GTK_MESSAGE_INFO, GTK_BUTTONS_OK, "There is nothing to undo." );
		gtk_window_set_title(GTK_WINDOW(dialog), "Undo");
		gint result = gtk_dialog_run(GTK_DIALOG(dialog));
		gtk_widget_destroy( GTK_WIDGET(dialog) );
	}
	else
	{
	Pages[0] = Pages[0] - Undo[Undo[0]];
	if (Pages[Pages[0] + 1] == 5) {g_print("Undo Color select.\n"); boRedrawBtn(Pages[Pages[0] + 2]); }
	if (Pages[Pages[0] + 1] == 6) {g_print("Undo Line.\n");}
	Undo[0]--;
	Redo++;
	}
}

static void bRedo_clicked(GtkWidget *button, struct Icons *icons)
{
	if (Redo < 1) 
	{
		GtkWidget *dialog ;
		dialog = gtk_message_dialog_new(NULL, 0, GTK_MESSAGE_INFO, GTK_BUTTONS_OK, "There is nothing to redo." );
		gtk_window_set_title(GTK_WINDOW(dialog), "Redo");
		gint result = gtk_dialog_run(GTK_DIALOG(dialog));
		gtk_widget_destroy( GTK_WIDGET(dialog) );
	}
	else
	{
	if (Pages[Pages[0] + 1] == 5) {g_print("Redo Color select.\n"); boRedrawBtn(Pages[Pages[0] + 3]); }
	if (Pages[Pages[0] + 1] == 6) {g_print("Redo Line.\n");}
	Pages[0] = Pages[0] + Undo[Undo[0] + 1];
	Undo[0]++;
	Redo--;
	}
}

static gboolean colorpicker_pressed(GtkWidget *widget, GdkEventButton *event, gpointer user_data) 
{
	gint row[10] = {9,7,5,3,1,0,2,4,6,8};
	gint col[26] = {0,10,20,30,40,50,60,70,80,90,100,110,120,130,140,150,160,170,180,190,200,210,220,230,240,250};
	gint xn = (gint) event->x;
	gint yn = (gint) event->y;   
	gint xabs = xn - iColorpickerLeft;
	gint yabs = yn - iColorpickerTop;
	gint iRow = (yn - iColorpickerTop) / 20;
	gint iCol = (xn - iColorpickerLeft) / 20;
	iAciold = iAci;
	iAci = col[iCol] + row[iRow];
	// put the greys in the right order
	if (iAci == 259) iAci = 0;	
	if (iAci == 8) iAci = 7;
	if (iAci == 9) iAci = 7;
	if (iAci == 253) iAci = 8;
	if (iAci == 252) iAci = 9;
	if (iAci == 250) iAci = 253;
	if (iAci == 251) iAci = 252;
	if (iAci == 257) iAci = 250;
	if (iAci == 255) iAci = 251;
	if (iAci == 256) iAci = 255;
	if (iAci == 258) iAci = 0;
    if (event->type == GDK_BUTTON_PRESS) 
	{
		//g_print("Select color(%.0f mm,%.0f mm)\n", (float)xabs, (float)yabs );
		g_print("Select aci %d\n",iAci);
		GdkPixbuf* pix0 = gtk_image_get_pixbuf(GTK_IMAGE(icons.color));
		guchar *pixels0 = gdk_pixbuf_get_pixels (pix0);
		int rowstride = gdk_pixbuf_get_rowstride (pix0);
		for (int j = 6; j < 34; j++)
		{
			for (int i = 6; i < 34; i++)
			{
				guchar *p = pixels0 + i * rowstride + j * 3;
				p[0] = (guchar)dxfcolor[4 * iAci + 1];
				p[1] = (guchar)dxfcolor[4 * iAci + 2];
				p[2] = (guchar)dxfcolor[4 * iAci + 3];
			}
		}
		icCol0 = gtk_image_new_from_pixbuf ( pix0);		
		gtk_button_set_image (GTK_BUTTON(bColor), icCol0 );
		gtk_widget_show_all (window);
		GdkPixbuf* pix = gtk_image_get_pixbuf(GTK_IMAGE(icons.color0));
		guchar *pixels = gdk_pixbuf_get_pixels (pix);
		rowstride = gdk_pixbuf_get_rowstride (pix);
		for (int j = 6; j < 34; j++)
		{
			for (int i = 6; i < 34; i++)
			{
				guchar *p = pixels + i * rowstride + j * 3;
				p[0] = (guchar)dxfcolor[4 * iAci + 1];
				p[1] = (guchar)dxfcolor[4 * iAci + 2];
				p[2] = (guchar)dxfcolor[4 * iAci + 3];
			}
		}
		//gtk_widget_destroy (GTK_WIDGET(icCol));		
		//icCol = gtk_image_new_from_pixbuf ( pix);
		//gtk_box_pack_start (GTK_BOX (acibox), icCol, FALSE, FALSE, 0);
		//gtk_widget_show_all (widget);
	}
	return TRUE;
}

static void changeicon(GtkDialog* self,  gint response_id,  gpointer user_data) 
{
	g_print("OK clicked.\n");
	Selectcolor(iAciold, iAci);
}

static void bColor_clicked(GtkWidget *button, struct Icons *icons)
{
	gtk_button_set_image(GTK_BUTTON(button), icons -> color );
	GtkWidget *label, *content_area, *acicolor, *cDialog;
	GtkDialogFlags flags;
	acibox = gtk_box_new (FALSE, 0);
	flags = GTK_DIALOG_DESTROY_WITH_PARENT;
	cDialog = gtk_dialog_new_with_buttons ("Colorpicker", GTK_WINDOW (window), flags, "_OK", GTK_RESPONSE_NONE, NULL);
	content_area = gtk_dialog_get_content_area (GTK_DIALOG (cDialog));
	label = gtk_label_new ("Autodesk color index");
	g_signal_connect(cDialog, "response", G_CALLBACK (changeicon), NULL);
	g_signal_connect_swapped (cDialog, "response", G_CALLBACK (gtk_widget_destroy), cDialog);
	gtk_container_add (GTK_CONTAINER (content_area), label);
	acicolor = GTK_WIDGET(icons->aci);
	gtk_container_add (GTK_CONTAINER (content_area), acibox);
	gtk_box_pack_start (GTK_BOX (acibox), acicolor, FALSE, FALSE, 0);
	GdkPixbuf* pix = gtk_image_get_pixbuf(GTK_IMAGE(icons->color0));
	guchar *pixels = gdk_pixbuf_get_pixels (pix);
	int rowstride = gdk_pixbuf_get_rowstride (pix);
	for (int j = 6; j < 34; j++)
	{
		for (int i = 6; i < 34; i++)
		{
			guchar *p = pixels + i * rowstride + j * 3;
			p[0] = (guchar)dxfcolor[4 * iAci + 1];
			p[1] = (guchar)dxfcolor[4 * iAci + 2];
			p[2] = (guchar)dxfcolor[4 * iAci + 3];
		}
	}	
	//icCol = gtk_image_new_from_pixbuf ( pix);
	//gtk_box_pack_start (GTK_BOX (acibox), icCol, FALSE, FALSE, 0);
	g_signal_connect(G_OBJECT(cDialog), "button-press-event", G_CALLBACK (colorpicker_pressed), NULL);
	g_signal_connect(acibox, "size-allocate", G_CALLBACK(getsizecolorpicker), "acibox");
	gtk_widget_show_all (cDialog);
}	

int main(int argc, char *argv[] )
{
	// main window
	
	GdkPixbuf *icon;
	gtk_init(&argc, &argv );
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL );
	GdkRectangle workarea = {0 };
	gdk_monitor_get_workarea(gdk_display_get_primary_monitor(gdk_display_get_default()), &workarea );	
	//g_print ("workarea.width %d, workarea.height %d\n", workarea.width, workarea.height);
    GdkGeometry hints;
	gint iRet = calibratescreen(&fPPMM, &fScreensize);
	//g_print("iLeft %d, iRight %d, iTop %d, iBottom %d\n",iLeft, iRight, iTop, iBottom);
	g_print("Pixels per mm %.2f Screen diagonal inches %.1f\" \n", fPPMM, fScreensize);
	hints.min_width = workarea.width;
    hints.max_width = workarea.width;
    hints.min_height = workarea.height;
    hints.max_height = workarea.height;
    gtk_window_set_geometry_hints( GTK_WINDOW(window), window, &hints, (GdkWindowHints)(GDK_HINT_MIN_SIZE | GDK_HINT_MAX_SIZE));
	gtk_widget_set_size_request(GTK_WIDGET (window), workarea.width, workarea.height);
	gtk_window_set_default_size (GTK_WINDOW (window), workarea.width, workarea.height);
	gtk_window_move (GTK_WINDOW(window), workarea.x, workarea.y);
	gtk_window_set_title(GTK_WINDOW(window), "Side Cutters" );

	// icon
    char *sRes = sFromConf("Resource");
    char *sIconfile = malloc(strlen(sRes) + strlen("icon.png") + 1);
    strcpy(sIconfile, sRes);
    strcat(sIconfile, "icon.png");
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
    char *sUndofile = malloc(strlen(sRes) + strlen("undo.xpm") + 1);
	char *sUndofile0 = malloc(strlen(sRes) + strlen("undo0.xpm") + 1);
	char *sRedofile = malloc(strlen(sRes) + strlen("redo.xpm") + 1);
	char *sRedofile0 = malloc(strlen(sRes) + strlen("redo0.xpm") + 1);
	char *sDoublethickfile = malloc(strlen(sRes) + strlen("doublethick.xpm") + 1);
	char *sDoublethickfile0 = malloc(strlen(sRes) + strlen("doublethick0.xpm") + 1);
	char *sTriplethickfile = malloc(strlen(sRes) + strlen("triplethick.xpm") + 1);
	char *sTriplethickfile0 = malloc(strlen(sRes) + strlen("triplethick0.xpm") + 1);
    char *sDashedlinefile = malloc(strlen(sRes) + strlen("dashedline.xpm") + 1);
    char *sDashedlinefile0 = malloc(strlen(sRes) + strlen("dashedline0.xpm") + 1);
    char *sCenterlinefile = malloc(strlen(sRes) + strlen("centerline.xpm") + 1);
    char *sCenterlinefile0 = malloc(strlen(sRes) + strlen("centerline0.xpm") + 1);
    char *sColorfile = malloc(strlen(sRes) + strlen("color.xpm") + 1);
    char *sColorfile0 = malloc(strlen(sRes) + strlen("color0.xpm") + 1);
	char *sAcifile = malloc(strlen(sRes) + strlen("aci.xpm") + 1);
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
	strcpy(sUndofile, sRes);
	strcat(sUndofile, "undo.xpm");
	strcpy(sUndofile0, sRes);
	strcat(sUndofile0, "undo0.xpm");
	strcpy(sRedofile, sRes);
	strcat(sRedofile, "redo.xpm");
	strcpy(sRedofile0, sRes);
	strcat(sRedofile0, "redo0.xpm");
	strcpy(sDoublethickfile, sRes);
	strcat(sDoublethickfile, "doublethick.xpm");
	strcpy(sDoublethickfile0, sRes);
	strcat(sDoublethickfile0, "doublethick0.xpm");
	strcpy(sTriplethickfile, sRes);
	strcat(sTriplethickfile, "triplethick.xpm");
	strcpy(sTriplethickfile0, sRes);
	strcat(sTriplethickfile0, "triplethick0.xpm");
	strcpy(sDashedlinefile, sRes);
	strcat(sDashedlinefile, "dashedline.xpm");
	strcpy(sDashedlinefile0, sRes);
	strcat(sDashedlinefile0, "dashedline0.xpm");
	strcpy(sCenterlinefile, sRes);
	strcat(sCenterlinefile, "centerline.xpm");
	strcpy(sCenterlinefile0, sRes);
	strcat(sCenterlinefile0, "centerline0.xpm");
	strcpy(sColorfile, sRes);
	strcat(sColorfile, "color.xpm");
	strcpy(sColorfile0, sRes);
	strcat(sColorfile0, "color0.xpm");
	strcpy(sAcifile, sRes);
	strcat(sAcifile, "aci.xpm");
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
	icons.undo = gtk_image_new_from_file(sUndofile );
	icons.undo0 = gtk_image_new_from_file(sUndofile0 );
	icons.redo = gtk_image_new_from_file(sRedofile );
	icons.redo0 = gtk_image_new_from_file(sRedofile0 );
	icons.doublethick = gtk_image_new_from_file(sDoublethickfile );
	icons.doublethick0 = gtk_image_new_from_file(sDoublethickfile0 );
	icons.triplethick = gtk_image_new_from_file(sTriplethickfile );
	icons.triplethick0 = gtk_image_new_from_file(sTriplethickfile0 );
	icons.dashedline = gtk_image_new_from_file(sDashedlinefile );
	icons.dashedline0 = gtk_image_new_from_file(sDashedlinefile0 );
	icons.centerline = gtk_image_new_from_file(sCenterlinefile );
	icons.centerline0 = gtk_image_new_from_file(sCenterlinefile0 );
	icons.color = gtk_image_new_from_file(sColorfile );
	icons.color0 = gtk_image_new_from_file(sColorfile0 );
	icons.aci = gtk_image_new_from_file(sAcifile );
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
	g_object_ref_sink(icons.undo );
	g_object_ref_sink(icons.undo0 );
	g_object_ref_sink(icons.redo );
	g_object_ref_sink(icons.redo0 );
	g_object_ref_sink(icons.doublethick );
	g_object_ref_sink(icons.doublethick0 );
	g_object_ref_sink(icons.triplethick );
	g_object_ref_sink(icons.triplethick0 );
	g_object_ref_sink(icons.dashedline );
	g_object_ref_sink(icons.dashedline0 );
	g_object_ref_sink(icons.centerline );
	g_object_ref_sink(icons.centerline0 );
	g_object_ref_sink(icons.color );
	g_object_ref_sink(icons.color0 );
	g_object_ref_sink(icons.aci );
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
	GtkWidget *iUndo = icons.undo;
	GtkWidget *iUndo0 = icons.undo0;
	GtkWidget *iRedo = icons.redo;
	GtkWidget *iRedo0 = icons.redo0;
	GtkWidget *iDoublethick = icons.doublethick;
	GtkWidget *iDoublethick0 = icons.doublethick0;
	GtkWidget *iTriplethick = icons.triplethick;
	GtkWidget *iTriplethick0 = icons.triplethick0;
	GtkWidget *iDashedline = icons.dashedline;
	GtkWidget *iDashedline0 = icons.dashedline0;
	GtkWidget *iCenterline = icons.centerline;
	GtkWidget *iCenterline0 = icons.centerline0;
	//GtkWidget *iColor = icons.color;
	//GtkWidget *iColor0 = icons.color0;
	icCol0 = icons.color0;
	GtkWidget *iAci = icons.aci;
	bLine = GTK_WIDGET(gtk_button_new());
	bPolyline = GTK_WIDGET(gtk_button_new());
	bPolygon = GTK_WIDGET(gtk_button_new());
	bRectangle = GTK_WIDGET(gtk_button_new());
	bSquare = GTK_WIDGET(gtk_button_new());
	bCircle = GTK_WIDGET(gtk_button_new());
	bCirclethree = GTK_WIDGET(gtk_button_new());
	bArc = GTK_WIDGET(gtk_button_new());
	bArcthree = GTK_WIDGET(gtk_button_new());
	bEllipse = GTK_WIDGET(gtk_button_new());
	bCubic = GTK_WIDGET(gtk_button_new());
	bQuadratic = GTK_WIDGET(gtk_button_new());
	bText = GTK_WIDGET(gtk_button_new());
	bImage = GTK_WIDGET(gtk_button_new());
	bLinear = GTK_WIDGET(gtk_button_new());
	bAligned = GTK_WIDGET(gtk_button_new());
	bAngular = GTK_WIDGET(gtk_button_new());
	bRadius = GTK_WIDGET(gtk_button_new());
	bRound = GTK_WIDGET(gtk_button_new());
	bChamfer = GTK_WIDGET(gtk_button_new());
	bBreak = GTK_WIDGET(gtk_button_new());
	bShorten = GTK_WIDGET(gtk_button_new());
	bExportpdf = GTK_WIDGET(gtk_button_new());
	bImportdxf = GTK_WIDGET(gtk_button_new());
	bUndo = GTK_WIDGET(gtk_button_new());
	bRedo = GTK_WIDGET(gtk_button_new());
	bDoublethick = GTK_WIDGET(gtk_button_new());
	bTriplethick = GTK_WIDGET(gtk_button_new());
	bDashedline = GTK_WIDGET(gtk_button_new());
	bCenterline = GTK_WIDGET(gtk_button_new());
	bColor = GTK_WIDGET(gtk_button_new());
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
	gtk_button_set_image (GTK_BUTTON(bUndo), iUndo0 );
	gtk_button_set_image (GTK_BUTTON(bRedo), iRedo0 );
	gtk_button_set_image (GTK_BUTTON(bDoublethick), iDoublethick0 );
	gtk_button_set_image (GTK_BUTTON(bTriplethick), iTriplethick0 );
	gtk_button_set_image (GTK_BUTTON(bDashedline), iDashedline0 );
	gtk_button_set_image (GTK_BUTTON(bCenterline), iCenterline0 );
	gtk_button_set_image (GTK_BUTTON(bColor), icCol0 );
	GtkWidget *vbox;
    vbox = gtk_box_new (FALSE, 0);
	gtk_box_pack_start (GTK_BOX(center_vbox), vbox, FALSE, FALSE, 0);
	GtkWidget *buttonbox;
    buttonbox = gtk_box_new (TRUE, 0);
	gtk_box_pack_start (GTK_BOX(vbox), buttonbox, FALSE, FALSE, 0);
	//GtkWidget *buttonbox2;
	buttonbox2 = gtk_box_new(TRUE, 0); 
	g_signal_connect(buttonbox, "size-allocate", G_CALLBACK(getsize), "buttonbox");
	//gtk_container_add(GTK_CONTAINER(vbox), buttonbox2 );
	gtk_box_pack_end (GTK_BOX(vbox), buttonbox2, FALSE, FALSE, 0);
	GtkWidget *drawing_area;
	frame = gtk_frame_new (NULL);
	gtk_box_pack_start (GTK_BOX(vbox), frame, FALSE, FALSE, 0);
	drawing_area = gtk_drawing_area_new ();
	gtk_widget_set_size_request (drawing_area, (gint)(320.0 * fPPMM), (gint)(230.0 * fPPMM) );
	gtk_container_add (GTK_CONTAINER(frame), drawing_area);
	g_signal_connect(G_OBJECT(frame), "draw", G_CALLBACK(on_draw_event), NULL);
	g_signal_connect(G_OBJECT(window), "motion-notify-event", G_CALLBACK (mouse_moved), NULL);
	g_signal_connect(G_OBJECT(window), "button-press-event", G_CALLBACK (button_pressed), NULL);
	//g_signal_connect(G_OBJECT(window), "button-release-event", G_CALLBACK (button_released), NULL);
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
	gtk_box_pack_start (GTK_BOX(buttonbox2), bUndo, FALSE, FALSE, 0);
	gchar *lUndo = "<span font='10' background='#00000002' foreground='#AFAFFFFF'>Undo</span>";
	gtk_widget_set_tooltip_markup(bUndo, lUndo);
	gtk_widget_show(bUndo );
	g_signal_connect(bUndo, "clicked", G_CALLBACK(bUndo_clicked ), &icons );
	gtk_box_pack_start (GTK_BOX(buttonbox2), bRedo, FALSE, FALSE, 0);
	gchar *lRedo = "<span font='10' background='#00000002' foreground='#AFAFFFFF'>Redo</span>";
	gtk_widget_set_tooltip_markup(bRedo, lRedo);
	gtk_widget_show(bRedo );
	g_signal_connect(bRedo, "clicked", G_CALLBACK(bRedo_clicked ), &icons );
	gtk_box_pack_start (GTK_BOX(buttonbox2), bDoublethick, FALSE, FALSE, 0);
	gchar *lDoublethick = "<span font='10' background='#00000002' foreground='#AFAFFFFF'>Double thickness 0.4 mm</span>";
	gtk_widget_set_tooltip_markup(bDoublethick, lDoublethick);
	gtk_widget_show(bDoublethick );
	gtk_box_pack_start (GTK_BOX(buttonbox2), bTriplethick, FALSE, FALSE, 0);
	gchar *lTriplethick = "<span font='10' background='#00000002' foreground='#AFAFFFFF'>Triple thickness 0.6 mm</span>";
	gtk_widget_set_tooltip_markup(bTriplethick, lTriplethick);
	gtk_widget_show(bTriplethick );
	gtk_box_pack_start (GTK_BOX(buttonbox2), bDashedline, FALSE, FALSE, 0);
	gchar *lDashedline = "<span font='10' background='#00000002' foreground='#AFAFFFFF'>Dashed line</span>";
	gtk_widget_set_tooltip_markup(bDashedline, lDashedline);
	gtk_widget_show(bDashedline );
	gtk_box_pack_start (GTK_BOX(buttonbox2), bCenterline, FALSE, FALSE, 0);
	gchar *lCenterline = "<span font='10' background='#00000002' foreground='#AFAFFFFF'>Centerline</span>";
	gtk_widget_set_tooltip_markup(bCenterline, lCenterline);
	gtk_widget_show(bCenterline );
	gtk_box_pack_start (GTK_BOX(buttonbox2), bColor, FALSE, FALSE, 0);
	gchar *lColor = "<span font='10' background='#00000002' foreground='#AFAFFFFF'>Color</span>";
	gtk_widget_set_tooltip_markup(bColor, lColor);
	gtk_widget_show(bColor );
	g_signal_connect(bColor, "clicked", G_CALLBACK(bColor_clicked ), &icons );
    g_signal_connect(bImportdxf, "query-tooltip", G_CALLBACK(query_tooltip ), NULL);
	g_signal_connect(bImportdxf, "clicked", G_CALLBACK(bImportdxf_clicked ), &icons );
	g_signal_connect(window, "delete-event", G_CALLBACK(gtk_main_quit ), NULL );
	gtk_widget_show(window );
	gint wix, wiy;
	gdk_window_get_origin (gtk_widget_get_window (GTK_WIDGET(window)), &wix, &wiy);
	iLeft = workarea.x;
	iTop = workarea.y;
	g_print("Window manager gives us borders. Client x %d Client y %d\n", wix - iLeft, wiy - iTop);
	hints.min_width = workarea.width - 2 * wix + 2 * iLeft;
	hints.max_width = workarea.width - 2 * wix + 2 * iLeft;
	hints.min_height = workarea.height - wiy + iTop - 2 * wix + 2 * iLeft;
	hints.max_height = workarea.height - wiy + iTop - 2 * wix + 2 * iLeft;
	gtk_window_set_geometry_hints( GTK_WINDOW(window), window, &hints, (GdkWindowHints)(GDK_HINT_MIN_SIZE | GDK_HINT_MAX_SIZE));
	gtk_widget_set_size_request(GTK_WIDGET (window), workarea.width - 2 * wix + 2 * iLeft, workarea.height - wiy + iTop - 2 * wix + 2 * iLeft);
	gtk_window_set_default_size (GTK_WINDOW (window), workarea.width - 2 * wix + 2 * iLeft, workarea.height - wiy + iTop - 2 * wix + 2 * iLeft);
	g_print("Request resize w %d h %d \n", workarea.width - 2 * wix + 2 * iLeft, workarea.height - wiy + iTop - 2 * wix + 2 * iLeft);
	gtk_window_move (GTK_WINDOW(window), iLeft, iTop + wix - iLeft);
	g_print("Move x %d y %d \n", iLeft, iTop + wix - iLeft);
	gtk_widget_show_all((GtkWidget*)window );
	g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit ), NULL );
	//g_signal_connect(G_OBJECT(window), "window-state-event", G_CALLBACK(callback_minimize), NULL);
	g_object_unref(icon ); 	
	gtk_main();
  
}

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
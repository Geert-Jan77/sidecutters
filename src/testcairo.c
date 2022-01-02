#include <cairo.h>
#include <gtk/gtk.h>
#include <stdlib.h>
#include "buttons.c"
#define MMPT 2.834646f      // 2.83 mm = 1 pt
#define PXPT 0.75f          // 0.75 pt = 1 px

static void do_drawing(cairo_t *);
static void do_drawing2(cairo_t *, GtkWidget *);

char label[MAX_LEN ];
float alpha = 0.0;
float fPPMM;               // Monitor resolution, platform dependent
float fScreensize;         // Monitor size in inches, platform dependent
float fScalefont;          // Font scaling, platform dependent
int x, y = 0;  
int hidecairo();
int showcairo();
gint iWindowx, iWindowy;
gint iDrawx0, iDrawx1, iDrawx2, iDrawx3, iDrawx4, iDrawy0, iDrawy1, iDrawy2, iDrawy3, iDrawy4;
gint iDonex0, iDonex1, iDonex2, iDonex3, iDonex4, iDoney0, iDoney1, iDoney2, iDoney3, iDoney4;
gint iInputs = 0;
gboolean bTransparency = FALSE;
gboolean bMarker1 = FALSE;
gboolean boLine = FALSE;
guint iAci = 0;
guint8 dxfcolor[1024] = {0,0,0,0,1,255,0,0,2,255,255,0,3,0,255,0,4,0,255,255,5,0,0,255,6,255,0,255,7,255,255,255,8,128,128,128,9,192,192,192,
	10,255,0,0,11,255,127,127,12,204,0,0,13,204,102,102,14,153,0,0,15,153,76,76,16,127,0,0,17,127,63,63,18,76,0,0,19,76,38,38,
	20,255,63,0,21,255,159,127,22,204,51,0,23,204,127,102,24,153,38,0,25,153,95,76,26,127,31,0,27,127,79,63,28,76,19,0,29,76,47,38,
	30,255,127,0,31,255,191,127,32,204,102,0,33,204,153,102,34,153,76,0,35,153,114,76,36,127,63,0,37,127,95,63,38,76,38,0,39,76,57,38,
	40,255,191,0,41,255,223,127,42,204,153,0,43,204,178,102,44,153,114,0,45,153,133,76,46,127,95,0,47,127,111,63,48,76,57,0,49,76,66,38,
	50,255,255,0,51,255,255,127,52,204,204,0,53,204,204,102,54,152,152,0,55,152,152,76,56,127,127,0,57,127,127,63,58,76,76,0,59,76,76,38,
	60,191,255,0,61,223,255,127,62,153,204,0,63,178,204,102,64,114,152,0,65,133,152,76,66,95,127,0,67,111,127,63,68,57,76,0,69,66,76,38,
	70,127,255,0,71,191,255,127,72,102,204,0,73,153,204,102,74,76,152,0,75,114,152,76,76,63,127,0,77,95,127,63,78,38,76,0,79,57,76,38,
	80,63,255,0,81,159,255,127,82,51,204,0,83,127,204,102,84,38,152,0,85,95,152,76,86,31,127,0,87,79,127,63,88,19,76,0,89,47,76,38,
	90,0,255,0,91,127,255,127,92,0,204,0,93,102,204,102,94,0,152,0,95,76,152,76,96,0,127,0,97,63,127,63,98,0,76,0,99,38,76,38,
	100,0,255,63,101,127,255,159,102,0,204,51,103,102,204,127,104,0,152,38,105,76,152,95,106,0,127,31,107,63,127,79,108,0,76,19,109,38,76,47,
	110,0,255,127,111,127,255,191,112,0,204,102,113,102,204,153,114,0,152,76,115,76,152,114,116,0,127,63,117,63,127,95,118,0,76,38,119,38,76,57,
	120,0,255,191,121,127,255,223,122,0,204,153,123,102,204,178,124,0,152,114,125,76,152,133,126,0,127,95,127,63,127,111,128,0,76,57,129,38,76,66,
	130,0,255,255,131,127,255,255,132,0,204,204,133,102,204,204,134,0,152,152,135,76,152,152,136,0,127,127,137,63,127,127,138,0,76,76,139,38,76,76,
	140,0,191,255,141,127,223,255,142,0,153,204,143,102,178,204,144,0,114,152,145,76,133,152,146,0,95,127,147,63,111,127,148,0,57,76,149,38,66,76,
	150,0,127,255,151,127,191,255,152,0,102,204,153,102,153,204,154,0,76,152,155,76,114,152,156,0,63,127,157,63,95,127,158,0,38,76,159,38,57,76,
	160,0,63,255,161,127,159,255,162,0,51,204,163,102,127,204,164,0,38,152,165,76,95,152,166,0,31,127,167,63,79,127,168,0,19,76,169,38,47,76,
	170,0,0,255,171,127,127,255,172,0,0,204,173,102,102,204,174,0,0,152,175,76,76,152,176,0,0,127,177,63,63,127,178,0,0,76,179,38,38,76,
	180,63,0,255,181,159,127,255,182,51,0,204,183,127,102,204,184,38,0,152,185,95,76,152,186,31,0,127,187,79,63,127,188,19,0,76,189,47,38,76,
	190,127,0,255,191,191,127,255,192,102,0,204,193,153,102,204,194,76,0,152,195,114,76,152,196,63,0,127,197,95,63,127,198,38,0,76,199,57,38,76,
	200,191,0,255,201,223,127,255,202,153,0,204,203,178,102,204,204,114,0,152,205,133,76,152,206,95,0,127,207,111,63,127,208,57,0,76,209,66,38,76,
	210,255,0,255,211,255,127,255,212,204,0,204,213,204,102,204,214,152,0,152,215,152,76,152,216,127,0,127,217,127,63,127,218,76,0,76,219,76,38,76,
	220,255,0,191,221,255,127,223,222,204,0,153,223,204,102,178,224,152,0,114,225,152,76,133,226,127,0,95,227,127,63,111,228,76,0,57,229,76,38,66,
	230,255,0,127,231,255,127,191,232,204,0,102,233,204,102,153,234,152,0,76,235,152,76,114,236,127,0,63,237,127,63,95,238,76,0,38,239,76,38,57,
	240,255,0,63,241,255,127,159,242,204,0,51,243,204,102,127,244,152,0,38,245,152,76,95,246,127,0,31,247,127,63,79,248,76,0,19,249,76,38,47,
	250,51,51,51,251,91,91,91,252,132,132,132,253,173,173,173,254,214,214,214,255,255,255,255};


guint Pages[1024]; // Pages[0] is the length in guint32
guint Undo[255];   // Undo[0]  is the length in quint32, number of objects  
guint Redo = 0;

static void tran_setup(GtkWidget *win)
{        
	GdkScreen *screen;
	GdkVisual *visual;
	gtk_widget_set_app_paintable(win, TRUE);
	screen = gdk_screen_get_default();
	visual = gdk_screen_get_rgba_visual(screen);
	if (visual != NULL && gdk_screen_is_composited(screen)) 
	{
		gtk_widget_set_visual(win, visual);
	}
}

static gboolean on_draw_event(GtkWidget *widget, cairo_t *Cairo, gpointer user_data)
{     
	if (!bTransparency) do_drawing(Cairo);
	if (bTransparency) do_drawing2(Cairo, widget);
	return FALSE;
}

static gboolean mouse_moved(GtkWidget *widget, GdkEvent *event, gpointer user_data) 
{
    // mouse coords to global x, y and label
	if (event->type==GDK_MOTION_NOTIFY) 
	{
        GdkEventMotion* e=(GdkEventMotion*)event;
		x = (guint)e->x;
		y = (guint)e->y;
		gint xn = (gint) x - iWindowx;
		gint yn = (gint) y - iWindowy;
		if (!boLine) snprintf(label, MAX_LEN, "Coordinates: (%.1f mm,%.1f mm)", (float)xn / fPPMM - 20.0 , 215.0 - (float)yn / fPPMM );
		if ((boLine) && (iInputs == 0)) snprintf(label, MAX_LEN, "Line first point %.0f mm,%.0f mm", (float)xn / fPPMM - 20.0 , 215.0 - (float)yn / fPPMM );
		if ((boLine) && (iInputs == 1)) 
		{
			iDrawx1 = (gint)((float)xn / fPPMM - 20.0); 
			iDrawy1 = (gint)(215.0 - (float)yn / fPPMM);
			snprintf(label, MAX_LEN, "Line second point %.0f mm,%.0f mm or Ctrl+click first point", (float)xn / fPPMM - 20.0 , 215.0 - (float)yn / fPPMM );
		}
		if ((boLine) && (iInputs == 2)) 
		{	
			boLine = FALSE; 
			iInputs = 0; 
			gtk_button_set_image (GTK_BUTTON(bLine), icons.line0 );
			Pages[Pages[0] + 1] = 6;
			Pages[Pages[0] + 2] = (guint)iDrawx0;
			Pages[Pages[0] + 3] = (guint)iDrawy0;
			Pages[Pages[0] + 4] = (guint)iDrawx1;
			Pages[Pages[0] + 5] = (guint)iDrawy1;
			Pages[0] = Pages[0] + 5;
			Undo[0]++;
			Undo[Undo[0]] = 5;
			Redo = 0;
		}
		gtk_widget_queue_draw(widget);
    }
	return FALSE;
}

void Selectcolor(guint iOld,guint iNew)
{  
	gtk_button_set_image(GTK_BUTTON(bColor), icons.color0 );
	Pages[Pages[0] + 1] = 5;
	Pages[Pages[0] + 2] = (guint)iOld;
	Pages[Pages[0] + 3] = (guint)iNew;
	Pages[0] = Pages[0] + 3;
	Undo[0]++;
	Undo[Undo[0]] = 3;
	Redo = 0;
}		

static gboolean button_pressed(GtkWidget *widget, GdkEventButton *event, gpointer user_data) 
{
	gint xn = (gint) event->x - iWindowx;
	gint yn = (gint) event->y - iWindowy;                               
    if ((event->type == GDK_BUTTON_PRESS) && !(event->state == GDK_CONTROL_MASK)) 
	{
		g_print("Click (%.1f mm,%.1f mm)\n", (float)xn / fPPMM - 20.0 , 215.0 - (float)yn / fPPMM);
		if ((boLine) && (iInputs == 1)) {iDrawx1 = (gint)((float)xn / fPPMM - 20.0); iDrawy1 = (gint)(215.0 - (float)yn / fPPMM); iInputs = 2;}
		if ((boLine) && (iInputs == 0)) {iDrawx0 = (gint)((float)xn / fPPMM - 20.0); iDrawy0 = (gint)(215.0 - (float)yn / fPPMM); iInputs = 1;}
	}
	if ((event->type == GDK_BUTTON_PRESS) && (event->state == GDK_CONTROL_MASK)) g_print("Control - Click (%.1f mm,%.1f mm)\n", (float)xn / fPPMM - 20.0 , 215.0 - (float)yn / fPPMM); 	
	if (event->type == GDK_2BUTTON_PRESS) g_print("Doubleclick (%.1f mm,%.1f mm)\n", (float)xn / fPPMM - 20.0 , 215.0 - (float)yn / fPPMM ); 
	return TRUE;
}
static gboolean button_released(GtkWidget *widget, GdkEventButton *event, gpointer user_data) 
{
    //g_print("Button Released\n");
	return TRUE;
}

static void do_drawing(cairo_t *Cairo)
{	
	cairo_set_source_rgb(Cairo, 0, 0, 0);
	cairo_text_extents_t extents1, extents2, extents3;
	// rectangle 
	cairo_set_line_width (Cairo, 0.2 * MMPT ); //0.2 mm linewidth
	cairo_move_to(Cairo, (20.0 * fPPMM), (5.0 * fPPMM));
	cairo_line_to(Cairo, (20.0 * fPPMM), (5.0 * fPPMM) + (210.0 * fPPMM) );
	cairo_move_to(Cairo, (20.0 * fPPMM), (5.0 * fPPMM) + (210.0 * fPPMM) );
	cairo_line_to(Cairo, (20.0 * fPPMM) + (297.0 * fPPMM) , (5.0 * fPPMM) + (210.0 * fPPMM) );
	cairo_move_to(Cairo, (20.0 * fPPMM), (5.0 * fPPMM));
	cairo_line_to(Cairo, (20.0 * fPPMM) + (297.0 * fPPMM) , (5.0 * fPPMM));
	cairo_move_to(Cairo, (20.0 * fPPMM) + (297.0 * fPPMM) , (5.0 * fPPMM));
	cairo_line_to(Cairo, (20.0 * fPPMM) + (297.0 * fPPMM) , (5.0 * fPPMM) + (210.0 * fPPMM) );
	cairo_stroke(Cairo);
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
	cairo_move_to(Cairo, (20.0 * fPPMM) + (297.0 * fPPMM) - extents1.width - extents1.x_bearing, (215.0 * fPPMM) - extents1.height - extents1.y_bearing  );   
	cairo_show_text(Cairo, "A4 297 x 210 mm. Calibri 3 mm.");
	// textbox
	cairo_set_source_rgb(Cairo, 0, 0, 0);
	cairo_select_font_face (Cairo, "Calibri", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL); 
    cairo_set_font_size (Cairo, 3.0 * fPPMM / PXPT);
	cairo_text_extents(Cairo, label, &extents2);
	cairo_move_to(Cairo, (20.0 * fPPMM) + (297.0 * fPPMM) - extents2.width - extents2.x_bearing, (215.0 * fPPMM) - extents1.height - extents2.height - extents2.y_bearing  );   
	cairo_show_text(Cairo, label);  
	// nomius
	cairo_set_source_rgb(Cairo, 0, 0, 0);
	cairo_select_font_face (Cairo, "Calibri", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL); 
    cairo_set_font_size (Cairo, 3.0 * fPPMM / PXPT);
	for(int i = 0; i <= 29; i++)
	{
		cairo_move_to(Cairo, (20.0 - 2.0 + (float)i * 10.0) * fPPMM , 195 * fPPMM + 30.0 * fPPMM);
		int length = snprintf( NULL, 0, "%d", i );
		char* str = malloc( length + 1 );
		snprintf( str, length + 1, "%d", i );
		cairo_show_text(Cairo, str);
		free(str);
	}
	for(int i = 0; i <= 59; i++)
	{
		cairo_move_to(Cairo, (20.0 + (float)i * 5.0) * fPPMM, 195 * fPPMM + 20.0 * fPPMM);
		cairo_line_to(Cairo, (20.0 + (float)i * 5.0) * fPPMM, 195 * fPPMM + 25.0 * fPPMM);
	}
	for(int i = 0; i <= 297; i++)
	{
		cairo_move_to(Cairo, (20.0 + (float)i) * fPPMM, 195 * fPPMM + 20.0 * fPPMM);
		cairo_line_to(Cairo, (20.0 + (float)i) * fPPMM, 195 * fPPMM + 23.0 * fPPMM);
	}
	// nomius vertical
	cairo_set_source_rgb(Cairo, 0, 0, 0);
	cairo_select_font_face (Cairo, "Calibri", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL); 
    cairo_set_font_size (Cairo, 3.0 * fPPMM / PXPT);
	for(int i = 0; i <= 21; i++)
	{
		cairo_move_to(Cairo, 10.0 * fPPMM, (215.0 + 1.0 - (float)i * 10.0) * fPPMM );
		int length = snprintf( NULL, 0, "%d", i );
		char* str = malloc( length + 1 );
		snprintf( str, length + 1, "%d", i );
		cairo_show_text(Cairo, str);
		free(str);
	}
	for(int i = 0; i <= 42; i++)
	{
		cairo_move_to(Cairo, 20.0 * fPPMM, (215.0 - (float)i * 5.0) * fPPMM );
		cairo_line_to(Cairo, 15.0 * fPPMM, (215.0 - (float)i * 5.0) * fPPMM );
	}
	for(int i = 0; i <= 210; i++)
	{
		cairo_move_to(Cairo, 20.0 * fPPMM, (215.0 - (float)i) * fPPMM);
		cairo_line_to(Cairo, 17.0 * fPPMM, (215.0 - (float)i) * fPPMM);
	}
	cairo_stroke(Cairo);  
	// dash lines
	//cairo_set_source_rgba(Cairo, 0, 0, 0, 1);
	double dCenterline[] = {3.0 * fPPMM, 1.0 * fPPMM , 1.0 * fPPMM, 1.0 * fPPMM};
	int len1  = sizeof(dCenterline) / sizeof(dCenterline[0]);
	double dDashline[] = {3.0 * fPPMM };
	int len2  = sizeof(dDashline) / sizeof(dDashline[0]);
	double dContiuous[] = {1.0};
	//cairo_set_line_width(cr, 1.5);
	cairo_set_dash(Cairo, dCenterline, len1, 0);
	cairo_move_to(Cairo, 40 * fPPMM, 30 * fPPMM);  
	cairo_line_to(Cairo, 200 * fPPMM, 30 * fPPMM);
	cairo_stroke(Cairo);
	cairo_set_dash(Cairo, dDashline, len2, 0);
	cairo_move_to(Cairo, 40 * fPPMM, 50 * fPPMM);  
	cairo_line_to(Cairo, 200 * fPPMM, 50 * fPPMM);
	cairo_stroke(Cairo);
	cairo_set_dash(Cairo, dContiuous, 0, 0);
	cairo_move_to(Cairo, 40 * fPPMM, 70 * fPPMM);  
	cairo_line_to(Cairo, 200 * fPPMM, 70 * fPPMM);
	cairo_stroke(Cairo);  
	// finished drawing objects
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
			cairo_move_to(Cairo, (20.0 + (float)iDonex0) * fPPMM, (215.0 - (float)iDoney0) * fPPMM );
			cairo_line_to(Cairo, (20.0 + (float)iDonex1) * fPPMM, (215.0 - (float)iDoney1) * fPPMM );
			cairo_stroke(Cairo);
		}
		if (Pages[iCounter] == 5)
		{
			iDonex0 = (gint)Pages[iCounter + 2];
			iCounter = iCounter + 3;
			cairo_set_source_rgb(Cairo,(float)dxfcolor[4 * iDonex0 + 1], (float)dxfcolor[4 * iDonex0 + 2], (float)dxfcolor[4 * iDonex0 + 3]/255);
		}
	}
	// current drawing object
	if ((boLine) && (iInputs == 1)) 
	{
		cairo_move_to(Cairo, (20.0 + (float)iDrawx0) * fPPMM, (215.0 - (float)iDrawy0) * fPPMM );
		cairo_line_to(Cairo, (20.0 + (float)iDrawx1) * fPPMM, (215.0 - (float)iDrawy1) * fPPMM );
	}
	cairo_stroke(Cairo);
}

static void do_drawing2(cairo_t *Cairo, GtkWidget *widget)
{
	if (alpha < 1.0 ) alpha = alpha + 0.01;
	cairo_set_source_rgba(Cairo, 1.0, 1.0, 1.0, alpha);
	cairo_set_operator(Cairo, CAIRO_OPERATOR_SOURCE);
	cairo_paint(Cairo);
	cairo_set_source_rgba(Cairo, 0.0, 0.0, 1.0, alpha);
		
	int milli_seconds = 10;
	clock_t start_time = clock();
	while (clock() < start_time + milli_seconds);
	cairo_text_extents_t extents1, extents2, extents3;
	// rectangle 
	cairo_set_line_width (Cairo, 0.2 * MMPT ); //0.2 mm linewidth
	cairo_move_to(Cairo, (20.0 * fPPMM), (5.0 * fPPMM));
	cairo_line_to(Cairo, (20.0 * fPPMM), (5.0 * fPPMM) + (210.0 * fPPMM) );
	cairo_move_to(Cairo, (20.0 * fPPMM), (5.0 * fPPMM) + (210.0 * fPPMM) );
	cairo_line_to(Cairo, (20.0 * fPPMM) + (297.0 * fPPMM) , (5.0 * fPPMM) + (210.0 * fPPMM) );
	cairo_move_to(Cairo, (20.0 * fPPMM), (5.0 * fPPMM));
	cairo_line_to(Cairo, (20.0 * fPPMM) + (297.0 * fPPMM) , (5.0 * fPPMM));
	cairo_move_to(Cairo, (20.0 * fPPMM) + (297.0 * fPPMM) , (5.0 * fPPMM));
	cairo_line_to(Cairo, (20.0 * fPPMM) + (297.0 * fPPMM) , (5.0 * fPPMM) + (210.0 * fPPMM) );
	cairo_stroke(Cairo);
	cairo_select_font_face(Cairo, "Calibri", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
	cairo_set_font_size(Cairo, 3.0 * fPPMM / PXPT);
	cairo_text_extents(Cairo, "A4 297 x 210 mm. Calibri 3 mm.", &extents1);
	cairo_move_to(Cairo, (20.0 * fPPMM) + (297.0 * fPPMM) - extents1.width - extents1.x_bearing, (215.0 * fPPMM) - extents1.height - extents1.y_bearing  );   
	cairo_show_text(Cairo, "A4 297 x 210 mm. Calibri 3 mm.");
	// textbox
	cairo_select_font_face (Cairo, "Calibri", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL); 
	cairo_set_font_size (Cairo, 3.0 * fPPMM / PXPT);
	cairo_text_extents(Cairo, label, &extents2);
	cairo_move_to(Cairo, (20.0 * fPPMM) + (297.0 * fPPMM) - extents2.width - extents2.x_bearing, (215.0 * fPPMM) - extents1.height - extents2.height - extents2.y_bearing  );   
	cairo_show_text(Cairo, label);  
	// nomius
	cairo_select_font_face (Cairo, "Calibri", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL); 
	cairo_set_font_size (Cairo, 3.0 * fPPMM / PXPT);
	for(int i = 0; i <= 29; i++)
	{
		cairo_move_to(Cairo, (20.0 - 2.0 + (float)i * 10.0) * fPPMM , 195 * fPPMM + 30.0 * fPPMM);
		int length = snprintf( NULL, 0, "%d", i );
		char* str = malloc( length + 1 );
		snprintf( str, length + 1, "%d", i );
		cairo_show_text(Cairo, str);
		free(str);
	}
	for(int i = 0; i <= 59; i++)
	{
		cairo_move_to(Cairo, (20.0 + (float)i * 5.0) * fPPMM, 195 * fPPMM + 20.0 * fPPMM);
		cairo_line_to(Cairo, (20.0 + (float)i * 5.0) * fPPMM, 195 * fPPMM + 25.0 * fPPMM);
	}
	for(int i = 0; i <= 297; i++)
	{
		cairo_move_to(Cairo, (20.0 + (float)i) * fPPMM, 195 * fPPMM + 20.0 * fPPMM);
		cairo_line_to(Cairo, (20.0 + (float)i) * fPPMM, 195 * fPPMM + 23.0 * fPPMM);
	}
	// nomius vertical
	cairo_select_font_face (Cairo, "Calibri", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL); 
	cairo_set_font_size (Cairo, 3.0 * fPPMM / PXPT);
	for(int i = 0; i <= 21; i++)
	{
		cairo_move_to(Cairo, 0 * fPPMM + 10.0 * fPPMM, (215.0 + 1.0 - (float)i * 10.0) * fPPMM );
		int length = snprintf( NULL, 0, "%d", i );
		char* str = malloc( length + 1 );
		snprintf( str, length + 1, "%d", i );
		cairo_show_text(Cairo, str);
		free(str);
	}
	for(int i = 0; i <= 42; i++)
	{
		cairo_move_to(Cairo, 0 * fPPMM + 20.0 * fPPMM, (215.0 - (float)i * 5.0) * fPPMM );
		cairo_line_to(Cairo, 0 * fPPMM + 15.0 * fPPMM, (215.0 - (float)i * 5.0) * fPPMM );
	}
	for(int i = 0; i <= 210; i++)
	{
		cairo_move_to(Cairo, 0 * fPPMM + 20.0 * fPPMM, (215.0 - (float)i) * fPPMM);
		cairo_line_to(Cairo, 0 * fPPMM + 17.0 * fPPMM, (215.0 - (float)i) * fPPMM);
	}
	cairo_stroke(Cairo);
	gtk_widget_queue_draw(widget);
}

int hidecairo(GtkWidget *cairowindow)
{
	gtk_widget_hide (cairowindow);
	return 0;
}

int showcairo(GtkWidget *cairowindow)
{
	gtk_widget_show_all (cairowindow);
	return 0;
}

int animate(GtkWidget *cairowindow)
{
	tran_setup(cairowindow); 
	bTransparency = TRUE;
	alpha = 0.0;
	g_print("Animate");
	gtk_widget_queue_draw(cairowindow);
	return 0;
}


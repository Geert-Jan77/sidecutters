#include <cairo.h>
#include <gtk/gtk.h>
#include <stdlib.h>
#define MMPT 2.834646f      // 2.83 mm = 1 pt
#define PTPX 0.75f          // 0.75 pt = 1 px

char label[MAX_LEN ];
int x, y = 0;  
static void do_drawing(cairo_t *);
static void do_drawing2(cairo_t *, GtkWidget *);
int hidecairo();
int showcairo();
gboolean bTransparency = FALSE;
gboolean bMarker1 = FALSE;
float alpha = 0.0;
gint iWindowx, iWindowy;
float fPPMM;               // Monitor resolution, platform dependent
float fScreensize;         // Monitor size in inches, platform dependent
float fScalefont;          // Font scaling, platform dependent


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
		int j1 = snprintf(label, MAX_LEN, "Coordinates: (%.1f mm,%.1f mm)", (float)xn / fPPMM - 20.0 , 215.0 - (float)yn / fPPMM );
		gtk_widget_queue_draw(widget);
    }
	return FALSE;
}

static gboolean button_pressed(GtkWidget *widget, GdkEventButton *event, gpointer user_data) 
{
	gint xn = (gint) event->x - iWindowx;
	gint yn = (gint) event->y - iWindowy;                               
    if ((event->type == GDK_BUTTON_PRESS) && !(event->state == GDK_CONTROL_MASK)) g_print("Click (%.1f mm,%.1f mm)\n", (float)xn / fPPMM - 20.0 , 215.0 - (float)yn / fPPMM); 
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
    cairo_set_font_size(Cairo, 3.0 * fPPMM / PTPX);
	cairo_text_extents(Cairo, "A4 297 x 210 mm. Calibri 3 mm.", &extents1);
    if (!bMarker1) g_print("Target font height %f mm Realised fontheight %f mm\n", 3.0, extents1.height /fPPMM );
    fScalefont = 3.0 * fPPMM / extents1.height;
	if (!bMarker1) {g_print("Font Scaling %.2f \n", fScalefont); bMarker1=TRUE;}
    cairo_set_font_size(Cairo, 3.0 * fPPMM / PTPX);
	cairo_text_extents(Cairo, "A4 297 x 210 mm. Calibri 3 mm.", &extents1);
	cairo_move_to(Cairo, (20.0 * fPPMM) + (297.0 * fPPMM) - extents1.width - extents1.x_bearing, (215.0 * fPPMM) - extents1.height - extents1.y_bearing  );   
	cairo_show_text(Cairo, "A4 297 x 210 mm. Calibri 3 mm.");
	// textbox
	cairo_set_source_rgb(Cairo, 0, 0, 0);
	cairo_select_font_face (Cairo, "Calibri", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL); 
    cairo_set_font_size (Cairo, 3.0 * fPPMM / PTPX);
	cairo_text_extents(Cairo, label, &extents2);
	cairo_move_to(Cairo, (20.0 * fPPMM) + (297.0 * fPPMM) - extents2.width - extents2.x_bearing, (215.0 * fPPMM) - extents1.height - extents2.height - extents2.y_bearing  );   
	cairo_show_text(Cairo, label);  
	// nomius
	cairo_set_source_rgb(Cairo, 0, 0, 0);
	cairo_select_font_face (Cairo, "Calibri", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL); 
    cairo_set_font_size (Cairo, 3.0 * fPPMM / PTPX);
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
    cairo_set_font_size (Cairo, 3.0 * fPPMM / PTPX);
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
	cairo_set_font_size(Cairo, 3.0 * fPPMM / PTPX);
	cairo_text_extents(Cairo, "A4 297 x 210 mm. Calibri 3 mm.", &extents1);
	cairo_move_to(Cairo, (20.0 * fPPMM) + (297.0 * fPPMM) - extents1.width - extents1.x_bearing, (215.0 * fPPMM) - extents1.height - extents1.y_bearing  );   
	cairo_show_text(Cairo, "A4 297 x 210 mm. Calibri 3 mm.");
	// textbox
	cairo_select_font_face (Cairo, "Calibri", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL); 
	cairo_set_font_size (Cairo, 3.0 * fPPMM / PTPX);
	cairo_text_extents(Cairo, label, &extents2);
	cairo_move_to(Cairo, (20.0 * fPPMM) + (297.0 * fPPMM) - extents2.width - extents2.x_bearing, (215.0 * fPPMM) - extents1.height - extents2.height - extents2.y_bearing  );   
	cairo_show_text(Cairo, label);  
	// nomius
	cairo_select_font_face (Cairo, "Calibri", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL); 
	cairo_set_font_size (Cairo, 3.0 * fPPMM / PTPX);
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
	cairo_set_font_size (Cairo, 3.0 * fPPMM / PTPX);
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


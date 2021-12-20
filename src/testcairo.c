#include <cairo.h>
#include <gtk/gtk.h>
#include <stdlib.h>
#define MM 2.834646f        // 1 pt = 2.83 mm
#define PPMM 3.55f          // Monitor resolution  
#define FSCALE 1.33333f     // Fontscaling
#define RDH -0.125f         // Relative Descender Height
char label[MAX_LEN ];
int x, y = 0;  
static void do_drawing(cairo_t *);
static void do_drawing2(cairo_t *);
GtkWidget *window2;

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
	do_drawing(Cairo);
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
		int j1 = snprintf(label, MAX_LEN, "Coordinates: (%u,%u)", x, y);
		gtk_widget_queue_draw(widget);
    }
	return FALSE;
}

static void do_drawing(cairo_t *Cairo)
{	
	// rectangle 
	cairo_set_line_width (Cairo, 0.2 * MM ); //0.2 mm linewidth
	cairo_move_to(Cairo, 0.0, 0.0);
	cairo_line_to(Cairo, 100.0, 0.0);
	cairo_move_to(Cairo, 0.0, 0.0);
	cairo_line_to(Cairo, 0.0, 100.0);
	cairo_move_to(Cairo, (5.0 * PPMM), (5.0 * PPMM));
	cairo_line_to(Cairo, (5.0 * PPMM), (5.0 * PPMM) + (210.0 * PPMM) );
	cairo_move_to(Cairo, (5.0 * PPMM), (5.0 * PPMM) + (210.0 * PPMM) );
	cairo_line_to(Cairo, (5.0 * PPMM) + (297.0 * PPMM) , (5.0 * PPMM) + (210.0 * PPMM) );
	cairo_move_to(Cairo, (5.0 * PPMM), (5.0 * PPMM));
	cairo_line_to(Cairo, (5.0 * PPMM) + (297.0 * PPMM) , (5.0 * PPMM));
	cairo_move_to(Cairo, (5.0 * PPMM) + (297.0 * PPMM) , (5.0 * PPMM));
	cairo_line_to(Cairo, (5.0 * PPMM) + (297.0 * PPMM) , (5.0 * PPMM) + (210.0 * PPMM) );
	cairo_stroke(Cairo);
	
	// textbox
	cairo_set_source_rgb(Cairo, 0, 0, 0);
	cairo_select_font_face (Cairo, "Calibri", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL); 
	//cairo_set_font_size (cr, 200 * FSCALE * MM);
	//cairo_move_to(cr, (5.0 * PPMM) , 200 * FSCALE * RDH * PPMM + (210.0 * PPMM)); // todo : calculate width
	//cairo_show_text(cr, "[|]");  
	cairo_set_font_size (Cairo, 4.0 * FSCALE * MM);
	cairo_move_to(Cairo,  (-49.0 * PPMM) + (297.0 * PPMM) , 4.0 * FSCALE * RDH * PPMM + (215.0 * PPMM)); 
	cairo_show_text(Cairo, "A4 297 x 210 mm. Calibri 4mm.");  
	
	// textbox
	cairo_set_source_rgb(Cairo, 0, 0, 0);
	cairo_select_font_face (Cairo, "Calibri", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL); 
	cairo_set_font_size (Cairo, 4.0 * FSCALE * MM);
	cairo_move_to(Cairo,  (-49.0 * PPMM) + (297.0 * PPMM) , 4.0 * FSCALE * RDH * PPMM + (210.0 * PPMM)); 
	cairo_show_text(Cairo, label);  
	
	// nomius
	cairo_set_source_rgb(Cairo, 0, 0, 0);
	cairo_select_font_face (Cairo, "Calibri", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL); 
	cairo_set_font_size (Cairo, 4.0 * FSCALE * MM);
	for(int i = 0; i <= 25; i++)
	{
		cairo_move_to(Cairo, (28.0 - 2.0 + (float)i * 10.0) * PPMM , 4.0 * FSCALE * RDH * PPMM  + (30.0 * PPMM));
		int length = snprintf( NULL, 0, "%d", i );
		char* str = malloc( length + 1 );
		snprintf( str, length + 1, "%d", i );
		cairo_show_text(Cairo, str);
		free(str);
	}
	for(int i = 0; i <= 50; i++)
	{
		cairo_move_to(Cairo, (28.0 + (float)i * 5.0) * PPMM, 20.0 * PPMM);
		cairo_line_to(Cairo, (28.0 + (float)i * 5.0) * PPMM, 25.0 * PPMM);
	}
	for(int i = 0; i <= 250; i++)
	{
		cairo_move_to(Cairo, (28.0 + (float)i) * PPMM, 20.0 * PPMM);
		cairo_line_to(Cairo, (28.0 + (float)i) * PPMM, 23.0 * PPMM);
	}
	cairo_stroke(Cairo);
}

static void do_drawing2(cairo_t *Cairo)
{
	cairo_set_source_rgba(Cairo, 1.0, 1.0, 1.0, 0.4);
	cairo_set_operator(Cairo, CAIRO_OPERATOR_SOURCE);
	cairo_paint(Cairo);
}

int testcairo(int iCairox, int iCairoy)
{
	//GtkWidget *window2;
	GtkWidget *darea;
	window2 = gtk_window_new(GTK_WINDOW_POPUP );
	GdkRectangle workarea = {0 };
	gdk_monitor_get_workarea(gdk_display_get_primary_monitor(gdk_display_get_default()), &workarea );
	//tran_setup(window2); //Transparency -> no coordinates are shown. 
	darea = gtk_drawing_area_new();
	gtk_container_add(GTK_CONTAINER(window2), darea);
	g_signal_connect(G_OBJECT(darea), "draw", G_CALLBACK(on_draw_event), NULL);
	g_signal_connect(G_OBJECT(darea), "motion-notify-event", G_CALLBACK (mouse_moved), NULL);
	gtk_widget_set_events(darea, GDK_POINTER_MOTION_MASK);
	GdkGeometry windowProperties;
	windowProperties.min_width = workarea.width - 140;
	windowProperties.min_height = workarea.height - 200;
	windowProperties.max_width = workarea.width;
	windowProperties.max_height = workarea.height;
	gtk_window_set_geometry_hints(GTK_WINDOW(window2), NULL, &windowProperties, GDK_HINT_MIN_SIZE | GDK_HINT_MAX_SIZE);
	//gtk_window_set_default_size (GTK_WINDOW (window), workarea.width - 20, workarea.height - 20 );	
	gtk_window_set_default_size (GTK_WINDOW (window2), workarea.width - 112 - 8, workarea.height - 154 );
	//gtk_window_move (GTK_WINDOW(window2), 112, 54);
	gtk_window_move (GTK_WINDOW(window2), iCairox, iCairoy);
	gtk_widget_show_all(window2);
	return 0;
}
int hidecairo()
{
	g_print("Hide Cairo\n");
	gtk_widget_hide (window2);
	return 0;
}

int showcairo()
{
	g_print("Show Cairo\n");
	gtk_widget_show_all (window2);
	return 0;
}


int animate()
{
	g_print("Animate");
	//change tranperancy
	return 0;
}


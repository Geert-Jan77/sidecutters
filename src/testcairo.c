#include <cairo.h>
#include <gtk/gtk.h>
#include <stdlib.h>
#define MM 2.834646f        // 1 pt = 2.83 mm
#define PPMM 3.55f          // Monitor resolution, platform dependent
#define FSCALE 1.426024f    // Fontscaling

char label[MAX_LEN ];
int x, y = 0;  
static void do_drawing(cairo_t *);
static void do_drawing2(cairo_t *);
int hidecairo();
int showcairo();
gboolean bTransparency = FALSE;
float alpha = 0.0;
gint iWindowx, iWindowy;

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
	if (bTransparency) do_drawing2(Cairo);
	if (!bTransparency) do_drawing(Cairo);
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
		int j1 = snprintf(label, MAX_LEN, "Coordinates: (%.1f mm,%.1f mm)", (float)xn / PPMM - 5.0 , 215.0 - (float)yn / PPMM );
		gtk_widget_queue_draw(widget);
    }
	return FALSE;
}

static void do_drawing(cairo_t *Cairo)
{	
	cairo_text_extents_t extents1, extents2, extents3;
	/*
	double x_bearing; the horizontal distance from the origin to the leftmost part of the glyphs as drawn. Positive if the glyphs lie entirely to the right of the origin.
	double y_bearing; the vertical distance from the origin to the topmost part of the glyphs as drawn. Positive only if the glyphs lie completely below the origin; will usually be negative.
	double width; width of the glyphs as drawn
	double height; height of the glyphs as drawn
	double x_advance; distance to advance in the X direction after drawing these glyphs
	double y_advance; distance to advance in the Y direction after drawing these glyphs. Will typically be zero except for vertical text layout as found in East-Asian languages.
	*/
	
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
	cairo_select_font_face(Cairo, "Calibri", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
	cairo_set_font_size(Cairo, 4.0 * FSCALE * MM);
	cairo_text_extents(Cairo, "A4 297 x 210 mm. Calibri 4mm.", &extents1);
	cairo_move_to(Cairo, (5.0 * PPMM) + (297.0 * PPMM) - extents1.width - extents1.x_bearing, (215.0 * PPMM) - extents1.height - extents1.y_bearing  );  
	cairo_show_text(Cairo, "A4 297 x 210 mm. Calibri 4mm.");    
	
	//cairo_set_font_size (Cairo, 200 * FSCALE * MM);
	//cairo_text_extents(Cairo, "[|]", &extents3);
	//g_print("Target font height %f Realised fontheight %f\n", 200.0, extents3.height / PPMM);
	//cairo_move_to(Cairo, (5.0 * PPMM) + (297.0 * PPMM) - extents3.width - extents3.x_bearing, (215.0 * PPMM) - extents3.height - extents3.y_bearing );   
	//cairo_show_text(Cairo, "[|]");  
	
	// textbox
	cairo_set_source_rgb(Cairo, 0, 0, 0);
	cairo_select_font_face (Cairo, "Calibri", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL); 
	cairo_set_font_size (Cairo, 4.0 * FSCALE * MM);
	cairo_text_extents(Cairo, label, &extents2);
	cairo_move_to(Cairo, (5.0 * PPMM) + (297.0 * PPMM) - extents2.width - extents2.x_bearing, (215.0 * PPMM) - extents1.height - extents2.height - extents2.y_bearing  );   
	cairo_show_text(Cairo, label);  
	
	// nomius
	cairo_set_source_rgb(Cairo, 0, 0, 0);
	cairo_select_font_face (Cairo, "Calibri", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL); 
	cairo_set_font_size (Cairo, 4.0 * FSCALE * MM);
	for(int i = 0; i <= 25; i++)
	{
		cairo_move_to(Cairo, (28.0 - 2.0 + (float)i * 10.0) * PPMM , 30.0 * PPMM);
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
	cairo_text_extents_t extents1, extents2, extents3;
	/*
	double x_bearing; the horizontal distance from the origin to the leftmost part of the glyphs as drawn. Positive if the glyphs lie entirely to the right of the origin.
	double y_bearing; the vertical distance from the origin to the topmost part of the glyphs as drawn. Positive only if the glyphs lie completely below the origin; will usually be negative.
	double width; width of the glyphs as drawn
	double height; height of the glyphs as drawn
	double x_advance; distance to advance in the X direction after drawing these glyphs
	double y_advance; distance to advance in the Y direction after drawing these glyphs. Will typically be zero except for vertical text layout as found in East-Asian languages.
	*/
	
	if (alpha < 1.0 ) alpha = alpha + 0.01;
	
	cairo_set_source_rgba(Cairo, 1.0, 1.0, 1.0, alpha);
	cairo_set_operator(Cairo, CAIRO_OPERATOR_SOURCE);
	cairo_paint(Cairo);
	cairo_set_source_rgba(Cairo, 0.0, 0.0, 1.0, alpha);
	
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
	cairo_set_source_rgba(Cairo, 0.0, 0.0, 1.0, alpha);
	cairo_select_font_face(Cairo, "Calibri", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
	cairo_set_font_size(Cairo, 4.0 * FSCALE * MM);
	cairo_text_extents(Cairo, "A4 297 x 210 mm. Calibri 4mm.", &extents1);
	cairo_move_to(Cairo, (5.0 * PPMM) + (297.0 * PPMM) - extents1.width - extents1.x_bearing, (215.0 * PPMM) - extents1.height - extents1.y_bearing  );   
	cairo_show_text(Cairo, "A4 297 x 210 mm. Calibri 4mm.");    
	
	//cairo_set_font_size (Cairo, 200 * FSCALE * MM);
	//cairo_text_extents(Cairo, "[|]", &extents3);
	//g_print("Target font height %f Realised fontheight %f\n", 200.0, extents3.height / PPMM);
	//cairo_move_to(Cairo, (5.0 * PPMM) + (297.0 * PPMM) - extents3.width - extents3.x_bearing, (215.0 * PPMM) - extents3.height - extents3.y_bearing );   
	//cairo_show_text(Cairo, "[|]");  
	
	// textbox
	cairo_set_source_rgba(Cairo, 0.0, 0.0, 1.0, alpha);
	cairo_select_font_face (Cairo, "Calibri", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL); 
	cairo_set_font_size (Cairo, 4.0 * FSCALE * MM);
	cairo_text_extents(Cairo, label, &extents2);
	cairo_move_to(Cairo, (5.0 * PPMM) + (297.0 * PPMM) - extents2.width - extents2.x_bearing, (215.0 * PPMM) - extents1.height - extents2.height - extents2.y_bearing  );   
	cairo_show_text(Cairo, label);  
	
	// nomius
	cairo_set_source_rgba(Cairo, 0.0, 0.0, 1.0, alpha);
	cairo_select_font_face (Cairo, "Calibri", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL); 
	cairo_set_font_size (Cairo, 4.0 * FSCALE * MM);
	for(int i = 0; i <= 25; i++)
	{
		cairo_move_to(Cairo, (28.0 - 2.0 + (float)i * 10.0) * PPMM , 30.0 * PPMM);
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
	alpha = 0.0;
	gtk_widget_queue_draw(cairowindow);
	g_print("Animate");
	//change tranperancy
	bTransparency=TRUE;
	tran_setup(cairowindow); //Transparency -> no coordinates are shown. 
	return 0;
}


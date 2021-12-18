#include <cairo.h>
#include <gtk/gtk.h>
#include <stdlib.h>
#define MM 2.834646f        // 1 pt = 2.83 mm
#define PPMM 3.55f          // Monitor resolution  
#define FSCALE 1.33333f     // Fontscaling
#define RDH -0.125f         // Relative Descender Height

static void do_drawing(cairo_t *);

static gboolean on_draw_event(GtkWidget *widget, cairo_t *cr, gpointer user_data)
{      
	do_drawing(cr);
	return FALSE;
}

static void do_drawing(cairo_t *cr)
{
	// textbox
	cairo_set_source_rgb(cr, 0, 0, 0);
	cairo_select_font_face (cr, "Calibri", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL); 
	//cairo_set_font_size (cr, 200 * FSCALE * MM);
	//cairo_move_to(cr, (5.0 * PPMM) , 200 * FSCALE * RDH * PPMM + (210.0 * PPMM)); // todo : calculate width
	//cairo_show_text(cr, "[|]");  
	cairo_set_font_size (cr, 4.0 * FSCALE * MM);
	cairo_move_to(cr,  (-49.0 * PPMM) + (297.0 * PPMM) , 4.0 * FSCALE * RDH * PPMM + (215.0 * PPMM)); // todo : calculate width
	cairo_show_text(cr, "A4 297 x 210 mm. Calibri 4mm.");  
	cairo_set_line_width (cr, 0.2 * MM ); //0.2 mm linewidth
	cairo_move_to(cr, 0.0, 0.0);
	cairo_line_to(cr, 100.0, 0.0);
	cairo_move_to(cr, 0.0, 0.0);
	cairo_line_to(cr, 0.0, 100.0);
	cairo_move_to(cr, (5.0 * PPMM), (5.0 * PPMM));
	cairo_line_to(cr, (5.0 * PPMM), (5.0 * PPMM) + (210.0 * PPMM) );
	cairo_move_to(cr, (5.0 * PPMM), (5.0 * PPMM) + (210.0 * PPMM) );
	cairo_line_to(cr, (5.0 * PPMM) + (297.0 * PPMM) , (5.0 * PPMM) + (210.0 * PPMM) );
	cairo_move_to(cr, (5.0 * PPMM), (5.0 * PPMM));
	cairo_line_to(cr, (5.0 * PPMM) + (297.0 * PPMM) , (5.0 * PPMM));
	cairo_move_to(cr, (5.0 * PPMM) + (297.0 * PPMM) , (5.0 * PPMM));
	cairo_line_to(cr, (5.0 * PPMM) + (297.0 * PPMM) , (5.0 * PPMM) + (210.0 * PPMM) );
	cairo_stroke(cr);
	// nomius
	cairo_set_source_rgb(cr, 0, 0, 0);
	cairo_select_font_face (cr, "Calibri", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL); 
	cairo_set_font_size (cr, 4.0 * FSCALE * MM);
	for(int i = 0; i <= 25; i++)
	{
		// Draw cm text
		cairo_move_to(cr, (28.0 - 2.0 + (float)i * 10.0) * PPMM , 4.0 * FSCALE * RDH * PPMM  + (30.0 * PPMM));
		int length = snprintf( NULL, 0, "%d", i );
		char* str = malloc( length + 1 );
		snprintf( str, length + 1, "%d", i );
		cairo_show_text(cr, str);
		free(str);
	}
	for(int i = 0; i <= 50; i++)
	{
		// Draw 5mm lines
		cairo_move_to(cr, (28.0 + (float)i * 5.0) * PPMM, 20.0 * PPMM);
		cairo_line_to(cr, (28.0 + (float)i * 5.0) * PPMM, 25.0 * PPMM);
	}
	for(int i = 0; i <= 250; i++)
	{
		// Draw 1mm lines
		cairo_move_to(cr, (28.0 + (float)i) * PPMM, 20.0 * PPMM);
		cairo_line_to(cr, (28.0 + (float)i) * PPMM, 23.0 * PPMM);
	}
	cairo_stroke(cr);
	
}
int testcairo()
//int testcairo(int argc, char *argv[])
{

	GtkWidget *window2;
	//GdkPixbuf *icon;
	GtkWidget *darea;
	//gtk_init(&argc, &argv );
	window2 = gtk_window_new(GTK_WINDOW_POPUP );
	GdkRectangle workarea = {0 };
	gdk_monitor_get_workarea(gdk_display_get_primary_monitor(gdk_display_get_default()), &workarea );
	darea = gtk_drawing_area_new();
	gtk_container_add(GTK_CONTAINER(window2), darea);
	g_signal_connect(G_OBJECT(darea), "draw", G_CALLBACK(on_draw_event), NULL); 
	//g_signal_connect(window2, "destroy", G_CALLBACK(gtk_main_quit), NULL);
	
	gtk_window_set_default_size (GTK_WINDOW (window2), workarea.width - 112 - 8, workarea.height - 54 );
	gtk_window_move (GTK_WINDOW(window2), 112, 54);
	//gtk_window_set_title(GTK_WINDOW(window2), "Side Cutters Drawing" );
	gtk_widget_show_all(window2);
	
	//gtk_main();
	
	return 0;
}
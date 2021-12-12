/*
-----------------------------------------------------------------------------------------
 testpdf performs an export of a bookmarked printable data file. 
 
 To compile:

     gcc src/test/testpdf.c -o testpdf.exe
	 
-----------------------------------------------------------------------------------------
*/
 
#include "pdf.h"
#include "pdf.c"
int main(int argc, char *argv[]) 
{
    struct pdf_info info = {.creator = "Side Cutter",
                            .producer = "Side Cutter",
                            .title = "Test printable data file export",
                            .author = "Side Cutter",
                            .subject = "Test printable data file export"};
    struct pdf_doc *pdf = pdf_create(PDF_A4_WIDTH, PDF_A4_HEIGHT, &info);
    int i;
    float height, width;
	float fontheight, textblockposition;
    int bm;
    int err;

    /* Unused */
    (void)argc;
    (void)argv;

    if (!pdf) {
        fprintf(stderr, "Unable to create PDF\n");
        return -1;
    }

    if (pdf_width(pdf) != PDF_A4_WIDTH || pdf_height(pdf) != PDF_A4_HEIGHT) {
        fprintf(stderr, "PDF Size mismatch: %fx%f\n", pdf_width(pdf),
                pdf_height(pdf));
        return -1;
    }

    err = pdf_get_font_text_width(pdf, "Times-BoldItalic", "foo", 14, &width);
    if (err < 0 || width < 18) {
        fprintf(stderr, "Font width invalid: %d/%f\n", err, width);
        return -1;
    }

    if (!pdf_get_err(pdf, &err))
        return -1;

    pdf_clear_err(pdf);
    /* From now on, we shouldn't see any errors */
    /*
	for (i = 65; i < 92; i++) 
	{
        float xpos = (i / 100) * 40.0f;
        float ypos = (i % 100) * 10.0f;
        //pdf_add_text(pdf, NULL, "Calibri width ", 8, xpos, ypos, PDF_RGB(i, (i * 4) & 0xff, (i * 8) & 0xff));
		printf("%d, ", times_widths[i]);
    }
	printf("Tilde width %d, ", calibri_widths[95]);
	printf("a width %d, ", calibri_widths[97]);
	printf("i width %d, ", calibri_widths[105]);
	*/
	
	pdf_append_page(pdf);
	pdf_add_bookmark(pdf, NULL, -1, "Page 1 Quadratic Bezier Curve");
	pdf_page_set_size(pdf, NULL, PDF_A4_HEIGHT, PDF_A4_WIDTH);
	pdf_set_font(pdf, "Calibri");
	pdf_add_text(pdf, NULL, "y = 20", 12, 50, 26, PDF_BLACK);
	pdf_add_line(pdf, NULL, 50, 20, 150, 20, 0.3, PDF_BLACK);
	pdf_add_circle(pdf, NULL, 500, 20, 2, 0.3, PDF_BLACK, PDF_WHITE); // x = 500 y = 20 radius 2 width 0.3
	pdf_add_text(pdf, NULL, "y = 200", 12, 50, 206, PDF_BLACK);
	pdf_add_line(pdf, NULL, 50, 200, 150, 200, 0.3, PDF_BLACK);
	pdf_add_circle(pdf, NULL, 250, 200, 2, 0.3, PDF_BLACK, PDF_WHITE);
	pdf_add_text(pdf, NULL, "y = 500", 12, 50, 506, PDF_BLACK);
    pdf_add_line(pdf, NULL, 50, 500, 150, 500, 0.3, PDF_BLACK);
	pdf_add_circle(pdf, NULL, 100, 500, 2, 0.3, PDF_BLACK, PDF_WHITE);
	pdf_add_quadratic_bezier(pdf, NULL, 500, 20, 250, 200, 100, 500, 0.3, PDF_BLACK);

    pdf_append_page(pdf);
	pdf_add_bookmark(pdf, NULL, -1, "Page 2 Cubic Bezier Curve");
	pdf_page_set_size(pdf, NULL, PDF_A4_HEIGHT, PDF_A4_WIDTH);
	pdf_set_font(pdf, "Calibri");
	pdf_add_text(pdf, NULL, "y = 20", 12, 50, 26, PDF_BLACK);
	pdf_add_line(pdf, NULL, 50, 20, 150, 20, 0.3, PDF_BLACK);
	pdf_add_circle(pdf, NULL, 500, 20, 2, 0.3, PDF_BLACK, PDF_WHITE); // x = 500 y = 20 radius 2 width 0.3
	pdf_add_text(pdf, NULL, "y = 120", 12, 50, 126, PDF_BLACK);
	pdf_add_line(pdf, NULL, 50, 120, 150, 120, 0.3, PDF_BLACK);
	pdf_add_circle(pdf, NULL, 400, 120, 2, 0.3, PDF_BLACK, PDF_WHITE); 
	pdf_add_text(pdf, NULL, "y = 200", 12, 50, 206, PDF_BLACK);
	pdf_add_line(pdf, NULL, 50, 200, 150, 200, 0.3, PDF_BLACK);
	pdf_add_circle(pdf, NULL, 250, 200, 2, 0.3, PDF_BLACK, PDF_WHITE);
	pdf_add_text(pdf, NULL, "y = 500", 12, 50, 506, PDF_BLACK);
    pdf_add_line(pdf, NULL, 50, 500, 150, 500, 0.3, PDF_BLACK);
	pdf_add_circle(pdf, NULL, 100, 500, 2, 0.3, PDF_BLACK, PDF_WHITE);
    pdf_add_cubic_bezier(pdf, NULL, 400, 120, 500, 20, 250, 200, 100, 500, 0.3, PDF_BLACK);
	
	pdf_append_page(pdf);
	pdf_add_bookmark(pdf, NULL, -1, "Page 3 Quadratic Bezier Curve");
	pdf_set_font(pdf, "Calibri");
	pdf_add_text(pdf, NULL, "y = 20", 12, 50, 26, PDF_BLACK);
	pdf_add_line(pdf, NULL, 50, 20, 150, 20, 0.3, PDF_BLACK);
	pdf_add_circle(pdf, NULL, 500, 20, 2, 0.3, PDF_BLACK, PDF_WHITE); // x = 500 y = 20 radius 2 width 0.3
	pdf_add_text(pdf, NULL, "y = 800", 12, 50, 806, PDF_BLACK);
	pdf_add_line(pdf, NULL, 50, 800, 150, 800, 0.3, PDF_BLACK);
	pdf_add_circle(pdf, NULL, 250, 800, 2, 0.3, PDF_BLACK, PDF_WHITE);
	pdf_add_text(pdf, NULL, "y = 500", 12, 50, 506, PDF_BLACK);
    pdf_add_line(pdf, NULL, 50, 500, 150, 500, 0.3, PDF_BLACK);
	pdf_add_circle(pdf, NULL, 100, 500, 2, 0.3, PDF_BLACK, PDF_WHITE);
	pdf_add_quadratic_bezier(pdf, NULL, 500, 20, 250, 800, 100, 500, 0.3, PDF_BLACK);

    pdf_append_page(pdf);
	bm = pdf_add_bookmark(pdf, NULL, -1, "Page 4");
	bm = pdf_add_bookmark(pdf, NULL, bm, "Bookmark menu");
    pdf_add_bookmark(pdf, NULL, bm, "Menu Item 1");
    pdf_add_bookmark(pdf, NULL, bm, "Menu Item 2");
    
    pdf_add_text(
        pdf, NULL,
        "the quick brown fox jumped over the lazy dog. "
        "THE QUICK BROWN FOX JUMPED OVER THE LAZY DOG. ",
        10, 100, 100, PDF_RGB(0, 0, 0));
    
    pdf_add_text(
        pdf, NULL,
        "the quick brown fox jumped over the lazy dog. "
        "THE QUICK BROWN FOX JUMPED OVER THE LAZY DOG. ",
        10, 100, 130, PDF_RGB(0, 0, 0));
    
    pdf_add_text(
        pdf, NULL,
        "the quick brown fox jumped over the lazy dog. "
        "THE QUICK BROWN FOX JUMPED OVER THE LAZY DOG. ",
        10, 100, 150, PDF_RGB(0, 0, 0));

	pdf_append_page(pdf);
	pdf_add_bookmark(pdf, NULL, -1, "Page 5 A3 landscape");
    pdf_page_set_size(pdf, NULL, PDF_A3_HEIGHT, PDF_A3_WIDTH);
    pdf_add_text(pdf, NULL, "A3 landscape", 10, 20, 30, PDF_RGB(0, 0, 0));
	
    pdf_append_page(pdf);
	pdf_add_bookmark(pdf, NULL, -1, "Page 6 A4 landscape");
    pdf_page_set_size(pdf, NULL, PDF_A4_HEIGHT, PDF_A4_WIDTH);
    pdf_add_text(pdf, NULL, "A4 landscape", 10, 20, 30, PDF_RGB(0, 0, 0));
    
	pdf_append_page(pdf);
	pdf_add_bookmark(pdf, NULL, -1, "Page 7 TextBoxes in all supported fonts");
	fontheight = 10;
	textblockposition = 800;
	pdf_set_font(pdf, "Calibri");
	pdf_add_text(pdf, NULL, "Calibri 10 pt.", fontheight, 50, textblockposition -  fontheight, PDF_BLACK);
	pdf_set_font(pdf, "Helvetica");
	pdf_add_text(pdf, NULL, "Helvetica", fontheight, 50, textblockposition - 2 * fontheight, PDF_BLACK);
	pdf_set_font(pdf, "Helvetica-Bold");
	pdf_add_text(pdf, NULL, "Helvetica Bold", fontheight, 50, textblockposition - 3 * fontheight, PDF_BLACK);
	pdf_set_font(pdf, "Helvetica-BoldOblique");
	pdf_add_text(pdf, NULL, "Helvetica Bold Oblique", fontheight, 50, textblockposition - 4 * fontheight, PDF_BLACK);
	pdf_set_font(pdf, "Helvetica-Oblique");
	pdf_add_text(pdf, NULL, "Helvetica Oblique", fontheight, 50, textblockposition - 5 * fontheight, PDF_BLACK);
	pdf_set_font(pdf, "Courier");
	pdf_add_text(pdf, NULL, "Courier New", fontheight, 50, textblockposition - 6 * fontheight, PDF_BLACK);
	pdf_set_font(pdf, "Courier-Bold");
	pdf_add_text(pdf, NULL, "Courier New Bold", fontheight, 50, textblockposition - 7 * fontheight, PDF_BLACK);
	pdf_set_font(pdf, "Courier-BoldOblique");
	pdf_add_text(pdf, NULL, "Courier New Bold Oblique", fontheight, 50, textblockposition - 8 * fontheight, PDF_BLACK);
	pdf_set_font(pdf, "Courier-Oblique");
	pdf_add_text(pdf, NULL, "Courier New Oblique", fontheight, 50, textblockposition - 9 * fontheight, PDF_BLACK);
	pdf_set_font(pdf, "Times-Roman");
	pdf_add_text(pdf, NULL, "Times New Roman", fontheight, 50, textblockposition - 10 * fontheight, PDF_BLACK);
	pdf_set_font(pdf, "Times-Bold");
	pdf_add_text(pdf, NULL, "Times New Roman Bold", fontheight, 50, textblockposition - 11 * fontheight, PDF_BLACK);
	pdf_set_font(pdf, "Times-Italic");
	pdf_add_text(pdf, NULL, "Times New Roman Italic", fontheight, 50, textblockposition - 12 * fontheight, PDF_BLACK);
	pdf_set_font(pdf, "Times-BoldItalic");
	pdf_add_text(pdf, NULL, "Times New Roman Bold Italic", fontheight, 50, textblockposition - 13 * fontheight, PDF_BLACK);
    
	fontheight = 12;
	textblockposition = 660;
	pdf_set_font(pdf, "Calibri");
	pdf_add_text(pdf, NULL, "Calibri 12 pt.", fontheight, 50, textblockposition -  fontheight, PDF_BLACK);
	pdf_set_font(pdf, "Helvetica");
	pdf_add_text(pdf, NULL, "Helvetica", fontheight, 50, textblockposition - 2 * fontheight, PDF_BLACK);
	pdf_set_font(pdf, "Helvetica-Bold");
	pdf_add_text(pdf, NULL, "Helvetica Bold", fontheight, 50, textblockposition - 3 * fontheight, PDF_BLACK);
	pdf_set_font(pdf, "Helvetica-BoldOblique");
	pdf_add_text(pdf, NULL, "Helvetica Bold Oblique", fontheight, 50, textblockposition - 4 * fontheight, PDF_BLACK);
	pdf_set_font(pdf, "Helvetica-Oblique");
	pdf_add_text(pdf, NULL, "Helvetica Oblique", fontheight, 50, textblockposition - 5 * fontheight, PDF_BLACK);
	pdf_set_font(pdf, "Courier");
	pdf_add_text(pdf, NULL, "Courier New", fontheight, 50, textblockposition - 6 * fontheight, PDF_BLACK);
	pdf_set_font(pdf, "Courier-Bold");
	pdf_add_text(pdf, NULL, "Courier New Bold", fontheight, 50, textblockposition - 7 * fontheight, PDF_BLACK);
	pdf_set_font(pdf, "Courier-BoldOblique");
	pdf_add_text(pdf, NULL, "Courier New Bold Oblique", fontheight, 50, textblockposition - 8 * fontheight, PDF_BLACK);
	pdf_set_font(pdf, "Courier-Oblique");
	pdf_add_text(pdf, NULL, "Courier New Oblique", fontheight, 50, textblockposition - 9 * fontheight, PDF_BLACK);
	pdf_set_font(pdf, "Times-Roman");
	pdf_add_text(pdf, NULL, "Times New Roman", fontheight, 50, textblockposition - 10 * fontheight, PDF_BLACK);
	pdf_set_font(pdf, "Times-Bold");
	pdf_add_text(pdf, NULL, "Times New Roman Bold", fontheight, 50, textblockposition - 11 * fontheight, PDF_BLACK);
	pdf_set_font(pdf, "Times-Italic");
	pdf_add_text(pdf, NULL, "Times New Roman Italic", fontheight, 50, textblockposition - 12 * fontheight, PDF_BLACK);
	pdf_set_font(pdf, "Times-BoldItalic");
	pdf_add_text(pdf, NULL, "Times New Roman Bold Italic", fontheight, 50, textblockposition - 13 * fontheight, PDF_BLACK);
	
	fontheight = 15.6;
	textblockposition = 492;
	pdf_set_font(pdf, "Calibri");
	pdf_add_text(pdf, NULL, "Calibri 15.6 pt.", fontheight, 50, textblockposition -  fontheight, PDF_BLACK);
	pdf_set_font(pdf, "Helvetica");
	pdf_add_text(pdf, NULL, "Helvetica", fontheight, 50, textblockposition - 2 * fontheight, PDF_BLACK);
	pdf_set_font(pdf, "Helvetica-Bold");
	pdf_add_text(pdf, NULL, "Helvetica Bold", fontheight, 50, textblockposition - 3 * fontheight, PDF_BLACK);
	pdf_set_font(pdf, "Helvetica-BoldOblique");
	pdf_add_text(pdf, NULL, "Helvetica Bold Oblique", fontheight, 50, textblockposition - 4 * fontheight, PDF_BLACK);
	pdf_set_font(pdf, "Helvetica-Oblique");
	pdf_add_text(pdf, NULL, "Helvetica Oblique", fontheight, 50, textblockposition - 5 * fontheight, PDF_BLACK);
	pdf_set_font(pdf, "Courier");
	pdf_add_text(pdf, NULL, "Courier New", fontheight, 50, textblockposition - 6 * fontheight, PDF_BLACK);
	pdf_set_font(pdf, "Courier-Bold");
	pdf_add_text(pdf, NULL, "Courier New Bold", fontheight, 50, textblockposition - 7 * fontheight, PDF_BLACK);
	pdf_set_font(pdf, "Courier-BoldOblique");
	pdf_add_text(pdf, NULL, "Courier New Bold Oblique", fontheight, 50, textblockposition - 8 * fontheight, PDF_BLACK);
	pdf_set_font(pdf, "Courier-Oblique");
	pdf_add_text(pdf, NULL, "Courier New Oblique", fontheight, 50, textblockposition - 9 * fontheight, PDF_BLACK);
	pdf_set_font(pdf, "Times-Roman");
	pdf_add_text(pdf, NULL, "Times New Roman", fontheight, 50, textblockposition - 10 * fontheight, PDF_BLACK);
	pdf_set_font(pdf, "Times-Bold");
	pdf_add_text(pdf, NULL, "Times New Roman Bold", fontheight, 50, textblockposition - 11 * fontheight, PDF_BLACK);
	pdf_set_font(pdf, "Times-Italic");
	pdf_add_text(pdf, NULL, "Times New Roman Italic", fontheight, 50, textblockposition - 12 * fontheight, PDF_BLACK);
	pdf_set_font(pdf, "Times-BoldItalic");
	pdf_add_text(pdf, NULL, "Times New Roman Bold Italic", fontheight, 50, textblockposition - 13 * fontheight, PDF_BLACK);
	
	pdf_append_page(pdf);
	pdf_add_bookmark(pdf, NULL, -1, "Page 8 Image, Barcode, Line");
	pdf_set_font(pdf, "Calibri");

    pdf_add_image_file(pdf, NULL, 150, 50, 200, 200, "rsc/side cutters.jpg"); // 995 * 996
    pdf_add_barcode(pdf, NULL, PDF_BARCODE_128A, 50, 300, 200, 50, "Code128", PDF_RGB(0, 0, 0));
    pdf_add_barcode(pdf, NULL, PDF_BARCODE_39, 50, 400, 400, 50, "CODE39", PDF_RGB(0, 0, 0));
    pdf_add_text(pdf, NULL, "Page 8", 10, 20, 30, PDF_RGB(0, 0, 0));
    pdf_add_line(pdf, NULL, 310, 470, 400, 560, 40, PDF_RGB(0xff, 0xff, 0));
	
	pdf_append_page(pdf);
	pdf_add_bookmark(pdf, NULL, -1, "Page 9 Path");
    struct pdf_path_operation operations[] = {
        {.op = 'm', .x1 = 100, .y1 = 100},
        {.op = 'l', .x1 = 230, .y1 = 800},
        {.op = 'c', .x1 = 350, .y1 = 150,
					.x2 = 100, .y2 = 200,
					.x3 = 430, .y3 = 430},
        {.op = 'l', .x1 = 550, .y1 = 720},
        {.op = 'h'},
    };
    int operation_count = (sizeof(operations) / sizeof((operations)[0]));
    pdf_add_custom_path(pdf, NULL, operations, operation_count, 1,
                        PDF_RGB(0, 0xff, 0), PDF_ARGB(0x80, 0, 0xff, 0));
    pdf_append_page(pdf);
	pdf_add_bookmark(pdf, NULL, -1, "Page 10 Text");
    for (i = 0; i < 3000; i++) {
        float xpos = (i / 100) * 40.0f;
        float ypos = (i % 100) * 10.0f;
        pdf_add_text(pdf, NULL, "Quick ", 8, xpos, ypos,
                     PDF_RGB(i, (i * 4) & 0xff, (i * 8) & 0xff));
    }
    pdf_add_text(pdf, NULL, "", 10, (i / 100) * 100, (i % 100) * 12,
                 PDF_RGB(0xff, 0, 0));

    
	pdf_append_page(pdf);
	pdf_add_bookmark(pdf, NULL, -1, "Page 11 Text Wrapping Calibri");
	pdf_page_set_size(pdf, NULL, PDF_A4_HEIGHT, PDF_A4_WIDTH);
	pdf_set_font(pdf, "Calibri");
    pdf_add_text_wrap(
        pdf, NULL,
		"space                       space                       space                       space                       space\n"
        "1234567890ABCDEFGHIJKLMNOPabcdefghijklmnop``~~!!@@##$$%%^^&&**(())__++==--{{}}[[]];;::''""\\||,,<<..>>//??"
        "______________________________________________________________________________________________________\n"
        "thequickbrownfoxjumpedoverthelazydogTHEQUICKBROWNFOXJUMPEDOVERTHELAZYDOG"
		"thequickbrownfoxjumpedoverthelazydogTHEQUICKBROWNFOXJUMPEDOVERTHELAZYDOG",
        16, 60, 400, PDF_RGB(0, 0, 0), 300, PDF_ALIGN_JUSTIFY, &height);
    pdf_add_rectangle(pdf, NULL, 58, 400 + 16 - 2, 304, -height - 2, 2, PDF_RGB(0, 0, 0));
	
	pdf_set_font(pdf, "Calibri");
    pdf_add_text_wrap(
        pdf, NULL,
		"space                       space                       space                       space                       space\n"
        "1234567890ABCDEFGHIJKLMNOPabcdefghijklmnop``~~!!@@##$$%%^^&&**(())__++==--{{}}[[]];;::''""\\||,,<<..>>//??"
        "______________________________________________________________________________________________________\n"
        "thequickbrownfoxjumpedoverthelazydogTHEQUICKBROWNFOXJUMPEDOVERTHELAZYDOG"
		"thequickbrownfoxjumpedoverthelazydogTHEQUICKBROWNFOXJUMPEDOVERTHELAZYDOG",
        12, 460, 400, PDF_RGB(0, 0, 0), 300, PDF_ALIGN_JUSTIFY, &height);
    pdf_add_rectangle(pdf, NULL, 458, 400 + 12 - 2, 304, -height - 2, 2, PDF_RGB(0, 0, 0));
	

	pdf_append_page(pdf);
	pdf_add_bookmark(pdf, NULL, -1, "Page 12 Text Wrapping Calibri");
	pdf_page_set_size(pdf, NULL, PDF_A3_WIDTH, PDF_A3_HEIGHT);
	pdf_set_font(pdf, "Calibri");
    pdf_add_text_wrap(
        pdf, NULL,
        "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\n"
		"bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb\n"
		"ccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc\n"
		"dddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddd\n"
		"eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee\n"
		"fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff\n"
		"gggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggg\n"
		"hhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhh\n"
        "iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii\n"
		"jjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjj\n"
		"kkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkk\n"
		"lllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllll\n"
		"mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm\n"
        "nnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnn\n"
		"ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo\n"
		"ppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppp\n"
		"qqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqq\n"
		"rrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrr\n"
		"sssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss\n"
		"tttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttt\n"
		"uuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuu\n"
		"vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv\n"
		"wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww\n"
		"xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n"
		"yyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyy\n"
        "zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz",
        16, 60, 1100, PDF_RGB(0, 0, 0), 300, PDF_ALIGN_JUSTIFY, &height);
    pdf_add_rectangle(pdf, NULL, 58, 1100 + 16 - 2, 304, -height - 2, 2, PDF_RGB(0, 0, 0));
	
	pdf_set_font(pdf, "Calibri");
    pdf_add_text_wrap(
        pdf, NULL,
        "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\n"
		"bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb\n"
		"ccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc\n"
		"dddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddd\n"
		"eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee\n"
		"fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff\n"
		"gggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggg\n"
		"hhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhh\n"
        "iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii\n"
		"jjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjj\n"
		"kkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkk\n"
		"lllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllll\n"
		"mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm\n"
        "nnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnn\n"
		"ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo\n"
		"ppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppp\n"
		"qqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqq\n"
		"rrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrr\n"
		"sssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss\n"
		"tttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttt\n"
		"uuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuu\n"
		"vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv\n"
		"wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww\n"
		"xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n"
		"yyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyy\n"
        "zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz",
        12, 460, 1100, PDF_RGB(0, 0, 0), 300, PDF_ALIGN_JUSTIFY, &height);
    pdf_add_rectangle(pdf, NULL, 458, 1100 + 12 - 2, 304, -height - 2 , 2, PDF_RGB(0, 0, 0));
	
	pdf_append_page(pdf);
	pdf_add_bookmark(pdf, NULL, -1, "Page 13 Text Wrapping Calibri");
	pdf_page_set_size(pdf, NULL, PDF_A3_WIDTH, PDF_A3_HEIGHT);
	pdf_set_font(pdf, "Calibri");
    pdf_add_text_wrap(
        pdf, NULL,
        "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n"
		"BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB\n"
		"CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC\n"
		"DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD\n"
		"EEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE\n"
		"FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF\n"
		"GGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG\n"
		"HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH\n"
        "IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII\n"
		"JJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJ\n"
		"KKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKK\n"
		"LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL\n"
		"MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM\n"
        "NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN\n"
		"OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO\n"
		"PPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP\n"
		"QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ\n"
		"RRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRR\n"
		"SSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS\n"
		"TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT\n"
		"UUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUU\n"
		"VVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVV\n"
		"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW\n"
		"XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n"
		"YYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYY\n"
        "ZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ",
        16, 60, 1100, PDF_RGB(0, 0, 0), 300, PDF_ALIGN_JUSTIFY, &height);
    pdf_add_rectangle(pdf, NULL, 58, 1100 + 16 - 2, 304, -height - 2, 2, PDF_RGB(0, 0, 0));
	
	pdf_set_font(pdf, "Calibri");
    pdf_add_text_wrap(
        pdf, NULL,
        "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n"
		"BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB\n"
		"CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC\n"
		"DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD\n"
		"EEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE\n"
		"FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF\n"
		"GGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG\n"
		"HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH\n"
        "IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII\n"
		"JJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJ\n"
		"KKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKK\n"
		"LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL\n"
		"MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM\n"
        "NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN\n"
		"OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO\n"
		"PPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP\n"
		"QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ\n"
		"RRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRR\n"
		"SSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS\n"
		"TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT\n"
		"UUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUU\n"
		"VVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVV\n"
		"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW\n"
		"XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n"
		"YYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYY\n"
        "ZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ",
        12, 460, 1100, PDF_RGB(0, 0, 0), 300, PDF_ALIGN_JUSTIFY, &height);
    pdf_add_rectangle(pdf, NULL, 458, 1100 + 12 - 2, 304, -height - 2 , 2, PDF_RGB(0, 0, 0));
	
	pdf_append_page(pdf);
	// other ascii 0-127 characters: !"#$%&'()*+,-./0123456789:;<=>?@
	pdf_add_bookmark(pdf, NULL, -1, "Page 14 Text Wrapping Calibri");
	pdf_page_set_size(pdf, NULL, PDF_A3_WIDTH, PDF_A3_HEIGHT);
	pdf_set_font(pdf, "Calibri");
    pdf_add_text_wrap(
        pdf, NULL,
        "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n"
		"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\n"
		"################################################\n"
		"$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n"
		"%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n"
		"&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&\n"
		"'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''\n"
		"((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((\n"
		")))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))\n"
		"*******************************************************************************************\n"
		"++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n"
		",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,\n"
		"----------------------------------------------------------------------------------------------------------------\n"
		"................................................................................................................\n"
		"////////////////////////////////////////////////////////////////////////////////////////////////////////////////\n"
		"0000000000000000000000000000000000000000000000000\n"
		"1111111111111111111111111111111111111111111111111\n"
		"2222222222222222222222222222222222222222222222222\n"
		"3333333333333333333333333333333333333333333333333\n"
		"4444444444444444444444444444444444444444444444444\n"
		"5555555555555555555555555555555555555555555555555\n"
		"666666666666666666666666666666666666666666666666\n"
		"777777777777777777777777777777777777777777777777\n"
		"888888888888888888888888888888888888888888888888\n"
		"999999999999999999999999999999999999999999999999\n"
		":::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n"
		";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n"
		"<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n"
		"==========================================================\n"
		">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n"
		"??????????????????????????????????????????????????????\n"
		"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n"
		"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n",
        16, 60, 1100, PDF_RGB(0, 0, 0), 300, PDF_ALIGN_JUSTIFY, &height);
    pdf_add_rectangle(pdf, NULL, 58, 1100 + 16 - 2, 304, -height - 2, 2, PDF_RGB(0, 0, 0));
	
	pdf_set_font(pdf, "Calibri");
    pdf_add_text_wrap(
        pdf, NULL,
        "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n"
		"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\n"
		"################################################\n"
		"$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n"
		"%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n"
		"&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&\n"
        "'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''\n"
		"((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((\n"
		")))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))\n"
		"*******************************************************************************************\n"
		"++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n"
		",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,\n"
		"----------------------------------------------------------------------------------------------------------------\n"
		"................................................................................................................\n"
		"////////////////////////////////////////////////////////////////////////////////////////////////////////////////\n"
		"0000000000000000000000000000000000000000000000000\n"
		"1111111111111111111111111111111111111111111111111\n"
		"2222222222222222222222222222222222222222222222222\n"
		"3333333333333333333333333333333333333333333333333\n"
		"4444444444444444444444444444444444444444444444444\n"
		"5555555555555555555555555555555555555555555555555\n"
		"666666666666666666666666666666666666666666666666\n"
		"777777777777777777777777777777777777777777777777\n"
		"888888888888888888888888888888888888888888888888\n"
		"999999999999999999999999999999999999999999999999\n"
		":::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n"
		";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n"
		"<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n"
		"==========================================================\n"
		">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n"
		"??????????????????????????????????????????????????????\n"
		"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n"
		"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n",
        12, 460, 1100, PDF_RGB(0, 0, 0), 300, PDF_ALIGN_JUSTIFY, &height);
    pdf_add_rectangle(pdf, NULL, 458, 1100 + 12 - 2, 304, -height - 2 , 2, PDF_RGB(0, 0, 0));
	
	// other ascii 0-127 characters: [\]^_`{|}~
	pdf_append_page(pdf);
	pdf_add_bookmark(pdf, NULL, -1, "Page 15 Text Wrapping Calibri");
	pdf_page_set_size(pdf, NULL, PDF_A3_WIDTH, PDF_A3_HEIGHT);
	pdf_set_font(pdf, "Calibri");
    pdf_add_text_wrap(
        pdf, NULL,
        "[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[["
		"\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\"
		"]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]"
		"^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^"
		"__________________________________________________________________________________"
		"````````````````````````````````````````````````````````````````````````````````````"
		"{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}"
		"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~",
        16, 60, 1100, PDF_RGB(0, 0, 0), 300, PDF_ALIGN_JUSTIFY, &height);
    pdf_add_rectangle(pdf, NULL, 58, 1100 + 16 - 2, 304, -height - 2, 2, PDF_RGB(0, 0, 0));
	
	pdf_set_font(pdf, "Calibri");
    pdf_add_text_wrap(
        pdf, NULL,
        "[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[["
		"\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\"
		"]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]"
		"^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^"
		"__________________________________________________________________________________"
		"````````````````````````````````````````````````````````````````````````````````````"
		"{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}"
		"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~",
        12, 460, 1100, PDF_RGB(0, 0, 0), 300, PDF_ALIGN_JUSTIFY, &height);
    pdf_add_rectangle(pdf, NULL, 458, 1100 + 12 - 2, 304, -height - 2 , 2, PDF_RGB(0, 0, 0));
	
    pdf_save(pdf, "testpdf.pdf");
    const char *err_str = pdf_get_err(pdf, &err);
    if (err_str) {
        fprintf(stderr, "PDF Error: %d - %s\n", err, err_str);
        pdf_destroy(pdf);
        return -1;
    }
    pdf_destroy(pdf);
	
/*		Todo			
    pdf_add_circle(pdf, NULL, 100, 240, 50, 5, PDF_RGB(0xff, 0, 0),
                   PDF_TRANSPARENT);
    pdf_add_ellipse(pdf, NULL, 100, 240, 40, 30, 2, PDF_RGB(0xff, 0xff, 0),
                    PDF_RGB(0, 0, 0));
    pdf_add_rectangle(pdf, NULL, 150, 150, 100, 100, 4, PDF_RGB(0, 0, 0xff));
    pdf_add_filled_rectangle(pdf, NULL, 150, 450, 100, 100, 4,
                             PDF_RGB(0, 0xff, 0));
    pdf_add_text(pdf, NULL, "This should be transparent", 20, 160, 500,
                 PDF_ARGB(0x80, 0, 0, 0));		 
    float p1X[] = {200, 200, 300, 300};
    float p1Y[] = {200, 300, 200, 300};
    pdf_add_polygon(pdf, NULL, p1X, p1Y, 4, 4, PDF_RGB(0xaa, 0xff, 0xee));
    float p2X[] = {400, 400, 500, 500};
    float p2Y[] = {400, 500, 400, 500};
    pdf_add_filled_polygon(pdf, NULL, p2X, p2Y, 4, 4,
                           PDF_RGB(0xff, 0x77, 0x77));
*/
    
    return 0;
}
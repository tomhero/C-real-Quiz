#include <stdio.h>
#include <gtk/gtk.h>

GtkWidget *main_menu;

int widget_destroy(GtkWidget *widget, gpointer data)
{
    gtk_widget_destroy(data);
}

int quiz(GtkWidget *widget, gpointer data)
{
    GtkWidget *window, *label, *but_ok, *vbox, *vbox_2, *choice_2, *layout, *image, *entry;
    label = gtk_label_new("Enter Your name");
    but_ok = gtk_button_new_with_label("OK");
    entry = gtk_entry_new();
    vbox_2 = gtk_vbox_new(0, 0);
    gtk_box_pack_start(GTK_BOX(data), vbox_2, 1, 1, 0);
    gtk_box_pack_start(GTK_BOX(vbox_2), label, 1, 1, 0);
    gtk_box_pack_start(GTK_BOX(vbox_2), entry, 1, 1, 0);
    gtk_box_pack_start(GTK_BOX(vbox_2), but_ok, 1, 1, 0);
    gtk_container_set_border_width (GTK_CONTAINER (main_menu), 250);
    gtk_widget_show_all(data);
}

int main (int argc, char *argv[])
{
    GtkWidget *but_start, *but_exit, *but_about, *boxin, *boxout, *bigbox, *doneleft, *doneright, *label, *label2, *label3, *first;
    GtkImage *logo, *bg;
    /*----- CSS ----------- */
    GtkCssProvider *provider;
    GdkDisplay *display;
    GdkScreen *screen;
    /*-----------------------*/
    gtk_init (&argc, &argv);
    main_menu = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title (GTK_WINDOW (main_menu), "C-real Quiz");
    logo = gtk_image_new_from_file("logo.png");
    bg = gtk_image_new_from_file("BG.jpg");
    but_start = gtk_button_new_with_label("Start");
    but_about = gtk_button_new_with_label("About");
    but_exit = gtk_button_new_with_label("Exit");
    label = gtk_label_new("");
    label2 = gtk_label_new("");
    label3 = gtk_label_new("");
    doneleft = gtk_vbox_new(0, 0);
    doneright = gtk_vbox_new(0, 0);
    boxin = gtk_vbox_new(0, 0);
    boxout = gtk_vbox_new(0, 0);
    bigbox = gtk_hbox_new(0, 80);
    first = gtk_vbox_new(0, 0);
    gtk_box_pack_start(GTK_BOX(first), bigbox, 1, 1, 0);
    gtk_box_pack_start(GTK_BOX(bigbox), doneleft, 1, 1, 0);
    gtk_box_pack_start(GTK_BOX(doneleft), label, 1, 1, 250);
    gtk_box_pack_start(GTK_BOX(doneleft), but_about, 1, 1, 0);
    gtk_box_pack_start(GTK_BOX(bigbox), boxout, 1, 1, 0);
    gtk_box_pack_start(GTK_BOX(boxout), boxin, 1, 1, 0);
    gtk_box_pack_start(GTK_BOX(boxin), logo, 0, 0, 10);
    gtk_box_pack_start(GTK_BOX(boxin), but_start, 1, 1, 50);
    gtk_box_pack_start(GTK_BOX(boxin), label3, 0, 0, 120);
    gtk_box_pack_start(GTK_BOX(bigbox), doneright, 1, 1, 5);
    gtk_box_pack_start(GTK_BOX(doneright), label2, 1, 1, 250);
    gtk_box_pack_start(GTK_BOX(doneright), but_exit, 1, 1, 0);
    gtk_widget_set_name(main_menu, "main");
    //gtk_widget_set_name(logo, "logo");
    gtk_widget_set_name(but_about, "about");
    gtk_widget_set_name(but_exit, "exit");
    g_signal_connect(but_start, "clicked", G_CALLBACK(quiz), first);
    g_signal_connect(but_start, "clicked", G_CALLBACK(widget_destroy), bigbox);
    gtk_container_add(GTK_CONTAINER(main_menu), first);
    gtk_window_set_position(GTK_WINDOW(main_menu), GTK_WIN_POS_CENTER);
    gtk_container_set_border_width (GTK_CONTAINER (main_menu), 10);
    gtk_window_set_resizable(GTK_WINDOW(main_menu), FALSE);
    gtk_widget_set_size_request(main_menu, 800, 600);

    /*------------- CSS  --------------------------------------------------------------------------------------------------*/
  provider = gtk_css_provider_new ();
  display = gdk_display_get_default ();
  screen = gdk_display_get_default_screen (display);

  gtk_style_context_add_provider_for_screen (screen,
                                             GTK_STYLE_PROVIDER(provider),
                                             GTK_STYLE_PROVIDER_PRIORITY_USER);

  gtk_css_provider_load_from_data (GTK_CSS_PROVIDER (provider),
                                     " #main {\n"
                                     "   background-image: url('BG.jpg');\n"
                                     "   background-size: 900px 700px;\n"
                                     "}\n"
                                     "#about {\n"
                                     "   color: green;\n"
                                     "   background-color: black;\n"
                                     "}\n"
                                     "#exit {\n"
                                     "   color: blue;\n"
                                     "}\n",
                                     -1, NULL);
  g_object_unref (provider);
/*----------------------------------------------------------------------------------------------------------------------*/

    gtk_widget_show_all(main_menu);
    gtk_main ();
    return 0;
}

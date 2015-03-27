#include <gtk/gtk.h>
#include <stdio.h>

static void  but_clk(GtkWidget* widget, gpointer data)
{
    GtkWidget *window;
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title (GTK_WINDOW (window), "TEST2");
    gtk_label_set_text(GTK_LABEL(data), "Passed");
    printf("stdclick\n");

    g_signal_connect(window, "destroy", G_CALLBACK (gtk_main_quit), NULL);
    gtk_widget_show_all(window);
}

int main (int argc, char *argv[])
{
  GtkWidget *window, *label, *button, *vbox, *label2;

  gtk_init (&argc, &argv);

  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title (GTK_WINDOW (window), "TEST");
  label = gtk_label_new("Hello World");
  label2 = gtk_label_new("The C-real Quiz!!");
  button = gtk_button_new_with_label("Click Me!!");
  vbox = gtk_vbox_new(0, 0);
  gtk_box_pack_start(GTK_BOX(vbox), label, 1, 1, 0);
  gtk_box_pack_start(GTK_BOX(vbox), button, 1, 1, 50);
  gtk_box_pack_start(GTK_BOX(vbox), label2, 1, 1, 0);

  g_signal_connect(window, "destroy", G_CALLBACK (gtk_main_quit), NULL);
  g_signal_connect(button, "clicked", G_CALLBACK(but_clk), label);
  gtk_container_add(GTK_CONTAINER(window), vbox);
  gtk_widget_set_size_request(window, 300, 300);
  gtk_window_set_title(GTK_WINDOW(window), "TEST");

  gtk_widget_show_all(window);

  gtk_main ();

  return 0;
}

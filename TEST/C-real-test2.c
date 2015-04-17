#include <stdio.h>
#include <gtk/gtk.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int score_board();
int timer_quiz(gpointer);
int doing_quiz_odd();
int doing_quiz_even();
int update();
int choose_quiz(GtkWidget *widget, gpointer bigbox);
int named(GtkWidget *widget, gpointer data);
int about();
int rule();
int show_credit();

// Global variable
GtkWidget *main_menu, *count_down, *quiz_window, *true_choice, *false_choice, *timer;
GtkEntry *entry;
char player_name[50] , str[2];
int set = 0, num_quiz = 0, round = 3, score = 0, sign = 9, alert = 0;
float percent = 0.0;

int widget_destroy(GtkWidget *widget, gpointer data)
{
    percent = 0.0;
    gtk_widget_destroy(data);
}

int widget_destroy_odd(GtkWidget *widget, gpointer data)
{
      if (num_quiz >= 9)
    {
        percent = 0.0;
        gtk_widget_destroy(data);
        return score_board();
    }
    gtk_widget_destroy(data);
    return doing_quiz_even();
}

int widget_destroy_even(GtkWidget *widget, gpointer data)
{
    if (num_quiz >= 10)
    {
        percent = 0.0;
        gtk_widget_destroy(data);
        return score_board();
    }
    gtk_widget_destroy(data);
    doing_quiz_odd();
}

int correct(GtkWidget *widget)
{
    score += 1;
    printf("score --> %d\n", score);
}

int select(GtkWidget *widget ,gint c)
{
    set = c;
    printf("SET -> %d\n", set);
}

int update()
{
    if (num_quiz <= 10)
    {
        gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(timer), percent);
        g_timeout_add(1, timer_quiz, timer);
    }
    return 0;
}

int random()
{
   int i, n;
   time_t t;

   n = 100;

   /* Intializes random number generator */
   srand((unsigned) time(&t));

   /* Print 5 random numbers from 0 to 99 */
   //printf("%d\n", rand() % 100);

  return(rand() % 100);
}

int score_board()
{
    GtkWidget *bigbox, *vbox_up, *vbox_down, *hbox, *but_home, *but_exit, *player, *label, *score_label;
    GtkImage *pic_your_score, *pic_replay, *pic_exit;
    char last_score[2], player_label[100] = "Player name \" ", label_score[20] = ">> ";
    printf("passed!!\n");
    /*----- CSS ----------- */
    GtkCssProvider *provider;
    GdkDisplay *display;
    GdkScreen *screen;
    /*-----------------------*/
    if (sign > alert)
    {
        sign -= 1;
        return 0;
    }
    gtk_widget_destroy(main_menu);
    main_menu = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title (GTK_WINDOW (main_menu), "C-real Quiz");
    strcat(player_label, player_name);
    strcat(player_label, " \"");
    player = gtk_label_new(player_label);
    pic_your_score = gtk_image_new_from_file("button/score.png");
    sprintf(last_score, "%d", score);
    strcat(label_score,  last_score);
    strcat(label_score,  " <<");
    score_label = gtk_label_new(label_score);
    but_home = gtk_button_new();
    but_exit = gtk_button_new();
    pic_replay = gtk_image_new_from_file("button/replay.png");
    pic_exit = gtk_image_new_from_file("exit.png");
    gtk_button_set_image(but_exit, pic_exit);
    gtk_button_set_image(but_home, pic_replay);
    bigbox = gtk_vbox_new(0, 0);
    vbox_up = gtk_vbox_new(0, 0);
    vbox_down = gtk_vbox_new(0, 0);
    hbox = gtk_hbox_new(0, 0);
    gtk_widget_set_name(score_label, "score");
    gtk_widget_set_name(main_menu, "main");
    gtk_widget_set_name(player, "player");
    gtk_box_pack_start(GTK_BOX(bigbox), vbox_up, 1, 1, 25);
    gtk_box_pack_start(GTK_BOX(bigbox), vbox_down, 1, 1, 0);
    gtk_box_pack_start(GTK_BOX(vbox_up), player, 1, 1, 10);
    gtk_box_pack_start(GTK_BOX(vbox_up), pic_your_score, 1, 1, 20);
    gtk_box_pack_start(GTK_BOX(vbox_up), score_label, 1, 1, 25);
    gtk_box_pack_start(GTK_BOX(vbox_down), hbox, 1, 1, 0);
    gtk_box_pack_start(GTK_BOX(hbox), but_home, 1, 1, 100);
    gtk_box_pack_start(GTK_BOX(hbox), but_exit, 1, 1, 100);
    gtk_container_add(GTK_CONTAINER(main_menu), bigbox);
    g_signal_connect(but_exit, "clicked", G_CALLBACK(gtk_main_quit), NULL);
    g_signal_connect(but_home, "clicked", G_CALLBACK(named), bigbox);
    g_signal_connect(but_home, "clicked", G_CALLBACK(widget_destroy), vbox_up);
    g_signal_connect(but_home, "clicked", G_CALLBACK(widget_destroy), vbox_down);
    /*------------- CSS  --------------------------------------------------------------------------------------------------*/
  provider = gtk_css_provider_new ();
  display = gdk_display_get_default ();
  screen = gdk_display_get_default_screen (display);

  gtk_style_context_add_provider_for_screen (screen,
                                             GTK_STYLE_PROVIDER(provider),
                                             GTK_STYLE_PROVIDER_PRIORITY_USER);

  gtk_css_provider_load_from_data (GTK_CSS_PROVIDER (provider),
                                     " #main {\n"
                                     "   background-image: url('background.jpg');\n"
                                     "   background-size: 800px 600px;\n"
                                     "   background-repeat: no-repeat;\n"
                                     "}\n"
                                     " #player {\n"
                                     " font: 25\n"
                                     "}\n"
                                     " #score {\n"
                                     " font: 60\n"
                                     "}\n",
                                     -1, NULL);
  g_object_unref (provider);
/*----------------------------------------------------------------------------------------------------------------------*/
    gtk_window_set_position(GTK_WINDOW(main_menu), GTK_WIN_POS_CENTER);
    gtk_container_set_border_width (GTK_CONTAINER (main_menu), 20);
    gtk_window_set_resizable(GTK_WINDOW(main_menu), FALSE);
    gtk_widget_set_size_request(main_menu, 800, 600);
    gtk_widget_show_all(main_menu);
    return 0;
}

int timer_quiz(gpointer data)
{
    percent -= 0.00009;
    if (percent <= 0.0)
    {
        gtk_widget_destroy(quiz_window);
        if (num_quiz % 2 == 0 && num_quiz < 10)
        {
            alert += 1;
            return doing_quiz_even();
        }
        else if (num_quiz < 10)
        {
            alert += 1;
            return doing_quiz_odd();
        }
        else
        {
            return score_board();
        }
    }
    else if (percent > 0.0)
    {
        if (num_quiz % 2 == 0)
        {
            g_signal_connect(true_choice, "clicked", G_CALLBACK(correct), NULL);
            g_signal_connect(true_choice, "clicked", G_CALLBACK(widget_destroy_odd), quiz_window);
            g_signal_connect(false_choice, "clicked", G_CALLBACK(widget_destroy_odd), quiz_window);
        }
        else
        {
            g_signal_connect(true_choice, "clicked", G_CALLBACK(correct), NULL);
            g_signal_connect(true_choice, "clicked", G_CALLBACK(widget_destroy_even), quiz_window);
            g_signal_connect(false_choice, "clicked", G_CALLBACK(widget_destroy_even), quiz_window);
        }
    }
    return update();
}

int doing_quiz_even()
{
    GtkWidget *bigbox, *vbox_in, *quiz, *hbox, *done;
    GtkImage *img_quiz, *img_true, *img_false;
    /*----- CSS ----------- */
    GtkCssProvider *provider;
    GdkDisplay *display;
    GdkScreen *screen;
    /*-----------------------*/
    char path[20] = "", str_2[10], path_for_quiz[20]="s", path_for_true[20]="s", path_for_false[20]="s";
    percent = 1.0;
    num_quiz += 1;
    sprintf(str_2, "%d", set);
    strcat(path_for_quiz, str_2);
    strcat(path_for_true, str_2);
    strcat(path_for_false, str_2);
    strcat(path_for_quiz, "/q");
    strcat(path_for_true, "/q");
    strcat(path_for_false, "/q");
    sprintf(str_2, "%d", num_quiz);
    strcat(path_for_quiz, str_2);
    strcat(path_for_true, str_2);
    strcat(path_for_false, str_2);
    strcat(path_for_quiz, "/");
    strcat(path_for_true, "/");
    strcat(path_for_false, "/");
    strcat(path_for_quiz, "Question.png");
    strcat(path_for_true, "True.png");
    strcat(path_for_false, "False.png");
    printf("%s\n", path_for_quiz);
    printf("%s\n", path_for_true);
    printf("%s\n", path_for_false);
    quiz_window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title (GTK_WINDOW (quiz_window), "C-real Quiz");
    img_quiz = gtk_image_new_from_file(path_for_quiz);
    img_true = gtk_image_new_from_file(path_for_true);
    img_false = gtk_image_new_from_file(path_for_false);
    gtk_widget_set_size_request(img_quiz, 150, 50);
    //quiz = gtk_label_new_with("Quiz");
    true_choice = gtk_button_new();
    false_choice = gtk_button_new();
    gtk_button_set_image(true_choice, img_true);
    gtk_button_set_image(false_choice, img_false);
    done = gtk_label_new("");
    timer = gtk_progress_bar_new();
    hbox = gtk_hbox_new(0, 10);
    bigbox = gtk_vbox_new(0, 0);
    vbox_in = gtk_vbox_new(0, 0);
    gtk_widget_set_name(true_choice, "true_choice");
    gtk_widget_set_name(quiz_window, "quiz_main");
    gtk_box_pack_start(GTK_BOX(bigbox), vbox_in, 1, 1, 5);
    gtk_box_pack_start(GTK_BOX(vbox_in), img_quiz, 1, 1, 5);
    gtk_box_pack_start(GTK_BOX(vbox_in), hbox, 1, 1, 5);
    if (random() % 2 == 0)
    {
        gtk_box_pack_start(GTK_BOX(hbox), true_choice, 1, 1, 30);
        gtk_box_pack_start(GTK_BOX(hbox), false_choice, 1, 1, 30);
    }
    else
    {
        gtk_box_pack_start(GTK_BOX(hbox), false_choice, 1, 1, 30);
        gtk_box_pack_start(GTK_BOX(hbox), true_choice, 1, 1, 30);
    }
    gtk_box_pack_start(GTK_BOX(vbox_in), timer, 1, 1, 20);
    //g_signal_connect(true_choice, "clicked", G_CALLBACK(widget_destroy_odd), quiz_window);
    //g_signal_connect(true_choice, "clicked", G_CALLBACK(correct), NULL);
    //g_signal_connect(false_choice, "clicked", G_CALLBACK(widget_destroy_odd), quiz_window);
    gtk_container_add(GTK_CONTAINER(quiz_window), bigbox);
    gtk_window_set_position(GTK_WINDOW(quiz_window), GTK_WIN_POS_CENTER);
    gtk_container_set_border_width (GTK_CONTAINER (quiz_window), 10);
    gtk_window_set_resizable(GTK_WINDOW(quiz_window), FALSE);
    //gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(timer), 1.0);
    g_timeout_add(1, timer_quiz, timer);
        /*------------- CSS  --------------------------------------------------------------------------------------------------*/
  provider = gtk_css_provider_new ();
  display = gdk_display_get_default ();
  screen = gdk_display_get_default_screen (display);

  gtk_style_context_add_provider_for_screen (screen,
                                             GTK_STYLE_PROVIDER(provider),
                                             GTK_STYLE_PROVIDER_PRIORITY_USER);

  gtk_css_provider_load_from_data (GTK_CSS_PROVIDER (provider),
                                     " #quiz_main {\n"
                                     "   background-image :url('background.jpg');\n"
                                     "   background-size: 800px 600px;\n"
                                     "   background-repeat: no-repeat;\n"
                                     "}\n"
                                     " #true_choice {\n"
                                     " border-color: green;\n"
                                     "}\n",
                                     -1, NULL);
  g_object_unref (provider);
/*----------------------------------------------------------------------------------------------------------------------*/
    gtk_widget_set_size_request(quiz_window, 800, 600);
    gtk_widget_show_all(quiz_window);
    return 0;
}

int doing_quiz_odd()
{
    GtkWidget *bigbox, *vbox_in, *quiz, *hbox, *done;
    GtkImage *img_quiz, *img_true, *img_false;
    /*----- CSS ----------- */
    GtkCssProvider *provider;
    GdkDisplay *display;
    GdkScreen *screen;
    /*-----------------------*/
    char path[20] = "", str_2[10], path_for_quiz[20]="s", path_for_true[20]="s", path_for_false[20]="s";
    percent = 1.0;
    if (num_quiz > 10)
    {
        gtk_widget_destroy(main_menu);
        return score_board();
    }
    num_quiz += 1;
    sprintf(str_2, "%d", set);
    strcat(path_for_quiz, str_2);
    strcat(path_for_true, str_2);
    strcat(path_for_false, str_2);
    strcat(path_for_quiz, "/q");
    strcat(path_for_true, "/q");
    strcat(path_for_false, "/q");
    sprintf(str_2, "%d", num_quiz);
    strcat(path_for_quiz, str_2);
    strcat(path_for_true, str_2);
    strcat(path_for_false, str_2);
    strcat(path_for_quiz, "/");
    strcat(path_for_true, "/");
    strcat(path_for_false, "/");
    strcat(path_for_quiz, "Question.png");
    strcat(path_for_true, "True.png");
    strcat(path_for_false, "False.png");
    printf("%s\n", path_for_quiz);
    printf("%s\n", path_for_true);
    printf("%s\n", path_for_false);
    quiz_window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title (GTK_WINDOW (quiz_window), "C-real Quiz");
    img_quiz = gtk_image_new_from_file(path_for_quiz);
    img_true = gtk_image_new_from_file(path_for_true);
    img_false = gtk_image_new_from_file(path_for_false);
    gtk_widget_set_size_request(img_quiz, 150, 50);
    //quiz = gtk_label_new_with("Quiz");
    true_choice = gtk_button_new();
    false_choice = gtk_button_new();
    gtk_button_set_image(true_choice, img_true);
    gtk_button_set_image(false_choice, img_false);
    done = gtk_label_new("");
    timer = gtk_progress_bar_new();
    hbox = gtk_hbox_new(0, 10);
    bigbox = gtk_vbox_new(0, 0);
    vbox_in = gtk_vbox_new(0, 0);
    gtk_widget_set_name(true_choice, "true_choice");
    gtk_widget_set_name(quiz_window, "quiz_main");
    gtk_box_pack_start(GTK_BOX(bigbox), vbox_in, 1, 1, 5);
    gtk_box_pack_start(GTK_BOX(vbox_in), img_quiz, 1, 1, 5);
    gtk_box_pack_start(GTK_BOX(vbox_in), hbox, 1, 1, 5);
    if (random() % 2 == 0)
    {
        gtk_box_pack_start(GTK_BOX(hbox), true_choice, 1, 1, 30);
        gtk_box_pack_start(GTK_BOX(hbox), false_choice, 1, 1, 30);
    }
    else
    {
        gtk_box_pack_start(GTK_BOX(hbox), false_choice, 1, 1, 30);
        gtk_box_pack_start(GTK_BOX(hbox), true_choice, 1, 1, 30);
    }
    gtk_box_pack_start(GTK_BOX(vbox_in), timer, 1, 1, 20);
    //g_signal_connect(true_choice, "clicked", G_CALLBACK(widget_destroy_odd), quiz_window);
    //g_signal_connect(true_choice, "clicked", G_CALLBACK(correct), NULL);
    //g_signal_connect(false_choice, "clicked", G_CALLBACK(widget_destroy_odd), quiz_window);
    gtk_container_add(GTK_CONTAINER(quiz_window), bigbox);
    gtk_window_set_position(GTK_WINDOW(quiz_window), GTK_WIN_POS_CENTER);
    gtk_container_set_border_width (GTK_CONTAINER (quiz_window), 10);
    gtk_window_set_resizable(GTK_WINDOW(quiz_window), FALSE);
    //gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(timer), 1.0);
    g_timeout_add(1, timer_quiz, timer);
        /*------------- CSS  --------------------------------------------------------------------------------------------------*/
  provider = gtk_css_provider_new ();
  display = gdk_display_get_default ();
  screen = gdk_display_get_default_screen (display);

  gtk_style_context_add_provider_for_screen (screen,
                                             GTK_STYLE_PROVIDER(provider),
                                             GTK_STYLE_PROVIDER_PRIORITY_USER);

  gtk_css_provider_load_from_data (GTK_CSS_PROVIDER (provider),
                                     " #quiz_main {\n"
                                     "   background-image :url('background.jpg');\n"
                                     "   background-size: 800px 600px;\n"
                                     "   background-repeat: no-repeat;\n"
                                     "}\n"
                                     " #true_choice {\n"
                                     " border-color: green;\n"
                                     "}\n",
                                     -1, NULL);
  g_object_unref (provider);
/*----------------------------------------------------------------------------------------------------------------------*/
    gtk_widget_set_size_request(quiz_window, 800, 600);
    gtk_widget_show_all(quiz_window);
    return 0;
}

int inc_progress_pre(gpointer data)
{
    /*----- CSS ----------- */
    GtkCssProvider *provider;
    GdkDisplay *display;
    GdkScreen *screen;
    /*-----------------------*/

    percent += 0.008;
    if(percent > 1.0)
    {
        round -= 1;
        percent = 0.0;
    }
    sprintf(str, "%d", round);
    gtk_label_set_text(count_down, str);
    if (round == 0)
    {
        percent = 1.0;
        gtk_widget_destroy(main_menu);
        doing_quiz_odd();
        return 0;
    }
    else
        gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(data), percent);

}

int pre_do(GtkWidget *widget, gpointer bigbox)
{
    GtkWidget *progress, *progress2, *vbox;
    GtkImage *ready;
    /*----- CSS ----------- */
    GtkCssProvider *provider;
    GdkDisplay *display;
    GdkScreen *screen;
    /*-----------------------*/
    sprintf(str, "%d", round);
    progress = gtk_progress_bar_new();
    vbox = gtk_vbox_new(0, 0);
    ready = gtk_image_new_from_file("button/ready.png");
    count_down = gtk_label_new(str);
    gtk_box_pack_start(GTK_BOX(bigbox), vbox, 1, 1, 5);
    gtk_box_pack_start(GTK_BOX(vbox), ready, 1, 1, 0);
    gtk_box_pack_start(GTK_BOX(vbox), progress, 1, 1, 10);
    gtk_box_pack_start(GTK_BOX(vbox), count_down, 1, 1, 25);
    gtk_widget_set_name(count_down, "count");

//      gtk_progress_bar_set_text(GTK_PROGRESS_BAR(progress), "50%");

//      gtk_progress_bar_set_orientation(GTK_PROGRESS_BAR(progress), GTK_PROGRESS_TOP_TO_BOTTOM);

/*------------- CSS  --------------------------------------------------------------------------------------------------*/
  provider = gtk_css_provider_new ();
  display = gdk_display_get_default ();
  screen = gdk_display_get_default_screen (display);

  gtk_style_context_add_provider_for_screen (screen,
                                             GTK_STYLE_PROVIDER(provider),
                                             GTK_STYLE_PROVIDER_PRIORITY_USER);

  gtk_css_provider_load_from_data (GTK_CSS_PROVIDER (provider),
                                     " #count {\n"
                                     " font: 60\n"
                                     "}\n",
                                     -1, NULL);
  g_object_unref (provider);
/*----------------------------------------------------------------------------------------------------------------------*/

    g_timeout_add(1, inc_progress_pre, progress);
    gtk_container_set_border_width (GTK_CONTAINER (main_menu), 125);
    gtk_widget_show_all(bigbox);
}

int choose_quiz(GtkWidget *widget, gpointer bigbox)
{
    GtkWidget *window, *vbox, *vbox_2, *layout, *image, *hbox, *vbox_left, *vbox_right;
    GtkWidget *done, *choice_1, *choice_2, *choice_3, *choice_4, *choice_5, *choice_6;
    GtkImage *img1, *img2, *img3, *img4, *img5, *img6, *label;
    strcpy(player_name, gtk_entry_get_text(entry));
    printf("%s\n", player_name);
    label = gtk_image_new_from_file("choose_set/select-quiz.png");
    choice_1 = gtk_button_new();
    choice_2 = gtk_button_new();
    choice_3 = gtk_button_new();
    choice_4 = gtk_button_new();
    choice_5 = gtk_button_new();
    choice_6 = gtk_button_new();
    img1 = gtk_image_new_from_file("choose_set/1.png");
    img2 = gtk_image_new_from_file("choose_set/2.png");
    img3 = gtk_image_new_from_file("choose_set/3.png");
    img4 = gtk_image_new_from_file("choose_set/4.png");
    img5 = gtk_image_new_from_file("choose_set/5.png");
    img6 = gtk_image_new_from_file("choose_set/6.png");
    gtk_button_set_image(choice_1,img1);
    gtk_button_set_image(choice_2,img2);
    gtk_button_set_image(choice_3,img3);
    gtk_button_set_image(choice_4,img4);
    gtk_button_set_image(choice_5,img5);
    gtk_button_set_image(choice_6,img6);
    done = gtk_label_new("");
    vbox_2 = gtk_vbox_new(0, 0);
    hbox = gtk_hbox_new(0, 0);
    vbox_left = gtk_vbox_new(0, 0);
    vbox_right = gtk_vbox_new(0, 0);
    gtk_box_pack_start(GTK_BOX(bigbox), label, 1, 1, 0);
    gtk_box_pack_start(GTK_BOX(bigbox), vbox_2, 1, 1, 5);
    gtk_box_pack_start(GTK_BOX(vbox_2), hbox, 1, 1, 0);
    gtk_box_pack_start(GTK_BOX(hbox), vbox_left, 1, 1, 50);
    gtk_box_pack_start(GTK_BOX(hbox), vbox_right, 1, 1, 50);
    gtk_box_pack_start(GTK_BOX(vbox_left), choice_1, 0, 1, 5);
    gtk_box_pack_start(GTK_BOX(vbox_right), choice_2, 0, 1, 5);
    gtk_box_pack_start(GTK_BOX(vbox_left), choice_3, 0, 1, 5);
    gtk_box_pack_start(GTK_BOX(vbox_right), choice_4, 0, 1, 5);
    gtk_box_pack_start(GTK_BOX(vbox_left), choice_5, 0, 1, 5);
    gtk_box_pack_start(GTK_BOX(vbox_right), choice_6, 0, 1, 5);
    //gtk_box_pack_start(GTK_BOX(bigbox), done, 1, 1, 5);
    g_signal_connect(choice_1, "clicked", G_CALLBACK(select), 1);
    g_signal_connect(choice_1, "clicked", G_CALLBACK(widget_destroy), label);
    g_signal_connect(choice_1, "clicked", G_CALLBACK(widget_destroy), done);
    g_signal_connect(choice_1, "clicked", G_CALLBACK(pre_do), bigbox);
    g_signal_connect(choice_1, "clicked", G_CALLBACK(widget_destroy), vbox_2);
    //
    g_signal_connect(choice_2, "clicked", G_CALLBACK(select), 2);
    g_signal_connect(choice_2, "clicked", G_CALLBACK(widget_destroy), label);
    g_signal_connect(choice_2, "clicked", G_CALLBACK(widget_destroy), done);
    g_signal_connect(choice_2, "clicked", G_CALLBACK(pre_do), bigbox);
    g_signal_connect(choice_2, "clicked", G_CALLBACK(widget_destroy), vbox_2);
    //
    g_signal_connect(choice_3, "clicked", G_CALLBACK(select), 3);
    g_signal_connect(choice_3, "clicked", G_CALLBACK(widget_destroy), label);
    g_signal_connect(choice_3, "clicked", G_CALLBACK(widget_destroy), done);
    g_signal_connect(choice_3, "clicked", G_CALLBACK(pre_do), bigbox);
    g_signal_connect(choice_3, "clicked", G_CALLBACK(widget_destroy), vbox_2);
    //
    g_signal_connect(choice_4, "clicked", G_CALLBACK(select), 4);
    g_signal_connect(choice_4, "clicked", G_CALLBACK(widget_destroy), label);
    g_signal_connect(choice_4, "clicked", G_CALLBACK(widget_destroy), done);
    g_signal_connect(choice_4, "clicked", G_CALLBACK(pre_do), bigbox);
    g_signal_connect(choice_4, "clicked", G_CALLBACK(widget_destroy), vbox_2);
    //
    g_signal_connect(choice_5, "clicked", G_CALLBACK(select), 5);
    g_signal_connect(choice_5, "clicked", G_CALLBACK(widget_destroy), label);
    g_signal_connect(choice_5, "clicked", G_CALLBACK(widget_destroy), done);
    g_signal_connect(choice_5, "clicked", G_CALLBACK(pre_do), bigbox);
    g_signal_connect(choice_5, "clicked", G_CALLBACK(widget_destroy), vbox_2);
    //
    g_signal_connect(choice_6, "clicked", G_CALLBACK(select), 6);
    g_signal_connect(choice_6, "clicked", G_CALLBACK(widget_destroy), label);
    g_signal_connect(choice_6, "clicked", G_CALLBACK(widget_destroy), done);
    g_signal_connect(choice_6, "clicked", G_CALLBACK(pre_do), bigbox);
    g_signal_connect(choice_6, "clicked", G_CALLBACK(widget_destroy), vbox_2);
    gtk_container_set_border_width (GTK_CONTAINER (main_menu), 50);
    gtk_widget_show_all(bigbox);
}

int named(GtkWidget *widget, gpointer data)
{
    GtkWidget *window, *label, *but_ok, *vbox, *vbox_2, *choice_2, *layout;
    GtkImage *enter, *pic_ok;
    set = 0;
    num_quiz = 0;
    round = 3;
    score = 0;
    sign = 9;
    alert = 0;
    label = gtk_image_new_from_file("button/name.png");
    but_ok = gtk_button_new();
    pic_ok = gtk_image_new_from_file("button/ok.png");
    gtk_button_set_image(but_ok,pic_ok);
    entry = gtk_entry_new();
    vbox_2 = gtk_vbox_new(0, 5);
    gtk_box_pack_start(GTK_BOX(data), vbox_2, 1, 1, 0);
    gtk_box_pack_start(GTK_BOX(vbox_2), label, 1, 1, 20);
    gtk_box_pack_start(GTK_BOX(vbox_2), entry, 1, 1, 0);
    gtk_box_pack_start(GTK_BOX(vbox_2), but_ok, 1, 1, 0);
    gtk_container_set_border_width (GTK_CONTAINER (main_menu), 180);
    g_signal_connect(but_ok, "clicked", G_CALLBACK(choose_quiz), data);
    g_signal_connect(but_ok, "clicked", G_CALLBACK(widget_destroy), vbox_2);
    gtk_widget_show_all(data);
}

int main (int argc, char *argv[])
{
    GtkWidget *but_start, *but_exit, *but_about, *boxin, *boxout, *bigbox, *doneleft, *doneright, *label, *label2, *label3, *first, *credit;
    GtkImage *logo, *pic_start, *pic_about, *pic_credit, *pic_exit;
    /*----- CSS ----------- */
    GtkCssProvider *provider;
    GdkDisplay *display;
    GdkScreen *screen;
    /*-----------------------*/
    gtk_init (&argc, &argv);
    main_menu = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title (GTK_WINDOW (main_menu), "C-real Quiz");
    logo = gtk_image_new_from_file("logo.png");
    but_start = gtk_button_new();
    but_about = gtk_button_new();
    but_exit = gtk_button_new();
    credit = gtk_button_new();
    pic_start = gtk_image_new_from_file("button/start.png");
    pic_about = gtk_image_new_from_file("button/about.png");
    pic_credit = gtk_image_new_from_file("button/credit.png");
    pic_exit = gtk_image_new_from_file("button/exit.png");
    gtk_button_set_image(but_start,pic_start);
    gtk_button_set_image(but_about,pic_about);
    gtk_button_set_image(but_exit,pic_exit);
    gtk_button_set_image(credit,pic_credit);
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
    gtk_box_pack_start(GTK_BOX(doneleft), label, 1, 1, 240);
    gtk_box_pack_start(GTK_BOX(doneleft), credit, 1, 1, 0);
    gtk_box_pack_start(GTK_BOX(bigbox), boxout, 1, 1, 0);
    gtk_box_pack_start(GTK_BOX(boxout), boxin, 1, 1, 0);
    gtk_box_pack_start(GTK_BOX(boxin), logo, 0, 0, 5);
    gtk_box_pack_start(GTK_BOX(boxin), but_start, 1, 1, 10);
    gtk_box_pack_start(GTK_BOX(boxin), but_about, 1, 1, 0);
    gtk_box_pack_start(GTK_BOX(boxin), label3, 0, 0, 100);
    gtk_box_pack_start(GTK_BOX(bigbox), doneright, 1, 1, 5);
    gtk_box_pack_start(GTK_BOX(doneright), label2, 1, 1, 240);
    gtk_box_pack_start(GTK_BOX(doneright), but_exit, 1, 1, 0);
    //gtk_widget_set_name(logo, "logo");
    gtk_widget_set_name(but_about, "about");
    gtk_widget_set_name(but_exit, "exit");
    gtk_widget_set_name(main_menu, "main");
    g_signal_connect(but_exit, "clicked", G_CALLBACK(gtk_main_quit), NULL);
    g_signal_connect(but_start, "clicked", G_CALLBACK(named), first);
    g_signal_connect(but_start, "clicked", G_CALLBACK(widget_destroy), bigbox);
    g_signal_connect(credit, "clicked", G_CALLBACK(show_credit), NULL);
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
                                     "   background-image: url('background.jpg');\n"
                                     "   background-size: 800px 600px;\n"
                                     "   background-repeat: no-repeat;\n"
                                     "}\n"
                                     "#about {\n"
                                     "   background-color: green;\n"
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

int show_credit()
{
    GtkWidget *window;
    GtkImage *pic_credit;
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title (GTK_WINDOW (window), "CREDIT");
    pic_credit = gtk_image_new_from_file("credit.jpg");
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_container_add(GTK_CONTAINER(window), pic_credit);
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
    gtk_widget_show_all(window);
}

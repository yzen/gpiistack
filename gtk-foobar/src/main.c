/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * main.c
 * Copyright (C) Steven Githens 2012 <swgithen@mtu.edu>
 * 
gtk-foobar is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * gtk-foobar is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <config.h>
#include <gtk/gtk.h>
#include <gio/gio.h>

#include <glib/gi18n.h>
#include <glib/gprintf.h>

void
on_my_setting_changed(GSettings* settings, gchar* key, GtkCheckButton* check_button)
{
	gtk_toggle_button_set_active (check_button, g_settings_get_boolean(settings,"highcontrast"));
}


void
on_check_button_toggled(GtkCheckButton* button, GSettings* settings)
{
	g_settings_set_boolean(settings, "highcontrast", 
	                       gtk_toggle_button_get_active (button));
}


static GtkWidget*
create_window (void)
{
	GtkWidget *window;
	GtkCheckButton *check_button;
	GSettings *settings;

	settings = g_settings_new ("apps.gpiisettings");
	
	window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title (GTK_WINDOW (window), "gtk-foobar");

	//g_printf("Hello there Fluid Project %s!", );
	
	check_button = gtk_check_button_new_with_label ("Use High Contrast Display Settings 3");
	gtk_container_add (GTK_CONTAINER (window), check_button);
	gtk_toggle_button_set_active (check_button, g_settings_get_boolean(settings,"highcontrast"));
	g_signal_connect(check_button, "toggled", on_check_button_toggled, settings);
	
	g_signal_connect(settings,"changed::highcontrast", on_my_setting_changed, check_button);
	
	/* Exit when the window is closed */
	g_signal_connect (window, "destroy", G_CALLBACK (gtk_main_quit), NULL);
	
	return window;
}


int
main (int argc, char *argv[])
{
 	GtkWidget *window;


#ifdef ENABLE_NLS
	bindtextdomain (GETTEXT_PACKAGE, PACKAGE_LOCALE_DIR);
	bind_textdomain_codeset (GETTEXT_PACKAGE, "UTF-8");
	textdomain (GETTEXT_PACKAGE);
#endif

	
	gtk_init (&argc, &argv);

	window = create_window ();
	gtk_widget_show_all (window);

	gtk_main ();

	g_printf("Whats going on");
	return 0;
}

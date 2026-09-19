/* XCHATUS
 * Copyright (C) 1998-2010 Peter Zelezny.
 * Copyright (C) 2009-2013 Berke Viktor.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA
 */

#ifndef HEXCHAT_COMMONPLUGIN_H
#define HEXCHAT_COMMONPLUGIN_H

#ifdef PLUGIN_C
struct _xchatus_plugin
{
	/* Keep these in sync with xchatus-plugin.h */
	/* !!don't change the order, to keep binary compat!! */
	xchatus_hook *(*xchatus_hook_command) (xchatus_plugin *ph,
		    const char *name,
		    int pri,
		    int (*callback) (char *word[], char *word_eol[], void *user_data),
		    const char *help_text,
		    void *userdata);
	xchatus_hook *(*xchatus_hook_server) (xchatus_plugin *ph,
		   const char *name,
		   int pri,
		   int (*callback) (char *word[], char *word_eol[], void *user_data),
		   void *userdata);
	xchatus_hook *(*xchatus_hook_print) (xchatus_plugin *ph,
		  const char *name,
		  int pri,
		  int (*callback) (char *word[], void *user_data),
		  void *userdata);
	xchatus_hook *(*xchatus_hook_timer) (xchatus_plugin *ph,
		  int timeout,
		  int (*callback) (void *user_data),
		  void *userdata);
	xchatus_hook *(*xchatus_hook_fd) (xchatus_plugin *ph,
		   int fd,
		   int flags,
		   int (*callback) (int fd, int flags, void *user_data),
		   void *userdata);
	void *(*xchatus_unhook) (xchatus_plugin *ph,
	      xchatus_hook *hook);
	void (*xchatus_print) (xchatus_plugin *ph,
	     const char *text);
	void (*xchatus_printf) (xchatus_plugin *ph,
	      const char *format, ...);
	void (*xchatus_command) (xchatus_plugin *ph,
	       const char *command);
	void (*xchatus_commandf) (xchatus_plugin *ph,
		const char *format, ...);
	int (*xchatus_nickcmp) (xchatus_plugin *ph,
	       const char *s1,
	       const char *s2);
	int (*xchatus_set_context) (xchatus_plugin *ph,
		   xchatus_context *ctx);
	xchatus_context *(*xchatus_find_context) (xchatus_plugin *ph,
		    const char *servname,
		    const char *channel);
	xchatus_context *(*xchatus_get_context) (xchatus_plugin *ph);
	const char *(*xchatus_get_info) (xchatus_plugin *ph,
		const char *id);
	int (*xchatus_get_prefs) (xchatus_plugin *ph,
		 const char *name,
		 const char **string,
		 int *integer);
	xchatus_list * (*xchatus_list_get) (xchatus_plugin *ph,
		const char *name);
	void (*xchatus_list_free) (xchatus_plugin *ph,
		 xchatus_list *xlist);
	const char * const * (*xchatus_list_fields) (xchatus_plugin *ph,
		   const char *name);
	int (*xchatus_list_next) (xchatus_plugin *ph,
		 xchatus_list *xlist);
	const char * (*xchatus_list_str) (xchatus_plugin *ph,
		xchatus_list *xlist,
		const char *name);
	int (*xchatus_list_int) (xchatus_plugin *ph,
		xchatus_list *xlist,
		const char *name);
	void * (*xchatus_plugingui_add) (xchatus_plugin *ph,
		     const char *filename,
		     const char *name,
		     const char *desc,
		     const char *version,
		     char *reserved);
	void (*xchatus_plugingui_remove) (xchatus_plugin *ph,
			void *handle);
	int (*xchatus_emit_print) (xchatus_plugin *ph,
			const char *event_name, ...);
	void *(*xchatus_read_fd) (xchatus_plugin *ph);
	time_t (*xchatus_list_time) (xchatus_plugin *ph,
		xchatus_list *xlist,
		const char *name);
	char *(*xchatus_gettext) (xchatus_plugin *ph,
		const char *msgid);
	void (*xchatus_send_modes) (xchatus_plugin *ph,
		  const char **targets,
		  int ntargets,
		  int modes_per_line,
		  char sign,
		  char mode);
	char *(*xchatus_strip) (xchatus_plugin *ph,
	     const char *str,
	     int len,
	     int flags);
	void (*xchatus_free) (xchatus_plugin *ph,
	    void *ptr);
	int (*xchatus_pluginpref_set_str) (xchatus_plugin *ph,
		const char *var,
		const char *value);
	int (*xchatus_pluginpref_get_str) (xchatus_plugin *ph,
		const char *var,
		char *dest);
	int (*xchatus_pluginpref_set_int) (xchatus_plugin *ph,
		const char *var,
		int value);
	int (*xchatus_pluginpref_get_int) (xchatus_plugin *ph,
		const char *var);
	int (*xchatus_pluginpref_delete) (xchatus_plugin *ph,
		const char *var);
	int (*xchatus_pluginpref_list) (xchatus_plugin *ph,
		char *dest);
	xchatus_hook *(*xchatus_hook_server_attrs) (xchatus_plugin *ph,
		   const char *name,
		   int pri,
		   int (*callback) (char *word[], char *word_eol[],
							xchatus_event_attrs *attrs, void *user_data),
		   void *userdata);
	xchatus_hook *(*xchatus_hook_print_attrs) (xchatus_plugin *ph,
		  const char *name,
		  int pri,
		  int (*callback) (char *word[], xchatus_event_attrs *attrs,
						   void *user_data),
		  void *userdata);
	int (*xchatus_emit_print_attrs) (xchatus_plugin *ph, xchatus_event_attrs *attrs,
									 const char *event_name, ...);
	xchatus_event_attrs *(*xchatus_event_attrs_create) (xchatus_plugin *ph);
	void (*xchatus_event_attrs_free) (xchatus_plugin *ph,
									  xchatus_event_attrs *attrs);

	/* PRIVATE FIELDS! */
	void *handle;		/* from dlopen */
	char *filename;	/* loaded from */
	char *name;
	char *desc;
	char *version;
	session *context;
	void *deinit_callback;	/* pointer to xchatus_plugin_deinit */
	unsigned int fake:1;		/* fake plugin. Added by xchatus_plugingui_add() */
	unsigned int free_strings:1;		/* free name,desc,version? */
};
#endif

GModule *module_load (char *filename);
char *plugin_load (session *sess, char *filename, char *arg);
int plugin_reload (session *sess, char *name, int by_filename);
void plugin_add (session *sess, char *filename, void *handle, void *init_func, void *deinit_func, char *arg, int fake);
int plugin_kill (char *name, int by_filename);
void plugin_kill_all (void);
void plugin_auto_load (session *sess);
int plugin_emit_command (session *sess, char *name, char *word[], char *word_eol[]);
int plugin_emit_server (session *sess, char *name, char *word[], char *word_eol[],
						time_t server_time);
int plugin_emit_print (session *sess, char *word[], time_t server_time);
int plugin_emit_dummy_print (session *sess, char *name);
int plugin_emit_keypress (session *sess, unsigned int state, unsigned int keyval, gunichar key);
GList* plugin_command_list(GList *tmp_list);
int plugin_show_help (session *sess, char *cmd);
void plugin_command_foreach (session *sess, void *userdata, void (*cb) (session *sess, void *userdata, char *name, char *usage));
session *plugin_find_context (const char *servname, const char *channel, server *current_server);

/* On macOS, G_MODULE_SUFFIX says "so" but meson uses "dylib"
 * https://github.com/mesonbuild/meson/issues/1160 */
#if defined(__APPLE__)
#  define PLUGIN_SUFFIX "dylib"
#else
#  define PLUGIN_SUFFIX G_MODULE_SUFFIX
#endif

#endif

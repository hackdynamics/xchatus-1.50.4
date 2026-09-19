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

/* You can distribute this header with your plugins for easy compilation */
#ifndef HEXCHAT_PLUGIN_H
#define HEXCHAT_PLUGIN_H

#include <time.h>

#define HEXCHAT_PRI_HIGHEST	127
#define HEXCHAT_PRI_HIGH		64
#define HEXCHAT_PRI_NORM		0
#define HEXCHAT_PRI_LOW		(-64)
#define HEXCHAT_PRI_LOWEST	(-128)

#define HEXCHAT_FD_READ		1
#define HEXCHAT_FD_WRITE		2
#define HEXCHAT_FD_EXCEPTION	4
#define HEXCHAT_FD_NOTSOCKET	8

#define HEXCHAT_EAT_NONE		0	/* pass it on through! */
#define HEXCHAT_EAT_HEXCHAT		1	/* don't let XCHATUS see this event */
#define HEXCHAT_EAT_PLUGIN	2	/* don't let other plugins see this event */
#define HEXCHAT_EAT_ALL		(HEXCHAT_EAT_HEXCHAT|HEXCHAT_EAT_PLUGIN)	/* don't let anything see this event */

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _xchatus_plugin xchatus_plugin;
typedef struct _xchatus_list xchatus_list;
typedef struct _xchatus_hook xchatus_hook;
#ifndef PLUGIN_C
typedef struct _xchatus_context xchatus_context;
#endif
typedef struct
{
	time_t server_time_utc; /* 0 if not used */
} xchatus_event_attrs;

#ifndef PLUGIN_C
struct _xchatus_plugin
{
	/* these are only used on win32 */
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
	      const char *format, ...)
#ifdef __GNUC__
	__attribute__((format(printf, 2, 3)))
#endif
	;
	void (*xchatus_command) (xchatus_plugin *ph,
	       const char *command);
	void (*xchatus_commandf) (xchatus_plugin *ph,
		const char *format, ...)
#ifdef __GNUC__
	__attribute__((format(printf, 2, 3)))
#endif
	;
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
	int (*xchatus_read_fd) (xchatus_plugin *ph,
			void *src,
			char *buf,
			int *len);
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
};
#endif


xchatus_hook *
xchatus_hook_command (xchatus_plugin *ph,
		    const char *name,
		    int pri,
		    int (*callback) (char *word[], char *word_eol[], void *user_data),
		    const char *help_text,
		    void *userdata);

xchatus_event_attrs *xchatus_event_attrs_create (xchatus_plugin *ph);

void xchatus_event_attrs_free (xchatus_plugin *ph, xchatus_event_attrs *attrs);

xchatus_hook *
xchatus_hook_server (xchatus_plugin *ph,
		   const char *name,
		   int pri,
		   int (*callback) (char *word[], char *word_eol[], void *user_data),
		   void *userdata);

xchatus_hook *
xchatus_hook_server_attrs (xchatus_plugin *ph,
		   const char *name,
		   int pri,
		   int (*callback) (char *word[], char *word_eol[],
							xchatus_event_attrs *attrs, void *user_data),
		   void *userdata);

xchatus_hook *
xchatus_hook_print (xchatus_plugin *ph,
		  const char *name,
		  int pri,
		  int (*callback) (char *word[], void *user_data),
		  void *userdata);

xchatus_hook *
xchatus_hook_print_attrs (xchatus_plugin *ph,
		  const char *name,
		  int pri,
		  int (*callback) (char *word[], xchatus_event_attrs *attrs,
						   void *user_data),
		  void *userdata);

xchatus_hook *
xchatus_hook_timer (xchatus_plugin *ph,
		  int timeout,
		  int (*callback) (void *user_data),
		  void *userdata);

xchatus_hook *
xchatus_hook_fd (xchatus_plugin *ph,
		int fd,
		int flags,
		int (*callback) (int fd, int flags, void *user_data),
		void *userdata);

void *
xchatus_unhook (xchatus_plugin *ph,
	      xchatus_hook *hook);

void
xchatus_print (xchatus_plugin *ph,
	     const char *text);

void
xchatus_printf (xchatus_plugin *ph,
	      const char *format, ...)
#ifdef __GNUC__
	__attribute__((format(printf, 2, 3)))
#endif
;

void
xchatus_command (xchatus_plugin *ph,
	       const char *command);

void
xchatus_commandf (xchatus_plugin *ph,
		const char *format, ...)
#ifdef __GNUC__
	__attribute__((format(printf, 2, 3)))
#endif
;

int
xchatus_nickcmp (xchatus_plugin *ph,
	       const char *s1,
	       const char *s2);

int
xchatus_set_context (xchatus_plugin *ph,
		   xchatus_context *ctx);

xchatus_context *
xchatus_find_context (xchatus_plugin *ph,
		    const char *servname,
		    const char *channel);

xchatus_context *
xchatus_get_context (xchatus_plugin *ph);

const char *
xchatus_get_info (xchatus_plugin *ph,
		const char *id);

int
xchatus_get_prefs (xchatus_plugin *ph,
		 const char *name,
		 const char **string,
		 int *integer);

xchatus_list *
xchatus_list_get (xchatus_plugin *ph,
		const char *name);

void
xchatus_list_free (xchatus_plugin *ph,
		 xchatus_list *xlist);

const char * const *
xchatus_list_fields (xchatus_plugin *ph,
		   const char *name);

int
xchatus_list_next (xchatus_plugin *ph,
		 xchatus_list *xlist);

const char *
xchatus_list_str (xchatus_plugin *ph,
		xchatus_list *xlist,
		const char *name);

int
xchatus_list_int (xchatus_plugin *ph,
		xchatus_list *xlist,
		const char *name);

time_t
xchatus_list_time (xchatus_plugin *ph,
		 xchatus_list *xlist,
		 const char *name);

void *
xchatus_plugingui_add (xchatus_plugin *ph,
		     const char *filename,
		     const char *name,
		     const char *desc,
		     const char *version,
		     char *reserved);

void
xchatus_plugingui_remove (xchatus_plugin *ph,
			void *handle);

int 
xchatus_emit_print (xchatus_plugin *ph,
		  const char *event_name, ...);

int 
xchatus_emit_print_attrs (xchatus_plugin *ph, xchatus_event_attrs *attrs,
						  const char *event_name, ...);

char *
xchatus_gettext (xchatus_plugin *ph,
	       const char *msgid);

void
xchatus_send_modes (xchatus_plugin *ph,
		  const char **targets,
		  int ntargets,
		  int modes_per_line,
		  char sign,
		  char mode);

char *
xchatus_strip (xchatus_plugin *ph,
	     const char *str,
	     int len,
	     int flags);

void
xchatus_free (xchatus_plugin *ph,
	    void *ptr);

int
xchatus_pluginpref_set_str (xchatus_plugin *ph,
		const char *var,
		const char *value);

int
xchatus_pluginpref_get_str (xchatus_plugin *ph,
		const char *var,
		char *dest);

int
xchatus_pluginpref_set_int (xchatus_plugin *ph,
		const char *var,
		int value);
int
xchatus_pluginpref_get_int (xchatus_plugin *ph,
		const char *var);

int
xchatus_pluginpref_delete (xchatus_plugin *ph,
		const char *var);

int
xchatus_pluginpref_list (xchatus_plugin *ph,
		char *dest);

#if !defined(PLUGIN_C) && (defined(WIN32) || defined(__CYGWIN__))
#ifndef HEXCHAT_PLUGIN_HANDLE
#define HEXCHAT_PLUGIN_HANDLE (ph)
#endif
#define xchatus_hook_command ((HEXCHAT_PLUGIN_HANDLE)->xchatus_hook_command)
#define xchatus_event_attrs_create ((HEXCHAT_PLUGIN_HANDLE)->xchatus_event_attrs_create)
#define xchatus_event_attrs_free ((HEXCHAT_PLUGIN_HANDLE)->xchatus_event_attrs_free)
#define xchatus_hook_server ((HEXCHAT_PLUGIN_HANDLE)->xchatus_hook_server)
#define xchatus_hook_server_attrs ((HEXCHAT_PLUGIN_HANDLE)->xchatus_hook_server_attrs)
#define xchatus_hook_print ((HEXCHAT_PLUGIN_HANDLE)->xchatus_hook_print)
#define xchatus_hook_print_attrs ((HEXCHAT_PLUGIN_HANDLE)->xchatus_hook_print_attrs)
#define xchatus_hook_timer ((HEXCHAT_PLUGIN_HANDLE)->xchatus_hook_timer)
#define xchatus_hook_fd ((HEXCHAT_PLUGIN_HANDLE)->xchatus_hook_fd)
#define xchatus_unhook ((HEXCHAT_PLUGIN_HANDLE)->xchatus_unhook)
#define xchatus_print ((HEXCHAT_PLUGIN_HANDLE)->xchatus_print)
#define xchatus_printf ((HEXCHAT_PLUGIN_HANDLE)->xchatus_printf)
#define xchatus_command ((HEXCHAT_PLUGIN_HANDLE)->xchatus_command)
#define xchatus_commandf ((HEXCHAT_PLUGIN_HANDLE)->xchatus_commandf)
#define xchatus_nickcmp ((HEXCHAT_PLUGIN_HANDLE)->xchatus_nickcmp)
#define xchatus_set_context ((HEXCHAT_PLUGIN_HANDLE)->xchatus_set_context)
#define xchatus_find_context ((HEXCHAT_PLUGIN_HANDLE)->xchatus_find_context)
#define xchatus_get_context ((HEXCHAT_PLUGIN_HANDLE)->xchatus_get_context)
#define xchatus_get_info ((HEXCHAT_PLUGIN_HANDLE)->xchatus_get_info)
#define xchatus_get_prefs ((HEXCHAT_PLUGIN_HANDLE)->xchatus_get_prefs)
#define xchatus_list_get ((HEXCHAT_PLUGIN_HANDLE)->xchatus_list_get)
#define xchatus_list_free ((HEXCHAT_PLUGIN_HANDLE)->xchatus_list_free)
#define xchatus_list_fields ((HEXCHAT_PLUGIN_HANDLE)->xchatus_list_fields)
#define xchatus_list_next ((HEXCHAT_PLUGIN_HANDLE)->xchatus_list_next)
#define xchatus_list_str ((HEXCHAT_PLUGIN_HANDLE)->xchatus_list_str)
#define xchatus_list_int ((HEXCHAT_PLUGIN_HANDLE)->xchatus_list_int)
#define xchatus_plugingui_add ((HEXCHAT_PLUGIN_HANDLE)->xchatus_plugingui_add)
#define xchatus_plugingui_remove ((HEXCHAT_PLUGIN_HANDLE)->xchatus_plugingui_remove)
#define xchatus_emit_print ((HEXCHAT_PLUGIN_HANDLE)->xchatus_emit_print)
#define xchatus_emit_print_attrs ((HEXCHAT_PLUGIN_HANDLE)->xchatus_emit_print_attrs)
#define xchatus_list_time ((HEXCHAT_PLUGIN_HANDLE)->xchatus_list_time)
#define xchatus_gettext ((HEXCHAT_PLUGIN_HANDLE)->xchatus_gettext)
#define xchatus_send_modes ((HEXCHAT_PLUGIN_HANDLE)->xchatus_send_modes)
#define xchatus_strip ((HEXCHAT_PLUGIN_HANDLE)->xchatus_strip)
#define xchatus_free ((HEXCHAT_PLUGIN_HANDLE)->xchatus_free)
#define xchatus_pluginpref_set_str ((HEXCHAT_PLUGIN_HANDLE)->xchatus_pluginpref_set_str)
#define xchatus_pluginpref_get_str ((HEXCHAT_PLUGIN_HANDLE)->xchatus_pluginpref_get_str)
#define xchatus_pluginpref_set_int ((HEXCHAT_PLUGIN_HANDLE)->xchatus_pluginpref_set_int)
#define xchatus_pluginpref_get_int ((HEXCHAT_PLUGIN_HANDLE)->xchatus_pluginpref_get_int)
#define xchatus_pluginpref_delete ((HEXCHAT_PLUGIN_HANDLE)->xchatus_pluginpref_delete)
#define xchatus_pluginpref_list ((HEXCHAT_PLUGIN_HANDLE)->xchatus_pluginpref_list)
#endif

#ifdef __cplusplus
}
#endif
#endif

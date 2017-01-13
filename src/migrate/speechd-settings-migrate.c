/*
 * speechd-settings-migrate.c - Dotconf to GSettings migration tool
 *
 * Copyright (C) 2016 Brailcom, o.p.s.
 *
 * This is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this package; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 *
 */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <glib.h>
#include <gstdio.h>
#include <dotconf.h>

/* Global data structures */
GSettings *speechd_server_settings = NULL;
GSettings *module_settings = NULL;

typedef struct
{
	gchar *dotconf_setting_name;
	gchar *gsettings_setting_name;
} DotConfToGSettingsMapping;

const DotConfToGSettingsMapping server_dotconf_integer_settings[] = {
{"DefaultRate", "default-rate"},
	{"DefaultPitch", "default-pitch"},
	{"DefaultVolume", "default-volume"},

const DotConfToGSettingsMapping server_)dotconf_uint_settings = {
	{"DefaultPauseContext", "default-pause-context"},
	{"Port", "port"},
	{"Timeout", "timeout"},
	{"LogLevel", "log-level"},
	{"AudioPulseMinLength", "audio-pulse-min-length"},

const DotConfToGSettingsMapping server_dotconf_string_settings = {
	{"SocketPath", "socket-path"},
	{"LogDir", "log-dir"},
	{"DefaultLanguage", "default-language"},
	{"DefaultClientName", "default-client-name"},
	{"AudioOutputMethod", "audio-output-method"},
	{"AudioPulseServer", "audio-pulse-server"},
	{"AudioALSADevice", "audio-alsa-device"},
	{"AudioOSSDevice", "audio-oss-device"},
	{"AudioNASServer", "audio-nas-server"},

const DotConfToGSettingsMapping server_dotconf_bool_settings = {
	{"LocalhostAccessOnly", "localhost-access-only"},
	{"DefaultSpelling", "default-spelling"},

const DotConfToGSettingsMapping server_dotconf_enum_settings = {
	{"DefaultVoiceType", "default-voice-type"},
	{"CommunicationMethod", "communication-method"},
	{"DefaultPriority", "default-priority"},
	{"DefaultPunctuationMode", "default-punctuation-mode"},
	{"DefaultCapLetRecognition", "default-capital-letter-recognition"},

# -----OUTPUT MODULES CONFIGURATION-----

# Each AddModule line loads an output module.
#  Syntax: AddModule "name" "binary" "configuration" "logfile"
#  - name is the name under which you can access this module
#  - binary is the path to the binary executable of this module,
#    either relative (to lib/speech-dispatcher-modules/) or absolute
#  - configuration is the path to the config file of this module,
#    either relative (to etc/speech-dispatcher/modules/) or absolute

#AddModule "espeak"       "sd_espeak"   "espeak.conf"
#AddModule "espeak-ng"    "sd_espeak-ng" "espeak-ng.conf"
#AddModule "festival"     "sd_festival"  "festival.conf"
#AddModule "flite"        "sd_flite"     "flite.conf"
#AddModule "ivona"	 "sd_ivona"    "ivona.conf"
#AddModule "pico"        "sd_pico"     "pico.conf"
#AddModule "espeak-generic" "sd_generic" "espeak-generic.conf"
#AddModule "espeak-mbrola-generic" "sd_generic" "espeak-mbrola-generic.conf"
#AddModule "swift-generic" "sd_generic" "swift-generic.conf"
#AddModule "epos-generic" "sd_generic"   "epos-generic.conf"
#AddModule "dtk-generic"  "sd_generic"   "dtk-generic.conf"
#AddModule "pico-generic"  "sd_generic"   "pico-generic.conf"
#AddModule "ibmtts"       "sd_ibmtts"    "ibmtts.conf"
#AddModule "cicero"        "sd_cicero"     "cicero.conf"

# DO NOT REMOVE the following line unless you have
# a specific reason -- this is the fallback output module
# that is only used when no other modules are in use
#AddModule "dummy"         "sd_dummy"      ""

# The output module testing doesn't actually connect to anything. It
# outputs the requested commands to standard output and reads
# responses from stdandard input. This way, Speech Dispatcher's
# communication with output modules can be tested easily.

# AddModule "testing"

# The DefaultModule selects which output module is the default.  You
# must use one of the names of the modules loaded with AddModule.

DefaultModule espeak

# The LanguageDefaultModule selects which output modules are prefered
# for specified languages.

#LanguageDefaultModule "en"  "espeak"
#LanguageDefaultModule "cs"  "festival"
#LanguageDefaultModule "es"  "festival"

# -----CLIENT SPECIFIC CONFIGURATION-----

# Here you can include the files with client-specific configuration
# for different types of clients. They must contain one or more sections with
# this structure:
#     BeginClient "emacs:*"
#          DefaultPunctuationMode "some"
#          ...and/or some other settings
#     EndClient
# The parameter of BeginClient tells Speech Dispatcher which clients
# it should apply the settings to (it does glob-style matching, you can use
# * to match any number of characters and ? to match one character)

# There are some sample client settings

Include "clients/*.conf"

# The DisableAutoSpawn option will disable the autospawn mechanism.
# Thus the server will not start automatically on requests from the clients
# DisableAutoSpawn


#ifndef STREAMLINE_ANNOTATE_H
#define STREAMLINE_ANNOTATE_H

/*
 *  User-space only macros:
 *  ANNOTATE_DEFINE  You must put 'ANNOTATE_DEFINE;' one place in your program
 *  ANNOTATE_SETUP   Execute at the start of the program before other ANNOTATE macros are called
 *  
 *  User-space and Kernel-space macros:
 *  ANNOTATE(string)                          String annotation
 *  ANNOTATE_COLOR(color, string)             String annotation with color
 *  ANNOTATE_END()                            Terminate an annotation
 *  ANNOTATE_VISUAL(data, length, string)     Image annotation with optional string
 *  ANNOTATE_MARKER()                         Marker annotation
 *  ANNOTATE_MARKER_STR(string)               Marker annotation with a string
 *  ANNOTATE_MARKER_COLOR(color)              Marker annotation with a color
 *  ANNOTATE_MARKER_COLOR_STR(color, string)  Marker annotation with a string and color
 */

// ESC character, hex RGB (little endian)
#define ANNOTATE_RED    0x0000ff1b
#define ANNOTATE_BLUE   0xff00001b
#define ANNOTATE_GREEN  0x00ff001b
#define ANNOTATE_PURPLE 0xff00ff1b
#define ANNOTATE_YELLOW 0x00ffff1b
#define ANNOTATE_CYAN   0xffff001b
#define ANNOTATE_WHITE  0xffffff1b
#define ANNOTATE_LTGRAY 0xbbbbbb1b
#define ANNOTATE_DKGRAY 0x5555551b
#define ANNOTATE_BLACK  0x0000001b

#ifdef __KERNEL__  // Start of kernel-space macro definitions
void gator_annotate(char* string);
void gator_annotate_color(int color, char* string);
void gator_annotate_end(void);
void gator_annotate_visual(char* data, unsigned int length, char* string);
void gator_annotate_marker(void);
void gator_annotate_marker_str(char* string);
void gator_annotate_marker_color(int color);
void gator_annotate_marker_color_str(int color, char* string);

#define ANNOTATE(string) do { \
	void (*annotate_ptr)(char*); \
	annotate_ptr = symbol_get(gator_annotate); \
	if (annotate_ptr) { \
		annotate_ptr(string); \
		symbol_put(gator_annotate); \
	}} while(0)

#define ANNOTATE_COLOR(color, string) do { \
	void (*annotate_color_ptr)(int, char*); \
	annotate_color_ptr = symbol_get(gator_annotate_color); \
	if (annotate_color_ptr) { \
		annotate_color_ptr(color, string); \
		symbol_put(gator_annotate_color); \
	}} while(0)

#define ANNOTATE_END() do { \
	void (*annotate_end_ptr)(void); \
	annotate_end_ptr = symbol_get(gator_annotate_end); \
	if (annotate_end_ptr) { \
		annotate_end_ptr(); \
		symbol_put(gator_annotate_end); \
	}} while(0)
	
#define ANNOTATE_VISUAL(data, length, string) do { \
	void (*annotate_visual_ptr)(char*, unsigned int, char*); \
	annotate_visual_ptr = symbol_get(gator_annotate_visual); \
	if (annotate_visual_ptr) { \
		annotate_visual_ptr(data, length, string); \
		symbol_put(gator_annotate_visual); \
	}} while(0)

#define ANNOTATE_MARKER() do { \
	void (*annotate_marker_ptr)(void); \
	annotate_marker_ptr = symbol_get(gator_annotate_marker); \
	if (annotate_marker_ptr) { \
		annotate_marker_ptr(); \
		symbol_put(gator_annotate_marker); \
	}} while(0)

#define ANNOTATE_MARKER_STR(string) do { \
	void (*annotate_marker_str_ptr)(char*); \
	annotate_marker_str_ptr = symbol_get(gator_annotate_marker_str); \
	if (annotate_marker_str_ptr) { \
		annotate_marker_str_ptr(string); \
		symbol_put(gator_annotate_marker_str); \
	}} while(0)

#define ANNOTATE_MARKER_COLOR(color) do { \
	void (*annotate_marker_color_ptr)(int); \
	annotate_marker_color_ptr = symbol_get(gator_annotate_marker_color); \
	if (annotate_marker_color_ptr) { \
		annotate_marker_color_ptr(color); \
		symbol_put(gator_annotate_marker_color); \
	}} while(0)

#define ANNOTATE_MARKER_COLOR_STR(color, string) do { \
	void (*annotate_marker_color_str_ptr)(int, char*); \
	annotate_marker_color_str_ptr = symbol_get(gator_annotate_marker_color_str); \
	if (annotate_marker_color_str_ptr) { \
		annotate_marker_color_str_ptr(color, string); \
		symbol_put(gator_annotate_marker_color_str); \
	}} while(0)

#else  // Start of user-space macro definitions

#include <stdio.h>
#include <string.h>
extern FILE *gator_annotate;

#define ANNOTATE_DEFINE   FILE *gator_annotate

#define ANNOTATE_SETUP  do { if (!gator_annotate) {\
	gator_annotate = fopen("/dev/gator/annotate", "wb"); \
	if (gator_annotate) { setvbuf(gator_annotate, (char *)NULL, _IONBF, 0); }}} while(0)

#define ANNOTATE(data)   do { if (gator_annotate) { \
	const char* annotate_data = (data); \
	ANNOTATE_WRITE(annotate_data, strlen(annotate_data) + 1); }} while(0)

#define ANNOTATE_COLOR(setColor, data) do { if (gator_annotate) { \
	char* annotate_data = (data); \
	int gator_color = (setColor); \
	ANNOTATE_WRITE(&gator_color, sizeof(gator_color)); \
	ANNOTATE_WRITE(annotate_data, strlen(annotate_data) + 1); }} while(0)

#define ANNOTATE_END() do { if (gator_annotate) { \
	int annotate_fputc_retval = -1; \
	while (annotate_fputc_retval == -1) { \
		annotate_fputc_retval = fputc('\0', gator_annotate); \
	}}} while(0)

#define ANNOTATE_VISUAL(data, length, str) do { if (gator_annotate) { \
	char* gator_str = (str); \
	int gator_str_size = strlen(gator_str) & 0xffff; \
	int gator_local_length = (length); \
	long long visual_annotation = 0x011c | (gator_str_size << 16) | ((long long)gator_local_length << 32); \
	ANNOTATE_WRITE(&visual_annotation, 8); \
	ANNOTATE_WRITE(gator_str, gator_str_size); \
	ANNOTATE_WRITE((data), gator_local_length); }} while(0)

#define ANNOTATE_MARKER() do { if (gator_annotate) { \
	int marker_annotation = 0x00021c; \
	ANNOTATE_WRITE(&marker_annotation, 3); }} while(0)

#define ANNOTATE_MARKER_STR(data) do { if (gator_annotate) { \
	char* annotate_data = (data); \
	int marker_annotation = 0x021c; \
	ANNOTATE_WRITE(&marker_annotation, 2); \
	ANNOTATE_WRITE(annotate_data, strlen(annotate_data) + 1); }} while(0)

#define ANNOTATE_MARKER_COLOR(setColor) do { if (gator_annotate) { \
	int gator_color = (setColor); \
	long long marker_annotation = (0x021c | ((long long)gator_color << 16)) & 0x0000ffffffffffffLL; \
	ANNOTATE_WRITE(&marker_annotation, 7); }} while(0)

#define ANNOTATE_MARKER_COLOR_STR(setColor, data) do { if (gator_annotate) { \
	char* annotate_data = (data); \
	int gator_color = (setColor); \
	long long marker_annotation = 0x021c | ((long long)gator_color << 16); \
	ANNOTATE_WRITE(&marker_annotation, 6); \
	ANNOTATE_WRITE(annotate_data, strlen(annotate_data) + 1); }} while(0)

// Not to be called by the user
#define ANNOTATE_WRITE(data, length) { \
	int annotate_pos = 0; \
	int annotate_fwrite_length = (length); \
	while (annotate_pos < (int)annotate_fwrite_length) { \
		annotate_pos += fwrite(&((char*)(data))[annotate_pos], 1, annotate_fwrite_length - annotate_pos, gator_annotate); \
	} \
	fflush(gator_annotate); }

#endif // _KERNEL_
#endif // STREAMLINE_ANNOTATE_H

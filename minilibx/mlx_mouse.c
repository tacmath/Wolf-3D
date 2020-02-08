#include        <stdio.h>	
#include	<X11/cursorfont.h>
#include	"mlx_int.h"


int     mlx_mouse_hide(void *mlx_ptrv, void *win_ptrv)
{
	t_xvar *mlx_ptr;
	t_win_list *win_ptr;
	Cursor invisibleCursor;
	Pixmap bitmapempty;
	XColor nope;
	static char empty[] = { 0,0,0,0,0,0,0,0};

	mlx_ptr = (t_xvar*) mlx_ptrv;
	win_ptr = (t_win_list*) win_ptrv;
	nope.red = nope.green = nope.blue = 0;
	bitmapempty = XCreateBitmapFromData(mlx_ptr->display, win_ptr->window, empty, 8, 8);
	invisibleCursor = XCreatePixmapCursor(mlx_ptr->display, bitmapempty, bitmapempty, 
                                     &nope, &nope, 0, 0);
	XDefineCursor(mlx_ptr->display,win_ptr->window, invisibleCursor);
	XFreeCursor(mlx_ptr->display, invisibleCursor);
	XFreePixmap(mlx_ptr->display, bitmapempty);
	return (0);
}

int     mlx_mouse_show(void *mlx_ptrv, void *win_ptrv)
{
 	t_xvar *mlx_ptr;
	t_win_list *win_ptr;
	Cursor cursor;
	
	mlx_ptr = (t_xvar*) mlx_ptrv;
	win_ptr = (t_win_list*) win_ptrv;
	cursor=XCreateFontCursor(mlx_ptr->display,XC_left_ptr);
	XDefineCursor(mlx_ptr->display, win_ptr->window, cursor);
	XFreeCursor(mlx_ptr->display, cursor);

  return (0);
}

int     mlx_mouse_move(void *mlx_ptrv, void *win_ptrv, int x, int y)
{

 	t_xvar *mlx_ptr;
	t_win_list *win_ptr;

	mlx_ptr = (t_xvar*) mlx_ptrv;
	win_ptr = (t_win_list*) win_ptrv;
	XWarpPointer(mlx_ptr->display, None, win_ptr->window, 0, 0, 0, 0, x, y);
	return (0);
}

#include        <stdio.h>

#import <Cocoa/Cocoa.h>
#import <OpenGL/gl3.h>

#include "mlx_int.h"
#include "mlx_new_window.h"

int     mlx_mouse_hide(void *mlx_ptr, void *win_ptr)
{
  //  CGDisplayHideCursor(kCGDirectMainDisplay);
  (void)mlx_ptr;
  (void)win_ptr;
  [NSCursor hide];
  return (0);
}

int     mlx_mouse_show(void *mlx_ptr, void *win_ptr)
{
  //  CGDisplayShowCursor(kCGDirectMainDisplay);
  (void)mlx_ptr;
  (void)win_ptr;
  [NSCursor unhide];
  return (0);
}

int     mlx_mouse_move(void *mlx_ptr, void *win_ptr, int x, int y)
{
  mlx_win_list_t *win;
  CGPoint       point;
  NSRect        pos;
  id    thewin;

  (void)mlx_ptr;
  win = (mlx_win_list_t*)win_ptr;
  thewin = [(id)(win->winid) window];
  pos = [thewin frame];
  //  printf("got win pos %f %f\n", pos.origin.x, pos.origin.y);
  point.x = pos.origin.x + x;
  point.y = NSHeight([[thewin screen] frame]) - NSHeight([(id)(win->winid) frame]) - pos.origin.y + 1 + y;
  CGWarpMouseCursorPosition(point);
  CGAssociateMouseAndMouseCursorPosition(true);
  return (0);
}


int     mlx_mouse_get_pos(mlx_win_list_t *win, int *x, int *y)
{
  CGPoint       point;
  id            thewin;
  NSRect        pos;

  thewin = [(id)(win->winid) window];
  pos = [(id)(win->winid) frame];
  point = [thewin mouseLocationOutsideOfEventStream];
  *x = point.x;
  *y = NSHeight(pos) - 1 - point.y;
  return (0);
}

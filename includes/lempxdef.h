/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   lempXdef.h                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lperron <lperron@student.le-101.f>         +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/27 16:03:54 by lperron      #+#   ##    ##    #+#       */
/*   Updated: 2019/05/09 15:44:29 by lperron     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef LEMPXDEF_H
# define LEMPXDEF_H

# define NOEVENTMASK			0L
# define KEYPRESSMASK			(1L<<0)
# define KEYRELEASEMASK			(1L<<1)
# define BUTTONPRESSMASK		(1L<<2)
# define BUTTONRELEASEMASK		(1L<<3)
# define ENTERWINDOWMASK		(1L<<4)
# define LEAVEWINDOWMASK		(1L<<5)
# define POINTERMOTIONMASK		(1L<<6)
# define POINTERMOTIONHINTMASK		(1L<<7)
# define BUTTON1MOTIONMASK		(1L<<8)
# define BUTTON2MOTIONMASK		(1L<<9)
# define BUTTON3MOTIONMASK		(1L<<10)
# define BUTTON4MOTIONMASK		(1L<<11)
# define BUTTON5MOTIONMASK		(1L<<12)
# define BUTTONMOTIONMASK		(1L<<13)
# define KEYMAPSTATEMASK		(1L<<14)
# define EXPOSUREMASK			(1L<<15)
# define VISIBILITYCHANGEMASK		(1L<<16)
# define STRUCTURENOTIFYMASK		(1L<<17)
# define RESIZEREDIRECTMASK		(1L<<18)
# define SUBSTRUCTURENOTIFYMASK		(1L<<19)
# define SUBSTRUCTUREREDIRECTMASK	(1L<<20)
# define FOCUSCHANGEMASK		(1L<<21)
# define PROPERTYCHANGEMASK		(1L<<22)
# define COLORMAPCHANGEMASK		(1L<<23)
# define OWNERGRABBUTTONMASK		(1L<<24)

# define KEYPRESS		2
# define KEYRELEASE		3
# define BUTTONPRESS		4
# define BUTTONRELEASE		5
# define MOTIONNOTIFY		6
# define ENTERNOTIFY		7
# define LEAVENOTIFY		8
# define FOCUSIN		9
# define FOCUSOUT		10
# define KEYMAPNOTIFY		11
# define EXPOSE			12
# define GRAPHICSEXPOSE		13
# define NOEXPOSE		14
# define VISIBILITYNOTIFY	15
# define CREATENOTIFY		16
# define DESTROYNOTIFY		17
# define UNMAPNOTIFY		18
# define MAPNOTIFY		19
# define MAPREQUEST		20
# define REPARENTNOTIFY		21
# define CONFIGURENOTIFY	22
# define CONFIGUREREQUEST	23
# define GRAVITYNOTIFY		24
# define RESIZEREQUEST		25
# define CIRCULATENOTIFY	26
# define CIRCULATEREQUEST	27
# define PROPERTYNOTIFY		28
# define SELECTIONCLEAR		29
# define SELECTIONREQUEST	30
# define SELECTIONNOTIFY	31
# define COLORMAPNOTIFY		32
# define CLIENTMESSAGE		33
# define MAPPINGNOTIFY		34
# define GENERICEVENT		35
# define LASTEVENT		36

#endif

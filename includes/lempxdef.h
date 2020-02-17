/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lempxdef.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperron <lperron@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/16 17:24:48 by lperron           #+#    #+#             */
/*   Updated: 2020/02/16 17:34:08 by lperron          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMPXDEF_H
# define LEMPXDEF_H

# define NOEVENTMASK			0L
# define KEYPRESSMASK			1L
# define KEYRELEASEMASK			2L
# define BUTTONPRESSMASK		4L
# define BUTTONRELEASEMASK		8L
# define ENTERWINDOWMASK		16L
# define LEAVEWINDOWMASK		32L
# define POINTERMOTIONMASK		64L
# define POINTERMOTIONHINTMASK		128L
# define BUTTON1MOTIONMASK		256L
# define BUTTON2MOTIONMASK		512L
# define BUTTON3MOTIONMASK		1024L
# define BUTTON4MOTIONMASK		2048L
# define BUTTON5MOTIONMASK		4096L
# define BUTTONMOTIONMASK		8192L
# define KEYMAPSTATEMASK		16384L
# define EXPOSUREMASK			0x8000L
# define VISIBILITYCHANGEMASK		0x10000L
# define STRUCTURENOTIFYMASK		0x20000L
# define RESIZEREDIRECTMASK		0x40000L
# define SUBSTRUCTURENOTIFYMASK		0x80000L
# define SUBSTRUCTUREREDIRECTMASK	0x100000L
# define FOCUSCHANGEMASK		0x200000L
# define PROPERTYCHANGEMASK		0x400000L
# define COLORMAPCHANGEMASK		0x800000L
# define OWNERGRABBUTTONMASK		0x1000000L

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

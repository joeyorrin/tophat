/*
Copyright_License {

  XCSoar Glide Computer - http://www.xcsoar.org/
  Copyright (C) 2000-2013 The XCSoar Project
  A detailed list of copyright holders can be found in the file "AUTHORS".

  This program is free software; you can redistribute it and/or
  modify it under the terms of the GNU General Public License
  as published by the Free Software Foundation; either version 2
  of the License, or (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
}
*/

#ifndef XCSOAR_OVERLAPPED_WIDGET_HPP
#define XCSOAR_OVERLAPPED_WIDGET_HPP

#include "WindowWidget.hpp"

/**
 * Base class for widgets that are designed to be "overlapped" windows
 * (in contrast to "tiled" windows): they obscur an area of another
 * #Window behind it.  That brings a few new aspects: the Z-order of
 * windows, and when the Widget gets hidden, the area "behind" it must
 * be redrawn.
 */
class OverlappedWidget : public WindowWidget {
public:
  /**
   * Bring this #Widget to the top of the z-order.  This is a hack to
   * allow overlapped widgets.
   */
  void Raise();

#ifdef USE_GDI
  virtual void Hide();
#endif
};

#endif
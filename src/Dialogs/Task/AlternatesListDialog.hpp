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

#ifndef DIALOG_ALTERNATES_LIST_HPP
#define DIALOG_ALTERNATES_LIST_HPP

#include "Widget/ListWidget.hpp"
#include "Widget/TextWidget.hpp"
#include "Engine/Task/Unordered/AlternateList.hpp"
#include "Form/ActionListener.hpp"
#include "Screen/Layout.hpp"

class WndButton;
class WidgetDialog;
class Canvas;
class WndForm;

struct DialogLook;

enum Buttons {
  Goto = 100,
  Details,
};

class AlternatesListWidget
  : public ListWidget, private ActionListener {
  enum Buttons {
    SETTINGS,
    GOTO,
  };

  const DialogLook &dialog_look;

  WndButton *details_button, *cancel_button, *goto_button;

public:
  AlternateList alternates;

public:
  void CreateButtons(WidgetDialog &dialog);

public:
  AlternatesListWidget(const DialogLook &_dialog_look)
    :dialog_look(_dialog_look) {}

  unsigned GetCursorIndex() const {
    return GetList().GetCursorIndex();
  }

  void Update();

public:
  /* virtual methods from class Widget */
  virtual void Prepare(ContainerWindow &parent, const PixelRect &rc) override;
  virtual void Unprepare() override {
    DeleteWindow();
  }

  /* virtual methods from class List::Handler */
  virtual void OnPaintItem(Canvas &canvas, const PixelRect rc,
                           unsigned index);

  virtual bool CanActivateItem(unsigned index) const {
    return true;
  }

  virtual void OnActivateItem(unsigned index) override;

  /* virtual methods from class ActionListener */
  virtual void OnAction(int id) override;
};

/**
 * a widget that lists the alternates and executes the actions
 * but has no buttons visible
 */
class AlternatesListWidget2 : public AlternatesListWidget
{
protected:
  WndForm *form;
public:
  AlternatesListWidget2(const DialogLook &_dialog_look)
    :AlternatesListWidget(_dialog_look) {}

  void SetForm(WndForm *_form) {
    assert(_form != nullptr);
    form = _form;
  }

  /* virtual methods from class Widget */
  virtual PixelSize GetMinimumSize() const {
    return GetMaximumSize();
  }
  virtual void Move(const PixelRect &rc) override;
  bool DoDetails();
  bool DoGoto();
  const Waypoint* GetWaypoint();

  virtual void OnActivateItem(unsigned index) override;

  void Refresh();
};


/**
 * A widget class that displays header rows above the List Widget
 * when used with TwoWidgets
 */
class AlternatesListHeaderWidget : public TextWidget
{
public:
  virtual void Prepare(ContainerWindow &parent, const PixelRect &rc);
  virtual void Unprepare();
  virtual void Move(const PixelRect &rc) override;

  virtual PixelSize GetMinimumSize() const {
    return PixelSize { 25u, Layout::GetMinimumControlHeight() / 2 };
  }
  virtual PixelSize GetMaximumSize() const {
    return PixelSize { 25u, Layout::GetMaximumControlHeight() };
  }
  void CalculateLayout(const PixelRect &rc);
};



#endif



/**************************************************************************

Game Editor - The Cross Platform Game Creation Tool
Copyright (C) 2009  Makslane Araujo Rodrigues, http://game-editor.com, http://game-editor.com

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

If GPL v3 does not work for you, we offer a "non-GPL" license 
More info at http://game-editor.com/License
Be a Game Editor developer: Be a Game Editor developer: <http://game-editor.com/Sharing_Software_Revenues_in_Open_Source>  .

***************************************************************************/


// MoveTo.h: interface for the MoveTo class.
//
//////////////////////////////////////////////////////////////////////

#ifndef STAND_ALONE_GAME

#if !defined(AFX_MOVETO_H__32813FA9_4082_45DD_AF64_427E88FDEE06__INCLUDED_)
#define AFX_MOVETO_H__32813FA9_4082_45DD_AF64_427E88FDEE06__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BaseAction.h"

class MoveTo : public BaseAction  
{
public:
	void UpdateEdition();
	void OnButton(Button *button, int buttonId);
	MoveTo(Actor *actor, bool bOnCollision);
	virtual ~MoveTo();

private:
	ListPop *listActor, *listRelative, *listAvoid;
	Actor *eventActor, *actionActor;
	EditBox *posX, *posY, *velocity;
};

#endif // !defined(AFX_MOVETO_H__32813FA9_4082_45DD_AF64_427E88FDEE06__INCLUDED_)


#endif //#ifndef STAND_ALONE_GAME
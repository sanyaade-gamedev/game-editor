/////////////////////////////////////////////////////////////////////////////
// Name:        DlgSaveLayout.h
// Purpose:     
// Author:      
// Modified by: 
// Created:     01/19/06 14:07:42
// RCS-ID:      
// Copyright:   
// Licence:     
/////////////////////////////////////////////////////////////////////////////

// Generated by DialogBlocks (unregistered), 01/19/06 14:07:42

#ifndef _DLGSAVELAYOUT_H_
#define _DLGSAVELAYOUT_H_

#if defined(__GNUG__) && !defined(__APPLE__)
#pragma interface "DlgSaveLayout.cpp"
#endif

/*!
 * Includes
 */

////@begin includes
#include "wx/xrc/xmlres.h"
////@end includes

/*!
 * Forward declarations
 */

////@begin forward declarations
////@end forward declarations

/*!
 * Control identifiers
 */

////@begin control identifiers
#define ID_DIALOG_SAVE_LAYOUT 10009
#define SYMBOL_DLGSAVELAYOUT_STYLE wxCAPTION|wxTAB_TRAVERSAL
#define SYMBOL_DLGSAVELAYOUT_TITLE _("Save Layout")
#define SYMBOL_DLGSAVELAYOUT_IDNAME ID_DIALOG_SAVE_LAYOUT
#define SYMBOL_DLGSAVELAYOUT_SIZE wxSize(400, 300)
#define SYMBOL_DLGSAVELAYOUT_POSITION wxDefaultPosition
////@end control identifiers

#define SYMBOL_DLGDELETELAYOUT_TITLE _("Delete Layout")

/*!
 * Compatibility
 */

#ifndef wxCLOSE_BOX
#define wxCLOSE_BOX 0x1000
#endif
#ifndef wxFIXED_MINSIZE
#define wxFIXED_MINSIZE 0
#endif

/*!
 * DlgSaveLayout class declaration
 */

class DlgSaveLayout: public wxDialog
{    
    DECLARE_DYNAMIC_CLASS( DlgSaveLayout )
    DECLARE_EVENT_TABLE()

public:
    /// Constructors
    DlgSaveLayout( );
    DlgSaveLayout( bool bSave );

    /// Creation
    bool Create( wxWindow* parent, wxWindowID id = SYMBOL_DLGSAVELAYOUT_IDNAME, const wxString& caption = SYMBOL_DLGSAVELAYOUT_TITLE, const wxPoint& pos = SYMBOL_DLGSAVELAYOUT_POSITION, const wxSize& size = SYMBOL_DLGSAVELAYOUT_SIZE, long style = SYMBOL_DLGSAVELAYOUT_STYLE );

    /// Creates the controls and sizers
    void CreateControls();

////@begin DlgSaveLayout event handler declarations

    /// wxEVT_COMMAND_BUTTON_CLICKED event handler for wxID_OK
    void OnOkClick( wxCommandEvent& event );

////@end DlgSaveLayout event handler declarations

////@begin DlgSaveLayout member function declarations

    /// Retrieves bitmap resources
    wxBitmap GetBitmapResource( const wxString& name );

    /// Retrieves icon resources
    wxIcon GetIconResource( const wxString& name );
////@end DlgSaveLayout member function declarations

    /// Should we show tooltips?
    static bool ShowToolTips();

////@begin DlgSaveLayout member variables
    wxComboBox* m_ComboLayout;
////@end DlgSaveLayout member variables

	bool bSave;
};

#endif
    // _DLGSAVELAYOUT_H_
///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Feb 20 2008)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __vLoveSocket__
#define __vLoveSocket__

#include <wx/string.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/gdicmn.h>
#include <wx/toolbar.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/stattext.h>
#include <wx/richtext/richtextctrl.h>
#include <wx/statbmp.h>
#include <wx/gauge.h>
#include <wx/sizer.h>
#include <wx/panel.h>
#include <wx/button.h>
#include <wx/listctrl.h>
#include <wx/choicebk.h>
#include <wx/splitter.h>
#include <wx/textctrl.h>
#include <wx/checkbox.h>
#include <wx/statbox.h>
#include <wx/radiobox.h>
#include <wx/fontpicker.h>
#include <wx/clrpicker.h>
#include <wx/filepicker.h>
#include <wx/datectrl.h>
#include <wx/dateevt.h>
#include <wx/html/htmlwin.h>
#include <wx/notebook.h>
#include <wx/frame.h>

///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// Class vMainFrame
///////////////////////////////////////////////////////////////////////////////
class vMainFrame : public wxFrame 
{
	private:
	
	protected:
		enum
		{
			wxID_Connect = 1000,
			wxID_SaveChat,
			wxID_SeeIP,
			wxID_SendFile,
			wxID_textSend,
			wxID_SendMessage,
			wxID_ResetPort,
			wxID_SaveConfig,
			wxID_ApplyConfig,
			wxID_ResetConfig,
			wxID_CancelConfig,
			wxID_OpenMem,
			wxID_SearchMem,
		};
		
		wxNotebook* mNotebook;
		wxPanel* chatPannel;
		wxToolBar* m_toolBar;
		wxStaticText* m_stxt_NameFeeling;
		wxSplitterWindow* mSplitter;
		wxPanel* yourChat;
		wxRichTextCtrl* m_chat;
		wxStaticBitmap* yourFace;
		wxStaticText* m_fileStatus;
		wxGauge* m_fileProgress;
		
		wxPanel* myChat;
		wxRichTextCtrl* m_textSend;
		wxButton* m_bSendFile;
		wxButton* m_bSend;
		wxChoicebook* myChoicebook;
		wxPanel* pMyFace;
		wxStaticBitmap* myFace;
		wxPanel* pQQFace;
		wxListCtrl* lQQFace;
		wxPanel* pAdFace;
		wxListCtrl* lAdFace;
		wxPanel* configPannel;
		
		
		wxStaticText* m_staticText11;
		wxTextCtrl* m_txt_Port;
		wxButton* m_bResetPort;
		wxCheckBox* m_chk_AutoSearch;
		wxStaticText* m_staticText12;
		wxTextCtrl* m_txt_HostName;
		wxStaticText* m_staticText13;
		wxTextCtrl* m_txt_IPRange;
		
		wxRadioBox* m_ChooseLanguage;
		
		
		wxStaticText* m_staticText211;
		wxTextCtrl* m_txt_MyName;
		
		wxStaticText* m_staticText212;
		wxFontPickerCtrl* m_fnt_MyName;
		wxColourPickerCtrl* m_cp_MyName;
		wxStaticText* m_staticText213;
		wxFontPickerCtrl* m_fnt_MyText;
		wxColourPickerCtrl* m_cp_MyText;
		wxStaticText* m_staticText214;
		wxFilePickerCtrl* m_fp_MyFace;
		
		wxStaticText* m_staticText215;
		wxButton* m_bMyFeeling;
		
		wxStaticText* m_staticText221;
		wxTextCtrl* m_txt_YourName;
		
		wxStaticText* m_staticText222;
		wxFontPickerCtrl* m_fnt_YourName;
		wxColourPickerCtrl* m_cp_YourName;
		wxStaticText* m_staticText223;
		wxFontPickerCtrl* m_fnt_YourText;
		wxColourPickerCtrl* m_cp_YourText;
		wxStaticText* m_staticText224;
		wxFilePickerCtrl* m_fp_YourFace;
		wxCheckBox* m_chkUseMyOwnSetting;
		
		
		wxButton* m_bSaveConfig;
		wxButton* m_bApplyConfig;
		wxButton* m_bResetConfig;
		wxButton* m_bCancelConfig;
		wxPanel* memPannel;
		wxButton* m_bOpenMem;
		wxButton* m_bSearch;
		wxCheckBox* m_chk_SearchByDate;
		wxDatePickerCtrl* m_datePicker_Mem;
		wxRichTextCtrl* m_mem;
		wxPanel* helpPannel;
		wxHtmlWindow* m_html_Help;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnConnect( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnSaveChat( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnSeeIP( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnCopyYourFeeling( wxMouseEvent& event ){ event.Skip(); }
		virtual void OnYourFaceChange( wxMouseEvent& event ){ event.Skip(); }
		virtual void OnSeeFileList( wxMouseEvent& event ){ event.Skip(); }
		virtual void OnSeeSpeed( wxMouseEvent& event ){ event.Skip(); }
		virtual void OnMessageEntering( wxKeyEvent& event ){ event.Skip(); }
		virtual void OnSendFile( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnMyFaceChange( wxMouseEvent& event ){ event.Skip(); }
		virtual void OnChoicebookNextPage( wxMouseEvent& event ){ event.Skip(); }
		virtual void OnQQFaceChosen( wxListEvent& event ){ event.Skip(); }
		virtual void OnQQFaceCancel( wxListEvent& event ){ event.Skip(); }
		virtual void OnQQFacePreview( wxListEvent& event ){ event.Skip(); }
		virtual void OnAdFaceChosen( wxListEvent& event ){ event.Skip(); }
		virtual void OnAdFaceCancel( wxListEvent& event ){ event.Skip(); }
		virtual void OnAdFacePreview( wxListEvent& event ){ event.Skip(); }
		virtual void OnResetPort( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnEnableAutoSearch( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnLanguageChanged( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnEditMyFeeling( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnEnableMySetting( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnSaveConfig( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnApplyConfig( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnResetConfig( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnCancelConfig( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnOpenMem( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnSearchMem( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnSearchByDate( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnMemDateChanged( wxDateEvent& event ){ event.Skip(); }
		
	
	public:
		vMainFrame( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("LoveSocket"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxDEFAULT_FRAME_STYLE|wxFRAME_SHAPED|wxTAB_TRAVERSAL );
		~vMainFrame();
		void mSplitterOnIdle( wxIdleEvent& )
		{
		mSplitter->SetSashPosition( 204 );
		mSplitter->Disconnect( wxEVT_IDLE, wxIdleEventHandler( vMainFrame::mSplitterOnIdle ), NULL, this );
		}
		
	
};

#endif //__vLoveSocket__

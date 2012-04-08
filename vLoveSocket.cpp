///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Feb 20 2008)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "vLoveSocket.h"

///////////////////////////////////////////////////////////////////////////

vMainFrame::vMainFrame( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxSize( 520,500 ), wxDefaultSize );
	
	wxBoxSizer* mSizer;
	mSizer = new wxBoxSizer( wxVERTICAL );
	
	mNotebook = new wxNotebook( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxNB_TOP );
	chatPannel = new wxPanel( mNotebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* chatSizer;
	chatSizer = new wxBoxSizer( wxVERTICAL );
	
	m_toolBar = new wxToolBar( chatPannel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTB_HORZ_TEXT|wxTB_TEXT );
	m_toolBar->SetToolBitmapSize( wxSize( 32,32 ) );
	m_toolBar->SetToolSeparation( 0 );
	m_toolBar->SetToolPacking( 0 );
	m_toolBar->AddTool( wxID_Connect, _("Connect"), wxIcon( wxT("iConnect"), wxBITMAP_TYPE_ICO_RESOURCE, 32, 32 ), wxNullBitmap, wxITEM_NORMAL, _("Connect"), wxEmptyString );
	m_toolBar->AddTool( wxID_SaveChat, _("Save Chat"), wxIcon( wxT("iSaveChat"), wxBITMAP_TYPE_ICO_RESOURCE, 32, 32 ), wxNullBitmap, wxITEM_NORMAL, _("Save Chat"), wxEmptyString );
	m_toolBar->AddTool( wxID_SeeIP, _("See My IP"), wxIcon( wxT("iSeeIP"), wxBITMAP_TYPE_ICO_RESOURCE, 32, 32 ), wxNullBitmap, wxITEM_NORMAL, _("See My IP"), wxEmptyString );
	m_toolBar->Realize();
	
	chatSizer->Add( m_toolBar, 0, wxEXPAND, 2 );
	
	m_stxt_NameFeeling = new wxStaticText( chatPannel, wxID_ANY, _("Unknown Name (Unknown Feeling)"), wxDefaultPosition, wxDefaultSize, 0 );
	m_stxt_NameFeeling->Wrap( 520 );
	m_stxt_NameFeeling->SetToolTip( _("Unknown Particular Feeling") );
	
	chatSizer->Add( m_stxt_NameFeeling, 0, wxALL, 5 );
	
	mSplitter = new wxSplitterWindow( chatPannel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_3DBORDER );
	mSplitter->SetSashGravity( 0.8 );
	mSplitter->SetMinimumPaneSize( 187 );
	mSplitter->Connect( wxEVT_IDLE, wxIdleEventHandler( vMainFrame::mSplitterOnIdle ), NULL, this );
	yourChat = new wxPanel( mSplitter, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* hSizer1;
	hSizer1 = new wxBoxSizer( wxHORIZONTAL );
	
	m_chat = new wxRichTextCtrl( yourChat, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_AUTO_URL|wxTE_READONLY|wxVSCROLL|wxWANTS_CHARS );
	m_chat->SetMinSize( wxSize( 350,195 ) );
	
	hSizer1->Add( m_chat, 1, wxEXPAND | wxALL, 5 );
	
	wxBoxSizer* faceSizer1;
	faceSizer1 = new wxBoxSizer( wxVERTICAL );
	
	yourFace = new wxStaticBitmap( yourChat, wxID_ANY, wxNullBitmap, wxDefaultPosition, wxDefaultSize, 0 );
	yourFace->SetMinSize( wxSize( 128,128 ) );
	
	faceSizer1->Add( yourFace, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_fileStatus = new wxStaticText( yourChat, wxID_ANY, _("0/0 files Received"), wxDefaultPosition, wxDefaultSize, 0 );
	m_fileStatus->Wrap( -1 );
	m_fileStatus->Hide();
	m_fileStatus->SetToolTip( _("Double click to see the file list.") );
	
	faceSizer1->Add( m_fileStatus, 0, wxALL|wxALIGN_RIGHT, 5 );
	
	m_fileProgress = new wxGauge( yourChat, wxID_ANY, 100, wxDefaultPosition, wxDefaultSize, wxGA_HORIZONTAL );
	m_fileProgress->SetValue( 50 ); 
	m_fileProgress->Hide();
	m_fileProgress->SetToolTip( _("0 kb/s") );
	
	faceSizer1->Add( m_fileProgress, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	
	faceSizer1->Add( 0, 0, 1, wxEXPAND, 5 );
	
	hSizer1->Add( faceSizer1, 0, wxEXPAND|wxALL, 5 );
	
	yourChat->SetSizer( hSizer1 );
	yourChat->Layout();
	hSizer1->Fit( yourChat );
	myChat = new wxPanel( mSplitter, wxID_SendFile, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* hSizer2;
	hSizer2 = new wxBoxSizer( wxHORIZONTAL );
	
	wxBoxSizer* vSizer;
	vSizer = new wxBoxSizer( wxVERTICAL );
	
	m_textSend = new wxRichTextCtrl( myChat, wxID_textSend, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0|wxWANTS_CHARS );
	m_textSend->SetMinSize( wxSize( 350,130 ) );
	
	vSizer->Add( m_textSend, 1, wxEXPAND | wxALL, 5 );
	
	wxBoxSizer* buttonSizer;
	buttonSizer = new wxBoxSizer( wxHORIZONTAL );
	
	m_bSendFile = new wxButton( myChat, wxID_ANY, _("Send File..."), wxDefaultPosition, wxDefaultSize, 0 );
	buttonSizer->Add( m_bSendFile, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_bSend = new wxButton( myChat, wxID_SendMessage, _("Send Message"), wxDefaultPosition, wxDefaultSize, 0 );
	m_bSend->SetToolTip( _("Ctrl-Enter") );
	
	buttonSizer->Add( m_bSend, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	vSizer->Add( buttonSizer, 0, wxALIGN_RIGHT, 5 );
	
	hSizer2->Add( vSizer, 1, wxEXPAND, 5 );
	
	wxBoxSizer* faceSizer2;
	faceSizer2 = new wxBoxSizer( wxVERTICAL );
	
	myChoicebook = new wxChoicebook( myChat, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxCHB_BOTTOM|wxCHB_DEFAULT );
	pMyFace = new wxPanel( myChoicebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* pSizer1;
	pSizer1 = new wxBoxSizer( wxVERTICAL );
	
	myFace = new wxStaticBitmap( pMyFace, wxID_ANY, wxNullBitmap, wxPoint( -1,-1 ), wxDefaultSize, 0 );
	myFace->SetMinSize( wxSize( 128,128 ) );
	
	pSizer1->Add( myFace, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	pMyFace->SetSizer( pSizer1 );
	pMyFace->Layout();
	pSizer1->Fit( pMyFace );
	myChoicebook->AddPage( pMyFace, _("My Face"), true );
	pQQFace = new wxPanel( myChoicebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* pSizer2;
	pSizer2 = new wxBoxSizer( wxVERTICAL );
	
	lQQFace = new wxListCtrl( pQQFace, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_AUTOARRANGE|wxLC_ICON|wxLC_SINGLE_SEL|wxLC_SORT_ASCENDING );
	pSizer2->Add( lQQFace, 1, wxALL|wxEXPAND, 5 );
	
	pQQFace->SetSizer( pSizer2 );
	pQQFace->Layout();
	pSizer2->Fit( pQQFace );
	myChoicebook->AddPage( pQQFace, _("QQ Faces"), false );
	pAdFace = new wxPanel( myChoicebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* pSizer3;
	pSizer3 = new wxBoxSizer( wxVERTICAL );
	
	lAdFace = new wxListCtrl( pAdFace, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_AUTOARRANGE|wxLC_ICON|wxLC_SINGLE_SEL|wxLC_SORT_ASCENDING );
	pSizer3->Add( lAdFace, 1, wxALL|wxEXPAND, 5 );
	
	pAdFace->SetSizer( pSizer3 );
	pAdFace->Layout();
	pSizer3->Fit( pAdFace );
	myChoicebook->AddPage( pAdFace, _("Other Faces"), false );
	faceSizer2->Add( myChoicebook, 1, wxEXPAND | wxALL, 0 );
	
	hSizer2->Add( faceSizer2, 0, wxEXPAND|wxALL, 5 );
	
	myChat->SetSizer( hSizer2 );
	myChat->Layout();
	hSizer2->Fit( myChat );
	mSplitter->SplitHorizontally( yourChat, myChat, 204 );
	chatSizer->Add( mSplitter, 1, wxEXPAND, 5 );
	
	chatPannel->SetSizer( chatSizer );
	chatPannel->Layout();
	chatSizer->Fit( chatPannel );
	mNotebook->AddPage( chatPannel, _("Chat"), true );
	configPannel = new wxPanel( mNotebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* configSizer;
	configSizer = new wxBoxSizer( wxVERTICAL );
	
	
	configSizer->Add( 0, 10, 0, 0, 5 );
	
	wxBoxSizer* rSizer1;
	rSizer1 = new wxBoxSizer( wxHORIZONTAL );
	
	
	rSizer1->Add( 5, 0, 0, 0, 5 );
	
	wxStaticBoxSizer* sbSizer1;
	sbSizer1 = new wxStaticBoxSizer( new wxStaticBox( configPannel, wxID_ANY, _("Connection Config") ), wxVERTICAL );
	
	wxBoxSizer* srSizer1;
	srSizer1 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* srSizer11;
	srSizer11 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText11 = new wxStaticText( configPannel, wxID_ANY, _("Port :"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText11->Wrap( -1 );
	srSizer11->Add( m_staticText11, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_txt_Port = new wxTextCtrl( configPannel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	srSizer11->Add( m_txt_Port, 0, wxALL|wxALIGN_BOTTOM, 5 );
	
	m_bResetPort = new wxButton( configPannel, wxID_ResetPort, _("Reset Port"), wxDefaultPosition, wxDefaultSize, 0 );
	m_bResetPort->Enable( false );
	
	srSizer11->Add( m_bResetPort, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	srSizer1->Add( srSizer11, 1, wxEXPAND, 5 );
	
	m_chk_AutoSearch = new wxCheckBox( configPannel, wxID_ANY, _("Enable Auto Search"), wxDefaultPosition, wxDefaultSize, 0 );
	
	m_chk_AutoSearch->Enable( false );
	
	srSizer1->Add( m_chk_AutoSearch, 0, wxALL, 5 );
	
	wxBoxSizer* srSizer12;
	srSizer12 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText12 = new wxStaticText( configPannel, wxID_ANY, _("Host Name :"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText12->Wrap( -1 );
	srSizer12->Add( m_staticText12, 0, wxALL, 5 );
	
	m_txt_HostName = new wxTextCtrl( configPannel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_txt_HostName->Enable( false );
	
	srSizer12->Add( m_txt_HostName, 0, wxALL, 5 );
	
	srSizer1->Add( srSizer12, 1, wxEXPAND, 5 );
	
	wxBoxSizer* srSizer13;
	srSizer13 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText13 = new wxStaticText( configPannel, wxID_ANY, _("IP Range:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText13->Wrap( -1 );
	srSizer13->Add( m_staticText13, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_txt_IPRange = new wxTextCtrl( configPannel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_txt_IPRange->Enable( false );
	
	srSizer13->Add( m_txt_IPRange, 0, wxALL|wxALIGN_BOTTOM, 5 );
	
	srSizer1->Add( srSizer13, 1, wxEXPAND, 5 );
	
	sbSizer1->Add( srSizer1, 0, wxEXPAND, 5 );
	
	rSizer1->Add( sbSizer1, 0, 0, 5 );
	
	
	rSizer1->Add( 5, 0, 0, 0, 5 );
	
	wxBoxSizer* bSizer22;
	bSizer22 = new wxBoxSizer( wxVERTICAL );
	
	wxString m_ChooseLanguageChoices[] = { _("English"), _("Chinese") };
	int m_ChooseLanguageNChoices = sizeof( m_ChooseLanguageChoices ) / sizeof( wxString );
	m_ChooseLanguage = new wxRadioBox( configPannel, wxID_ANY, _("Choose Language"), wxDefaultPosition, wxDefaultSize, m_ChooseLanguageNChoices, m_ChooseLanguageChoices, 2, wxRA_SPECIFY_ROWS );
	m_ChooseLanguage->SetSelection( 1 );
	bSizer22->Add( m_ChooseLanguage, 0, wxALL, 5 );
	
	rSizer1->Add( bSizer22, 0, 0, 5 );
	
	configSizer->Add( rSizer1, 0, 0, 5 );
	
	
	configSizer->Add( 0, 10, 0, 0, 5 );
	
	wxBoxSizer* rSizer2;
	rSizer2 = new wxBoxSizer( wxHORIZONTAL );
	
	
	rSizer2->Add( 5, 0, 1, wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer21;
	sbSizer21 = new wxStaticBoxSizer( new wxStaticBox( configPannel, wxID_ANY, _("Chose My Style") ), wxVERTICAL );
	
	wxFlexGridSizer* fgSizer21;
	fgSizer21 = new wxFlexGridSizer( 2, 0, 0, 0 );
	fgSizer21->SetFlexibleDirection( wxBOTH );
	fgSizer21->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText211 = new wxStaticText( configPannel, wxID_ANY, _("My Name"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText211->Wrap( -1 );
	fgSizer21->Add( m_staticText211, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_txt_MyName = new wxTextCtrl( configPannel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer21->Add( m_txt_MyName, 0, wxALL, 5 );
	
	
	fgSizer21->Add( 0, 0, 0, 0, 5 );
	
	m_staticText212 = new wxStaticText( configPannel, wxID_ANY, _("Name Font"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText212->Wrap( -1 );
	fgSizer21->Add( m_staticText212, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_fnt_MyName = new wxFontPickerCtrl( configPannel, wxID_ANY, wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 90, false, wxEmptyString ), wxDefaultPosition, wxDefaultSize, wxFNTP_USEFONT_FOR_LABEL );
	m_fnt_MyName->SetMaxPointSize( 100 ); 
	fgSizer21->Add( m_fnt_MyName, 0, wxALL, 5 );
	
	m_cp_MyName = new wxColourPickerCtrl( configPannel, wxID_ANY, *wxBLACK, wxDefaultPosition, wxDefaultSize, wxCLRP_DEFAULT_STYLE );
	fgSizer21->Add( m_cp_MyName, 0, wxALL, 5 );
	
	m_staticText213 = new wxStaticText( configPannel, wxID_ANY, _("Text Font"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText213->Wrap( -1 );
	fgSizer21->Add( m_staticText213, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_fnt_MyText = new wxFontPickerCtrl( configPannel, wxID_ANY, wxNullFont, wxDefaultPosition, wxDefaultSize, wxFNTP_USEFONT_FOR_LABEL );
	m_fnt_MyText->SetMaxPointSize( 100 ); 
	fgSizer21->Add( m_fnt_MyText, 0, wxALL, 5 );
	
	m_cp_MyText = new wxColourPickerCtrl( configPannel, wxID_ANY, *wxBLACK, wxDefaultPosition, wxDefaultSize, wxCLRP_DEFAULT_STYLE );
	fgSizer21->Add( m_cp_MyText, 0, wxALL, 5 );
	
	m_staticText214 = new wxStaticText( configPannel, wxID_ANY, _("My Face File"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText214->Wrap( -1 );
	fgSizer21->Add( m_staticText214, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_fp_MyFace = new wxFilePickerCtrl( configPannel, wxID_ANY, wxEmptyString, _("Select a jpg (128 * 128):"), wxT("*.jpg"), wxDefaultPosition, wxDefaultSize, wxFLP_FILE_MUST_EXIST|wxFLP_OPEN );
	fgSizer21->Add( m_fp_MyFace, 0, wxALL, 5 );
	
	
	fgSizer21->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_staticText215 = new wxStaticText( configPannel, wxID_ANY, _("My Feeling"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText215->Wrap( -1 );
	fgSizer21->Add( m_staticText215, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_bMyFeeling = new wxButton( configPannel, wxID_ANY, _("Edit"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer21->Add( m_bMyFeeling, 0, wxALL, 5 );
	
	sbSizer21->Add( fgSizer21, 1, wxEXPAND, 5 );
	
	rSizer2->Add( sbSizer21, 0, 0, 5 );
	
	
	rSizer2->Add( 10, 0, 0, 0, 5 );
	
	wxStaticBoxSizer* sbSizer22;
	sbSizer22 = new wxStaticBoxSizer( new wxStaticBox( configPannel, wxID_ANY, _("Chose His/Her Style") ), wxVERTICAL );
	
	wxFlexGridSizer* fgSizer22;
	fgSizer22 = new wxFlexGridSizer( 2, 0, 0, 0 );
	fgSizer22->SetFlexibleDirection( wxBOTH );
	fgSizer22->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText221 = new wxStaticText( configPannel, wxID_ANY, _("His/Her Name"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText221->Wrap( -1 );
	fgSizer22->Add( m_staticText221, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_txt_YourName = new wxTextCtrl( configPannel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer22->Add( m_txt_YourName, 0, wxALL, 5 );
	
	
	fgSizer22->Add( 0, 0, 0, 0, 5 );
	
	m_staticText222 = new wxStaticText( configPannel, wxID_ANY, _("Name Font"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText222->Wrap( -1 );
	fgSizer22->Add( m_staticText222, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_fnt_YourName = new wxFontPickerCtrl( configPannel, wxID_ANY, wxFont( 9, 70, 90, 90, false, wxEmptyString ), wxDefaultPosition, wxDefaultSize, wxFNTP_USEFONT_FOR_LABEL );
	m_fnt_YourName->SetMaxPointSize( 100 ); 
	fgSizer22->Add( m_fnt_YourName, 0, wxALL, 5 );
	
	m_cp_YourName = new wxColourPickerCtrl( configPannel, wxID_ANY, *wxBLACK, wxDefaultPosition, wxDefaultSize, wxCLRP_DEFAULT_STYLE );
	fgSizer22->Add( m_cp_YourName, 0, wxALL, 5 );
	
	m_staticText223 = new wxStaticText( configPannel, wxID_ANY, _("Text Font"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText223->Wrap( -1 );
	fgSizer22->Add( m_staticText223, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_fnt_YourText = new wxFontPickerCtrl( configPannel, wxID_ANY, wxNullFont, wxDefaultPosition, wxDefaultSize, wxFNTP_USEFONT_FOR_LABEL );
	m_fnt_YourText->SetMaxPointSize( 100 ); 
	fgSizer22->Add( m_fnt_YourText, 0, wxALL, 5 );
	
	m_cp_YourText = new wxColourPickerCtrl( configPannel, wxID_ANY, *wxBLACK, wxDefaultPosition, wxDefaultSize, wxCLRP_DEFAULT_STYLE );
	fgSizer22->Add( m_cp_YourText, 0, wxALL, 5 );
	
	m_staticText224 = new wxStaticText( configPannel, wxID_ANY, _("His/Her Face File"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText224->Wrap( -1 );
	fgSizer22->Add( m_staticText224, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_fp_YourFace = new wxFilePickerCtrl( configPannel, wxID_ANY, wxEmptyString, _("Select a jpg (128 * 128):"), wxT("*.jpg"), wxDefaultPosition, wxDefaultSize, wxFLP_FILE_MUST_EXIST|wxFLP_OPEN );
	fgSizer22->Add( m_fp_YourFace, 0, wxALL, 5 );
	
	sbSizer22->Add( fgSizer22, 1, wxEXPAND, 5 );
	
	m_chkUseMyOwnSetting = new wxCheckBox( configPannel, wxID_ANY, _("Use My Own Setting"), wxDefaultPosition, wxDefaultSize, 0 );
	
	m_chkUseMyOwnSetting->Enable( false );
	
	sbSizer22->Add( m_chkUseMyOwnSetting, 0, wxALL, 5 );
	
	rSizer2->Add( sbSizer22, 0, 0, 5 );
	
	
	rSizer2->Add( 5, 0, 1, wxEXPAND, 5 );
	
	configSizer->Add( rSizer2, 0, 0, 5 );
	
	
	configSizer->Add( 0, 10, 1, wxEXPAND, 5 );
	
	wxBoxSizer* rSizerLast;
	rSizerLast = new wxBoxSizer( wxHORIZONTAL );
	
	m_bSaveConfig = new wxButton( configPannel, wxID_SaveConfig, _("Save"), wxDefaultPosition, wxDefaultSize, 0 );
	rSizerLast->Add( m_bSaveConfig, 0, wxALL, 5 );
	
	m_bApplyConfig = new wxButton( configPannel, wxID_ApplyConfig, _("Apply"), wxDefaultPosition, wxDefaultSize, 0 );
	rSizerLast->Add( m_bApplyConfig, 0, wxALL, 5 );
	
	m_bResetConfig = new wxButton( configPannel, wxID_ResetConfig, _("Reset All"), wxDefaultPosition, wxDefaultSize, 0 );
	rSizerLast->Add( m_bResetConfig, 0, wxALL, 5 );
	
	m_bCancelConfig = new wxButton( configPannel, wxID_CancelConfig, _("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	rSizerLast->Add( m_bCancelConfig, 0, wxALL, 5 );
	
	configSizer->Add( rSizerLast, 0, wxALIGN_BOTTOM|wxALIGN_RIGHT|wxALL, 5 );
	
	configPannel->SetSizer( configSizer );
	configPannel->Layout();
	configSizer->Fit( configPannel );
	mNotebook->AddPage( configPannel, _("Config"), false );
	memPannel = new wxPanel( mNotebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* memSizer;
	memSizer = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer23;
	bSizer23 = new wxBoxSizer( wxHORIZONTAL );
	
	m_bOpenMem = new wxButton( memPannel, wxID_OpenMem, _("Open"), wxDefaultPosition, wxDefaultSize, 0 );
	m_bOpenMem->Hide();
	
	bSizer23->Add( m_bOpenMem, 0, wxALL, 5 );
	
	m_bSearch = new wxButton( memPannel, wxID_SearchMem, _("Search"), wxDefaultPosition, wxDefaultSize, 0 );
	m_bSearch->Hide();
	
	bSizer23->Add( m_bSearch, 0, wxALL, 5 );
	
	m_chk_SearchByDate = new wxCheckBox( memPannel, wxID_ANY, _("Search By Date"), wxDefaultPosition, wxDefaultSize, 0 );
	
	m_chk_SearchByDate->Hide();
	
	bSizer23->Add( m_chk_SearchByDate, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_datePicker_Mem = new wxDatePickerCtrl( memPannel, wxID_ANY, wxDefaultDateTime, wxDefaultPosition, wxDefaultSize, wxDP_DROPDOWN|wxDP_SHOWCENTURY );
	m_datePicker_Mem->Enable( false );
	m_datePicker_Mem->Hide();
	
	bSizer23->Add( m_datePicker_Mem, 0, wxALL, 5 );
	
	memSizer->Add( bSizer23, 0, 0, 5 );
	
	m_mem = new wxRichTextCtrl( memPannel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_AUTO_URL|wxTE_READONLY|wxVSCROLL|wxHSCROLL|wxNO_BORDER|wxWANTS_CHARS );
	memSizer->Add( m_mem, 1, wxALL|wxEXPAND, 5 );
	
	memPannel->SetSizer( memSizer );
	memPannel->Layout();
	memSizer->Fit( memPannel );
	mNotebook->AddPage( memPannel, _("Chat Record"), false );
	helpPannel = new wxPanel( mNotebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* helpSizer;
	helpSizer = new wxBoxSizer( wxVERTICAL );
	
	m_html_Help = new wxHtmlWindow( helpPannel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHW_SCROLLBAR_AUTO );
	helpSizer->Add( m_html_Help, 1, wxALL|wxEXPAND, 5 );
	
	helpPannel->SetSizer( helpSizer );
	helpPannel->Layout();
	helpSizer->Fit( helpPannel );
	mNotebook->AddPage( helpPannel, _("Help"), false );
	
	mSizer->Add( mNotebook, 1, wxEXPAND | wxALL, 0 );
	
	this->SetSizer( mSizer );
	this->Layout();
	mSizer->Fit( this );
	
	this->Centre( wxBOTH );
	
	// Connect Events
	this->Connect( wxID_Connect, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( vMainFrame::OnConnect ) );
	this->Connect( wxID_SaveChat, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( vMainFrame::OnSaveChat ) );
	this->Connect( wxID_SeeIP, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( vMainFrame::OnSeeIP ) );
	m_stxt_NameFeeling->Connect( wxEVT_LEFT_DCLICK, wxMouseEventHandler( vMainFrame::OnCopyYourFeeling ), NULL, this );
	yourFace->Connect( wxEVT_LEFT_DCLICK, wxMouseEventHandler( vMainFrame::OnYourFaceChange ), NULL, this );
	m_fileStatus->Connect( wxEVT_LEFT_DCLICK, wxMouseEventHandler( vMainFrame::OnSeeFileList ), NULL, this );
	m_fileProgress->Connect( wxEVT_MOTION, wxMouseEventHandler( vMainFrame::OnSeeSpeed ), NULL, this );
	m_textSend->Connect( wxEVT_KEY_DOWN, wxKeyEventHandler( vMainFrame::OnMessageEntering ), NULL, this );
	m_bSendFile->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( vMainFrame::OnSendFile ), NULL, this );
	myFace->Connect( wxEVT_LEFT_DCLICK, wxMouseEventHandler( vMainFrame::OnMyFaceChange ), NULL, this );
	myFace->Connect( wxEVT_RIGHT_DOWN, wxMouseEventHandler( vMainFrame::OnChoicebookNextPage ), NULL, this );
	lQQFace->Connect( wxEVT_COMMAND_LIST_ITEM_ACTIVATED, wxListEventHandler( vMainFrame::OnQQFaceChosen ), NULL, this );
	lQQFace->Connect( wxEVT_COMMAND_LIST_ITEM_DESELECTED, wxListEventHandler( vMainFrame::OnQQFaceCancel ), NULL, this );
	lQQFace->Connect( wxEVT_COMMAND_LIST_ITEM_SELECTED, wxListEventHandler( vMainFrame::OnQQFacePreview ), NULL, this );
	lQQFace->Connect( wxEVT_RIGHT_DOWN, wxMouseEventHandler( vMainFrame::OnChoicebookNextPage ), NULL, this );
	lAdFace->Connect( wxEVT_COMMAND_LIST_ITEM_ACTIVATED, wxListEventHandler( vMainFrame::OnAdFaceChosen ), NULL, this );
	lAdFace->Connect( wxEVT_COMMAND_LIST_ITEM_DESELECTED, wxListEventHandler( vMainFrame::OnAdFaceCancel ), NULL, this );
	lAdFace->Connect( wxEVT_COMMAND_LIST_ITEM_SELECTED, wxListEventHandler( vMainFrame::OnAdFacePreview ), NULL, this );
	lAdFace->Connect( wxEVT_RIGHT_DOWN, wxMouseEventHandler( vMainFrame::OnChoicebookNextPage ), NULL, this );
	m_bResetPort->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( vMainFrame::OnResetPort ), NULL, this );
	m_chk_AutoSearch->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( vMainFrame::OnEnableAutoSearch ), NULL, this );
	m_ChooseLanguage->Connect( wxEVT_COMMAND_RADIOBOX_SELECTED, wxCommandEventHandler( vMainFrame::OnLanguageChanged ), NULL, this );
	m_bMyFeeling->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( vMainFrame::OnEditMyFeeling ), NULL, this );
	m_chkUseMyOwnSetting->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( vMainFrame::OnEnableMySetting ), NULL, this );
	m_bSaveConfig->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( vMainFrame::OnSaveConfig ), NULL, this );
	m_bApplyConfig->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( vMainFrame::OnApplyConfig ), NULL, this );
	m_bResetConfig->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( vMainFrame::OnResetConfig ), NULL, this );
	m_bCancelConfig->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( vMainFrame::OnCancelConfig ), NULL, this );
	m_bOpenMem->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( vMainFrame::OnOpenMem ), NULL, this );
	m_bSearch->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( vMainFrame::OnSearchMem ), NULL, this );
	m_chk_SearchByDate->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( vMainFrame::OnSearchByDate ), NULL, this );
	m_datePicker_Mem->Connect( wxEVT_DATE_CHANGED, wxDateEventHandler( vMainFrame::OnMemDateChanged ), NULL, this );
}

vMainFrame::~vMainFrame()
{
	// Disconnect Events
	this->Disconnect( wxID_Connect, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( vMainFrame::OnConnect ) );
	this->Disconnect( wxID_SaveChat, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( vMainFrame::OnSaveChat ) );
	this->Disconnect( wxID_SeeIP, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( vMainFrame::OnSeeIP ) );
	m_stxt_NameFeeling->Disconnect( wxEVT_LEFT_DCLICK, wxMouseEventHandler( vMainFrame::OnCopyYourFeeling ), NULL, this );
	yourFace->Disconnect( wxEVT_LEFT_DCLICK, wxMouseEventHandler( vMainFrame::OnYourFaceChange ), NULL, this );
	m_fileStatus->Disconnect( wxEVT_LEFT_DCLICK, wxMouseEventHandler( vMainFrame::OnSeeFileList ), NULL, this );
	m_fileProgress->Disconnect( wxEVT_MOTION, wxMouseEventHandler( vMainFrame::OnSeeSpeed ), NULL, this );
	m_textSend->Disconnect( wxEVT_KEY_DOWN, wxKeyEventHandler( vMainFrame::OnMessageEntering ), NULL, this );
	m_bSendFile->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( vMainFrame::OnSendFile ), NULL, this );
	myFace->Disconnect( wxEVT_LEFT_DCLICK, wxMouseEventHandler( vMainFrame::OnMyFaceChange ), NULL, this );
	myFace->Disconnect( wxEVT_RIGHT_DOWN, wxMouseEventHandler( vMainFrame::OnChoicebookNextPage ), NULL, this );
	lQQFace->Disconnect( wxEVT_COMMAND_LIST_ITEM_ACTIVATED, wxListEventHandler( vMainFrame::OnQQFaceChosen ), NULL, this );
	lQQFace->Disconnect( wxEVT_COMMAND_LIST_ITEM_DESELECTED, wxListEventHandler( vMainFrame::OnQQFaceCancel ), NULL, this );
	lQQFace->Disconnect( wxEVT_COMMAND_LIST_ITEM_SELECTED, wxListEventHandler( vMainFrame::OnQQFacePreview ), NULL, this );
	lQQFace->Disconnect( wxEVT_RIGHT_DOWN, wxMouseEventHandler( vMainFrame::OnChoicebookNextPage ), NULL, this );
	lAdFace->Disconnect( wxEVT_COMMAND_LIST_ITEM_ACTIVATED, wxListEventHandler( vMainFrame::OnAdFaceChosen ), NULL, this );
	lAdFace->Disconnect( wxEVT_COMMAND_LIST_ITEM_DESELECTED, wxListEventHandler( vMainFrame::OnAdFaceCancel ), NULL, this );
	lAdFace->Disconnect( wxEVT_COMMAND_LIST_ITEM_SELECTED, wxListEventHandler( vMainFrame::OnAdFacePreview ), NULL, this );
	lAdFace->Disconnect( wxEVT_RIGHT_DOWN, wxMouseEventHandler( vMainFrame::OnChoicebookNextPage ), NULL, this );
	m_bResetPort->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( vMainFrame::OnResetPort ), NULL, this );
	m_chk_AutoSearch->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( vMainFrame::OnEnableAutoSearch ), NULL, this );
	m_ChooseLanguage->Disconnect( wxEVT_COMMAND_RADIOBOX_SELECTED, wxCommandEventHandler( vMainFrame::OnLanguageChanged ), NULL, this );
	m_bMyFeeling->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( vMainFrame::OnEditMyFeeling ), NULL, this );
	m_chkUseMyOwnSetting->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( vMainFrame::OnEnableMySetting ), NULL, this );
	m_bSaveConfig->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( vMainFrame::OnSaveConfig ), NULL, this );
	m_bApplyConfig->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( vMainFrame::OnApplyConfig ), NULL, this );
	m_bResetConfig->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( vMainFrame::OnResetConfig ), NULL, this );
	m_bCancelConfig->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( vMainFrame::OnCancelConfig ), NULL, this );
	m_bOpenMem->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( vMainFrame::OnOpenMem ), NULL, this );
	m_bSearch->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( vMainFrame::OnSearchMem ), NULL, this );
	m_chk_SearchByDate->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( vMainFrame::OnSearchByDate ), NULL, this );
	m_datePicker_Mem->Disconnect( wxEVT_DATE_CHANGED, wxDateEventHandler( vMainFrame::OnMemDateChanged ), NULL, this );
}


#include "LoveSocket.h"
#include "FileTransferThread.h"

wxRichTextCtrl & operator << (wxRichTextCtrl & rt, const wxString & s)
{
	rt.AppendText(s);
	return rt;
}

void MainFrame::AppendRecord(wxRichTextCtrl * rt,const m_tagStyle & style,const wxString s)
{
    wxDateTime now = wxDateTime::Now();

    wxTextAttr tmpAttr = wxTextAttr(style.NameColor, wxNullColour, style.NameFont);
    rt->SetDefaultStyle(tmpAttr);
    *rt << style.Name << wxT(" ") << now.FormatISODate() << wxT(" ") << now.FormatISOTime() << wxT("\n");

    tmpAttr = wxTextAttr(style.TextColor, wxNullColour, style.TextFont);
    rt->SetDefaultStyle(tmpAttr);
    *rt << s << wxT("\n") << wxT("\n");
}

wxString MainFrame::m_tagStyle::Serialize()
{
    wxString descript;
    long len;
    wxString tmp;

    len = Name.Len();

    const wxChar format[] = wxT("%#010x");

    //Name
    descript << wxString::Format(format,len) << Name;

    //NameFont
    tmp = NameFont.GetNativeFontInfoDesc();
    len = tmp.Len();
    descript << wxString::Format(format,len) << tmp;

    //NameColor
    tmp = NameColor.GetAsString(wxC2S_HTML_SYNTAX);
    len = tmp.Len();
    descript << wxString::Format(format,len) << tmp;

    //TextFont
    tmp = TextFont.GetNativeFontInfoDesc();
    len = tmp.Len();
    descript << wxString::Format(format,len) << tmp;

    //TextColor
    tmp = TextColor.GetAsString(wxC2S_HTML_SYNTAX);
    len = tmp.Len();
    descript << wxString::Format(format,len) << tmp;

    //FaceFile
    len = FaceFile.Len();
    descript << wxString::Format(format,len) << FaceFile;

    //Feeling
    len = Feeling.Len();
    descript << wxString::Format(format,len) << Feeling;

    return descript;
}

void MainFrame::m_tagStyle::Deserialize(wxString descript)
{
    long len;
    long cnt = 0;
    wxString tmp;

    const size_t width = 10;

    //Name
    descript(cnt, width).ToLong(&len,16);
    cnt += width;
    Name = descript(cnt, len);
    cnt += len;

    //NameFont
    descript(cnt, width).ToLong(&len,16);
    cnt += width;
    tmp = descript(cnt, len);
    NameFont.SetNativeFontInfo(tmp);
    cnt += len;

    //NameColor
    descript(cnt, width).ToLong(&len,16);
    cnt += width;
    tmp = descript(cnt, len);
    NameColor.Set(tmp);
    cnt += len;

    //TextFont
    descript(cnt, width).ToLong(&len,16);
    cnt += width;
    tmp = descript(cnt, len);
    TextFont.SetNativeFontInfo(tmp);
    cnt += len;

    //TextColor
    descript(cnt, width).ToLong(&len,16);
    cnt += width;
    tmp = descript(cnt, len);
    TextColor.Set(tmp);
    cnt += len;

    //FaceFile
    descript(cnt, width).ToLong(&len,16);
    cnt += width;
    FaceFile = descript(cnt, len);
    cnt += len;

    //Feeling
    descript(cnt, width).ToLong(&len,16);
    cnt += width;
    Feeling = descript(cnt, len);
    cnt += len;

}

void MainFrame::AutoSave()
{
    wxString record = wxT("chat/default.xml");
    if(!wxDir::Exists(wxT("chat"))) wxMkdir(wxT("chat"));
    m_mem->SaveFile(record);
}


MainFrame::MainFrame(wxLocale & locale, wxWindow* parent, wxWindowID id , const wxString& title)
            : vMainFrame( parent, id, title ),
              m_locale(locale)
{
    InitConfig();

    SetIcon(wxICON(aLoveSocket));

    const wxString record = wxT("chat/default.xml");
    if(wxFileName::FileExists(record))
        m_mem->LoadFile(record);

    if(!InitSocketServer(m_port))
        wxMessageBox(_("Could not listen at the specified port !"), _("Socket Server Initialization Failure"), wxOK|wxICON_EXCLAMATION , this);

    InitSocketClient();

    this->Connect( SOCKET_ID, wxEVT_SOCKET, wxSocketEventHandler( MainFrame::OnSocketEvent));
	this->Connect( SERVER_ID, wxEVT_SOCKET, wxSocketEventHandler( MainFrame::OnServerEvent));

    wxAcceleratorEntry entries[1];

    this->Connect( wxID_SendMessage,
                    wxEVT_COMMAND_BUTTON_CLICKED,
                    wxCommandEventHandler( MainFrame::OnSendMessage));
    entries[0] = wxAcceleratorEntry( wxACCEL_CTRL, WXK_RETURN, wxID_SendMessage);
//    entries[1] = wxAcceleratorEntry( wxACCEL_CTRL, 'C', wxID_COPY);
//    entries[2] = wxAcceleratorEntry( wxACCEL_CTRL, 'X', wxID_CUT);
//    entries[3] = wxAcceleratorEntry( wxACCEL_CTRL, 'V', wxID_PASTE);



    this->SetAcceleratorTable(wxAcceleratorTable(1, entries));

    m_textSend->SetFocus();
}

MainFrame::~MainFrame()
{
    AutoSave();
    m_server->Close();
	//m_sock->Close();
    this->Disconnect( SOCKET_ID, wxEVT_SOCKET, wxSocketEventHandler( MainFrame::OnSocketEvent));
	this->Disconnect( SERVER_ID, wxEVT_SOCKET, wxSocketEventHandler( MainFrame::OnServerEvent));

}

void MainFrame::UpdateGUI()
{
    //Port
    m_txt_Port->SetValue(m_port);

    //Face
    myFace->SetBitmap(wxBitmap( m_style.FaceFile, wxBITMAP_TYPE_ANY));
    yourFace->SetBitmap(wxBitmap( y_style.FaceFile, wxBITMAP_TYPE_ANY));

    m_fp_MyFace->SetPath(m_style.FaceFile);
    m_fp_YourFace->SetPath(y_style.FaceFile);

    //Name
    m_txt_MyName->SetValue(m_style.Name);
    m_txt_YourName->SetValue(y_style.Name);

    //Feeling
    wxString nameFeeling;
    nameFeeling << y_style.Name << wxT("(") << y_style.Feeling(0,35) << wxT("...)");
    m_stxt_NameFeeling->SetLabel(nameFeeling);
    m_stxt_NameFeeling->SetToolTip(y_style.Feeling);

    //Font
    m_fnt_MyName->SetSelectedFont(m_style.NameFont);
    m_fnt_MyText->SetSelectedFont(m_style.TextFont);


    m_fnt_YourName->SetSelectedFont(y_style.NameFont);
    m_fnt_YourText->SetSelectedFont(y_style.TextFont);


    //Color
    m_cp_MyName->SetColour(m_style.NameColor);
    m_cp_MyText->SetColour(m_style.TextColor);


    m_cp_YourName->SetColour(y_style.NameColor);
    m_cp_YourText->SetColour(y_style.TextColor);

    if(!useMySetting)
    {
        m_txt_YourName->Disable();
        m_fnt_YourName->Disable();
        m_cp_YourName->Disable();
        m_fnt_YourText->Disable();
        m_cp_YourText->Disable();
        m_fp_YourFace->Disable();
    }

}


void MainFrame::InitConfig()
{
    m_config = (wxConfig*)wxConfig::Get();

    //port
    m_config->Read(wxT("/Port"),&m_port,wxT("3000"));


    //Language
    if(m_config->Read(wxT("/Language"),wxLANGUAGE_CHINESE_SIMPLIFIED) == wxLANGUAGE_CHINESE_SIMPLIFIED)
        m_ChooseLanguage->SetSelection(1);
    else
        m_ChooseLanguage->SetSelection(0);

    //Load Last Connection
    m_config->Read(wxT("/LastConnection"), &m_lastConnection, wxT("localhost"));

    //My Style : String Part
    m_config->SetPath(wxT("/MyStyle"));
    m_config->Read(wxT("Name"), &(m_style.Name),_("My Name"));
    m_config->Read(wxT("FaceFile"), &(m_style.FaceFile),wxT("face/m_face.jpg"));
    m_config->Read(wxT("Feeling"), &(m_style.Feeling),_("Unknown My Feeling"));

    //Your Style : String Part
    m_config->SetPath(wxT("/YourStyle"));
    m_config->Read(wxT("Name"), &(y_style.Name),_("His/Her Name"));
    m_config->Read(wxT("FaceFile"), &(y_style.FaceFile),wxT("face/y_face.jpg"));
    m_config->Read(wxT("Feeling"), &(y_style.Feeling),_("Unknown His/Her Feeling"));

    //My Style : Font Part
    m_config->SetPath(wxT("/MyStyle/NameFont"))   ;
    m_style.NameFont = wxFont(
                            m_config->Read(wxT("PointSize"), wxNORMAL_FONT->GetPointSize()),
                            m_config->Read(wxT("Family"), wxDEFAULT),
                            m_config->Read(wxT("Style"), wxFONTSTYLE_NORMAL),
                            m_config->Read(wxT("FontWeight"), wxFONTWEIGHT_NORMAL),
                            m_config->Read(wxT("Underline"), 0L),
                            m_config->Read(wxT("FaceName"), wxNORMAL_FONT->GetFaceName()));

    m_config->SetPath(wxT("/MyStyle/TextFont"));
    m_style.TextFont = wxFont(
                            m_config->Read(wxT("PointSize"), wxNORMAL_FONT->GetPointSize()),
                            m_config->Read(wxT("Family"), wxDEFAULT),
                            m_config->Read(wxT("Style"), wxFONTSTYLE_NORMAL),
                            m_config->Read(wxT("FontWeight"), wxFONTWEIGHT_NORMAL),
                            m_config->Read(wxT("Underline"), 0L),
                            m_config->Read(wxT("FaceName"), wxNORMAL_FONT->GetFaceName()));

    //Your Style : Font Part
    m_config->SetPath(wxT("/YourStyle/NameFont"));
    y_style.NameFont = wxFont(
                            m_config->Read(wxT("PointSize"), wxNORMAL_FONT->GetPointSize()),
                            m_config->Read(wxT("Family"), wxDEFAULT),
                            m_config->Read(wxT("Style"), wxFONTSTYLE_NORMAL),
                            m_config->Read(wxT("FontWeight"), wxFONTWEIGHT_NORMAL),
                            m_config->Read(wxT("Underline"), 0L),
                            m_config->Read(wxT("FaceName"), wxNORMAL_FONT->GetFaceName()));
    m_config->SetPath(wxT("/YourStyle/TextFont"));
    y_style.TextFont = wxFont(
                            m_config->Read(wxT("PointSize"), wxNORMAL_FONT->GetPointSize()),
                            m_config->Read(wxT("Family"), wxDEFAULT),
                            m_config->Read(wxT("Style"), wxFONTSTYLE_NORMAL),
                            m_config->Read(wxT("FontWeight"), wxFONTWEIGHT_NORMAL),
                            m_config->Read(wxT("Underline"), 0L),
                            m_config->Read(wxT("FaceName"), wxNORMAL_FONT->GetFaceName()));

    //My Style : Color Part
    wxString color;
    m_config->SetPath(wxT("/MyStyle/NameFont"));
    m_config->Read(wxT("Color"), &color, wxT("#008040"));
    m_style.NameColor.Set(color);

    m_config->SetPath(wxT("/MyStyle/TextFont"));
    m_config->Read(wxT("Color"), &color, wxT("#000000"));
    m_style.TextColor.Set(color);

    //Your Style : Color Part
    m_config->SetPath(wxT("/YourStyle/NameFont"));
    m_config->Read(wxT("Color"), &color, wxT("#004080"));
    y_style.NameColor.Set(color);
    m_config->SetPath(wxT("/YourStyle/TextFont"));
    m_config->Read(wxT("Color"), &color, wxT("#000000"));
    y_style.TextColor.Set(color);

    //
    m_config->SetPath(wxT("/YourStyle"));
    useMySetting = m_config->Read(wxT("UseMySetting"),0L);

    UpdateGUI();

}

void MainFrame::ApplyConfig()
{
    //port
    m_port = m_txt_Port->GetValue();

    //My Name
    m_style.Name = m_txt_MyName->GetValue();

    //Your Name
    y_style.Name = m_txt_YourName->GetValue();

    //FaceFile
    wxString FaceFullPath;
    FaceFullPath = m_fp_MyFace->GetPath();
    if(!FaceFullPath.StartsWith(wxFileName::GetCwd().Append(wxFileName::GetPathSeparator()).c_str(),
                            &m_style.FaceFile))
    {
        m_fp_MyFace->SetPath(m_style.FaceFile);
    }

    FaceFullPath = m_fp_YourFace->GetPath();
    if(!FaceFullPath.StartsWith(wxFileName::GetCwd().Append(wxFileName::GetPathSeparator()).c_str(),
                            &y_style.FaceFile))
    {
        m_fp_YourFace->SetPath(y_style.FaceFile);
    }

//    m_style.FaceFile = m_fp_MyFace->GetPath();
//    y_style.FaceFile = m_fp_YourFace->GetPath();


    //My Style : Font Part
    m_style.NameFont = m_fnt_MyName->GetSelectedFont();
    m_style.TextFont = m_fnt_MyText->GetSelectedFont();

    //Your Style : Font Part
    y_style.NameFont = m_fnt_YourName->GetSelectedFont();
    y_style.TextFont = m_fnt_YourText->GetSelectedFont();


    //My Style : Color Part
    m_style.NameColor = m_cp_MyName->GetColour();
    m_style.TextColor = m_cp_MyText->GetColour();


    //Your Style : Color Part
    y_style.NameColor = m_cp_YourName->GetColour();
    y_style.TextColor = m_cp_YourText->GetColour();

    UpdateGUI();

    if(m_sock->IsOk())
        SendBasicInfo();

}

void MainFrame::OnApplyConfig( wxCommandEvent& event )
{
    ApplyConfig();
}

void MainFrame::OnSaveConfig( wxCommandEvent& event )
{
    ApplyConfig();

    //port
    m_config->Write(wxT("/Port"), m_port);

    //My Style
    m_config->SetPath(wxT("/MyStyle"));
    m_config->Write(wxT("Name"), m_style.Name);
    m_config->Write(wxT("FaceFile"), m_style.FaceFile);
    m_config->Write(wxT("Feeling"), m_style.Feeling);

    //Your Style
    m_config->SetPath(wxT("/YourStyle"));
    m_config->Write(wxT("Name"), y_style.Name);
    m_config->Write(wxT("FaceFile"), y_style.FaceFile);

    //My Style : Font Part
    m_config->SetPath(wxT("/MyStyle/NameFont"));
    m_config->Write(wxT("PointSize"), m_style.NameFont.GetPointSize());
    m_config->Write(wxT("Family"), (long)m_style.NameFont.GetFamily());
    m_config->Write(wxT("Style"), (long)m_style.NameFont.GetStyle());
    m_config->Write(wxT("FontWeight"), (long)m_style.NameFont.GetWeight());
    m_config->Write(wxT("Underline"), long(m_style.NameFont.GetUnderlined()));
    m_config->Write(wxT("FaceName"), m_style.NameFont.GetFaceName());

    m_config->SetPath(wxT("/MyStyle/TextFont"));
    m_config->Write(wxT("PointSize"), m_style.TextFont.GetPointSize());
    m_config->Write(wxT("Family"), (long)m_style.TextFont.GetFamily());
    m_config->Write(wxT("Style"), (long)m_style.TextFont.GetStyle());
    m_config->Write(wxT("FontWeight"), (long)m_style.TextFont.GetWeight());
    m_config->Write(wxT("Underline"), long(m_style.TextFont.GetUnderlined()));
    m_config->Write(wxT("FaceName"), m_style.TextFont.GetFaceName());

    //Your Style : Font Part
    m_config->SetPath(wxT("/YourStyle/NameFont"));
    m_config->Write(wxT("PointSize"), y_style.NameFont.GetPointSize());
    m_config->Write(wxT("Family"), (long)y_style.NameFont.GetFamily());
    m_config->Write(wxT("Style"), (long)y_style.NameFont.GetStyle());
    m_config->Write(wxT("FontWeight"), (long)y_style.NameFont.GetWeight());
    m_config->Write(wxT("Underline"), long(y_style.NameFont.GetUnderlined()));
    m_config->Write(wxT("FaceName"), y_style.NameFont.GetFaceName());

    m_config->SetPath(wxT("/YourStyle/TextFont"));
    m_config->Write(wxT("PointSize"), y_style.TextFont.GetPointSize());
    m_config->Write(wxT("Family"), (long)y_style.TextFont.GetFamily());
    m_config->Write(wxT("Style"), (long)y_style.TextFont.GetStyle());
    m_config->Write(wxT("FontWeight"), (long)y_style.TextFont.GetWeight());
    m_config->Write(wxT("Underline"), long(y_style.TextFont.GetUnderlined()));
    m_config->Write(wxT("FaceName"), y_style.TextFont.GetFaceName());

    //My Style : Color Part
    wxString color;
    color = m_style.NameColor.GetAsString(wxC2S_HTML_SYNTAX);
    m_config->SetPath(wxT("/MyStyle/NameFont"));
    m_config->Write(wxT("Color"), color);
    color = m_style.TextColor.GetAsString(wxC2S_HTML_SYNTAX);
    m_config->SetPath(wxT("/MyStyle/TextFont"));
    m_config->Write(wxT("Color"), color);

    //Your Style : Color Part
    color = y_style.NameColor.GetAsString(wxC2S_HTML_SYNTAX);
    m_config->SetPath(wxT("/YourStyle/NameFont"));
    m_config->Write(wxT("Color"), color);
    color = y_style.TextColor.GetAsString(wxC2S_HTML_SYNTAX);
    m_config->SetPath(wxT("/YourStyle/TextFont"));
    m_config->Write(wxT("Color"), color);
}

void MainFrame::OnEditMyFeeling( wxCommandEvent& event )
{
    wxString myFormerFeeling = m_style.Feeling;
    m_style.Feeling = wxGetTextFromUser(
        _("Write your feeling here"),
        _("Feeling..."),
        myFormerFeeling);
    if(m_style.Feeling == wxT(""))
        m_style.Feeling = myFormerFeeling;
}

void MainFrame::OnResetConfig( wxCommandEvent& event )
{
    //port
    m_txt_Port->SetValue(wxT("3000"));

/*
    //Language
    m_ChooseLanguage->SetSelection(1);
*/

    //My Style
    m_txt_MyName->SetValue(_("My Name"));
    m_fp_MyFace->SetPath(wxT("face/m_face.jpg"));



    //Your Style
    m_txt_YourName->SetValue(_("His/Her Name"));
    m_fp_YourFace->SetPath(wxT("face/y_face.jpg"));



    //My Style : Font Part
    m_fnt_MyName->SetSelectedFont(*wxNORMAL_FONT);
    m_fnt_MyText->SetSelectedFont(*wxNORMAL_FONT);

    //Your Style : Font Part
    m_fnt_YourName->SetSelectedFont(*wxNORMAL_FONT);
    m_fnt_YourText->SetSelectedFont(*wxNORMAL_FONT);



    //My Style : Color Part
    m_cp_MyName->SetColour(wxColor(wxT("#008040")));
    m_cp_MyText->SetColour(wxColor(wxT("#000000")));


    //Your Style : Color Part
    m_cp_YourName->SetColour(wxColor(wxT("#004080")));
    m_cp_YourText->SetColour(wxColor(wxT("#000000")));


}

void MainFrame::OnCancelConfig( wxCommandEvent& event )
{
    UpdateGUI();
}


bool MainFrame::InitSocketServer(const wxString & port)
{
    // Create the address - defaults to localhost:0 initially
    wxIPV4address addr;
    addr.Service(port);

    // Create the socket
    m_server = new wxSocketServer(addr,wxSOCKET_REUSEADDR);

    // We use Ok() here to see if the server is really listening
    if (! m_server->Ok())
        return false;

    // Setup the event handler and subscribe to connection events
    m_server->SetEventHandler(*this, SERVER_ID);
    m_server->SetNotify(wxSOCKET_CONNECTION_FLAG);
    m_server->Notify(true);

    return true;
}

void MainFrame::InitSocketClient()
{
    // Create the socket
    m_sock = new wxSocketClient();

    // Setup the event handler and subscribe to most events
    m_sock->SetEventHandler(*this, SOCKET_ID);
    m_sock->SetNotify(wxSOCKET_CONNECTION_FLAG |
                        wxSOCKET_INPUT_FLAG |
                        wxSOCKET_LOST_FLAG);
    m_sock->Notify(true);
}

void MainFrame::OnSeeIP( wxCommandEvent& event )
{
    wxIPV4address tmp_addr;
    m_addr.Hostname(tmp_addr.Hostname());
    *m_textSend << _("My IP is ") << m_addr.IPAddress();

    //AutoSave();

//    *m_textSend << m_style.Serialize();
//    m_tagStyle tmp;
//    tmp.Deserialize(m_style.Serialize());
//    *m_textSend << tmp.Serialize();

//    *m_textSend << wxFileName::GetCwd();

//    if(m_sock->IsConnected())
//    {
//        const ContentType type = File_Tranfer_Request;
//        m_Socket->Write(&type, sizeof(type));
//
//    }
}

void MainFrame::OpenConnection(wxIPV4address & addr)
{
    m_toolBar->SetToolNormalBitmap(wxID_Connect, wxIcon(wxT("iConnecting")));

    m_sock->Connect(addr, false);
    m_sock->WaitOnConnect(10);


    if (m_sock->IsConnected())
    {

        y_addr = addr;
        m_config->Write(wxT("/LastConnection"),y_addr.IPAddress());
        wxString title;
        title << _("LoveSocket Connected To ") << y_addr.Hostname()
            << wxT("(") << y_addr.IPAddress() << wxT(")");
        this->SetTitle(title);
        m_toolBar->SetToolNormalBitmap(wxID_Connect, wxIcon(wxT("iConnected")));
        SendBasicInfo();
    }
    else
    {
        m_toolBar->SetToolNormalBitmap(wxID_Connect, wxIcon(wxT("iConnect")));
        m_sock->Close();
        wxMessageBox(_("Can't connect to the specified host"), _("Connection Failure"));
    }
}

void MainFrame::OnConnect( wxCommandEvent& event )
{
    if (m_sock->IsConnected())
    {
        return;
    }

    wxIPV4address addr;

    // Ask user for server address
    wxString hostname = wxGetTextFromUser(
        _("Enter the address of the one you wanna connect:\n(The default address is your last connection)"),
        _("Connect To..."),
        m_lastConnection);

    if(hostname == wxT("") ) return;
    if(!addr.Hostname(hostname)) return;
    addr.Service(m_port);
    OpenConnection(addr);
}

void MainFrame::SendBasicInfo()
{
    m_sock->SetFlags(wxSOCKET_WAITALL);

    const ContentType type = Basic_Info;
    m_sock->Write(&type, sizeof(type));

    wxString descrpt = m_style.Serialize();

    const wxChar *info = descrpt.c_str();
    wxUint32 len;
    len  = (wxStrlen(info) + 1) * sizeof(wxChar);
    m_sock->Write(&len,sizeof(len));
    m_sock->Write(info, len);

//    long len = descrpt.Len();
//    m_sock->Write(&len, sizeof(len));
//    m_sock->Write(descrpt.c_str(), len * sizeof(wxChar));

}

void MainFrame::SendTextOnly()
{


    const wxChar *msg1;
    wxUint32 len;

    m_sock->SetFlags(wxSOCKET_WAITALL);

    wxString s = m_textSend->GetValue();

    AppendRecord(m_chat, m_style, s);
    AppendRecord(m_mem, m_style, s);

    m_chat->ShowPosition(m_chat->GetCaretPosition());

    m_textSend->Clear();

    msg1 = s.c_str();
    len  = (wxStrlen(msg1) + 1) * sizeof(wxChar);
    const ContentType type = Text_Only;

    m_sock->Write(&type,sizeof(type));
    m_sock->Write(&len,sizeof(len));
    m_sock->Write(msg1, len);

    m_textSend->SetFocus();
}

void MainFrame::OnSendMessage( wxCommandEvent& event )
{
    SendTextOnly();
}

void MainFrame::OnMessageEntering( wxKeyEvent& event )
{
//    if(event.GetKeyCode() == WXK_RETURN && !event.ShiftDown())
//    {
//        SendTextOnly();
//        return;
//    }
    event.Skip();

}

void MainFrame::OnServerEvent(wxSocketEvent& event)
{
    wxSocketBase *sock;

    // Accept new connection if there is one in the pending
    // connections queue, else exit. We use Accept(false) for
    // non-blocking accept (although if we got here, there
    // should ALWAYS be a pending connection).

    sock = m_server->Accept(false);

    if (!sock)
        return;

    sock->SetEventHandler(*this, SOCKET_ID);
    sock->SetNotify(wxSOCKET_INPUT_FLAG | wxSOCKET_LOST_FLAG);
    sock->Notify(true);

    //Auto connect back
    wxIPV4address addr;

    sock->GetPeer(addr);

    addr.Service(m_port);

    if(addr.IPAddress() != m_addr.IPAddress()
       && addr.IPAddress() != wxT("127.0.0.1")
       && addr.IPAddress() != y_addr.IPAddress())
    {
       OpenConnection(addr);
    }

    if(!IsActive()) RequestUserAttention();
}


void MainFrame::OnSocketEvent(wxSocketEvent& event)
{
    wxSocketBase *sock = event.GetSocket();

    switch(event.GetSocketEvent())
    {
        case wxSOCKET_INPUT:
            // We disable input events, so that the test doesn't trigger
            // wxSocketEvent again.
            sock->SetNotify(wxSOCKET_LOST_FLAG);

            ProcessMessageIn(sock);

            // Enable input events again.
            sock->SetNotify(wxSOCKET_LOST_FLAG | wxSOCKET_INPUT_FLAG);
            break;
        case wxSOCKET_LOST:
            sock->Destroy();
            m_toolBar->SetToolNormalBitmap(wxID_Connect, wxIcon(wxT("iConnect")));
            break;
        default: ;
    }
}

void MainFrame::ProcessMessageIn(wxSocketBase *sock)
{
    ContentType type;
    sock->Read(&type, sizeof(type));

    switch(type)
    {
        case Basic_Info :
            ProcessBasicInfo(sock);
            //sock->Discard();
            break;
        case Text_Only :
            ProcessTextOnly(sock);
            break;
        case File_Tranfer_Request :
        {
            sock->SetFlags(wxSOCKET_WAITALL);

            //Get the file name length
            wxUint32 len;
            sock->Read(&len,sizeof(wxUint32));

            wxChar *buf = new wxChar[len];

            // Reads the file name
            sock->Read(buf, len * sizeof(wxChar));

            wxString filename(buf);

            delete[] buf;

            //Reads the file size
            unsigned long low;
            long high;

            sock->Read(&low, sizeof(unsigned long));
            sock->Read(&high, sizeof(long));

            wxULongLong filesize(high, low);

            wxString saveMsg;

            saveMsg << _("Choose a location to save ") << filename
                << _T("(")
                << wxFileName::GetHumanReadableSize(filesize, _("Not available"), 2)
                << _T(") from ")
                << y_style.Name;

            wxString progMsg;
            progMsg << _T("Receving ") << filename
                << _T("(")
                << wxFileName::GetHumanReadableSize(filesize, _("Not available"), 2)
                << _T(")");

            wxFileDialog fileDlg(this,
                            saveMsg,
                            _T(""),
                            filename,
                            _T("*.*"),
                            wxFD_SAVE);

            if(fileDlg.ShowModal() == wxID_CANCEL)
            {
                //ToDo: Add some refusing code here
                const ContentType type = File_Tranfer_Cancelled;
                sock->Write(&type, sizeof(type));
                return;
            }

            filename = fileDlg.GetPath();

            wxProgressDialog* fileProgress = new wxProgressDialog
                                            (
                                             _T("Progress"),
                                             progMsg,
                                             100,
                                             (wxWindow*)NULL,
                                             wxPD_ELAPSED_TIME |
                                             wxPD_ESTIMATED_TIME |
                                             wxPD_REMAINING_TIME
                                            );

            new ServerListenThread(filename, filesize, fileProgress);

            const ContentType type = File_Tranfer_Ready;
            sock->Write(&type, sizeof(type));

            break;
        }
        case File_Tranfer_Ready :
        {
            wxCommandEvent readyEvt;
            readyEvt.SetInt(wxID_OK);
            OnSendFile(readyEvt);

            break;
        }
        case File_Tranfer_Cancelled :
        {
            wxCommandEvent cancelEvt;
            cancelEvt.SetInt(wxID_CANCEL);
            OnSendFile(cancelEvt);

            break;
        }
        case Face_Only :
        case Writing_Now :
        case Writing_No_Longer :
        default : break;
    }

}

void MainFrame::ProcessBasicInfo(wxSocketBase *sock)
{

    m_sock->SetFlags(wxSOCKET_WAITALL);

    m_tagStyle tmp;

    wxUint32 len;
    sock->Read(&len,sizeof(wxUint32));

    wxChar *buf = new wxChar[len];
    sock->Read(buf, len * sizeof(wxChar));

    wxString descript(buf, len);

    tmp.Deserialize(descript);

//    assert(tmp.Serialize() == descript)

    //Ensure that we will have Feeling from the other side
    y_style.Feeling = tmp.Feeling;

    //Prevent face overwritten because face transferring hasnt been implemented
    //tmp.FaceFile = y_style.FaceFile;
    //Assigning
    y_style = tmp;


    UpdateGUI();

}

void MainFrame::ProcessTextOnly(wxSocketBase *sock)
{
    sock->SetFlags(wxSOCKET_WAITALL);

    //Get the message length
    wxUint32 len;
    sock->Read(&len,sizeof(wxUint32));

    wxChar *buf = new wxChar[len];

    // Read the message
    sock->Read(buf, len * sizeof(wxChar));

    wxString s(buf);

    delete[] buf;

    AppendRecord(m_chat, y_style, s);
    AppendRecord(m_mem, y_style, s);

//    wxDateTime now = wxDateTime::Now();
//
//    wxTextAttr tmpAttr = wxTextAttr(y_style.NameColor, wxNullColour, y_style.NameFont);
//    m_chat->SetDefaultStyle(tmpAttr);
//    *m_chat << y_style.Name << wxT(" ") << now.FormatISODate() << wxT(" ") << now.FormatISOTime() << wxT("\n");
//    tmpAttr = wxTextAttr(y_style.TextColor, wxNullColour, y_style.TextFont);
//    m_chat->SetDefaultStyle(tmpAttr);
//    *m_chat << buf << wxT("\n");

    m_chat->ShowPosition(m_chat->GetCaretPosition());



    if(!IsActive()) RequestUserAttention();
}



void MainFrame::OnSaveChat( wxCommandEvent& event )
{
        wxString filter = wxRichTextBuffer::GetExtWildcard(false, true);
        wxString path;
        wxString filename;

        wxFileDialog dialog(this,
            _("Choose a filename"),
            path,
            filename,
            filter,
            wxFD_SAVE);

        if (dialog.ShowModal() == wxID_OK)
        {
            wxString path = dialog.GetPath();

            if (!path.empty())
            {
                m_chat->SaveFile(path);
            }
        }
}

void MainFrame::OnLanguageChanged( wxCommandEvent& event )
{
   wxMessageDialog * warning =
    new wxMessageDialog(this, _("If you continue, the program will reboot to the language you selected, all information you dindn't save will be lost!\nDo you want to continue?"), _("Warning"), wxOK | wxCANCEL | wxICON_EXCLAMATION );

    if(warning->ShowModal() == wxID_OK)
    {
        if(m_ChooseLanguage->GetSelection() == 0)
        {
            wxGetApp().SelectLanguage(wxLANGUAGE_ENGLISH);
            wxGetApp().Reboot();
        }
        else
        {
            wxGetApp().SelectLanguage(wxLANGUAGE_CHINESE_SIMPLIFIED);
            wxGetApp().Reboot();
        }
    }
    else
    {
        if(m_ChooseLanguage->GetSelection() == 0)
        {
            m_ChooseLanguage->SetSelection(1);
        }
        else
        {
            m_ChooseLanguage->SetSelection(0);
        }
    }

}

void MainFrame::OnSearchMem( wxCommandEvent& event )
{
    wxString text = wxGetTextFromUser(
        _("Text to search for"),
        _("Search..."));

    if(text == wxT("")) return;

}

void MainFrame::OnSendFile(wxCommandEvent& event)
{
    if(!m_sock->IsConnected())
        return;

    static wxString filepath;
    static wxULongLong filesize;

    int status;
    status = event.GetInt();

    switch(status)
    {
        case 0: //Which means it's called the first time
        {
            wxFileDialog fileDlg(this,
                                _("Choose a file to send"),
                                _T(""),
                                _T(""),
                                _T("*.*"),
                                wxFD_OPEN|wxFD_FILE_MUST_EXIST);
            if(fileDlg.ShowModal() == wxID_CANCEL)
                return;

            filepath = fileDlg.GetPath();


            filesize = wxFileName::GetSize(filepath);

            m_sock->SetFlags(wxSOCKET_WAITALL);

            //Writes the request flag
            const ContentType type = File_Tranfer_Request;
            m_sock->Write(&type, sizeof(type));

            //Writes the file name----only the name and extension

            wxString filename = wxFileName(filepath).GetFullName();
            wxUint32 len;
            len = filename.Len()+1;

            m_sock->Write(&len,sizeof(wxUint32));
            m_sock->Write(filename.c_str(), len * sizeof(wxChar));

            //Wirtes the file size
            unsigned long low = filesize.GetLo();
            long high = filesize.GetHi();

            m_sock->Write(&low, sizeof(unsigned long));
            m_sock->Write(&high, sizeof(long));

            break;
        }
        case wxID_OK: //Which means the server is ready
        {
            new ClientConnectThread(y_addr, filepath, filesize);

            break;
        }
        case wxID_CANCEL: //Which means the server refused the transfer
        {
            wxMessageBox(_("Transmission refused."));

            break;
        }
    }
}




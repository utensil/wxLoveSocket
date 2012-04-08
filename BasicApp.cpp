#include "BasicApp.h"

/** Destructor **/
BasicApp::~BasicApp()
{
    delete m_locale;
}

/** Operations **/
bool BasicApp::OnInit()
{
    //Init both wxConfig and wxLocale
    InitConfig();

    //Init image handlers
    wxInitAllImageHandlers();
    //Add richtext extra handlers (plain text is automatically added)
    wxRichTextBuffer::AddHandler(new wxRichTextXMLHandler);
    wxRichTextBuffer::AddHandler(new wxRichTextHTMLHandler);

    wxSocketBase::Initialize();

    InitMainFrame();

  return TRUE;
}

void BasicApp::Reboot()
{
    if (frame)
    {
    	delete frame;
    	InitMainFrame();
        OnRun();
    }
}

void BasicApp::SelectLanguage(int lang)
{
    if (m_locale)
    	delete m_locale;

    m_locale = new wxLocale;

    if (m_locale->Init(lang))//,wxLOCALE_CONV_ENCODING))
    {
        m_locale->AddCatalog(wxT("LoveSocket"));
    }
    wxConfig::Get()->Write(wxT("/Language"), lang);
}

/** Toolkit **/
void BasicApp::InitConfig()
{
    wxConfig * the_one = new wxConfig(wxT("LoveSocket1.0"),wxT("Utensil"));
    wxConfig::Set(the_one);

    long lang;

    the_one->Read(wxT("/Language"), &lang, wxLANGUAGE_CHINESE_SIMPLIFIED);

    //fixing a unclear bug with TrojWall
    if(lang == 56) lang = wxLANGUAGE_CHINESE_SIMPLIFIED;

    m_locale = NULL;

    wxLocale::AddCatalogLookupPathPrefix(wxT("."));

    SelectLanguage(lang);
}

void BasicApp::InitMainFrame()
{
    frame = new MainFrame( *m_locale, (wxWindow *)NULL, wxID_ANY, _("LoveSocket"));
    frame->Show(TRUE);
    SetTopWindow(frame);
}











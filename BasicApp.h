#ifndef __BasicApp__
#define __BasicApp__

//#include "rc/iConnect.xpm"
//#include "rc/iConnecting.xpm"
//#include "rc/iSaveChat.xpm"
//#include "rc/iConnected.xpm"
//#include "rc/iSeeIP.xpm"
//#include "rc/aLoveSocket.xpm"

#include <wx/wx.h>
#include <wx/config.h>
#include "LoveSocket.h"

class MainFrame;

class BasicApp : public wxApp
{

    public:
    /** Destructor **/
         ~BasicApp();

    /** Operations **/
        virtual bool OnInit();
        void SelectLanguage(int lang);
        void Reboot();

    private:
    /** Toolkit **/
        void InitConfig();
        void InitMainFrame();

    /** Data Member **/
        wxLocale * m_locale;
        MainFrame * frame;
};

DECLARE_APP(BasicApp) //For using wxGetApp()

#endif //__BasicApp__


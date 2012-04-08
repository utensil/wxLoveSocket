#ifndef __LoveSocket__
#define __LoveSocket__

#include "BasicApp.h"
#include "vLoveSocket.h"

#include <wx/socket.h>
#include <wx/wfstream.h>
#include <wx/datetime.h>
#include <wx/richtext/richtextctrl.h>
#include <wx/richtext/richtextxml.h>
#include <wx/richtext/richtexthtml.h>
#include <wx/dir.h>


class MainFrame : public vMainFrame
{
    private:
        enum
        {   // id for sockets
            SERVER_ID = 100,
            SOCKET_ID
        };

		enum ContentType
		{
            Basic_Info = 123,
            Text_Only,
            File_Tranfer_Request,
            File_Tranfer_Ready,
            File_Tranfer_Cancelled,
            Face_Only,
            Writing_Now,
            Writing_No_Longer
        };
        struct m_tagStyle
        {
            wxString Name;
            wxFont NameFont;
            wxColour NameColor;
            wxFont TextFont;
            wxColour TextColor;
            wxString FaceFile;
            wxString Feeling;

            wxString Serialize();
            void Deserialize(wxString descript);
        };


    private:
        wxLocale & m_locale;
        wxConfig * m_config;

        wxSocketServer *m_server;
		wxSocketClient *m_sock;
		wxIPV4address   m_addr;
		wxIPV4address   y_addr;

		wxString m_port;
		wxString m_lastConnection;
		m_tagStyle m_style;
        m_tagStyle y_style;

        bool useMySetting; //Use My Own Setting On Your Style

	private:
        void InitConfig();
        void UpdateGUI();
        void ApplyConfig();

        bool InitSocketServer(const wxString & port);
        void InitSocketClient();
        void OpenConnection(wxIPV4address & addr);

        void ProcessMessageIn(wxSocketBase *sock);
        void ProcessTextOnly(wxSocketBase *sock);
        void ProcessBasicInfo(wxSocketBase *sock);
        void ProcessFileTransferRequest(wxSocketBase *sock);
        void ProcessFileTransferReady(wxSocketBase *sock);

        void SendTextOnly();
        void SendBasicInfo();

        void AppendRecord(wxRichTextCtrl * rt,const m_tagStyle & style,const wxString s);

        void AutoSave();

    protected:
        void OnServerEvent(wxSocketEvent& event);
        void OnSocketEvent(wxSocketEvent& event);



    public:
        MainFrame( wxLocale & locale, wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("LoveSocket"));

        ~MainFrame();

    protected:
		// Virtual event handlers, overide them in your derived class
		virtual void OnConnect( wxCommandEvent& event );
		virtual void OnSaveChat( wxCommandEvent& event );
		virtual void OnSeeIP( wxCommandEvent& event );
		virtual void OnCopyYourFeeling( wxMouseEvent& event ){ event.Skip(); }
		virtual void OnYourFaceChange( wxMouseEvent& event ){ event.Skip(); }
		virtual void OnSeeFileList( wxMouseEvent& event ){ event.Skip(); }
		virtual void OnSeeSpeed( wxMouseEvent& event ){ event.Skip(); }
		virtual void OnMessageEntering( wxKeyEvent& event );
		virtual void OnSendFile( wxCommandEvent& event );
		virtual void OnSendMessage( wxCommandEvent& event );
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
		virtual void OnLanguageChanged( wxCommandEvent& event );
		virtual void OnEditMyFeeling( wxCommandEvent& event );
		virtual void OnEnableMySetting( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnSaveConfig( wxCommandEvent& event );
		virtual void OnApplyConfig( wxCommandEvent& event );
		virtual void OnResetConfig( wxCommandEvent& event );
		virtual void OnCancelConfig( wxCommandEvent& event );
		virtual void OnOpenMem( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnSearchMem( wxCommandEvent& event );
		virtual void OnSearchByDate( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnMemDateChanged( wxDateEvent& event ){ event.Skip(); }
};

#endif //__LoveSocket__


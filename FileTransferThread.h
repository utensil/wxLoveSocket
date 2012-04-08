#include <wx/wx.h>
#include <wx/thread.h>
#include <wx/string.h>
#include <wx/socket.h>
#include <wx/progdlg.h>

class ServerListenThread : public wxThread
{
    public:
        ServerListenThread(wxString filename, wxULongLong filesize, wxProgressDialog* progDlgToUpdate);
        ~ServerListenThread(){}

    protected:
        void* Entry();

    private:
        wxString m_filename;
        wxULongLong m_filesize;
        wxProgressDialog* m_progDlg;
};

class ClientConnectThread : public wxThread
{
    public:
        ClientConnectThread(wxIPV4address addr, wxString filename, wxULongLong filesize);
        ~ClientConnectThread(){}

    protected:
        void* Entry();

    private:
        wxSocketClient * m_client;
        wxIPV4address m_serverAddr;
        wxString m_filename;
        wxULongLong m_filesize;
};

class FileSendThread : public wxThread
{
    public:
        FileSendThread(wxString filename,
                       wxULongLong filesize,
                       wxSocketBase* socket);
        ~FileSendThread()
        {
            m_socket->Destroy();
        }

    protected:
        void* Entry();

    private:
        wxString m_filename;
        wxULongLong m_filesize;

        wxSocketBase * m_socket;
};

class FileReceiveThread : public wxThread
{
    public:
        FileReceiveThread(wxString filename,
                          wxULongLong filesize,
                          wxSocketBase* socket,
                          wxSocketServer* serverToDestroy,
                          wxProgressDialog* progDlgToUpdate);
        ~FileReceiveThread()
        {
            m_serverToDestroy->Destroy();
            m_socket->Destroy();
        }

    protected:
        void* Entry();

    private:
        wxString m_filename;
        wxULongLong m_filesize;

        wxSocketBase * m_socket;
        wxSocketServer* m_serverToDestroy;
        wxProgressDialog* m_progDlg;
};



#include "FileTransferThread.h"
#include <wx/wfstream.h>
#include <wx/sckstrm.h>
#include <wx/zstream.h>
#include <wx/buffer.h>

#define UxNO_SPEED

ServerListenThread::ServerListenThread(wxString filename, wxULongLong filesize, wxProgressDialog* progDlgToUpdate)
{
    m_filename = filename;
    m_filesize = filesize;
    m_progDlg = progDlgToUpdate;

    Create();
    Run();
}

void * ServerListenThread::Entry()
{
    wxIPV4address addr;
    int port = 3007;
    addr.Service(port);

    wxSocketServer * server = new wxSocketServer(addr, wxSOCKET_REUSEADDR);
    if(!server->IsOk())
    {
        wxMessageBox(_("Listen failed!!!"));
        return NULL;
    }

    wxSocketBase * sock = server->Accept();

    new FileReceiveThread(m_filename, m_filesize, sock, server, m_progDlg);

    return NULL;
}

ClientConnectThread::ClientConnectThread(wxIPV4address addr, wxString filename, wxULongLong filesize)
{
    m_filename = filename;
    m_filesize = filesize;

    m_serverAddr = addr;
    m_serverAddr.Service(3007);

    m_client = new wxSocketClient();

    Create();
    Run();
}

void * ClientConnectThread::Entry()
{
    m_client->Connect(m_serverAddr, false);
    m_client->WaitOnConnect(30);

    if(!m_client->IsConnected())
    {
        wxMessageBox(_("Connect failed!!!"));
        return NULL;
    }

    new FileSendThread(m_filename, m_filesize, m_client);

    return NULL;
}



FileSendThread::FileSendThread(wxString filename, wxULongLong filesize, wxSocketBase* socket)
{
    m_filename = filename;
    m_filesize = filesize;
    m_socket = socket;

    Create();
    Run();
}

void* FileSendThread::Entry()
{
#if defined(UxNO_SPEED)

    //Basic flow: FileIn->ZipOut->SocketOut

    // If we can't write anything for 10 seconds, assume a timeout
    m_socket->SetTimeout(10);

    // Wait for all the data to write, blocking on the socket calls
    m_socket->SetFlags(wxSOCKET_WAITALL | wxSOCKET_BLOCK);

    // Read from the specified file
    wxFileInputStream* FileInputStream =
        new wxFileInputStream(m_filename);

    // An output stream writing to the socket
    wxSocketOutputStream* SocketOutputStream =
        new wxSocketOutputStream(*m_socket);

    // The results of the compression will be written to the
    // socket stream
    wxZlibOutputStream* ZlibOutputStream =
        new wxZlibOutputStream(*SocketOutputStream);

    // Write the results of the zlib decompression to the file stream
    ZlibOutputStream->Write(*FileInputStream);

    // Write all data
    ZlibOutputStream->Sync();

    // Destroying will send Zlib compression EOF
    delete ZlibOutputStream;

    // Clean up
    delete SocketOutputStream;
    delete FileInputStream;

    wxMessageBox(_("Transmision completed"));

    return NULL;
#else
    // If we can't write anything for 10 seconds, assume a timeout
    m_socket->SetTimeout(10);

    // Wait for all the data to write, blocking on the socket calls
    m_socket->SetFlags(wxSOCKET_WAITALL | wxSOCKET_BLOCK);

    //FileIn->ZipOut[%->]SocketOut

    // Read from the specified file
    wxFileInputStream* FileInputStream =
        new wxFileInputStream(m_filename);

    // An output stream writing to the socket
    wxSocketOutputStream* SocketOutputStream =
        new wxSocketOutputStream(*m_socket);

    // The results of the compression will be written to the
    // socket stream
    wxZlibOutputStream* ZlibOutputStream =
        new wxZlibOutputStream(*SocketOutputStream);

    // Write the results of the zlib decompression to the file stream
    ZlibOutputStream->Write(*FileInputStream);

    // Write all data
    ZlibOutputStream->Sync();

    // Destroying will send Zlib compression EOF
    delete ZlibOutputStream;

    // Clean up
    delete SocketOutputStream;
    delete FileInputStream;

    wxMessageBox(_("Transmision completed"));

    return NULL;
#endif
}

FileReceiveThread::FileReceiveThread(wxString filename,
                                    wxULongLong filesize,
                                    wxSocketBase* socket,
                                    wxSocketServer* serverToDestroy,
                                    wxProgressDialog* progDlgToUpdate)
{
    m_filename = filename;
    m_filesize = filesize;
    m_socket = socket;
    m_serverToDestroy = serverToDestroy;
    m_progDlg = progDlgToUpdate;

    Create();
    Run();
}

void* FileReceiveThread::Entry()
{
#if defined(UxNO_SPEED_RECV)
    //Basic flow: SocketIn->ZipIn->FileOut

    // If we don't receive anything for 10 seconds, assume a timeout
    m_socket->SetTimeout(10);

    // Wait for some data to come in, or for an error
    // and block on the socket calls
    m_socket->SetFlags(wxSOCKET_WAITALL | wxSOCKET_BLOCK);

    // Output to the specified file
    wxFileOutputStream FileOutputStream(m_filename);

    // Stream data in from the socket
    wxSocketInputStream SocketInputStream(*m_socket);

    // The zlib decompression will decompress data from the
    // socket stream
    wxZlibInputStream ZlibInputStream(SocketInputStream);

    // Write to the file stream the results of reading from the
    // zlib input stream
    FileOutputStream.Write(ZlibInputStream);

    //wxMessageBox(_("Transmision completed"));

    return NULL;
#else

    //Basic flow: SocketIn->ZipIn[%->]FileOut

    // If we don't receive anything for 10 seconds, assume a timeout
    m_socket->SetTimeout(10);

    // Wait for some data to come in, or for an error
    // and block on the socket calls
    m_socket->SetFlags(wxSOCKET_WAITALL | wxSOCKET_BLOCK);

    // Output to the specified file
    wxFileOutputStream FileOutputStream(m_filename);

    // Stream data in from the socket
    wxSocketInputStream SocketInputStream(*m_socket);

    // The zlib decompression will decompress data from the
    // socket stream
    wxZlibInputStream ZlibInputStream(SocketInputStream);

    // Write to the file stream the results of reading from the
    // zlib input stream
    const size_t buf_size = 1024 * 1024;

    wxMemoryBuffer buf(buf_size);
    wxULongLong count = 0;
    size_t lastRead = 0;
    int percent;

    while(!ZlibInputStream.Eof())
    {
        ZlibInputStream.Read(buf.GetWriteBuf(buf_size), buf_size);
        lastRead = ZlibInputStream.LastRead();
        count += lastRead;
        FileOutputStream.Write(buf.GetData(), lastRead);

        percent = count.ToDouble() * 100 / m_filesize.ToDouble();

        wxMutexGuiEnter();

        if(percent < 100)
            m_progDlg->Update(percent);
        wxMutexGuiLeave();
    }
    //FileOutputStream.Write(ZlibInputStream);

    wxMutexGuiEnter();
    m_progDlg->Update(99);
    wxMutexGuiLeave();

    m_progDlg->Destroy();
    m_progDlg = (wxProgressDialog *)NULL;

    return NULL;
#endif
}






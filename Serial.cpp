#include "g-header.h"
///DEFINE SERIAL CLASS FXNS
///Function to define constructor
Serial::Serial(const char *port_name)
{
    //not connected upon initialization
    this->connected = false;

    //Set up handler
    this->hSerial = CreateFile(port_name,GENERIC_READ | GENERIC_WRITE,
                          0,0,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,0);

    //Check is connection was successful
    if(this->hSerial==INVALID_HANDLE_VALUE)
    {
        if(GetLastError()==ERROR_FILE_NOT_FOUND)
        {
            //Display serial communication error (debug only)
            printf("Port opening error");
        }
        else
        {
            //Add message dialog for use debugging
            //window.on_serial_error();
        }
    }
    else
    {
        //If connection successful, setup serial params
        //Control settings for serial comms device
        DCB SerialParams = {0};
        SerialParams.DCBlength = sizeof(DCB); //set size of structure

        //Default settings
        auto baudRate = CBR_9600;
        int byteSize = 8;
        auto stopBits = ONESTOPBIT;
        auto parity = NOPARITY;

        SerialParams.BaudRate = baudRate;
        SerialParams.ByteSize = byteSize;
        SerialParams.StopBits = stopBits;
        SerialParams.Parity = parity;
        SerialParams.fDtrControl = DTR_CONTROL_ENABLE; //ensure arduino is reset (may want to change this later)

        if(!SetCommState(this->hSerial,&SerialParams))
        {
            std::cout << "Error setting serial parameters" << std::endl;
            //window.on_serial_error();
        }
        else
        {
            //Set timeouts
            COMMTIMEOUTS timeout = {0};
            timeout.ReadIntervalTimeout = 50;
            timeout.ReadTotalTimeoutConstant = 50;
            timeout.ReadTotalTimeoutMultiplier = 50;
            timeout.WriteTotalTimeoutConstant = 50;
            timeout.WriteTotalTimeoutMultiplier = 10;
            SetCommTimeouts(hSerial,&timeout);

            //We should now be connected successfully
            this->connected = true;
            //Flush remaining characters in the buffers
            PurgeComm(hSerial,PURGE_RXCLEAR | PURGE_TXCLEAR);
            Sleep(ARDUINO_WAIT_TIME); //give Ad time to reset
        }

    }

}

///Function to define destructor
Serial::~Serial()
{
    if(this->connected)
    {
        //Check connection even exists first
        this->connected=false;
        CloseHandle(this->hSerial);
    }
}

///Function to read in data
int Serial::ReadData(char *buffer,unsigned int mChar)
{
    //Number of bytes read
    DWORD bytesRead;

    //Number of bytes requested to read
    unsigned int toRead;

    //Get status of Serial Port
    ClearCommError(this->hSerial,&this->errors,&this->status);

    //Is there data to read from port?
    if(this->status.cbInQue>0)
    {
        //Is there enough data storage to read allocated characters?
        //If not, we will limit it to prevent crashing
        if(this->status.cbInQue>mChar)
        {
            toRead = mChar;
        }
        else
        {
            toRead = this->status.cbInQue;
        }

        //Atempt to read required number of characters
        if(ReadFile(this->hSerial,buffer,toRead,&bytesRead,NULL))
        {
            return bytesRead;
        }
    }

    //If nothing is read, return 0
    return 0;
}

///Function to write data
bool Serial::WriteData(const char* buffer,unsigned int mChar)
{
    DWORD bytesSend;

    //Try to write the buffer on a serial port
    if(!WriteFile(this->hSerial,(void *)buffer,mChar,&bytesSend,0))
    {
        //If it didnt work, retrieve the error and return false
        ClearCommError(this->hSerial,&this->errors,&this->status);
        return false;
    }
    else return true;
}

///Function to determine whether port is connected
bool Serial::IsConnected()
{
    return this->connected;
}

///Function to change serial communication parameters
//int Serial::set_serial_params(DWORD baudRate,BYTE byteSize,BYTE stopBits,BYTE parity)
//{

//}
///END OF SERIAL CLASS FXNS

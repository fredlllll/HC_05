#ifndef HC_05_h
#define HC_05_h
#include "simpleitoa/simpleitoa.h"

enum HC_05WorkRole{
    Slave = 0,
    Master = 1,
    Loopback = 2
};

enum HC_05WorkMode{
    OrderResponse,
    AutomaticConnection
};

class HC_05{
    uint8_t modePin, statePin;
    Stream* stream;
    
    void setWorkMode(HC_05WorkMode mode){
        switch(mode){
            case HC_05WorkMode::OrderResponse:
            digitalWrite(modePin,HIGH);
            break;
            case HC_05WorkMode::AutomaticConnection:
            digitalWrite(modePin,LOW);
            break;
        }
    }
    
    public:
    HC_05(const uint8_t modePin, const uint8_t statePin, Stream* stream):modePin(modePin),statePin(statePin), stream(stream) {
        
    }
    
    void connect(){
        pinMode(modePin,OUTPUT);
        pinMode(statePin,OUTPUT);
    }
    
    void loop(){
        
    }
    
    void cmdTest(){
        sendCmd("AT");
    }
    
    void cmdReset(){
        sendCmd("AT+RESET");
    }
    
    void cmdGetVersion(){
        sendCmd("AT+VERSION?");
    }
    
    void cmdRestoreDefaults(){
        sendCmd("AT+ORGL");
    }
    
    void cmdGetBluetoothAddress(){
        sendCmd("AT+ADDR?");
    }
    
    void cmdSetName(const char *name){
        beginCmd("AT+NAME=");
        addCmd(name);
        endCmd();
    }
    
    void cmdGetName(){
        sendCmd("AT+NAME?");
    }
    
    void cmdGetRemoteName(uint8_t *raddress){
        beginCmd("AT+RNAME?");
        addCmd(raddress);
        endCmd();
    }
    
    void cmdSetRole(HC_05WorkRole role){
        switch(role){
            case HC_05WorkRole::Slave:
                sendCmd("AT+ROLE=0");
                break;
            case HC_05WorkRole::Master:
                sendCmd("AT+ROLE=1");
                break;
            case HC_05WorkRole::Loopback:
                sendCmd("AT+ROLE=2");
                break;
        }
    }
    
    void cmdGetRole(){
        sendCmd("AT+ROLE?");
    }
    
    void cmdSetDeviceType(uint32_t type){
        char[11] num;
        simpleitoa(type,10,num);
        beginCmd("AT+CLASS=");
        addCmd(num);
        endCmd();
    }
    
    void cmdGetDeviceType(){
        sendCmd("AT+CLASS?");
    }
    
    void cmdSetInquireAccessCode(uint8_t *code){
        beginCmd("AT+IAC=");
        addCmd(code);
        endCmd();
    }
    
    void cmdGetInquireAccessCode(){
        sendCmd("AT+IAC?");
    }
    
    void cmdSetInquireAccessMode(uint8_t mode, int maxDevices, uint8_t maxTime){
        beginCmd("AT+INQM=");
        char[11] num;
        simpleitoa(mode,10,num);
        addCmd(num);
        addCmd(",");
        simpleitoa(maxDevices,10,num);
        addCmd(num);
        addCmd(",");
        simpleitoa(maxTime,10,num);
        addCmd(num);
        endCmd();
    }
    
    void cmdGetInquireAccessMode(){
        sendCmd("AT+INQM?");
    }
    
    void cmdSetPassKey(uint8_t *pswd){
        beginCmd("AT+PSWD=");
        addCmd(pswd);
        endCmd();
    }
    
    void cmdGetPassKey(){
        sendCmd("AT+PSWD?");
    }
    
    //stopBits 0=1 bits, 1 = 2 bits. parityBit 0 = none, 1= odd, 2 = even.
    void cmdSetBaud(uint32_t baud, uint8_t stopBits, uint8_t parityBit){
        beginCmd("AT+UART=");
        char[11] num;
        simpleitoa(baud,10,num);
        addCmd(num);
        addCmd(",")
        simpleitoa(stopBit,10,num);
        addCmd(num);
        addCmd(",")
        simpleitoa(parityBit,10,num);
        addCmd(num);
        endCmd();
    }
    
    void cmdGetBaud(){
        sendCmd("AT+UART?");
    }
    
    void cmdSetConnectionMode(uint8_t mode){
        beginCmd("AT+CMODE=");
        char[11] num;
        simpleitoa(mode,10,num);
        addCmd(num);
        endCmd();
    }
    
    void cmdGetConnectionMode(){
        sendCmd("AT+CMODE?");
    }
    
    void cmdSetBindAddress(uint8_t *address){
        beginCmd("AT+BIND=");
        addCmd(address);
        endCmd();
    }
    
    void cmdGetBindAddress(){
        sendCmd("AT+BIND?");
    }
    
    void cmdSetLEDAndConnectionStatus(uint8_t pio8, uint8_t pio9){
        beginCmd("AT+POLAR=");
        if(pio8){
            addCmd("1");
        }else{
            addCmd("0");
        }
        addCmd(",");
        if(pio9){
            addCmd("1");
        }else{
            addCmd("0");
        }
        endCmd();
    }
    
    void cmdGetLEDAndConnectionStatus(){
        sendCmd("AT+POLAR?");
    }
    
    void cmdSetPIO(uint8_t pin, uint8_t level){
        beginCmd("AT+PIO=");
        char[11] num;
        simpleitoa(pin,10,num);
        addCmd(num);
        addCmd(",");
        if(level){
            addCmd("1");
        }else{
            addCmd("0");
        }
        endCmd();
    }
    
    void cmdSetPIOMask(uint16_t mask){
        beginCmd("AT+MPIO=");
        char[6] num;
        simpleitoa(mask,16,num); //why suddenly base 16?? the command set specification says so :C
        addCmd(num);
        endCmd();
    }
    
    void cmdGetPIOMask(){
        sendCmd("AT+MPIO?");
    }
    
    void cmdSetPageScan(int inquiryInterval, int inquiryDuration, int pagingInterval, int pagingDuration){
        beginCmd("AT+IPSCAN=");
        char[11] num;
        simpleitoa(inquiryInterval,10,num);
        addCmd(num);
        addCmd(",");
        simpleitoa(inquiryDuration,10,num);
        addCmd(num);
        addCmd(",");
        simpleitoa(pagingInterval,10,num);
        addCmd(num);
        addCmd(",");
        simpleitoa(pagingDuration,10,num);
        addCmd(num);
        endCmd();
    }
    
    void cmdGetPageScan(){
        sendCmd("AT+IPSCAN?");
    }
    
    void cmdSetSNIFF(){
        //later
    }
    
    void cmdGetSNIFF(){
        sendCmd("AT+SNIFF?");
    }
    
    void cmdSetSafety(){
        //later
    }
    
    void cmdGetSafety(){
        sendCmd("AT+SENM?");
    }
    
    void cmdDeleteAuthDevice(){
        //later
    }
    
    void cmdDeleteAllAuthDevices(){
        sendCmd("AT+RMAAD");
    }
    
    void cmdSeekAuthDevice(){
        //later
    }
    
    void cmdGetAuthDeviceCount(){
        sendCmd("AT+ADCN?");
    }
    
    void cmdGetRecentDeviceAddress(){
        sendCmd("AT+MRAD?");
    }
    
    void cmdGetWorkStatus(){
        sendCmd("AT+STATE?");
    }
    
    void cmdInitializeSPPProfileLib(){
        sendCmd("AT+INIT");
    }
    
    void cmdGetVisibleBluetoothDevices(){
        sendCmd("AT+INQ");
    }
    
    void cmdCancelDevice(){
        sendCmd("AT+INQC");
    }
    
    void cmdSetPair(){
        //later
    }
    
    void cmdConnectDevice(){
        //later
    }
    
    void cmdDisconnect(){
        sendCmd("AT+DISC");
    }
    
    void cmdEnterEnergyMode(){
        //later
    }
    
    void cmdExitEnergyMode(){
        //later
    }   
    
    void beginCmd(const uint8_t *cmd, const int len){
        setWorkMode(HC_05WorkMode::OrderResponse);
        stream.write(cmd,len);
    }
    
    void beginCmd(const uint8_t *cmd){
        beginCmd(cmd,strlen(cmd));
    }
    
    void addCmd(const uint8_t *cmd, const int len){
        stream.write(cmd,len);
    }
    
    void addCmd(const uint8_t *cmd){
        addCmd(cmd,strlen(cmd));    
    }
    
    void endCmd(){
        stream.write("\r\n");
        setWorkMode(HC_05WorkMode::AutomaticConnection);
    }
    
    void sendCmd(const uint8_t *cmd, const int len){
        setWorkMode(HC_05WorkMode::OrderResponse);
        stream.write(cmd,len);
        stream.write("\r\n");
        setWorkMode(HC_05WorkMode::AutomaticConnection);
    }
    
    void sendCmd(const uint8_t *cmd){
        sendCmd(cmd,strlen(cmd));
    }
};

#endif
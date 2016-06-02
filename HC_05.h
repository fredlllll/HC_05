#ifndef HC_05_h
#define HC_05_h
#include "simpleitoa/simpleitoa.h"

#define STRINGS_IN_FLASH
#ifdef STRINGS_IN_FLASH
	#define STR(X) (const char*)F(X)
#else
	#define STR(X) X
#endif


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
            case HC_05WorkMode::AutomaticConnection: //floating or low should mean auto connection.
            digitalWrite(modePin,LOW);
            break;
        }
    }
    
    public:
    HC_05(const uint8_t modePin, const uint8_t statePin, Stream* stream):modePin(modePin),statePin(statePin), stream(stream) {
        
    }
    
    void connect(){
        pinMode(modePin,OUTPUT);
        pinMode(statePin,INPUT);
    }
    
    void loop(){
        
    }
	
	uint8_t getStatePin(){
		return digitalRead(statePin);
	}
    
    void cmdTest(){
        sendCmd(STR("AT"));
    }
    
    void cmdReset(){
        sendCmd(STR("AT+RESET"));
    }
    
    void cmdGetVersion(){
        sendCmd(STR("AT+VERSION?"));
    }
    
    void cmdRestoreDefaults(){
        sendCmd(STR("AT+ORGL"));
    }
    
    void cmdGetBluetoothAddress(){
        sendCmd(STR("AT+ADDR?"));
    }
    
    void cmdSetName(const char *name){
        beginCmd(STR("AT+NAME="));
        addCmd(name);
        endCmd();
    }
    
    void cmdGetName(){
        sendCmd(STR("AT+NAME?"));
    }
    
    void cmdGetRemoteName(const char *raddress){
        beginCmd(STR("AT+RNAME?"));
        addCmd(raddress);
        endCmd();
    }
    
    void cmdSetRole(HC_05WorkRole role){
        switch(role){
            case HC_05WorkRole::Slave:
                sendCmd(STR("AT+ROLE=0"));
                break;
            case HC_05WorkRole::Master:
                sendCmd(STR("AT+ROLE=1"));
                break;
            case HC_05WorkRole::Loopback:
                sendCmd(STR("AT+ROLE=2"));
                break;
        }
    }
    
    void cmdGetRole(){
        sendCmd(STR("AT+ROLE?"));
    }
    
    void cmdSetDeviceType(uint32_t type){
        char num[11];
        simpleitoa(type,10,num);
        beginCmd(STR("AT+CLASS="));
        addCmd(num);
        endCmd();
    }
    
    void cmdGetDeviceType(){
        sendCmd(STR("AT+CLASS?"));
    }
    
    void cmdSetInquireAccessCode(const char *code){
        beginCmd(STR("AT+IAC="));
        addCmd(code);
        endCmd();
    }
    
    void cmdGetInquireAccessCode(){
        sendCmd(STR("AT+IAC?"));
    }
    
    void cmdSetInquireAccessMode(uint8_t mode, int maxDevices, uint8_t maxTime){
        beginCmd(STR("AT+INQM="));
        char num[11];
        simpleitoa(mode,10,num);
        addCmd(num);
        addCmd(STR(","));
        simpleitoa(maxDevices,10,num);
        addCmd(num);
        addCmd(STR(","));
        simpleitoa(maxTime,10,num);
        addCmd(num);
        endCmd();
    }
    
    void cmdGetInquireAccessMode(){
        sendCmd(STR("AT+INQM?"));
    }
    
    void cmdSetPassKey(const char *pswd){
        beginCmd(STR("AT+PSWD="));
        addCmd(pswd);
        endCmd();
    }
    
    void cmdGetPassKey(){
        sendCmd(STR("AT+PSWD?"));
    }
    
    //stopBit 0=1 bits, 1 = 2 bits. parityBit 0 = none, 1= odd, 2 = even.
    void cmdSetBaud(uint32_t baud, uint8_t stopBit, uint8_t parityBit){
        beginCmd(STR("AT+UART="));
        char num[11];
        simpleitoa(baud,10,num);
        addCmd(num);
        addCmd(STR(","));
        simpleitoa(stopBit,10,num);
        addCmd(num);
        addCmd(STR(","));
        simpleitoa(parityBit,10,num);
        addCmd(num);
        endCmd();
    }
    
    void cmdGetBaud(){
        sendCmd(STR("AT+UART?"));
    }
    
    void cmdSetConnectionMode(uint8_t mode){
        beginCmd(STR("AT+CMODE="));
        char num[11];
        simpleitoa(mode,10,num);
        addCmd(num);
        endCmd();
    }
    
    void cmdGetConnectionMode(){
        sendCmd(STR("AT+CMODE?"));
    }
    
    void cmdSetBindAddress(const char *address){
        beginCmd(STR("AT+BIND="));
        addCmd(address);
        endCmd();
    }
    
    void cmdGetBindAddress(){
        sendCmd(STR("AT+BIND?"));
    }
    
    void cmdSetLEDAndConnectionStatus(uint8_t pio8, uint8_t pio9){
        beginCmd(STR("AT+POLAR="));
        if(pio8){
            addCmd(STR("1"));
        }else{
            addCmd(STR("0"));
        }
        addCmd(STR(","));
        if(pio9){
            addCmd(STR("1"));
        }else{
            addCmd(STR("0"));
        }
        endCmd();
    }
    
    void cmdGetLEDAndConnectionStatus(){
        sendCmd(STR("AT+POLAR?"));
    }
    
    void cmdSetPIO(uint8_t pin, uint8_t level){
        beginCmd(STR("AT+PIO="));
        char num[11];
        simpleitoa(pin,10,num);
        addCmd(num);
        addCmd(STR(","));
        if(level){
            addCmd(STR("1"));
        }else{
            addCmd(STR("0"));
        }
        endCmd();
    }
    
    void cmdSetPIOMask(uint16_t mask){
        beginCmd(STR("AT+MPIO="));
        char num[6];
        simpleitoa(mask,16,num); //why suddenly base 16?? the command set specification says so :C
        addCmd(num);
        endCmd();
    }
    
    void cmdGetPIOMask(){
        sendCmd(STR("AT+MPIO?"));
    }
    
    void cmdSetPageScan(int inquiryInterval, int inquiryDuration, int pagingInterval, int pagingDuration){
        beginCmd(STR("AT+IPSCAN="));
        char num[11];
        simpleitoa(inquiryInterval,10,num);
        addCmd(num);
        addCmd(STR(","));
        simpleitoa(inquiryDuration,10,num);
        addCmd(num);
        addCmd(STR(","));
        simpleitoa(pagingInterval,10,num);
        addCmd(num);
        addCmd(STR(","));
        simpleitoa(pagingDuration,10,num);
        addCmd(num);
        endCmd();
    }
    
    void cmdGetPageScan(){
        sendCmd(STR("AT+IPSCAN?"));
    }
    
    void cmdSetSNIFF(){
        //later
    }
    
    void cmdGetSNIFF(){
        sendCmd(STR("AT+SNIFF?"));
    }
    
    void cmdSetSafety(){
        //later
    }
    
    void cmdGetSafety(){
        sendCmd(STR("AT+SENM?"));
    }
    
    void cmdDeleteAuthDevice(){
        //later
    }
    
    void cmdDeleteAllAuthDevices(){
        sendCmd(STR("AT+RMAAD"));
    }
    
    void cmdSeekAuthDevice(){
        //later
    }
    
    void cmdGetAuthDeviceCount(){
        sendCmd(STR("AT+ADCN?"));
    }
    
    void cmdGetRecentDeviceAddress(){
        sendCmd(STR("AT+MRAD?"));
    }
    
    void cmdGetWorkStatus(){
        sendCmd(STR("AT+STATE?"));
    }
    
    void cmdInitializeSPPProfileLib(){
        sendCmd(STR("AT+INIT"));
    }
    
    void cmdGetVisibleBluetoothDevices(){
        sendCmd(STR("AT+INQ"));
    }
    
    void cmdCancelDevice(){
        sendCmd(STR("AT+INQC"));
    }
    
    void cmdSetPair(){
        //later
    }
    
    void cmdConnectDevice(){
        //later
    }
    
    void cmdDisconnect(){
        sendCmd(STR("AT+DISC"));
    }
    
    void cmdEnterEnergyMode(){
        //later
    }
    
    void cmdExitEnergyMode(){
        //later
    }   
    
    void beginCmd(const char *cmd, const int len){
        setWorkMode(HC_05WorkMode::OrderResponse);
        stream->write(cmd,len);
    }
    
    void beginCmd(const char *cmd){
        beginCmd(cmd,strlen(cmd));
    }
    
    void addCmd(const char *cmd, const int len){
        stream->write(cmd,len);
    }
    
    void addCmd(const char *cmd){
        addCmd(cmd,strlen(cmd));    
    }
    
    void endCmd(){
        stream->write(STR("\r\n"));
        setWorkMode(HC_05WorkMode::AutomaticConnection);
    }
    
    void sendCmd(const char *cmd, const int len){
        setWorkMode(HC_05WorkMode::OrderResponse);
        stream->write(cmd,len);
        stream->write(STR("\r\n"));
        setWorkMode(HC_05WorkMode::AutomaticConnection);
    }
    
    void sendCmd(const char *cmd){
        sendCmd(cmd,strlen(cmd));
    }
};

#endif
SYSTEM_MODE(AUTOMATIC);


//NNNNNNNNNNNNNNNNNNNNNN
int CUSD_CallBack(int type, const char* CUSD_RESPONSE, int len, char* RAW_RESPONSE);
void Check_Remaining_Credit(void);

void setup()
{
  char* buff;
  
  int flag=Cellular.command(buff, 10000, "AT+CUSD=1,*131#,15\r\n");
  
   if(RESP_OK==flag)
  {
    //Log.info("SIM ICCID = %s\r\n", iccid);
    Particle.publish(buff);
  }
  else
  {
    //Log.info("SIM ICCID NOT FOUND!");
    Particle.publish("FAIL");
    //Particle.publish(flag);
  }
}

void loop()
{
  // your loop code
}

int CUSD_CallBack(int type, const char* CUSD_RESPONSE, int len, char* RAW_RESPONSE){

/*
  if ((type == TYPE_PLUS) && CUSD_RESPONSE) {

    if (sscanf(AT_CMD_RESPONSE, "\r\n+CCID: \r\n", CUSD_RESPONSE) == 1)
      //nothing
  }

  *13 different enumerated AT command responses passed by the system into the Cellular.command()
   callback as type
    TYPE_UNKNOWN = 0x000000
    TYPE_OK = 0x110000
    TYPE_ERROR = 0x120000
    TYPE_RING = 0x210000
    TYPE_CONNECT = 0x220000
    TYPE_NOCARRIER = 0x230000
    TYPE_NODIALTONE = 0x240000
    TYPE_BUSY = 0x250000
    TYPE_NOANSWER = 0x260000
    TYPE_PROMPT = 0x300000
    TYPE_PLUS = 0x400000
    TYPE_TEXT = 0x500000
    TYPE_ABORTED = 0x600000

*/

   CUSD_RESPONSE=RAW_RESPONSE;

    //printf("%s\n",CUSD_RESPONSE);

  // Particle.publish("Credit=",CUSD_RESPONSE);

  return WAIT; 

  /*
  Cellular.command() returns an int with one of the following 6 enumerated AT command responses:

    NOT_FOUND = 0
    WAIT = -1 // TIMEOUT  //Currently being used
    RESP_OK = -2
    RESP_ERROR = -3
    RESP_PROMPT = -4
    RESP_ABORTED = -5
*/


}

/*********************AT+CUSD command for Ublox Modem******************

>syntx

*set
AT+CUSD=[<n>[,<str>[,<dcs>]]]

*Response
[+CUSD: <m>[,<str>,<dcs>]]OK


*The parameter <n> disables/enables the URC presentation.
*Value <n>=2 is used to cancel an ongoing USSD session.
*When <str> is given, a mobile initiated USSD-string
or a response USSD-string to a network initiated operation is sent to
the network. The response USSD-string from the network is returned in
the URC +CUSD format. 

URC+CUSD: <m>[,<str>,<dcs>]

NOTE: *Command respond: up to 3 min (timeout)
      *error reference : +CME Error


>for example

//Set AT command for checking credit
  AT+CUSD=1,"*100#",15

//Response
  +CUSD: 2,"Residual credit: 7,87Euro",15OK
  OK

*/

void Check_Remaining_Credit(void){

  char RAW_RESPONSE[255] = "";
  
  int flag;

   flag=Cellular.command(CUSD_CallBack,RAW_RESPONSE, 10000, "AT+CUSD=1,*131#,15\r\n");
  

  if(RESP_OK == flag){
      
        strcmp(RAW_RESPONSE,"");
        
        Particle.publish("CUSD_CMD_SUCCESS");
        Particle.publish(RAW_RESPONSE);
    }
    else{
         Particle.publish("CUSD_CMD_FAILED");
    }

}

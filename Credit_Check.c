
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

//------------------------------------------

void Check_Available_Credit(void){

  char CUSD_Response[200] = ""; //character array containing the AT command response.

  if ((RESP_OK == Cellular.command(CUSD_Response,10000,"AT+CUSD=1,*131#,15\r\n")) && (strcmp(CUSD_Response,"") != 0))
  {
    printf("CREDIT= %s\r\n",CUSD_Response);
  }
  else
  {
    printf("CHECK_FAILED!");
  }

}

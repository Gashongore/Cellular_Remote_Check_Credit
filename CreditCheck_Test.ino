SYSTEM_MODE(AUTOMATIC);

SerialLogHandler logHandler;


//NNNNNNNNNNNNNNNNNNNNNN- Call back function prototype

int CUSD_CallBack(int type, const char* CUSD_RESPONSE, int len, char* RAW_RESPONSE);

//NNNNNNNNNNNNNNNNNNNNNN-- Check credit  prototype
void Check_Remaining_Credit(void);
//-------------------------------------------------------------------------------------

void setup()
{
    Check_Remaining_Credit();
}

void loop()
{
    // your loop code
}
//buff                        //iccid
int CUSD_CallBack(int type, const char* CUSD_RESPONSE, int len, char* RAW_RESPONSE){

    if ((type == TYPE_PLUS) && RAW_RESPONSE) {

        if (sscanf(CUSD_RESPONSE,"\r\n+CUSD: %[^\r] \r\n", RAW_RESPONSE) == 1)
            /*nothing*/;
    }
    return WAIT;

}

void Check_Remaining_Credit(void){

    char RAW_RESPONSE[255] = "";

    if ((RESP_OK == Cellular.command(CUSD_CallBack, RAW_RESPONSE, 10000, "AT+CUSD=1,*131#,15\r\n"))
        && (strcmp(RAW_RESPONSE,"") != 0))
    {
        //Log.info("SIM CUSD = %s\r\n", RAW_RESPONSE);
        Particle.publish("CUSD_CMD_SUCCESS");
        Particle.publish(RAW_RESPONSE);
    }
    else
    {
        Log.info("CUSD CMD FAILED!");
        Particle.publish("CUSD_CMD_FAILED");
    }

}
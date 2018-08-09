/*
 * This code scan the wifi network.
 * more commands at : http://wiki.seeedstudio.com/Grove-UART_Wifi/ 
 */
 
#include <Wire.h>

char ap_buf[30][16];
int ap_cnt = 0;

void setup()
{
    Serial3.begin(115200); //Init serial connection on port 3 for wifi
    Serial.begin(9600); //Init serial connection on port 3 for monitor
    delay(3000);
    Wire.begin(); //Start connection
}


void loop()
{
    Serial.println("------------------------"); 
    Serial.println("Wifi Scan..."); 
    ap_cnt = 0;
    cmd_send("AT+CWLAP"); //We verify if connection is up (AT+CWLAP = Lists available APs)
    wait_result();
    display_ap();
    delay(5000);
}

// send command
void cmd_send(char *cmd)
{
    if(NULL == cmd)return;
    Serial3.println(cmd);
}


// wait result of ap scan
// +CWLAP:(3,"360WiFi-UZ",-81,"08:57:00:01:61:ec",1)
void wait_result()
{
    while(1)
    {
LOOP1:
        char c1=0;
        if(Serial3.available()>=2)
        {
            c1 = Serial3.read();
            if(c1 == 'O' && 'K' == Serial3.read())return;       // OK means over
        }
        
        if('('==c1)
        {
            while(Serial3.available()<3);
            Serial3.read();
            Serial3.read();
            Serial3.read();

            int d = 0;
            while(1)
            {
                if(Serial3.available() && '"' == Serial3.read());      // find "
                {
                    while(1)
                    {
                        if(Serial3.available())
                        {
                            char c = Serial3.read();
                            ap_buf[ap_cnt][d++] = c; //save datas on buffer
                            if(c == '"' || d==16)
                            {
                                ap_buf[ap_cnt][d-1] = '\0';
                                ap_cnt++;
                                goto LOOP1;
                            }
                        }
                    }
                }
            }
        }
    }
}

// display on serial monitor
void display_ap()
{
    char strtmp[16];
    sprintf(strtmp, "get %d ap : ", ap_cnt);
    Serial.println(strtmp);        // Print the String
    delay(2000);
    int cnt = ap_cnt;
    int offset = 0;
    while(1)
    {
        if(cnt>=8)
        {
            for(int i=0; i<8; i++)
            {
                Serial.println(ap_buf[8*offset+i]);
            }
            cnt-=8;
            offset++;
        }
        else 
        {
            for(int i=0; i<cnt; i++)
            {
                Serial.println(ap_buf[8*offset+i]);
            }
            return;
        }
        delay(2000);
    }
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "sqlite3.h"

char Link_Style[20];
char Gateway_ID[30];
char Interface_Mode[30];
char Board_IP_Address[30];
char Gateway_Address[30];
char Subnet_Mask[30];
char Server_Address[30];
unsigned int  Serv_Port_Up;
unsigned int  Serv_Port_Down;
unsigned int  Keepalive_Interval;
unsigned int  Stat_Interval;
long int Push_Timeout=0L;
char Forward_Crc_Valid[30];
char Forward_Crc_Error[30];
char Forward_Crc_Disabled[30];
unsigned long int Freq0;
unsigned long int Freq1;
char Tx_Enable0[30];
char Tx_Enable1[30];
char Module_State[20];
unsigned int Tx_Power;

char file_name[] = "/dev/ttyUSB2";

int is_file_exist(const char *file_path);

int main()
{
    int row,col;
    char **result;
    sqlite3 *db=NULL;
    
    if(is_file_exist(file_name) == 0)
    {
        strcpy(Module_State,"true");
    }else{
        strcpy(Module_State,"false");
    }

    if(!sqlite3_open("/usr/httproot/cgi-bin/gateway_conf.db", &db))
    {
        if(!sqlite3_get_table(db,"select *  from gateway_conf ",&result,&row,&col,NULL))
        {
            int index = 0;
            index += col+1;

            sscanf(result[index], "%s", Link_Style);
            sscanf(result[index+1], "%s", Gateway_ID);
            sscanf(result[index+2], "%s", Interface_Mode);
            sscanf(result[index+3], "%s", Board_IP_Address);
            sscanf(result[index+4], "%s", Gateway_Address);
            sscanf(result[index+5], "%s", Subnet_Mask);
            sscanf(result[index+6], "%s", Server_Address);
            sscanf(result[index+7], "%u", &Serv_Port_Up);
            sscanf(result[index+8], "%u", &Serv_Port_Down);
            sscanf(result[index+9], "%u", &Keepalive_Interval);
            sscanf(result[index+10], "%u", &Stat_Interval);
            sscanf(result[index+11], "%ld", &Push_Timeout);
            sscanf(result[index+12], "%s", Forward_Crc_Error);
            sscanf(result[index+13], "%s", Forward_Crc_Disabled);
            sscanf(result[index+14], "%lu", &Freq0);
            sscanf(result[index+15], "%lu", &Freq1);
            sscanf(result[index+16], "%lu", &Tx_Power);
        }
    }
    
    printf("\n");

    if(!strcmp(Link_Style,"wirenet"))
    {
        printf("Connecting style : wirenet!\n");

        if(!strcmp(Interface_Mode,"static"))
        {
            printf("real connection is static wirenet!\n\n");
        }

        if(!strcmp(Interface_Mode,"dhcp"))
        {
            printf("real connection is dhcp wirenet!\n\n");
        }

    }
    if(!strcmp(Link_Style,"4gppp"))
    {
        if(!strcmp(Module_State,"true"))
        {
            printf("4G module exist!\n");
            printf("real connecting is : 4G!\n\n");
        }
        
        if(!strcmp(Module_State,"false"))
        {
            printf("4G module not exist!\n");

            if(!strcmp(Interface_Mode,"static"))
            {
                printf("real connection is static wirenet!\n\n");
            }

            if(!strcmp(Interface_Mode,"dhcp"))
            {
                printf("real connection is dhcp wirenet!\n\n");
            }
        }
        
    }

    printf("----1----Link_Style is:       %s\n",Link_Style);
    printf("----2----Gateway_ID:          %s\n",Gateway_ID);
    printf("----3----Interface_Mode:      %s\n",Interface_Mode);
    printf("----4----Board_IP_Address:    %s\n",Board_IP_Address);
    printf("----5----Router_IP_Address:   %s\n",Gateway_Address);
    printf("----6----Subnet_Mask_temp:    %s\n",Subnet_Mask);
    printf("----7----Server_address:      %s\n",Server_Address);
    printf("----8----Serv_port_up:        %u\n",Serv_Port_Up);
    printf("----9----Serv_port_down:      %u\n",Serv_Port_Down);
    printf("----10---Keepalive_interval:  %u\n",Keepalive_Interval);
    printf("----11---Stat_interval:       %u\n",Stat_Interval);
    printf("----12---Push_timeout_ms:     %ld\n",Push_Timeout);
    printf("----13---Forward_crc_error:   %s\n",Forward_Crc_Error);
    printf("----14---Forward_crc_disabled:%s\n",Forward_Crc_Disabled);
    printf("----15---Freq0:               %lu\n",Freq0);
    printf("----16---Freq1:               %lu\n",Freq1);
    printf("----17---Module_State:        %s\n",Module_State);
    printf("----18---Tx_Power:            %lu\n",Tx_Power);

}

int is_file_exist(const char *file_path)
{
    if(access(file_path,F_OK) == 0)
    {
        printf("%s exits!\n",file_path);
        return 0;
    }
    else{
        printf("%s not exist!\n",file_path);
        return -1;
    }
}

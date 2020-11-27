#ifndef NTP_TIME_SYNC
#define NTP_TIME_SYNC

int _udp_read(void *p_socket,unsigned char *p_data,unsigned int datalen);

int _udp_read_timeout(void *p_socket, unsigned char *p_data,unsigned int datalen,unsigned int timeout);

uint64_t get_utc_time_from_ntp(void);


#endif

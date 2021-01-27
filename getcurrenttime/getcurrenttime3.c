#include <stdio.h>
#include <time.h>
#include <string.h>

int main()
{
	time_t now;
	//int unixTime = (int)time(&now);
	//time_t tick = (time_t)unixTime;
	time_t tick = (time_t)(1587353564657363/1000000);

	struct tm tm;
	char s[64];
	tm = *localtime(&tick);
	strftime(s, sizeof(s), "%Y-%m-%d %H:%M:%S", &tm);

	printf("%s\n",  s);
	return 0;
}

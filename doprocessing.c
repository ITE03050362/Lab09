#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include <time.h>

void doprocessing (int sock) 
{
   int n;
   char buffer[256];

   //
	time_t mytime;
	mytime=time(NULL);  
	int answer[8];//猜數答案和使用者的回答
	int count1,count2,countA,countB;//記數用變數
	char *message;
	char reply[8],compare[8],message2[50];
   //
   if (n < 0) {
      perror("ERROR reading from socket");
      exit(1);
   }
   
 //original
 //  printf("Here is the message: %s\n",buffer);
 //  n = write(sock,"I got your message",18);

 //////////////////////
	countA=0; 
	countB=0;
	srand( time(NULL) ); 
	for(count1=0;count1<4;count1++)
	{
		answer[count1]=rand()%10; //亂數產生1~10任意數字並放入陣列內
		for(count2=0;count2<count1;count2++) 
		{ 
			if(answer[count1]==answer[count2]) //比較是否重複
			{
			count1--; //重複則重新產生
			} 
		}
	} 
	printf("Answer:%d%d%d%d\n",answer[0],answer[1],answer[2],answer[3]);
//Reply to the client
	while(1)
	{
		bzero(buffer,256);
		n = read(sock,buffer,255);
		compare[0]=(buffer[0]-'0');
		compare[1]=(buffer[1]-'0');
		compare[2]=(buffer[2]-'0');
		compare[3]=(buffer[3]-'0');
	
		for(count1=0;count1<4;count1++)
		{
			if(answer[count1]==compare[count1]) //比較數字及位置相同的數
			{
				countA+=1;
			}
		}
	
		for(count2=0;count2<=3;count2++)
		{
			for(count1=0;count1<=3;count1++)
			{
				if(compare[count1]==answer[count2] && count1!=count2)
				{
					countB++;
				}
			}
		}			
	
		if(countA==4)
		{
			message="This game end!!";
			write(sock , message, strlen(message)+1);
		}
		else
		{
			sprintf(message2,"%dA%dB",countA,countB);
			write(sock , message2, strlen(message2)+1);
			countA=0;countB=0;
		}
	}
   //////////////////////
   if (n < 0)
   {
      perror("ERROR writing to socket");
      exit(1);
   }
	
}

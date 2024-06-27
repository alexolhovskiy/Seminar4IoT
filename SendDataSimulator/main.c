////////////////////////////////////
///                              ///
///        ALEX OLHOVSKIY        ///
///                              ///
////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void description(){
    printf("This program simulates data transfer from a portable device\n");
    printf("flags:\n");
    printf("-f Set the data source file,\nenter -f<file_name.csv> , where <file_name> - name of file with sensor data\n");
    printf("-s Set the address of the server - data receiver,\nenter -s<table_name> , where <table_name> - name of the selected table for receiving data\n");
}

void interprogramFunc(char*file,char*table){
    int h=0,m=0,Y=0,M=0,d=0,t=0,error=255,num=0;
    char res[256]={0};
    char str[]="http://h50149iy.beget.tech/db_handler.php?x={\"table\": \"";
    char str2[]="\", \"x\": ";
    char str3[]="}";
    char numBuf[20]={0};
    FILE *fd=fopen(file,"r");
    if(fd!=NULL){
        printf("Opened success!\n");

        while((error=fscanf(fd,"%d;%d;%d;%d;%d;%s",&Y,&M,&d,&h,&m,numBuf))!=EOF){
            if(error==0){
                while(fgetc(fd)!='\n'){}
                printf("Error in line # %d\n",num);
            }
            num++;

            strcat(res,str);
            strcat(res,table);
            strcat(res,str2);
            strcat(res,numBuf);
            strcat(res,str3);

            //printf("%s\n",res);
            //printf("%d\n",num);

            FILE*lfd=fopen("url.txt","w");
            if(lfd!=NULL){
                fprintf(lfd,"%s",res);
            }
            else{
                printf("Error in url formation");
            }
            fclose(lfd);

            system("python requestForTheServer3.py");
            res[0]='\0';

            sleep(5);
        }
        fclose(fd);

    }else{
        printf("Error! Cannot open file!\n");
    }
}


int main(int argc,char*argv[])
{

    char*fileName;
    char*tableName;
    int rez=0,key=0;
	// opterr=0;
	while ( (rez = getopt(argc,argv,"hf:s:")) != -1){
		switch (rez){
			case 'h':
                key=0;
                break;
			case 'f':
                fileName=optarg;
                key++;
                break;
            case 's':
                tableName=optarg;
                key++;
                break;
		};
	};

    switch(key){
        case 0:description();
            break;
        case 2:
            interprogramFunc(fileName,tableName);
            //printf("%s,%s\n",fileName,tableName);
            break;
        default:;
    }



    return 0;
}

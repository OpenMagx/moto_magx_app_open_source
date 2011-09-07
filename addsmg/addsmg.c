/*
 制作刷机包辅助工具，Version 2.0。
        addsmg <file> -head num1 B1 -total total B2
 -head   num1 B1  : 在文件<file>的开头添加num1个ASCII码为B1字节。
 -total total B2  : 在文件<file>的末尾追加ASCII为B2的字节，使文件总长度恰好为total。
 注意：num1，total，B1，B2均为十六进制非负整数，前缀0x可有可无。
 Written by goodluck1982 @ IT168    2007-04-18
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void showusage()
{     
   printf("\nUsage: addsmg <file> < -head num1 B1| -total total B2 >\n");
   printf("       NOTE: num1, total, B1 and B2 all have to be hexadecimal inteters! \n");
   printf("       For example:\n");
   printf("       addsmg xxx.smg -head 0x1000  FF\n");
   printf("       addsmg xxx.smg -total 0x2000  0\n");
   printf("       addsmg xxx.smg -total 0x2000 FF -head  0x1000 FF\n");
   printf("       addsmg xxx.smg -head  0x1000 FF -total 0x2000 FF\n\n");
   printf("       Written by goodluck1982 @ IT168\n\n");
   exit(1);
}
 
int FileLen(FILE *fp)
{ long pos=ftell(fp);
  fseek(fp,0L,SEEK_END);
  long end=ftell(fp);
  fseek(fp,pos,SEEK_SET);
  return end;
}

int main( int argc, char* argv[])
{
  char *smgfile;
  unsigned int B1=0,B2=0;
  unsigned long  head=0,total,fh=0,ft=0,i,length;
  char c,*buf;
  FILE *fp;

  if(!(argc==5||argc==8)) showusage();

   smgfile=argv[1]; 
   fp=fopen(smgfile,"r+b");
   if(fp==NULL) {printf("  Open file %s error!\n",smgfile);  exit(2);}

   if(argc==5)
   {
      if( strcmp(argv[2],"-head")==0 ) { fh=1; sscanf(argv[3],"%x",&head); sscanf(argv[4],"%x",&B1); }
      else if( strcmp(argv[2],"-total")==0 ) { ft=1; sscanf(argv[3],"%x",&total);  sscanf(argv[4],"%x",&B2);}
      else showusage();
   }
   else
   {
      if( strcmp(argv[2],"-head")==0 && strcmp(argv[5],"-total")==0 ) 
          {
             fh=ft=1;   
             sscanf(argv[3],"%x",&head);
             sscanf(argv[4],"%x",&B1); 
             sscanf(argv[6],"%x",&total);
             sscanf(argv[7],"%x",&B2); 
          }
      else if( strcmp(argv[2],"-total")==0 && strcmp(argv[5],"-head")==0 ) 
          {
             fh=ft=1;   
             sscanf(argv[3],"%x",&total);
             sscanf(argv[4],"%x",&B2); 
             sscanf(argv[6],"%x",&head);
             sscanf(argv[7],"%x",&B1); 
          }
      else showusage();
   }

   if(B1>255||B2>255)
    {  
      printf(" Error:  B1 and B2 both should be less than 0xFF !\n");
      exit(3);
    }

    length=FileLen(fp);
    if(ft==1&&length+head>total)
    {
     printf("Error: The origional file length 0x%X plus the header length  0x%X\n",length,head);
     printf("       have to be less than the total length 0x%X\n",total);
     exit(4);
    }

    if(fh) 
    {
      buf=(char*) malloc(length);
      for(i=0;i<length;i++)  buf[i]=fgetc(fp); 
      rewind(fp);
      for(i=0;i<head;i++) fputc((unsigned char)B1,fp);
      for(i=0;i<length;i++)  fputc(buf[i],fp); 
      free(buf);
    }
   else
      fseek(fp,0L,SEEK_END);
    
   if(ft)  for(i=0;i<total-length-head;i++) fputc((unsigned char)B2,fp); 
   
   fclose(fp);
  
   return 0;
}

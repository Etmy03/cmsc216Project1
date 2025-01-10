#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define LEN 1024*4
#define BUFFER_LEN 1000

int equals (const char* a, const char* b){
  if((a[0]==b[0])&&(a[1]==b[1])&&(a[2]==b[2])){
    return 1;
  }
  else{
    return 0;
  }
}

char* getRegisters(char* a){
  char delim[] = "R";
  char *myR = strtok(a, delim);
  int c=-1;
  char reg[6];
  char *p_reg = reg;

  while(myR != NULL)
	{
    if(c==-1){
      myR = strtok(NULL, delim);
      c=0;
      continue;
    }
    
    switch(myR[1]){
      case '0':
        reg[c]='A';
        break;
      case '1':
        reg[c]='B';
        break;
      case '2':
        reg[c]='C';
        break;
      case '3':
        reg[c]='D';
        break;
      case '4':
        reg[c]='E';
        break;
      case '5':
        reg[c]='F';
        break;
      default:
        reg[c]=myR[0];
    }
    c++;
    myR = strtok(NULL, delim);
	}
  return p_reg; 
}

char* getHex(char* a){
  char *myHex;
  int x = 'x';
  myHex = strchr(a,x)+1;
  return myHex;
}

int main (int argc, char *argv[])
{
    //char out[LEN];
    char buffer[BUFFER_LEN];
    char buffer2[BUFFER_LEN];
    char opCode[4];
    char *p_buffer = buffer;
    char *p_buffer2 = buffer2;
  
    char line[5];
    char *reg;
    //char myH[3];
    char *hex;

    while(fgets(buffer, BUFFER_LEN, stdin)){
      if(buffer[0] == '#' || buffer[0] == '\n'){
        continue;
      }
      int t=1;
      for( int i=0; i< sizeof(buffer);i++){
        if(buffer[i]=='X' || buffer[i]=='x' ){
          buffer[i]= 'x';
          continue;
        }
        buffer[i] = toupper(buffer[i]);
        if((buffer[i] != ' ')&&(t==1)){
          opCode[0] = buffer[i];
          opCode[1] = toupper(buffer[i+1]);
          opCode[2] = toupper(buffer[i+2]);
          t=0;
        }
      }

      if(equals(opCode,"ADD")){
        line[0]='0';
        reg = getRegisters(p_buffer);
        line[1]=reg[0];
        line[2]=reg[1];
        line[3]=reg[2];
        
      }
      else if(equals(opCode,"SUB")){
        line[0]='1';
        reg = getRegisters(p_buffer);
        line[1]=reg[0];
        line[2]=reg[1];
        line[3]=reg[2];
      }
      else if(equals(opCode,"AND")){
        line[0]='2';
        reg = getRegisters(p_buffer);
        line[1]=reg[0];
        line[2]=reg[1];
        line[3]=reg[2];
      }
      else if(equals(opCode,"ORR")){
        line[0]='3';
        reg = getRegisters(p_buffer);
        line[1]=reg[1];
        line[2]=reg[2];
        line[3]=reg[3];
      }
      else if(equals(opCode,"EOR")){
        line[0]='4';
        reg = getRegisters(p_buffer);
        line[1]=reg[1];
        line[2]=reg[2];
        line[3]=reg[3];
      }
      else if(equals(opCode,"LSL")){
        line[0]='5';
        reg = getRegisters(p_buffer);
        line[1]=reg[0];
        line[2]=reg[1];
        line[3]=reg[2];
      }
      else if(equals(opCode,"LSR")){
        line[0]='6';
        reg = getRegisters(p_buffer);
        line[1]=reg[1];
        line[2]=reg[2];
        line[3]=reg[3];
      }
      else if(equals(opCode,"ASR")){
        line[0]='7';
        reg = getRegisters(p_buffer);
        line[1]=reg[1];
        line[2]=reg[2];
        line[3]=reg[3];
      }
      else if(equals(opCode,"LDR")){
        line[0]='8';
        reg = getRegisters(p_buffer);
        line[1]=reg[1];
        line[2]=reg[2];
        line[3]='0';
      }
      else if(equals(opCode,"STR")){
        line[0]='9';
        reg = getRegisters(p_buffer);
        line[1]=reg[1];
        line[2]=reg[2];
        line[3]='0';
      }
      else if(equals(opCode,"CMP")){
        line[0]='A';
        reg = getRegisters(p_buffer);
        line[1]=reg[0];
        line[2]=reg[1];
        line[3]='0';
      }
      else if(equals(opCode,"MOV")){
        strncpy(buffer2, buffer, BUFFER_LEN);
        line[0]='B';
        reg = getRegisters(p_buffer);
        line[1]=reg[0];
        hex = getHex(p_buffer2);
        if(hex[2]=='\0' || hex[2]==' '){
          line[2]='0';
          line[3]=hex[0];
        }
        else{
          line[2]=hex[0];
          line[3]=hex[1];
        }
        
      }
      else if(equals(opCode,"BEQ")){
        line[0]='D';
        hex = getHex(p_buffer);
        if(hex[2]=='\0' || hex[2]==' '){
          line[1]='0';
          line[2]='0';
          line[3]=hex[0];
        }
        else if(hex[3]=='\0' || hex[3]==' '){
          line[1]='0';
          line[2]=hex[0];
          line[3]=hex[1];
        }
        else{
          line[1]=hex[0];
          line[2]=hex[1];
          line[3]=hex[2];
        }
      }
      else if(equals(opCode,"END")){
        line[0]='E';
        line[1]='0';
        line[2]='0';
        line[3]='0';
      }
      else if(equals(opCode,"NOP")){
        line[0]='F';
        line[1]='0';
        line[2]='0';
        line[3]='0';
      }
      else if(buffer[0]=='B'){
        line[0]='C';
        hex = getHex(p_buffer);
        if(hex[2]=='\0'){
          line[1]='0';
          line[2]='0';
          line[3]=hex[0];
        }
        else if(hex[3]=='\0'){
          line[1]='0';
          line[2]=hex[0];
          line[3]=hex[1];
        }
        else{
          line[1]=hex[0];
          line[2]=hex[1];
          line[3]=hex[2];
        }
      }
      printf("%s", line);
      
    }
}
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
//intruções disponiveis
/*add,addi,addiu,addu,and,andi,lui,nor,or,ori,slt,slti,sltiu,sltu,sub,subu,xor,xori,
sll,sllv,sra,srav,srl,srlv,div,divu,mult,multu,beq,bne,j*/
//reconhecidas mais sem ação(apenas opcode)
//mfhi,mflo,mthi,mtlo

char *decToBin(int n){
    static char bin[32];
    for(int i=0;i<32;i++){
        bin[i]='0';
    }
    for(int i=0;n>0;i++){
        if((n%2)==0)
            bin[i]='0';
        else
            bin[i]='1';
        n=n/2;
    }
    //printf("binn%s\n\n",bin);
    return bin;
}

int binToDec(char binNum[]){
    int numDec=0;
    for(int i=0;i<32;i++){
        if(binNum[i]=='1'){
            numDec=numDec + pow(2,i);
        }
    }
    return numDec;
}

int regPosi(char reg[]){
    if(strcmp(reg,"r0")==0)
        return 0;
    else if(strcmp(reg,"at")==0)
        return 1;
    else if(strcmp(reg,"v0")==0)
        return 2;
    else if(strcmp(reg,"v1")==0)
        return 3;
    else if(strcmp(reg,"a0")==0)
        return 4;
    else if(strcmp(reg,"a1")==0)
        return 5;
    else if(strcmp(reg,"a2")==0)
        return 6;
    else if(strcmp(reg,"a3")==0)
        return 7;
    else if(strcmp(reg,"t0")==0)
        return 8;
    else if(strcmp(reg,"t1")==0)
        return 9;
    else if(strcmp(reg,"t2")==0)
        return 10;
    else if(strcmp(reg,"t3")==0)
        return 11;
    else if(strcmp(reg,"t4")==0)
        return 12;
    else if(strcmp(reg,"t5")==0)
        return 13;
    else if(strcmp(reg,"t6")==0)
        return 14;
    else if(strcmp(reg,"t7")==0)
        return 15;
    else if(strcmp(reg,"s0")==0)
        return 16;
    else if(strcmp(reg,"s1")==0)
        return 17;
    else if(strcmp(reg,"s2")==0)
        return 18;
    else if(strcmp(reg,"s3")==0)
        return 19;
    else if(strcmp(reg,"s4")==0)
        return 20;
    else if(strcmp(reg,"s5")==0)
        return 21;
    else if(strcmp(reg,"s6")==0)
        return 22;
    else if(strcmp(reg,"s7")==0)
        return 23;
    else if(strcmp(reg,"t8")==0)
        return 24;
    else if(strcmp(reg,"t9")==0)
        return 25;
    else if(strcmp(reg,"k0")==0)
        return 26;
    else if(strcmp(reg,"k1")==0)
        return 27;
    else if(strcmp(reg,"gp")==0)
        return 28;
    else if(strcmp(reg,"sp")==0)
        return 29;
    else if(strcmp(reg,"s8")==0)
        return 30;
    else if(strcmp(reg,"ra")==0)
        return 31;
    else
        return -1;
}


void error(FILE *File2){
    fclose(File2);
    File2 = fopen("MontadorSaida.txt", "w");
    fprintf(File2,"ERROR");
    fclose(File2);
}

int charToInt(char c){
    if(c=='0')
        return 0;
    if(c=='1')
        return 1;
    if(c=='2')
        return 2;
    if(c=='3')
        return 3;
    if(c=='4')
        return 4;
    if(c=='5')
        return 5;
    if(c=='6')
        return 6;
    if(c=='7')
        return 7;
    if(c=='8')
        return 8;
    if(c=='9')
        return 9;
}


int main(){
    //abre arquivo de leitura
    FILE *File = fopen("MontadorEntrada.txt", "r");
    //limpa arquivo de saida
    FILE *File2 = fopen("MontadorSaida.txt","w");
    fprintf(File2,"");
    fclose(File2);

    File2 = fopen("MontadorSaida.txt","a");
    int dest,reg1,reg2;
    char comand[5];
    //declarando registradores
    int regs[32]={0,0,0,0,3,2147481308,2147481324,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,268468224,2147481304,0,0};
    /*espelho de regs
    0 r0 = 0;
    1 at = 0;
    2 v0 = 0;
    3 v1 = 0;
    4 a0 = 3;
    5 a1 = 2147481308;
    6 a2 = 2147481324;
    7 a3 = 0;
    8 t0 = 0;
    9 t1 = 0;
    10 t2 = 0;
    11 t3 = 0;
    12 t4 = 0;
    13 t5 = 0;
    14 t6 = 0;
    15 t7 = 0;
    16 s0 = 0;
    17 s1 = 0;
    18 s2 = 0;
    19 s3 = 0;
    20 s4 = 0;
    21 s5 = 0;
    22 s6 = 0;
    23 s7 = 0;
    24 t8 = 0;
    25 t9 = 0;
    26 k0 = 0;
    27 k1 = 0;
    28 gp = 268468224;
    29 sp = 2147481304;
    30 s8 = 0;
    31 ra = 0;
*/
    char line[100];
    char texto[100];
    char temp[5];
    char temp2[5];
    char tempD[5];
    char temp16[17];
    char label[20];
    char temp26[17];
    char *sub;
    int comment;

    while(fgets(line,100,File) != NULL){
        comment=0;
        if(strcmp(line,"\n")!=0){
            //printf("%s",line);

            sub = strtok(line," ,");
            if(line[0]=='#'){
                comment=1;
            }
            while(sub != NULL){
                //remove \n do final da linha
                if(sub[strlen(sub)-1]=='\n')
                    sub[strlen(sub)-1]='\0';
                    //se for comentario pega outra linha
                    if(comment==0 && sub[0]!='#'){
                        if(strcmp(sub,"add")==0 || strcmp(sub,"addu")==0 || strcmp(sub,"sub")==0 || strcmp(sub,"subu")==0 || strcmp(sub,"and")==0
                            || strcmp(sub,"nor")==0 || strcmp(sub,"or")==0 || strcmp(sub,"slt")==0 || strcmp(sub,"sltu")==0 || strcmp(sub,"xor")==0
                            || strcmp(sub,"addi")==0 ||strcmp(sub,"addiu")==0 ||strcmp(sub,"andi")==0 ||strcmp(sub,"ori")==0 ||strcmp(sub,"slti")==0
                            || strcmp(sub,"sltiu")==0 || strcmp(sub,"xori")==0){
                            strcpy(comand,sub);
                            if(strcmp(sub,"add")==0 || strcmp(sub,"addu")==0 || strcmp(sub,"sub")==0 || strcmp(sub,"subu")==0 || strcmp(sub,"and")==0
                            || strcmp(sub,"nor")==0 || strcmp(sub,"or")==0 || strcmp(sub,"slt")==0 || strcmp(sub,"sltu")==0 || strcmp(sub,"xor")==0)
                                fprintf(File2, "000000");
                            else if(strcmp(sub,"addi")==0)
                                fprintf(File2, "001000");
                            else if(strcmp(sub,"addiu")==0)
                                fprintf(File2, "001001");
                            else if(strcmp(sub,"andi")==0)
                                fprintf(File2, "001100");
                            else if(strcmp(sub,"ori")==0)
                                fprintf(File2, "001101");
                            else if(strcmp(sub,"slti")==0)
                                fprintf(File2, "001010");
                            else if(strcmp(sub,"sltiu")==0)
                                fprintf(File2, "001011");
                            else if(strcmp(sub,"xori")==0)
                                fprintf(File2, "001110");

                            sub = strtok(NULL," ,");
                            //printf("SUB %s\n",sub);
                            if(sub[0]=='$'){
                                char reg[2];
                                reg[0]=sub[1];
                                reg[1]=sub[2];
                                reg[2]='\0';
                                dest = regPosi(reg);
                                if(dest!=-1){
                                    char *binNum;
                                    binNum = decToBin(dest);
                                    tempD[0]=binNum[4],tempD[1]=binNum[3],tempD[2]=binNum[2],tempD[3]=binNum[1],tempD[4]=binNum[0],tempD[5]='\0';
                                    sub = strtok(NULL," ,");
                                    //printf("SUB %s\n",sub);
                                    if(sub[0]=='$'){
                                        char reg[2];
                                        reg[0]=sub[1];
                                        reg[1]=sub[2];
                                        reg[2]='\0';
                                        reg1 = regPosi(reg);
                                        if(reg1!=-1){
                                            binNum = decToBin(reg1);
                                            temp[0]=binNum[4],temp[1]=binNum[3],temp[2]=binNum[2],temp[3]=binNum[1],temp[4]=binNum[0],temp[5]='\0';
                                            fprintf(File2,temp);
                                            sub = strtok(NULL," ,");
                                            //printf("SUB %s\n",sub);
                                            if(sub[0]=='$'){
                                                char reg[2];
                                                reg[0]=sub[1];
                                                reg[1]=sub[2];
                                                reg[2]='\0';
                                                reg2 = regPosi(reg);
                                                if(reg2!=-1){
                                                    binNum = decToBin(reg2);
                                                    temp[0]=binNum[4],temp[1]=binNum[3],temp[2]=binNum[2],temp[3]=binNum[1],temp[4]=binNum[0],temp[5]='\0';
                                                    fprintf(File2,temp);
                                                    tempD[5]='\0';
                                                    fprintf(File2,tempD);
                                                    if(strcmp(comand,"add")==0){
                                                        fprintf(File2, "00000");
                                                        fprintf(File2, "100000\n");
                                                        regs[dest]+=regs[reg1]+regs[reg2];
                                                    }
                                                    else if(strcmp(comand,"addu")==0){
                                                        fprintf(File2, "00000");
                                                        fprintf(File2, "100100\n");
                                                        regs[dest]+=regs[reg1]+regs[reg2];
                                                    }
                                                    else if(strcmp(comand,"sub")==0){
                                                        fprintf(File2, "00000");
                                                        fprintf(File2, "100010\n");
                                                        regs[dest]-=regs[reg1]-regs[reg2];
                                                    }
                                                    else if(strcmp(comand,"subu")==0){
                                                        fprintf(File2, "00000");
                                                        fprintf(File2, "100011\n");
                                                        regs[dest]-=regs[reg1]-regs[reg2];
                                                    }
                                                    else if(strcmp(comand,"and")==0){
                                                        fprintf(File2, "00000");
                                                        fprintf(File2, "100100\n");
                                                        regs[dest]=(regs[reg1]&&regs[reg2]);
                                                    }
                                                    else if(strcmp(comand,"nor")==0){
                                                        fprintf(File2, "00000");
                                                        fprintf(File2, "100111\n");
                                                        regs[dest]=!(regs[reg1]||regs[reg2]);
                                                    }
                                                    else if(strcmp(comand,"or")==0){
                                                        fprintf(File2, "00000");
                                                        fprintf(File2, "100101\n");
                                                        regs[dest]=(regs[reg1]||regs[reg2]);
                                                    }
                                                    else if(strcmp(comand,"slt")==0){
                                                        fprintf(File2, "00000");
                                                        fprintf(File2, "101010\n");
                                                        regs[dest]=(regs[reg1]<regs[reg2]);
                                                    }
                                                    else if(strcmp(comand,"sltu")==0){
                                                        fprintf(File2, "00000");
                                                        fprintf(File2, "101011\n");
                                                        regs[dest]=(regs[reg1]<regs[reg2]);
                                                    }
                                                    else if(strcmp(comand,"xor")==0){
                                                        fprintf(File2, "00000");
                                                        fprintf(File2, "100110\n");
                                                        regs[dest]=(!regs[reg1]&&regs[reg2] || (regs[reg1]&&!regs[reg2]));
                                                    }
                                                }
                                                else{
                                                    fclose(File2);
                                                    FILE *File2 = fopen("MontadorSaida.txt", "w");
                                                    fprintf(File2,"ERROR");
                                                    fclose(File2);
                                                 }
                                            }else if(sub[0]=='0'||sub[0]=='1'||sub[0]=='2'||sub[0]=='3'||sub[0]=='4'||sub[0]=='5'||sub[0]=='6'||sub[0]=='7'||sub[0]=='8'||sub[0]=='9'){
                                                    fprintf(File2,tempD);
                                                    int cont = charToInt(sub[0]);
                                                    if(sub[1]!='\n' && sub[1]!='\0'){
                                                        cont = cont*10;
                                                        int cont2 = charToInt(sub[1]);
                                                        cont += cont2;
                                                    }
                                                    if(strcmp(comand,"addi")==0 || strcmp(comand,"addiu")==0){
                                                        regs[dest]+=regs[reg1]+cont;
                                                    }
                                                    else if(strcmp(comand,"andi")==0){
                                                        regs[dest]=(regs[reg1]&&cont);
                                                    }
                                                    else if(strcmp(comand,"ori")==0){
                                                        regs[dest]=(regs[reg1]||cont);
                                                    }
                                                    else if(strcmp(comand,"slti || sltiu")==0){
                                                        regs[dest]=(regs[reg1]<cont);
                                                    }
                                                    else if(strcmp(comand,"xori")==0){
                                                        regs[dest]=(!regs[reg1]&&cont || (regs[reg1]&&!cont));
                                                    }

                                                    binNum = decToBin(cont);
                                                    temp16[0]=binNum[15],temp16[1]=binNum[14],temp16[2]=binNum[13],temp16[3]=binNum[12],temp16[4]=binNum[11],temp16[5]=binNum[10],temp16[6]=binNum[9],
                                                    temp16[7]=binNum[8],temp16[8]=binNum[7],temp16[9]=binNum[6],temp16[10]=binNum[5],temp16[11]=binNum[4],temp16[12]=binNum[3],temp16[13]=binNum[2],
                                                    temp16[14]=binNum[1],temp16[15]=binNum[0],temp16[16]='\n',temp16[17]='\0';
                                                    fprintf(File2,temp16);

                                             }else{
                                                error(File2);
                                             }
                                        }else{
                                            error(File2);
                                         }
                                    }else{
                                        error(File2);
                                     }
                                }else{
                                    error(File2);
                                 }
                            }else{
                                error(File2);
                             }
                        }
                        //shift
                        else if(strcmp(sub,"sll")==0 || strcmp(sub,"sra")==0 || strcmp(sub,"srl")==0 || strcmp(sub,"sllv")==0 || strcmp(sub,"srav")==0 || strcmp(sub,"srlv")==0){
                            strcpy(comand,sub);
                            fprintf(File2, "000000");
                            if(strcmp(sub,"sll")==0 || strcmp(sub,"sra")==0 || strcmp(sub,"srl")==0)
                                fprintf(File2, "00000");
                            sub = strtok(NULL," ,");
                            if(sub[0]=='$'){
                                char reg[2];
                                reg[0]=sub[1];
                                reg[1]=sub[2];
                                reg[2]='\0';
                                dest = regPosi(reg);
                                if(dest!=-1){
                                    char *binNum;
                                    char *binNum2;
                                    binNum = decToBin(dest);
                                    tempD[0]=binNum[4],tempD[1]=binNum[3],tempD[2]=binNum[2],tempD[3]=binNum[1],tempD[4]=binNum[0],tempD[5]='\0';
                                    sub = strtok(NULL," ,");
                                    if(sub[0]=='$'){
                                        char reg[2];
                                        reg[0]=sub[1];
                                        reg[1]=sub[2];
                                        reg[2]='\0';
                                        reg1 = regPosi(reg);
                                        if(reg1!=-1){
                                            binNum = decToBin(reg1);
                                            temp[0]=binNum[4],temp[1]=binNum[3],temp[2]=binNum[2],temp[3]=binNum[1],temp[4]=binNum[0],temp[5]='\0';
                                            if(strcmp(comand,"sll")==0 || strcmp(comand,"sra")==0 || strcmp(comand,"srl")==0)
                                                fprintf(File2,temp);
                                            tempD[5]='\0';
                                            fprintf(File2,tempD);
                                            sub = strtok(NULL," ,");
                                            if(strcmp(comand,"sll")==0 || strcmp(comand,"sra")==0 || strcmp(comand,"srl")==0){
                                                if(sub[0]=='0'||sub[0]=='1'||sub[0]=='2'||sub[0]=='3'||sub[0]=='4'||sub[0]=='5'||sub[0]=='6'||sub[0]=='7'||sub[0]=='8'||sub[0]=='9'){
                                                    int cont = charToInt(sub[0]);
                                                    if(sub[1]!='\n' && sub[1]!='\0'){
                                                        cont = cont*10;
                                                        int cont2 = charToInt(sub[1]);
                                                        cont += cont2;
                                                    }
                                                    binNum = decToBin(cont);
                                                    temp[0]=binNum[4],temp[1]=binNum[3],temp[2]=binNum[2],temp[3]=binNum[1],temp[4]=binNum[0],temp[5]='\0';
                                                    fprintf(File2,temp);
                                                    if(strcmp(comand,"sll")==0){
                                                        fprintf(File2, "000000\n");
                                                        for(int i=0;i<cont;i++){
                                                            for(int k=30;k>=0;k--){
                                                                binNum[k+1]=binNum[k];
                                                            }
                                                            binNum[0]=0;
                                                        }
                                                    }
                                                    else if(strcmp(comand,"sra")==0 || strcmp(comand,"srl")==0){
                                                        if(strcmp(comand,"sra")==0)
                                                            fprintf(File2, "000011\n");
                                                        else if(strcmp(comand,"srl")==0)
                                                            fprintf(File2, "000010\n");
                                                        for(int i=0;i<cont;i++){
                                                            for(int k=1;k<32;k++){
                                                                binNum[k-1]=binNum[k];
                                                            }
                                                            binNum[31]=0;
                                                        }
                                                    }
                                                    regs[dest] = binToDec(binNum);
                                                }
                                                else
                                                    error(File2);
                                            }
                                            else if(strcmp(comand,"sllv")==0 || strcmp(comand,"srav")==0 || strcmp(comand,"srlv")==0){
                                                fprintf(File2,"00000");
                                                sub = strtok(NULL," ,");
                                                if(sub[0]=='$'){
                                                    char reg[2];
                                                    reg[0]=sub[1];
                                                    reg[1]=sub[2];
                                                    reg[2]='\0';
                                                    reg2 = regPosi(reg);
                                                    if(reg2!=-1){
                                                        binNum = decToBin(reg2);
                                                        temp[0]=binNum[4],temp[1]=binNum[3],temp[2]=binNum[2],temp[3]=binNum[1],temp[4]=binNum[0],temp[5]='\0';
                                                        temp2[5]='\0';
                                                        fprintf(File2,temp2);
                                                        fprintf(File2,temp);
                                                        tempD[5]='\0';
                                                        fprintf(File2,tempD);
                                                        fprintf(File2,"00000");
                                                        if(strcmp(comand,"sllv")==0){
                                                            fprintf(File2,"00100");
                                                            for(int i=0;i<regs[reg2];i++){
                                                                for(int k=30;k>=0;k--){
                                                                    binNum2[k+1]=binNum2[k];
                                                                }
                                                                binNum2[0]=0;
                                                            }
                                                        }
                                                        else if(strcmp(comand,"srav")==0 || strcmp(comand,"srlv")==0){
                                                            if(strcmp(comand,"srav")==0)
                                                                fprintf(File2, "000111\n");
                                                            else if(strcmp(comand,"srlv")==0)
                                                                fprintf(File2, "000110\n");
                                                            for(int i=0;i<regs[reg2];i++){
                                                                for(int k=1;k<32;k++){
                                                                    binNum2[k-1]=binNum2[k];
                                                                }
                                                                binNum2[31]=0;
                                                            }
                                                        }
                                                        regs[dest] = binToDec(binNum2);
                                                    }
                                                    else
                                                        error(File2);
                                                }
                                                else
                                                    error(File2);
                                            }
                                        }
                                        else
                                            error(File2);
                                    }
                                    else
                                        error(File2);
                                }
                                else
                                    error(File2);
                            }
                            else
                                error(File2);
                        }//mult e div
                         //não consegue implementar o MFLO,MFHI,MTHI e MTLO obs monta opcode mas é só isso q faz nesse caso
                        else if(strcmp(sub,"div")==0 || strcmp(sub,"divu")==0 || strcmp(sub,"mfhi")==0 || strcmp(sub,"mflo")==0
                                || strcmp(sub,"mthi")==0 || strcmp(sub,"mtlo")==0 || strcmp(sub,"mult")==0 || strcmp(sub,"multu")==0){
                            strcpy(comand,sub);
                            fprintf(File2, "000000");
                            sub = strtok(NULL," ,");
                            if(strcmp(comand,"div")==0 || strcmp(comand,"divu")==0 || strcmp(comand,"mult")==0 || strcmp(comand,"multu")==0){
                                if(sub[0]=='$'){
                                    char reg[2];
                                    reg[0]=sub[1];
                                    reg[1]=sub[2];
                                    reg[2]='\0';
                                    dest = regPosi(reg);
                                    if(dest!=-1){
                                        char *binNum;
                                        char *binNum2;
                                        binNum = decToBin(dest);
                                        tempD[0]=binNum[4],tempD[1]=binNum[3],tempD[2]=binNum[2],tempD[3]=binNum[1],tempD[4]=binNum[0],tempD[5]='\0';
                                        fprintf(File2, tempD);
                                        sub = strtok(NULL," ,");
                                        if(sub[0]=='$'){
                                            char reg[2];
                                            reg[0]=sub[1];
                                            reg[1]=sub[2];
                                            reg[2]='\0';
                                            reg1 = regPosi(reg);
                                            if(reg1!=-1){
                                                binNum = decToBin(reg1);
                                                temp[0]=binNum[4],temp[1]=binNum[3],temp[2]=binNum[2],temp[3]=binNum[1],temp[4]=binNum[0],temp[5]='\0';
                                                fprintf(File2,temp);
                                                fprintf(File2,"0000000000");
                                                if(strcmp(comand,"div")==0){
                                                    fprintf(File2,"011010\n");
                                                    regs[dest]=regs[dest]/regs[reg1];
                                                }
                                                else if(strcmp(comand,"divu")==0){
                                                    fprintf(File2,"011011\n");
                                                    regs[dest]=regs[dest]/regs[reg1];
                                                }
                                                else if(strcmp(comand,"mult")==0){
                                                    printf("aqui\n");
                                                    fprintf(File2,"011000\n");
                                                    regs[dest]=regs[dest]*regs[reg1];
                                                }
                                                else if(strcmp(comand,"multu")==0){
                                                    fprintf(File2,"011001\n");
                                                    regs[dest]=regs[dest]*regs[reg1];
                                                }
                                            }
                                            else
                                                error(File2);
                                        }
                                        else
                                            error(File2);
                                    }
                                    else
                                        error(File2);
                                }
                                else
                                    error(File2);
                            }
                            else if(strcmp(comand,"mfhi")==0 || strcmp(comand,"mflo")==0){
                                fprintf(File2,"0000000000");
                                sub = strtok(NULL," ,");
                                if(sub[0]=='$'){
                                    char reg[2];
                                    reg[0]=sub[1];
                                    reg[1]=sub[2];
                                    reg[2]='\0';
                                    reg1 = regPosi(reg);
                                    if(reg1!=-1){
                                        char *binNum;
                                        binNum = decToBin(reg1);
                                        temp[0]=binNum[4],temp[1]=binNum[3],temp[2]=binNum[2],temp[3]=binNum[1],temp[4]=binNum[0],temp[5]='\0';
                                        fprintf(File2,temp);
                                        fprintf(File2,"00000");
                                        if(strcmp(comand,"mfhi")==0)
                                            fprintf(File2,"010000\n");
                                        else if(strcmp(comand,"mflo")==0)
                                            fprintf(File2,"010010\n");
                                    }
                                    else
                                        error(File2);
                                }
                                else
                                    error(File2);
                            }
                            else if(strcmp(comand,"mthi")==0 || strcmp(comand,"mtlo")==0){
                                sub = strtok(NULL," ,");
                                if(sub[0]=='$'){
                                    char reg[2];
                                    reg[0]=sub[1];
                                    reg[1]=sub[2];
                                    reg[2]='\0';
                                    reg1 = regPosi(reg);
                                    if(reg1!=-1){
                                        char *binNum;
                                        binNum = decToBin(reg1);
                                        temp[0]=binNum[4],temp[1]=binNum[3],temp[2]=binNum[2],temp[3]=binNum[1],temp[4]=binNum[0],temp[5]='\0';
                                        fprintf(File2,temp);
                                        if(strcmp(comand,"mthi")==0)
                                            fprintf(File2,"010001\n");
                                        else if(strcmp(comand,"mtlo")==0)
                                            fprintf(File2,"010011\n");
                                    }
                                    else
                                        error(File2);
                                }
                                else
                                    error(File2);
                            }
                        }
                        //branch
                        else if(strcmp(sub,"beq")==0 || strcmp(sub,"bneq")==0){
                            int found=0;
                            strcpy(comand,sub);
                            if(strcmp(sub,"beq")==0)
                                fprintf(File2,"000100");
                            else
                                fprintf(File2,"000101");
                            sub = strtok(NULL," ,");
                            if(sub[0]=='$'){
                                char reg[2];
                                reg[0]=sub[1];
                                reg[1]=sub[2];
                                reg[2]='\0';
                                dest = regPosi(reg);
                                if(dest!=-1){
                                    char *binNum;
                                    binNum = decToBin(dest);
                                    temp[0]=binNum[4],temp[1]=binNum[3],temp[2]=binNum[2],temp[3]=binNum[1],temp[4]=binNum[0],temp[5]='\0';
                                    fprintf(File2,temp);
                                    sub = strtok(NULL," ,");
                                    if(sub[0]=='$'){
                                        char reg[2];
                                        reg[0]=sub[1];
                                        reg[1]=sub[2];
                                        reg[2]='\0';
                                        reg1 = regPosi(reg);
                                        if(reg1!=-1){
                                            char *binNum;
                                            binNum = decToBin(reg1);
                                            temp[0]=binNum[4],temp[1]=binNum[3],temp[2]=binNum[2],temp[3]=binNum[1],temp[4]=binNum[0],temp[5]='\0';
                                            fprintf(File2,temp);
                                            fprintf(File2,"xxxxxxxxxxxxxxxx\n");
                                            sub = strtok(NULL," ,");
                                            strcpy(label,sub);
                                            label[strlen(label)-1]='\0';
                                            if(strcmp(comand,"beq")==0){
                                                if(regs[dest]==regs[reg1]){
                                                    fclose(File);
                                                    FILE *File = fopen("MontadorEntrada.txt", "r");
                                                    while(fgets(line,100,File) != NULL){
                                                        sub = strtok(line," ,");
                                                        while(sub != NULL){
                                                            //remove \n do final da linha
                                                            if(sub[strlen(sub)-1]=='\n')
                                                                sub[strlen(sub)-1]='\0';
                                                                //se for comentario pega outra linha
                                                                if(sub[0]!='#' && sub[strlen(sub)-1]==':'){
                                                                    sub[strlen(sub)-1]='\0';
                                                                    if(strcmp(label,sub)==0){
                                                                        found=1;
                                                                        //printf("%s\n",label);
                                                                        break;
                                                                    }
                                                                }
                                                            if(found==1)
                                                                break;
                                                            sub = strtok(NULL," ,");
                                                        }
                                                        if(found==1)
                                                            break;
                                                    }
                                                    if(found==0 && regs[dest]==regs[reg1]){
                                                        printf("aqui\n");
                                                        error(File2);
                                                    }
                                                }
                                            }
                                            else if(strcmp(comand,"bneq")==0){
                                                if(regs[dest]!=regs[reg1]){
                                                    fclose(File);
                                                    FILE *File = fopen("MontadorEntrada.txt", "r");
                                                    while(fgets(line,100,File) != NULL){
                                                        sub = strtok(line," ,");
                                                        while(sub != NULL){
                                                            //remove \n do final da linha
                                                            if(sub[strlen(sub)-1]=='\n')
                                                                sub[strlen(sub)-1]='\0';
                                                                //se for comentario pega outra linha
                                                                //printf("\n\n\n%s %s\n%d %d\n\n",label,sub,strlen(label),strlen(sub));
                                                                if(sub[0]!='#' && sub[strlen(sub)-1]==':'){
                                                                    sub[strlen(sub)-1]='\0';
                                                                    if(strcmp(label,sub)==0){
                                                                        found=1;
                                                                        //printf("%s\n",label);
                                                                        break;
                                                                    }
                                                                }
                                                            if(found==1)
                                                                break;
                                                            sub = strtok(NULL," ,");
                                                        }
                                                        if(found==1)
                                                            break;
                                                    }
                                                    if(found==0 && regs[dest]!=regs[reg1]){
                                                        error(File2);
                                                    }
                                                }
                                            }
                                            else
                                                error(File2);
                                        }
                                        else
                                            error(File2);
                                    }
                                    else
                                        error(File2);
                                }
                                else
                                    error(File2);
                            }
                            else
                                error(File2);
                        }
                        //jump
                        else if(strcmp(sub,"j")==0 || strcmp(sub,"jal")==0){
                            int found=0,lineNum=0;
                            if(strcmp(sub,"j")==0)
                                fprintf(File2,"000010");
                            else
                                fprintf(File2,"000011");
                            strcpy(comand,sub);
                            sub = strtok(NULL," ,");
                            strcpy(label,sub);
                            label[strlen(label)-1]='\0';
                            //printf("%s\n",label);
                            fclose(File);
                            FILE *File = fopen("MontadorEntrada.txt", "r");
                            while(fgets(line,100,File) != NULL){
                                sub = strtok(line," ,");
                                while(sub != NULL){
                                    //remove \n do final da linha
                                    if(sub[strlen(sub)-1]=='\n')
                                        sub[strlen(sub)-1]='\0';
                                        //se for comentario pega outra linha
                                        if(sub[0]!='#' && sub[strlen(sub)-1]==':'){
                                            sub[strlen(sub)-1]='\0';
                                            if(strcmp(label,sub)==0){
                                                found=1;
                                                char *binNum;
                                                binNum = decToBin(lineNum);
                                                //target "bin com 26 bits da linha da label"
                                                int I=25;
                                                for(int i=0;i<26;i++){
                                                    temp26[i]=binNum[I];
                                                    I--;
                                                }
                                                temp26[26]='\n',temp26[27]='\0';
                                                fprintf(File2,temp26);
                                                if(strcmp(comand,"jal")==0){
                                                    //guarda o numero da linha da proxima instrução
                                                    regs[31]=lineNum+1;
                                                }
                                                break;
                                            }
                                        }
                                        if(found==1)
                                            break;
                                        sub = strtok(NULL," ,");
                                }
                                if(found==1)
                                    break;
                                lineNum++;
                            }
                            if(found==0){
                                error(File2);
                            }
                        }
                        //load word
                        //nao implementei as funcões lw e sw
                        else if(strcmp(sub,"lui")==0){
                            fprintf(File2, "001111");
                            fprintf(File2, "00000");
                            sub = strtok(NULL," ,");
                            if(sub[0]=='$'){
                                char reg[2];
                                reg[0]=sub[1];
                                reg[1]=sub[2];
                                reg[2]='\0';
                                dest = regPosi(reg);
                                if(dest!=-1){
                                    char *binNum;
                                    binNum = decToBin(dest);
                                    tempD[0]=binNum[4],tempD[1]=binNum[3],tempD[2]=binNum[2],tempD[3]=binNum[1],tempD[4]=binNum[0],tempD[5]='\0';
                                    fprintf(File2,tempD);
                                    sub = strtok(NULL," ,");
                                    if(sub[0]=='0'||sub[0]=='1'||sub[0]=='2'||sub[0]=='3'||sub[0]=='4'||sub[0]=='5'||sub[0]=='6'||sub[0]=='7'||sub[0]=='8'||sub[0]=='9'){
                                        int cont = charToInt(sub[0]);
                                        if(sub[1]!='\n' && sub[1]!='\0'){
                                            cont = cont*10;
                                            int cont2 = charToInt(sub[1]);
                                            cont += cont2;
                                        }
                                        regs[dest]=cont;
                                        binNum = decToBin(cont);
                                        int I=15;
                                        for(int i=0;i<16;i++){
                                            temp16[i]=binNum[I];
                                            I--;
                                        }
                                        temp16[16]='\n',temp16[17]='\0';
                                        fprintf(File2,temp16);
                                    }
                                    else{
                                        error(File2);
                                    }
                                }
                                else{
                                    error(File2);
                                }
                            }
                            else{
                                error(File2);
                            }
                        }
                        else if(sub[0]!='.' && sub[strlen(sub)-1]!=':'){
                            error(File2);
                            printf("SUB %s %c\n",sub,sub[strlen(sub)-1]);
                        }
                    }
                    //comentario
                    else
                        comment=1;

                sub = strtok(NULL," ,");
            }
        }
    }
    fclose(File2);
    fclose(File);

    return 0;
}











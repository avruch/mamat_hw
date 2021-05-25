#include "string.h"
#include "ip.h"
#include <stddef.h>
#include <iostream>
#include <cstring>

#define BYTE_MAX_VAL 255
#define BYTE_MIN_VAL 0
#define MAX_SHIFT_VAL 24
#define SIZE_OF_BYTE 8

    /**
     * @brief Initiates an empty string
     */
    String::String(){
        length=0;
        data=NULL;
    return;
    }

    /**
     * @brief Initiates string from other string
     */
    String::String(const String &str){
        length=str.length;
        if (!length){
            data=NULL;
        }
        else {
            data=new char[length+1];
            strncpy(data, str.data, length+1);
        }
    return;
    }

    /**
     * @brief Initiates a string from char array
     */
    String::String(const char *str){
        if(!str){
            data=NULL;
            length=0;
            return;
        }
        length=strlen(str);
        if (!length){
            data=NULL;
        }
        else {
        	data=new char[length+1];
             strncpy(data, str, length+1);
        }
        return;
    }


    String::~String(){
        if(NULL!=data){
            delete[]data;
        }
    }

    /**
     * @brief Changes this from String
     */
    String& String::operator=(const String &rhs){
        delete[] data;
        length=rhs.length;
        if(!length){
            data=NULL;
        }
        else{
        data=new char[length];
        strncpy(data,rhs.data,length);
        }
        return *this;
    }

    /**
     * @brief Changes this from char array
     */
    String& String::operator=(const char *str){
        delete[] data;
        length=strlen(str);
        if(!length){
            data=NULL;
        }
        else {
            data=new char[length+1];
            strncpy(data,str,length+1);
        }
        return *this;
    }



    /**
     * @brief Returns true iff the contents of this equals to the
     * contents of rhs
     */
    bool String::equals(const String &rhs) const {
        //printf("this.length=%ld,rhs.data='%s'\n",length,rhs.data);
        if ((rhs.length)!=(length)){
            //printf("LENGTH WRONG during equals method string \n");
            return false;
        }
        if((strncmp(rhs.data,data,length))){
          //printf("comparison wrong during equals method string\n");
            return false;
        }
            return true;
    }

    /**
     * @brief Returns true iff the contents of this equals to rhs
     */
    bool String::equals(const char *rhs) const{
        if(strlen(rhs)!=(length)) {
         //printf("LENGTH WRONG during equals method array\n");
            return false;
        }
        if(strncmp(rhs,data,length)) {
            return true;
        }
         //printf("comparison wrong during equals method array\n");
        return false;
    }

    /**
     * @brief Splits this to several sub-strings according to delimiters.
     * Allocates memory for output that the user must delete (using delete[]).
     * @note Does not affect this.
     * @note If "output" is set to NULL, do not allocated memory, only
     * compute "size".
     */
    void String::split(const char *delimiters, String **output, size_t *size) const {
        // printf("string split function with delimiters '%s' \n",delimiters);
         if(NULL==data){
            //printf("split returning null in data\n");
            return;
         }
        char orig_str [length+1]={0};
        strncpy(orig_str,data,length);
        orig_str[length]='\0';
        int length_str=length ;
        //printf("split_1,orig_str='%s'\n",orig_str);
        int num_of_delimiters=strlen(delimiters);
        size_t num_of_strings=1;
        int begin_index=0, sub_string_index=0;
        //first we only count the number of sub strings to create
       for (int i=0 ; i < length_str ; i++) {
            for(int j=0 ; j < num_of_delimiters ; j++){
                if (orig_str[i]==delimiters[j]){
                    num_of_strings++;
                 }
            }
        }
        *size=num_of_strings;
         //printf("split_2,num_of_strings=%ld\n",num_of_strings);


       if(NULL == output){
        //printf("split returning null\n");
            return;
        }
        *output = new String[num_of_strings]; 
        //printf("split_3 output decleard\n");

        for (int i=0;i<length_str;i++) {
            for(int j=0;j<num_of_delimiters;j++){
                if (orig_str[i]==delimiters[j]){
                    orig_str[i]='\0';
                    (*output)[sub_string_index]=String(&(orig_str[begin_index]));//ends with "/0" that we included
                    //printf("output[%d]=%s\n",sub_string_index,(*output)[sub_string_index].data);
                    sub_string_index++;
                    begin_index=i+1;
                 }
            
            }
        }
        (*output)[sub_string_index]=String(&orig_str[begin_index]);//put last string in array
        //printf("output[%d]=%s\n",sub_string_index,(*output)[sub_string_index].data);
       //  printf("split_end output, sub string index=%d\n",sub_string_index);
        //delete[] orig_str;
        return;
    }

    /**
     * @brief Try to convert this to an integer. Returns 0 on error.
     */
    int String::to_integer() const{
        //printf("to integer function\n");
        String* sub_strings;
        size_t size=0;
        int res=0;
        split(".",&sub_strings,&size);
        if (size==SEGMENTS){
            for(size_t sub_string_index=0;sub_string_index<size;sub_string_index++){
               int curr_num= ((sub_strings[sub_string_index]).trim().to_integer());//returns int value of sub-segment
               if ((curr_num>BYTE_MAX_VAL)||(curr_num<BYTE_MIN_VAL)){
                delete[] sub_strings;
                return 0;
               }
               //printf("curr num is = %x res=%x\n",curr_num,res);
               res+=curr_num<<(MAX_SHIFT_VAL-(SIZE_OF_BYTE*sub_string_index));
               //printf("after shifting and adding res=%x\n",res);
           }
           delete[] sub_strings;
           return res;
        } 
        else {
         res=atoi(data);
         return res;
         }
    }

    /**
     * @brief Remove any leading or trailing white-spaces.
     * Does not change this.
     */
    String String::trim() const{

        //printf("trim function\n");
        if(!data){
            //rintf("data null trim\n");
            return NULL;
        }
        char orig_str[length+1];
        strncpy(orig_str,data,length);
         orig_str[length]='\0';
        int i=0, j=length-1;//should not be zero
        while(orig_str[i]==' '){
            i++;
        }
        //printf("data stater deleted, first ='%c'\n",orig_str[i]);
        while((j>i)&&(orig_str[j]==' ')){
            j--;
        }
        //printf("data ending deleted, last char ='%c'\n",orig_str[j]);
        if (i>j){
            //printf("i>j\n");
            return NULL;
        }
        else{
            char string_to_copy[j-i+2];
            for(int k=0;k<(j-i+1);k++){
                string_to_copy[k]=orig_str[i+k];
            }
            string_to_copy[j-i+1]='\0';
          //  printf("string to copy in trim func is '%s'\n", string_to_copy);
            return String(string_to_copy);
        }


    }

    void String::print(){
        printf("'%s'\n",this->data);
    }




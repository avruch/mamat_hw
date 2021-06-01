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
            delete[] data;
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
        if ((rhs.length)!=(length)){
            return false;
        }
        if((strncmp(rhs.data,data,length))){
            return false;
        }
            return true;
    }

    /**
     * @brief Returns true iff the contents of this equals to rhs
     */
    bool String::equals(const char *rhs) const{
        if(strlen(rhs)!=(length)) {
            return false;
        }
        if(strncmp(rhs,data,length)) {
            return true;
        }
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
         if(NULL==data){
            return;
         }
        char orig_str [length+1]={0};
        strncpy(orig_str,data,length);
        orig_str[length]='\0';
        int length_str=length ;
        int num_of_delimiters=strlen(delimiters);
        size_t num_of_strings=1;
        int begin_index=0, sub_string_index=0;
       for (int i=0 ; i < length_str ; i++) {
            for(int j=0 ; j < num_of_delimiters ; j++){
                if (orig_str[i]==delimiters[j]){
                    num_of_strings++;
                 }
            }
        }
        *size=num_of_strings;

       if(NULL == output){
            return;
        }
        *output = new String[num_of_strings]; 

        for (int i=0;i<length_str;i++) {
            for(int j=0;j<num_of_delimiters;j++){
                if (orig_str[i]==delimiters[j]){
                    orig_str[i]='\0';
                    (*output)[sub_string_index]=String(&(orig_str[begin_index]));//ends with "/0" that we included
                    sub_string_index++;
                    begin_index=i+1;
                 }
            
            }
        }
        (*output)[sub_string_index]=String(&orig_str[begin_index]);//put last string in array
        return;
    }

    /**
     * @brief Try to convert this to an integer. Returns 0 on error.
     */
    int String::to_integer() const{
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
               res+=curr_num<<(MAX_SHIFT_VAL-(SIZE_OF_BYTE*sub_string_index));
           }
           delete[] sub_strings;
           return res;
        } 
        else {
         res=atoi(data);
         delete[] sub_strings;
         return res;
         }
    }

    /**
     * @brief Remove any leading or trailing white-spaces.
     * Does not change this.
     */
    String String::trim() const{

        if(!data){
            return NULL;
        }
        char orig_str[length+1];
        strncpy(orig_str,data,length);
         orig_str[length]='\0';
        int i=0, j=length-1;//should not be zero
        while(orig_str[i]==' '){
            i++;
        }
        while((j>i)&&(orig_str[j]==' ')){
            j--;
        }
        if (i>j){
            return NULL;
        }
        else{
            char string_to_copy[j-i+2];
            for(int k=0;k<(j-i+1);k++){
                string_to_copy[k]=orig_str[i+k];
            }
            string_to_copy[j-i+1]='\0';
            return String(string_to_copy);
        }


    }
    bool String::is_empty(){
        return (!(this->length));
    }




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
        data=new char[length+1];
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
        printf("this->length=%d,rhs.data=%s",this->length,rhs.data);
        if ((rhs.length)!=(this->length)){
            printf("LENGTH WRONG\n");
            return false;
        }
        if((strncmp(rhs.data,this->data,this->length))){
            return false;
        }
        
            return true;
        
    }

    /**
     * @brief Returns true iff the contents of this equals to rhs
     */
    bool String::equals(const char *rhs) const{
        if(strlen(rhs)!=(this->length)) {
            return false;
        }
        if(strncmp(rhs,this->data,this->length)) {
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
         printf("string split function with delimiters %s \n",delimiters);
         if(NULL==this->data){
            return;
         }
        char orig_str [this->length+1];
        strncpy(orig_str,this->data,length);
        orig_str[length]='\0';
        unsigned int length_str=this->length , length_delimiters=strlen(delimiters);
        unsigned int num_of_strings=1;
        unsigned int begin_index=0, sub_string_index=0;
        //first we only count the number of sub strings to create
       for (int i=0 ; i < length_str ; i++) {
            for(int j=0 ; j < length_delimiters ; j++){
                if (orig_str[i]==delimiters[j]){
                    num_of_strings++;
                 }
            }
        }
        *size=num_of_strings;
       if(NULL == output){
            return;
        }
        (*output) = new String[num_of_strings]; 
        for (unsigned int i=0;i<length_str;i++) {
            for(unsigned int j=0;j<length_delimiters;j++){
                if (orig_str[i]==delimiters[j]){
                    orig_str[i]='\0';
                    (*output)[sub_string_index]=String((const char*) orig_str[begin_index]);
                    printf("output[sub_string_index]=%s\n",&output[sub_string_index]);
                    sub_string_index++;
                    begin_index=i+1;
                 }
            
            }
        }
        (*output)[sub_string_index]=String((const char*) orig_str[begin_index]);
        delete[] orig_str;
        return;
    }

    /**
     * @brief Try to convert this to an integer. Returns 0 on error.
     */
    int String::to_integer() const{
        String* sub_strings;
        size_t size=0;
        int res=0;
        String *curr_string;
        split(".",&sub_strings,&size);
        if (size==SEGMENTS){
            for( int sub_string_index=0;sub_string_index<size;sub_string_index++){
                strcpy(curr_string->data,((sub_strings[sub_string_index]).data));
               int curr_num= atoi((char*)(curr_string));
               if ((curr_num>BYTE_MAX_VAL)||(curr_num<BYTE_MIN_VAL)){
                delete[] sub_strings;
                return 0;
               }
               res+=curr_num<<(MAX_SHIFT_VAL-(SIZE_OF_BYTE*sub_string_index));
           }
           delete[] sub_strings;
           return res;
        } 
         strcpy((char*)curr_string, this->data);
         res=atoi((char*)curr_string);
         delete[] curr_string;
         return res;
    }

    /**
     * @brief Remove any leading or trailing white-spaces.
     * Does not change this.
     */
    String String::trim() const{
        if(this->data){
            return NULL;
        }
        char orig_str[this->length+1];
        strncpy(orig_str,this->data,length);
         orig_str[length]='\0';
        int i=0, j=this->length-1;
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
            char string_to_copy[j-i+1];
            for(int k=0;k<(j-i+1);k++){
                string_to_copy[k]=orig_str[i+k];
            }
            string_to_copy[j-i]='\0';
            printf("string to copy in trim func is %s", string_to_copy);
            String str(string_to_copy);
            return str;
        }


    }




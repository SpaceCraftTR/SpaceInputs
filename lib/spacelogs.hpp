/*

SpaceLogs

SpaceLogs is an easy to use logging library for C++ developers. 

If you don't want to get your hands dirty with date formats, SpaceLogs is here to save your back!

Copyright (c) 2021 - SpaceCraft

Distributed under terms of the MIT licence.
*/
#pragma once
#include <string>
#include <fstream>
#include <ctime>
#include <iostream>

/*Date format definitions.*/
#define MMDDYY 0
#define DDMMYY 1
#define YYMMDD 2
#define MMDDYYYY 3
#define DDMMYYYY 4
#define YYYYMMDD 5

class SpaceLogs{
    std::string log;
    struct tm *time__;
    char cur_time[80];
    char* date_format_array[6] = {
        "%D %T","%d/%m/%y %T","%y/%m/%d %T",
        "%m/%d/%Y %T","%d/%m/%Y %T","%Y/%m/%d %T"
    };
    char* selected_date_format = nullptr;
    public:
        SpaceLogs(){
            update_time(date_format_array[MMDDYYYY]);
        }

        SpaceLogs(std::string log, unsigned int date_format){
        
        try{
            if(date_format < 6){
                selected_date_format = date_format_array[date_format];
                update_time(selected_date_format);
            }
            else{
                throw std::string("Invalid time format! You can use a custom date format instead, or you can just rely on SpaceLogs defaults.");
            }
            write_log(log); 
           }
        catch(std::string& ex){
            std::cout<<"[SpaceLogs] "<<ex<<std::endl;
            exit(-1);
        }
    }
        SpaceLogs(std::string log, char* custom_date_format){
            update_time(custom_date_format);
            selected_date_format = custom_date_format;
            write_log(log); 
        }
        SpaceLogs(std::string log){
            update_time(date_format_array[DDMMYYYY]);
            write_log(log);    
        }
        inline void write_log(std::string &log){
            this->log = log;
        }
        inline std::string current_time(){
            return this->cur_time;
        }
        inline std::string get_selected_date_format(){
            return this->selected_date_format;
        }
        std::string get_latest_log(){return this->log;}
        inline friend std::ostream& operator<<(std::ostream& output, SpaceLogs &obj){return output<<"["<<obj.cur_time<<"] "<<obj.get_latest_log()<<std::endl;} //Returns the latest log.
        inline friend void operator>>(std::string input, SpaceLogs &log){
                int pos = input.npos;       
                if((pos = input.find("\n")) != input.npos){
                    std::string temp_str = "["+log.current_time()+"] ";
                    input.insert(pos+1,temp_str);
                }     
                log.write_log(input);
            }
    private:
    inline void update_time(char* date_format){
        const time_t temp_time = time(nullptr);
        time__ = localtime(&temp_time);
        strftime(cur_time,sizeof(cur_time),date_format,time__);
    }
    inline void update_time(std::string date_format){
        const time_t temp_time = time(nullptr);
        time__ = localtime(&temp_time);
        strftime(cur_time,sizeof(cur_time),date_format.c_str(),time__);
    }

};
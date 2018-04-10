// time2code.c
// Assignment 1, COMP1511 18s1: Time To Code.
//
// This program by YOUR-NAME-HERE (z5555555) on INSERT-DATE-HERE
//
// Version 1.0.2: Add version numbers and header comment.
// Version 1.0.1: Fix day/time variable mix-up in main function.
// Version 1.0.0: Assignment released.

#include <stdio.h>
#include <assert.h>

// You must use these #defines - DO NOT CHANGE THEM

#define TOWN_ADELAIDE       0
#define TOWN_BRISBANE       1
#define TOWN_BROKEN_HILL    2
#define TOWN_CANBERRA       3
#define TOWN_DARWIN         4
#define TOWN_EUCLA          5
#define TOWN_HOBART         6
#define TOWN_LORD_HOWE_IS   7
#define TOWN_MELBOURNE      8
#define TOWN_PERTH          9
#define TOWN_SYDNEY         10

// New Zealand

#define TOWN_AUCKLAND       11
#define TOWN_CHRISTCHURCH   12
#define TOWN_WELLINGTON     13

// Australia

#define TIMEZONE_AWST_OFFSET  800 // Australian Western Standard Time

#define TIMEZONE_ACWST_OFFSET 845 // Australian Central Western Standard Time

#define TIMEZONE_ACST_OFFSET  930 // Australian Central Standard Time
#define TIMEZONE_ACDT_OFFSET 1030 // Australian Central Daylight Time

#define TIMEZONE_AEST_OFFSET 1000 // Australian Eastern Standard Time
#define TIMEZONE_AEDT_OFFSET 1100 // Australian Eastern Daylight Time

#define TIMEZONE_LHST_OFFSET 1030 // Lord Howe Standard Time
#define TIMEZONE_LHDT_OFFSET 1100 // Lord Howe Daylight Time

// New Zealand
#define TIMEZONE_NZST_OFFSET 1200 // NZ Standard Time
#define TIMEZONE_NZDT_OFFSET 1300 // NZ Daylight Time

// returned by get_local_time
#define INVALID_INPUT (-1)


// ADD YOUR #defines (if any) here

int get_local_time(int town, int utc_month, int utc_day, int utc_time);
void run_unit_tests(void);

// ADD PROTOTYPES FOR YOUR FUNCTIONS HERE
int invalid_function_return(int town, int utc_month, int utc_day, int utc_time);
int calc_offset(int town, int utc_month, int utc_day, int utc_time);
int refine_time(int raw_time);
// DO NOT CHANGE THIS FUNCTION

// This main function won't be marked as part of the assignment
// It tests the functions you have to write.
// Do not change this main function.  If it does not work with
// your functions you have misunderstood the assignment.

int main(void) {
    int call_get_local_time = 0;

    printf("Enter 0 to call run_unit_tests()\n");
    printf("Enter 1 to call get_local_time()\n");
    printf("Call which function: ");
    scanf("%d", &call_get_local_time);

    if (!call_get_local_time) {
        printf("calling run_unit_tests()\n");
        run_unit_tests();
        printf("unit tests done\n");
        return 0;
    }

    int town = 0;
    int month = 0;
    int day = 0;
    int time = 0;
    
    printf("Enter %d for Adelaide\n", TOWN_ADELAIDE);
    printf("Enter %d for Brisbane\n", TOWN_BRISBANE);
    printf("Enter %d for Broken_hill\n", TOWN_BROKEN_HILL);
    printf("Enter %d for Canberra\n", TOWN_CANBERRA);
    printf("Enter %d for Darwin\n", TOWN_DARWIN);
    printf("Enter %d for Eucla\n", TOWN_EUCLA);
    printf("Enter %d for Hobart\n", TOWN_HOBART);
    printf("Enter %d for Lord Howe Island\n", TOWN_LORD_HOWE_IS);
    printf("Enter %d for Melbourne\n", TOWN_MELBOURNE);
    printf("Enter %d for Perth\n", TOWN_PERTH);
    printf("Enter %d for Sydney\n", TOWN_SYDNEY);
    printf("Enter %d for Auckland\n", TOWN_AUCKLAND);
    printf("Enter %d for Christchurch\n", TOWN_CHRISTCHURCH);
    printf("Enter %d for Wellington\n", TOWN_WELLINGTON);

    printf("Which town: ");
    scanf("%d", &town);

    printf("Enter UTC month as integer 1..12: ");
    scanf("%d", &month);

    printf("Enter UTC day as integer 1..31: ");
    scanf("%d", &day);

    printf("Enter UTC time as hour * 100 + minutes\n");
    printf("Enter UTC time as integer [0..2359]: ");
    scanf("%d", &time);

    int local_time = get_local_time(town, month, day, time);

    if (local_time == INVALID_INPUT) {
        printf("invalid input - local time could not be calculated\n");
    } else {
        printf("local_time is %d\n", local_time);
    }
    return 0;
}



// Given an Australian town and a 2018 UTC time
// return the local time in the Australian town
//
// time is returned as hours*100 + minutes
// INVALID_INPUT is return for invalid inputs
//
// utc_month should be 1..12
// utc_day should be 1..31
// utc_time should be 0..2359
// utc_time is hours*100 + minutes
//
// note UTC year is assumed to be 2018
// note UTC seconds is assumed to be zero
//

int get_local_time(int town, int utc_month, int utc_day, int utc_time) {
            // code here buddy boy you can do it   
    int raw_time = utc_time; 
    int offset = 0 ;
    int refined_time; 
    offset = calc_offset(town, utc_month, utc_day, utc_time); // the offset calculator
    if(invalid_function_return(town, utc_month, utc_day, utc_time) == INVALID_INPUT){
        raw_time = INVALID_INPUT ;
    }
    if(invalid_function_return(town, utc_month, utc_day, utc_time) == 1){ 
        raw_time += offset ;
    }    
    refined_time =refine_time(raw_time);
    return refined_time;
}


// ADD YOUR FUNCTIONS HERE
// check for invalid inputs
////////////////////////////
// the invalid input function

int invalid_function_return(int town, int utc_month, int utc_day, int utc_time){
    
    if(town != TOWN_ADELAIDE && town != TOWN_BRISBANE && town != TOWN_BROKEN_HILL && town != TOWN_CANBERRA && town != TOWN_DARWIN && town != TOWN_EUCLA && town != TOWN_HOBART && town != TOWN_LORD_HOWE_IS && town != TOWN_MELBOURNE && town != TOWN_PERTH && town != TOWN_SYDNEY && town != TOWN_AUCKLAND && town != TOWN_CHRISTCHURCH && town != TOWN_WELLINGTON){
        return INVALID_INPUT ;
    }
    if(utc_time < 0 ||utc_time > 2359){ // time check
       return  INVALID_INPUT ;
    } 
    if(utc_time % 100 > 59){
        return INVALID_INPUT ;
    }
    if(utc_month == 9 || utc_month == 4 || utc_month == 6 || utc_month == 11){ // sep april jun nov day check
        if(utc_day < 1 || utc_day > 30){
        return INVALID_INPUT;
        }
    }
    if(utc_month == 1 || utc_month == 3 || utc_month == 5 || utc_month == 7 || utc_month == 8 || utc_month == 10 || utc_month == 12){ // jan mar may jul aug oct dec month check
        if(utc_day < 1 || utc_day > 31){
        return INVALID_INPUT;
        }
    }    
    if(utc_month == 2){ // february month check
        if(utc_day < 1 || utc_day > 28){
        return INVALID_INPUT;
        }
    }
    if(utc_month < 1 || utc_month > 12){  // month check
        return INVALID_INPUT ;        
    }  
    return 1 ;
}    

// calculate offset
/////////////////////////////

int calc_offset(int town, int utc_month, int utc_day, int utc_time){
int offset = 0 ;
    if(town == TOWN_BRISBANE){                     // Brisbane
        offset = TIMEZONE_AEST_OFFSET;
    }
    if(town == TOWN_DARWIN){                       // darwin
        offset = TIMEZONE_ACST_OFFSET;
    }   
    if(town == TOWN_EUCLA){                        // eucla
        if(utc_time %100 > 54){
            offset = TIMEZONE_ACWST_OFFSET + 40 ;
        } 
        else{                      
        offset = TIMEZONE_ACWST_OFFSET;
        }
    }
    if(town == TOWN_PERTH){                        // perth
        offset = TIMEZONE_AWST_OFFSET;
    }
    if(town == TOWN_AUCKLAND || town == TOWN_CHRISTCHURCH || town == TOWN_WELLINGTON){//Auckland, Christchurch, Wellington 
        // non daylight times  + 12  NZST   
        if(utc_month == 3 && utc_day == 31 && utc_time >= 1400){
            offset = TIMEZONE_NZST_OFFSET ; 
        } 
        if(utc_month >= 4 && utc_month < 10){   
            offset = TIMEZONE_NZST_OFFSET ;
        }
        if(utc_month == 10 && utc_day < 6){
            offset = TIMEZONE_NZST_OFFSET;
        }     
        if(utc_month == 10 && utc_day == 6 && utc_time < 1400){
            offset = TIMEZONE_NZST_OFFSET; 
        }
        //daylight times + 13 NZDT
        if(utc_month == 10 && utc_day == 6 && utc_time >= 1400){
            offset = TIMEZONE_NZDT_OFFSET; 
        } 
        if(utc_month == 10 && utc_day > 6 ){
            offset = TIMEZONE_NZDT_OFFSET; 
        } 
        if(utc_month > 10 ){
            offset = TIMEZONE_NZDT_OFFSET; 
        }  
        if(utc_month == 3 && utc_day == 31 && utc_time < 1400){
            offset = TIMEZONE_NZDT_OFFSET;          
        }
        if(utc_month == 3 && utc_day < 31 ){
            offset = TIMEZONE_NZDT_OFFSET; 
        }
        if(utc_month < 3 ){
            offset = TIMEZONE_NZDT_OFFSET; 
        }          
    }
    if(town == TOWN_SYDNEY || town == TOWN_CANBERRA || town == TOWN_HOBART || town == TOWN_MELBOURNE){//Sydney, Hobart, canbera, melbourne 
        // non daylight times  + 10 AEST 
        if(utc_month == 3 && utc_day == 31 && utc_time >= 1600){
            offset = TIMEZONE_AEST_OFFSET  ; 
        } 
        if(utc_month >= 4 && utc_month < 10){   
            offset = TIMEZONE_AEST_OFFSET ;
        }
        if(utc_month == 10 && utc_day < 6){
            offset = TIMEZONE_AEST_OFFSET;
        }     
        if(utc_month == 10 && utc_day == 6 && utc_time < 1600){
            offset = TIMEZONE_AEST_OFFSET; 
        }
        //daylight times + 11 AEDT
        if(utc_month == 10 && utc_day == 6 && utc_time >= 1600){
            offset = TIMEZONE_AEDT_OFFSET; 
        } 
        if(utc_month == 10 && utc_day > 6 ){
            offset = TIMEZONE_AEDT_OFFSET; 
        } 
        if(utc_month > 10 ){
            offset = TIMEZONE_AEDT_OFFSET; 
        }  
        if(utc_month == 3 && utc_day == 31 && utc_time < 1600){
            offset = TIMEZONE_AEDT_OFFSET;          
        }
        if(utc_month == 3 && utc_day < 31 ){
            offset = TIMEZONE_AEDT_OFFSET; 
        }
        if(utc_month < 3 ){
            offset = TIMEZONE_AEDT_OFFSET; 
        }          
    }
    if(town == TOWN_ADELAIDE || town == TOWN_BROKEN_HILL){//ADELAIDE , Broken hill
        // non daylight times  + 9:30  ACST   
        if(utc_month == 3 && utc_day == 31 && utc_time >= 1630){
            offset = TIMEZONE_ACST_OFFSET ; 
        } 
        if(utc_month >= 4 && utc_month < 10){   
            offset = TIMEZONE_ACST_OFFSET ;
        }
        if(utc_month == 10 && utc_day < 6){
            offset = TIMEZONE_ACST_OFFSET;
        }     
        if(utc_month == 10 && utc_day == 6 && utc_time < 1630){
            offset = TIMEZONE_ACST_OFFSET; 
        }
        //daylight times + 10:30 ACDT
        if(utc_month == 10 && utc_day == 6 && utc_time >= 1630){
            offset = TIMEZONE_ACDT_OFFSET; 
        } 
        if(utc_month == 10 && utc_day > 6 ){
            offset = TIMEZONE_ACDT_OFFSET; 
        } 
        if(utc_month > 10 ){
            offset = TIMEZONE_ACDT_OFFSET; 
        }  
        if(utc_month == 3 && utc_day == 31 && utc_time < 1630){
            offset = TIMEZONE_ACDT_OFFSET;          
        }
        if(utc_month == 3 && utc_day < 31 ){
            offset = TIMEZONE_ACDT_OFFSET; 
        }
        if(utc_month < 3 ){
            offset = TIMEZONE_ACDT_OFFSET; 
        }          
    }
    if(town == TOWN_LORD_HOWE_IS){//Lord Howe 
        // non daylight times  + 10:30  LHST   
        if(utc_month == 3 && utc_day == 31 && utc_time >= 1530){
            offset = TIMEZONE_LHST_OFFSET ; 
        } 
        if(utc_month >= 4 && utc_month < 10){   
            offset = TIMEZONE_LHST_OFFSET ;
        }
        if(utc_month == 10 && utc_day < 6){
            offset = TIMEZONE_LHST_OFFSET;
        }     
        if(utc_month == 10 && utc_day == 6 && utc_time < 1530){
            offset = TIMEZONE_LHST_OFFSET; 
        }
        //daylight times + 11:00 LHDT
        if(utc_month == 10 && utc_day == 6 && utc_time >= 1530){
            offset = TIMEZONE_LHDT_OFFSET; 
        } 
        if(utc_month == 10 && utc_day > 6 ){
            offset = TIMEZONE_LHDT_OFFSET; 
        } 
        if(utc_month > 10 ){
            offset = TIMEZONE_LHDT_OFFSET; 
        }  
        if(utc_month == 3 && utc_day == 31 && utc_time < 1530){
            offset = TIMEZONE_LHDT_OFFSET;          
        }
        if(utc_month == 3 && utc_day < 31 ){
            offset = TIMEZONE_LHDT_OFFSET; 
        }
        if(utc_month < 3 ){
            offset = TIMEZONE_LHDT_OFFSET; 
        }          
    }
    return offset ;
}

    
     
//refine time
////////////////////
int refine_time(int raw_time){
    
    int minute_refined ; 
    int refined_time = 0;
    
    minute_refined = raw_time ;
    if(raw_time %100 > 59){
        minute_refined = raw_time + 40 ;
    }        
    if(minute_refined >= 2400){
        refined_time = minute_refined - 2400 ;   
    }    
    else if (minute_refined < 2400){
        refined_time = minute_refined;
    }    
   
    return refined_time ;
}

// ADD A COMMENT HERE EXPLAINING YOUR OVERALL TESTING STRATEGY

// run unit tests for get_local_time

void run_unit_tests(void) {
    //TEST THE DAYLIGHT SWITCHOVER TIMES ALL CITIES ARE CORRECT AND INTERVAL TIMES INBETWEEN WORK
    
    // +10 AEST --> +11 AEDT
    //test the imediate points of daylight savings change in sydney
    assert(get_local_time(TOWN_SYDNEY, 3, 31, 1600) == 200);
    assert(get_local_time(TOWN_SYDNEY, 10, 6, 1600) == 300);
    //test the time works in the middle of each individual offset in sydney
    assert(get_local_time(TOWN_SYDNEY, 6, 15, 1000) == 2000);
    assert(get_local_time(TOWN_SYDNEY, 12, 6, 1000) == 2100);
    //test the imediate points of daylight savings change in hobart
    assert(get_local_time(TOWN_HOBART, 3, 31, 1600) == 200);
    assert(get_local_time(TOWN_HOBART, 10, 6, 1600) == 300);
    //test the time works in the middle of each individual offset in hobart
    assert(get_local_time(TOWN_HOBART, 6, 15, 1000) == 2000);
    assert(get_local_time(TOWN_HOBART, 12, 6, 1000) == 2100);
    //test the imediate points of daylight savings change in canberra
    assert(get_local_time(TOWN_CANBERRA, 3, 31, 1600) == 200);
    assert(get_local_time(TOWN_CANBERRA, 10, 6, 1600) == 300);
    //test the time works in the middle of each individual offset in canberra
    assert(get_local_time(TOWN_CANBERRA, 6, 15, 1000) == 2000);
    assert(get_local_time(TOWN_CANBERRA, 12, 6, 1000) == 2100);
    //test the imediate points of daylight savings change in melbourne
    assert(get_local_time(TOWN_MELBOURNE, 3, 31, 1600) == 200);
    assert(get_local_time(TOWN_MELBOURNE, 10, 6, 1600) == 300);
    //test the time works in the middle of each individual offset in melbourne
    assert(get_local_time(TOWN_MELBOURNE, 6, 15, 1000) == 2000);
    assert(get_local_time(TOWN_MELBOURNE, 12, 6, 1000) == 2100);
    // +12  NZST -- >  +13 NZDT
    //test the imediate points of daylight savings change in christchurch
    assert(get_local_time(TOWN_CHRISTCHURCH, 3, 31, 1400) == 200);
    assert(get_local_time(TOWN_CHRISTCHURCH, 10, 6, 1400) == 300);
    //test the time works in the middle of each individual offset in christchurch
    assert(get_local_time(TOWN_CHRISTCHURCH, 6, 15, 1000) == 2200);
    assert(get_local_time(TOWN_CHRISTCHURCH, 12, 6, 1000) == 2300);
    //test the imediate points of daylight savings change in auckland
    assert(get_local_time(TOWN_AUCKLAND, 3, 31, 1400) == 200);
    assert(get_local_time(TOWN_AUCKLAND, 10, 6, 1400) == 300);
    //test the time works in the middle of each individual offset in auckland
    assert(get_local_time(TOWN_AUCKLAND, 6, 15, 1000) == 2200);
    assert(get_local_time(TOWN_AUCKLAND, 12, 6, 1000) == 2300);
    //test the imediate points of daylight savings change in wellington
    assert(get_local_time(TOWN_WELLINGTON, 3, 31, 1400) == 200);
    assert(get_local_time(TOWN_WELLINGTON, 10, 6, 1400) == 300);
    //test the time works in the middle of each individual offset in wellington
    assert(get_local_time(TOWN_WELLINGTON, 6, 15, 1000) == 2200);
    assert(get_local_time(TOWN_WELLINGTON, 12, 6, 1000) == 2300);
    // +9:30 ACST --> +10:30 ACDT
    //test the imediate points of daylight savings change in adelaide
    assert(get_local_time(TOWN_ADELAIDE, 3, 31, 1630) == 200);
    assert(get_local_time(TOWN_ADELAIDE, 10, 6, 1630) == 300);
    //test the time works in the middle of each individual offset in adelaide
    assert(get_local_time(TOWN_ADELAIDE, 6, 15, 1000) == 1930);
    assert(get_local_time(TOWN_ADELAIDE, 12, 6, 1000) == 2030);
    //test the imediate points of daylight savings change in broken hill
    assert(get_local_time(TOWN_BROKEN_HILL, 3, 31, 1630) == 200);
    assert(get_local_time(TOWN_BROKEN_HILL, 10, 6, 1630) == 300);
    //test the time works in the middle of each individual offset in broken hill
    assert(get_local_time(TOWN_BROKEN_HILL, 6, 15, 1000) == 1930);
    assert(get_local_time(TOWN_BROKEN_HILL, 12, 6, 1000) == 2030);
    //+ 10:30  LHST  --> + 11:00 LHDT
    //test the imediate points of daylight savings change in lorde howe island
    assert(get_local_time(TOWN_LORD_HOWE_IS, 3, 31, 1530) == 200);
    assert(get_local_time(TOWN_LORD_HOWE_IS, 10, 6, 1530) == 230);
    //test the time works in the middle of each individual offset in lorde howe island
    assert(get_local_time(TOWN_LORD_HOWE_IS, 6, 15, 1000) == 2030);
    assert(get_local_time(TOWN_LORD_HOWE_IS, 12, 6, 1000) == 2100);
    
    // test non daylight savings cities return correct output
    
    //Brisbane + 10
    assert(get_local_time(TOWN_BRISBANE, 6, 15, 1000) == 2000);
    //darwin + 9:30
    assert(get_local_time(TOWN_DARWIN, 6, 15, 1000) == 1930);
    //Perth + 8:00
    assert(get_local_time(TOWN_PERTH, 6, 15, 1000) == 1800);
    //Eucla + 8:45 *special case 1 : minutes < 55 (this affects the final calulation
    assert(get_local_time(TOWN_EUCLA, 6, 15, 1000) == 1845);
    //Eucla + 8:45 *case 2 : minutes > 54
    assert(get_local_time(TOWN_EUCLA, 6, 15, 1055) == 1940);
    
    // Check incorrect month input *in invalid_function_return* (correct tested above)
    
    // possitive input
    assert(invalid_function_return(TOWN_BRISBANE, 13, 15, 1000) == INVALID_INPUT); 
    // negative input
    assert(invalid_function_return(TOWN_BRISBANE, -1, 15, 1000) == INVALID_INPUT);
  
    // Check incorrect days (correct tested above)
    
    // possitive input
    assert(invalid_function_return(TOWN_BRISBANE, 1, 50, 1000) == INVALID_INPUT); 
    // negative input
    assert(invalid_function_return(TOWN_BRISBANE, 1, -15, 1000) == INVALID_INPUT);
  
    // Check incorrect time
  
    // possitive input
    assert(invalid_function_return(TOWN_BRISBANE, 1, 5, 10000) == INVALID_INPUT); 
    // negative input
    assert(invalid_function_return(TOWN_BRISBANE, 1, 15, -1000) == INVALID_INPUT);
  
    // Check incorrect town : 20 != town
    assert(invalid_function_return(20 , 1, 15, 1000) == INVALID_INPUT);
    
    // check incorrect output in MAIN FUNCTION
    assert(get_local_time(TOWN_LORD_HOWE_IS, 12, 50, 1000) == INVALID_INPUT);    
}

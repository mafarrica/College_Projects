
/* -------------------------------------------------

Name: Mafalda Fernandes
IST ID: 102702
Email: mafalda.m.fernandes@tecnico.ulisboa.pt
Class: IAED 2021/2022

---------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAXFLIGHTS 30000
#define MAXAIRPORTS 40

#define MAXIDLEN 4
#define MAXCOUNTRYCHAR 31
#define MAXCITYCHAR 51
#define MAXFLIGHTDURATION 12
#define MINFLIGHTPASSANGERS 10
#define MAXFLIGHTPASSANGERS 100
#define MAXFLIGHTCODECHAR 2
#define MAXFLIGHTCODENUM 4


/* airport structure */

struct Airport {
    char id[MAXIDLEN];
    char country[MAXCOUNTRYCHAR];
    char city[MAXCITYCHAR];
    int numflights;
};

/* flight structure */

struct Flight {
    char code[MAXFLIGHTCODECHAR + MAXFLIGHTCODENUM + 1];
    char airportDeparture[MAXIDLEN];
    char airportArrival[MAXIDLEN];
    int date[3];
    int time[2];
    int duration[2];
    int passangers;
    int arrivalDate[3];
    int arrivalTime[2];
};


/* global variables and arrays */

struct Airport airportsList[MAXAIRPORTS];

struct Flight flightsList[MAXFLIGHTS];

struct Flight departFlights[MAXFLIGHTS];

struct Flight arrivalFlights[MAXFLIGHTS];

int currentDate[3] = {1, 1, 2022};

int totalAirports = 0;

int totalFlights = 0;

int totalDepartFlights = 0;

int totalArrivalFlights = 0;




/*
Name: checkAirportID
Entry: airport ID
Return: 1 if the ID is valid
        0 if the ID is invalid
Description: checks if the given ID has the required characteristics, 
            printing a warning if it doesnt
*/

int checkAirportID(char id[]){
    int letter;
    int len = strlen(id);
    for(letter = 0; letter < MAXIDLEN - 1; letter++){
        /* checking ID length and if the letters are capital letters*/
        if(len != MAXIDLEN - 1 || (id[letter] < 'A') || (id[letter] > 'Z')){
            printf("invalid airport ID\n");
            return 0;
        }
    }
    return 1;
}


/*
Name: checkNumAirports
Entry: airport ID
Return: 1 if the airport doesnt exist yet and if there too many airports
        0 if the airport already exists or if there too many airports
Description: checks if the number of airports has reached its limit and if
            the given airport already exists, printing a warning if it does
*/
int checkNumAirports(char id[]){
    int airprtIndex;

    if(totalAirports == MAXAIRPORTS){
        printf("too many airports\n");
        return 0;
    }

    for(airprtIndex = 0; airprtIndex < totalAirports; airprtIndex++){
        if(strcmp(airportsList[airprtIndex].id, id) == 0){
            printf("duplicate airport\n");
            return 0;
        }
    }
    return 1;

}


/*
Name: putAirport
Entry: airport ID, airport country, airport city, the index of where the 
    airport should go on the list
Return: void
Description: inserts the airport in a given place of the list of airports
*/
void putAirport(char id[], char country[], char city[], int place){
    strcpy(airportsList[place].id, id);
    strcpy(airportsList[place].country, country);
    strcpy(airportsList[place].city, city);
    airportsList[place].numflights = 0;
}


/*
Name: addAirport
Entry: airport ID, airport country, airport city
Return: void
Description: analyses where the airport should go, using alphabetical order,
            right shifts the elements of the list to open space for the new
            airport and calls putAirport to insert it
*/
void addAirport(char id[], char country[], char city[]){
    int airprtIndex = 0, auxIndex, aux = 0;

    if(totalAirports == 0)
        putAirport(id, country, city, airprtIndex);

    else{
    for(airprtIndex = 0; airprtIndex < totalAirports; airprtIndex++){
        if(strcmp(airportsList[airprtIndex].id, id) > 0){
            for(auxIndex = totalAirports - 1; auxIndex >= airprtIndex; 
            auxIndex--){
                airportsList[auxIndex + 1] = airportsList[auxIndex];
            }
            putAirport(id, country, city, airprtIndex);
            aux = 1;
            break;
        }
        if(strcmp(airportsList[airprtIndex].id, id) < 0){
            aux = 0;
            continue;
        }
    }
    if(aux == 0)
        putAirport(id, country, city, totalAirports);
    }
}

/*
Name: Acomand
Entry: none
Return: void
Description: main function of the "a" comand, reads the inputs, checks the
            information, adds the airport to the list and prints out the
            wanted result
*/
void Acomand(){
    char id[MAXIDLEN];
    char country[MAXCOUNTRYCHAR];
    char city[MAXCITYCHAR];
    getchar();
    scanf("%s", id);
    scanf("%s", country);
    getchar();
    scanf("%[^\n]%*c", city);

    if(checkAirportID(id) && checkNumAirports(id)){
        addAirport(id, country, city);
        totalAirports++;
        printf("airport %s\n", id);
    }

} 





/*
Name: checkDate
Entry: day, month, year
Return: 1 if the date is valid
        0 if the date is invalid
Description: checks if the given date doesnt correspond to the past or to
            more than one year in the future, printing a warning if it does
*/
int checkDate(int day, int month, int year){

    if(
        /* same year, same month, past day */
        (year == currentDate[2] && 
        month == currentDate[1] && 
        day < currentDate[0]) ||

        /* same year, past month */
        (year == currentDate[2] && 
        month < currentDate[1]) ||
        
        /* past year */
        (year < currentDate[2]) ||

        /* more than one year in the future */
        ((year > currentDate[2] + 1)) ||
        (year == currentDate[2] + 1 &&
        ((month == currentDate[1] &&
        day > currentDate[0]) || 
        month > currentDate[1])))
        {
            printf("invalid date\n");
            return 0;
    }
    else
        return 1;
}

/*
Name: Tcomand
Entry: none
Return: void
Description: main function of the "t" comand, read the input, checks the date,
            saves it as the current date and prints it out
*/
void Tcomand(){
    int day, month, year;
    int auxlist[3];

    getchar();
    scanf("%d-%d-%d", &day, &month, &year);

    auxlist[0] = day;
    auxlist[1] = month;
    auxlist[2] = year;
    
    if(checkDate(day, month, year)){
        currentDate[0] = auxlist[0];
        currentDate[1] = auxlist[1];
        currentDate[2] = auxlist[2];
        printf("%02d-%02d-%02d\n", day, month, year);
    }
    
}





/*
Name: printAirport
Entry: index in the list of airports
Return: void
Description: prints out the information of an airport
*/
void printAirport(int index){
    printf("%s ", airportsList[index].id);
    printf("%s ", airportsList[index].city);
    printf("%s ", airportsList[index].country);
    printf("%d", airportsList[index].numflights);
    printf("\n");
}

/*
Name: listAllAirports
Entry: none
Return: void
Description: iterates through the list of airports and prints them out one
            by one
*/
void listAllAirports(){
    int index;
    for(index = 0; index < totalAirports; index++){
        printAirport(index);
    }
}

/*
Name: listGivenAirports
Entry: none
Return: void
Description: reads the input to check what airport to print out and prints it
            out if the airport exists, giving a warning if it doesnt
*/
void listGivenAirports(){
    int index,  verifier = 0;
    char airport[MAXIDLEN];
    do{
        scanf("%s", airport);
        for(index = 0; index < totalAirports; index++){
            if(strcmp(airport, airportsList[index].id) == 0){
                printAirport(index);
                verifier = 1;
                break;}
        }
        if(verifier == 0)
            printf("%s: no such airport ID\n", airport);

        verifier = 0;
    }
    while(getchar() != '\n');
}

/*
Name: Lcomand
Entry: none
Return: void
Description: main function of the "l" comand, checks if the comand is to
            print all airports or just the given ones and redirects to the
            specific functions
*/
void Lcomand(){
    if(getchar() == '\n'){
        listAllAirports();
    }
    else{
        listGivenAirports();
    }
}






/*
Name: checkFlightCode
Entry: flight code
Return: 1 if the code is valid
        0 if the code is invalid
Description: checks whether the given code consists of two capital letters
            followed by a number between 1 and 9999, printing a warning if it
            doesnt
*/
int checkFlightCode(char code[]){
    long unsigned int i;
    for(i = 0; i < MAXFLIGHTCODECHAR; i++){
        /* capital letters check*/
        if(code[i] < 'A' || code[i] > 'Z'){
            printf("invalid flight code\n");
            return 0;
        }
    }
    /* numbers check*/
    for(i = MAXFLIGHTCODENUM; i < strlen(code); i++){
        if(code[MAXFLIGHTCODECHAR] == '0'  ||
        code[i] < '0' || code[i] > '9'){
            printf("invalid flight code\n");
            return 0;
        }
    }
    return 1;
}


/*
Name: checkExistingFlight
Entry: flight code, departure day, month and year
Return: 1 if the flight doesnt exist already
        0 if the flight already exists
Description: checks if the given flight already exists, printing out a
            warning if it does
*/
int checkExistingFlight(char code[], int day, int month, int year){
    int index;
    for(index = 0; index < totalFlights; index++){
        if(strcmp(code, flightsList[index].code) == 0 &&
        flightsList[index].date[0] == day &&
        flightsList[index].date[1] == month &&
        flightsList[index].date[2] == year){
            printf("flight already exists\n");
            return 0;
            break;
        }
    }
    return 1;
}


/*
Name: checkAirportExistence
Entry: airport ID
Return: 1 if the airport exists
        0 if the aiport doesnt exist
Description: checks if the given airport exists, printing a warning if it
            doesnt
*/
int checkAirportExistence(char airportID[]){
    int index;
    for(index = 0; index < totalAirports; index++){
        if(strcmp(airportID, airportsList[index].id) == 0){
            return 1;
        }
    }
    
    printf("%s: no such airport ID\n", airportID);
    return 0;
    
}


/*
Name: checkFlightLimit
Entry: none
Return: 1 if the number of flights is valid
        0 if the number of flights is invalid
Description: checks if the number of flights is within the limit, printing a 
            warning if it doesnt
*/
int checkFlightLimit(){
    if(totalFlights == MAXFLIGHTS){
        printf("too many flights\n");
        return 0;
    }
    return 1;
}


/*
Name: checkFlightDuration
Entry: hours, minutes
Return: 1 if the duration of the flight is valid
        0 if the duration of the flight is invalid
Description: checks if the duration of the flight is within the limit,
            printing out a warning if it doesnt
*/
int checkFlightDuration(int hours, int minutes){

    if((hours < MAXFLIGHTDURATION && minutes <= 59) ||
    (hours == MAXFLIGHTDURATION && minutes == 0)){
        return 1;
    }
    printf("invalid duration\n");
    return 0;
}


/*
Name: checkFlightCapacity
Entry: capacity
Return: 1 if the capacity is valid
        0 if the capacity is invalid
Description: checks if the capacity of a flight is within the limits, 
            printing out a warning if it isnt
*/
int checkFlightCapacity(int capacity){
    if(capacity > MAXFLIGHTPASSANGERS || capacity < MINFLIGHTPASSANGERS){
        printf("invalid capacity\n");
        return 0;
    }
    return 1;
}


/*
Name: FlightMainCheck
Entry: flight code, departure day, month, year, hour and minute, departure
        airport, arrival airport, duration in hours, duration in minutes,
        flight capacity
Return: TRUE if all the information is valid
        FALSE if there is invalid information
Description: checks all the given information using the functions above
*/
int FlightMainCheck(char code[], int dayDeparture, int monthDeparture,
int yearDeparture, char apDeparture[], char apArrival[], int hourDuration,
int minuteDuration, int capacity){

    return
    checkFlightCode(code) &&
    checkExistingFlight(code, dayDeparture, monthDeparture, yearDeparture) &&
    checkAirportExistence(apDeparture) &&
    checkAirportExistence(apArrival) &&
    checkFlightLimit() &&
    checkDate(dayDeparture, monthDeparture, yearDeparture) &&
    checkFlightDuration(hourDuration, minuteDuration) &&
    checkFlightCapacity(capacity);
}


/*
Name: addFlight
Entry: flight code, departure airport, arrival airport,  departure day, month, 
        year, hour and minute, duration in hours, duration in minutes,
        flight capacity
Return: void
Description: adds the specific flight to the end of the flights list
*/
void addFlight(char code[], char departure[], char arrival[], int day, 
int month, int year, int hour, int minutes, int HDuration, 
int MDuration, int capacity){
    
    int index;
    if(totalFlights == 0)
        index = 0;
    else
        index = totalFlights;

    strcpy(flightsList[index].code, code);
    strcpy(flightsList[index].airportDeparture, departure);
    strcpy(flightsList[index].airportArrival, arrival);
    flightsList[index].date[0] = day;
    flightsList[index].date[1] = month;
    flightsList[index].date[2] = year;
    flightsList[index].time[0] = hour;
    flightsList[index].time[1] = minutes;
    flightsList[index].duration[0] = HDuration;
    flightsList[index].duration[1] = MDuration;
    flightsList[index].passangers = capacity;

    totalFlights++;
}


/*
Name: generateFlight
Entry: none
Return: void
Description: reads the information from the input, checks if its valid,
            saves the flight on the list of flight and adds one flight to the
            number of flights of the departure airport
*/
void generateFlight(){
    char code[MAXFLIGHTCODECHAR + MAXFLIGHTCODENUM];
    char apDeparture[MAXIDLEN], apArrival[MAXIDLEN];
    int dayDeparture, monthDeparture, yearDeparture, hourDeparture;
    int minutesDeparture, hourDuration, minuteDuration, capacity;
    int auxIndex;

    scanf("%s %s %s %d-%d-%d %d:%d %d:%d %d", code, apDeparture,
    apArrival, &dayDeparture, &monthDeparture, &yearDeparture,
    &hourDeparture, &minutesDeparture, &hourDuration, &minuteDuration,
    &capacity);
    getchar();

    if(FlightMainCheck(code, dayDeparture, monthDeparture, yearDeparture,
        apDeparture, apArrival, hourDuration, minuteDuration, capacity))
        {

        addFlight(code, apDeparture, apArrival, dayDeparture, monthDeparture,
        yearDeparture, hourDeparture, minutesDeparture, hourDuration,
        minuteDuration, capacity);
        for(auxIndex = 0; auxIndex < totalAirports; auxIndex++){
            if(strcmp(apDeparture, airportsList[auxIndex].id) == 0){
                airportsList[auxIndex].numflights++;
                break;
            }
        }
    }
}


/*
Name: listAllFlights
Entry: none
Return: void
Description: iterates through the list of flights, printing them out one
            by one
*/
void listAllFlights(){
    int index;
    for(index = 0; index < totalFlights; index++){
        printf("%s ", flightsList[index].code);
        printf("%s ", flightsList[index].airportDeparture);
        printf("%s ", flightsList[index].airportArrival);
        printf("%02d-%02d-%02d ", flightsList[index].date[0], 
            flightsList[index].date[1], flightsList[index].date[2]);
        printf("%02d:%02d", flightsList[index].time[0], 
            flightsList[index].time[1]);
        printf("\n");
    }
}


/*
Name: Vcomand
Entry: none
Return: void
Description: main function of the "v" comand, checks if the comand is to 
        print all flight or save a flight and redirects to the specific 
        functions
*/
void Vcomand(){
    if(getchar() == '\n'){
        listAllFlights();
    }
    else{
        generateFlight();
    }
}







/*
Name: rightShiftDeepartList
Entry: index of the comparison flight, index of the current flight
Return: void
Description: right shifts all flights to the right of the comparison flight 
            (including the comparison flight) in the list of departure flights 
            from an airport and adds the current flight to its right place
*/
void rightShiftDeepartList(int flightComp, int flightIndex){
    int auxIndex;
    for(auxIndex = totalDepartFlights - 1; 
    auxIndex >= flightComp; auxIndex--){
        departFlights[auxIndex + 1] = departFlights[auxIndex];
    }
    departFlights[flightComp] = flightsList[flightIndex];
}


/*
Name: CompareDatesFlights
Entry: day, month, year, hour, minute and comparison day, month, year, hour,
        minute
Return: TRUE if the comparison date is future to the flight's date
        FALSE if  the comparison date is past to the flight's date
Description: checks if the date being compared to the main date is future to
            it or not
*/
int CompareDatesFlights(int day, int month, int year, int hour, int minute,
int dayComp, int monthComp, int yearComp, int hourComp, int minuteComp){
    
    return ((yearComp == year && monthComp == month && dayComp == day) &&
        ((hourComp == hour && minuteComp > minute) || hourComp > hour)) ||

        (yearComp == year && monthComp == month && dayComp > day) ||

        (yearComp == year && monthComp > month) ||

        yearComp > year;
}


/*
Name: FindPlaceInListDepart
Entry: day, month, year, hour, minute, current flight's index in flights list
Return: void
Description: compares the dates of each flight in the departure list and the
            current flight, adding it to the right place of the list
*/
void FindPlaceInListDepart(int day, int month, int year, int hour, int minute,
int flightIndex){
    int dayComp, monthComp, yearComp, hourComp, minuteComp; 
    int flightComp, aux = 0;

    for(flightComp = 0; flightComp < totalDepartFlights; flightComp++){
        dayComp = departFlights[flightComp].date[0];
        monthComp = departFlights[flightComp].date[1];
        yearComp = departFlights[flightComp].date[2];
        hourComp = departFlights[flightComp].time[0];
        minuteComp = departFlights[flightComp].time[1];

        if(CompareDatesFlights(day, month, year, hour, minute, dayComp,
        monthComp, yearComp, hourComp, minuteComp)){
            rightShiftDeepartList(flightComp, flightIndex);
            totalDepartFlights++;
            aux = 1;
            break;}
    }
        if(aux == 0){
            departFlights[totalDepartFlights] = flightsList[flightIndex];
            totalDepartFlights++;
        }
}


/*
Name: organizeByTimeDepart
Entry: flights index in the list of all flights
Return: void
Description: main function of the process of organization of the list of
            flights with departure from a specific airport
*/
void organizeByTimeDepart(int index){
    int day, month, year, hour, minute;
    
    day = flightsList[index].date[0];
    month = flightsList[index].date[1];
    year = flightsList[index].date[2];
    hour = flightsList[index].time[0];
    minute = flightsList[index].time[1];

    if(totalDepartFlights == 0){
        departFlights[0] = flightsList[index];
        totalDepartFlights++;
    }

    else{
        FindPlaceInListDepart(day, month,  year, hour, minute, index);
    }

}


/*
Name: Pcomand
Entry: none
Return: void
Description: main function of the "p" comand, reads the airport from the
            input, puts all the flights leaving from that airport in an
            organized list and prints them out one by one
*/
void Pcomand(){
    char id[MAXIDLEN];
    int index = 0;

    scanf("%s", id);
    if(checkAirportExistence(id)){

        while(index < totalFlights){
            if(strcmp(flightsList[index].airportDeparture, id) == 0){
                organizeByTimeDepart(index);
            }
            index++;
        }

        for(index = 0; index < totalDepartFlights; index++){
            printf("%s ", departFlights[index].code);
            printf("%s ", departFlights[index].airportArrival);
            printf("%02d-%02d-%02d ", departFlights[index].date[0], 
                departFlights[index].date[1], departFlights[index].date[2]);
            printf("%02d:%02d", departFlights[index].time[0], 
                departFlights[index].time[1]);
            printf("\n");
        }
    }
    /* reseting the list and departure flight counter for future usage
    of the "p" comand */
    memset(departFlights, 0, sizeof totalDepartFlights);
    totalDepartFlights = 0;
}







/*
Name: AddArrivalTimeToFlightInfo
Entry: arrival day, month, year, hour and minute, and index of the flight
        in the list of all flights
Return: void
Description: adds the calculated arrival date and time to the flight's
            information
*/
void AddArrivalTimeToFlightInfo(int ArrDay, int ArrMonth, int ArrYear, 
int ArrHour, int ArrMinute, int flightIndex){
    flightsList[flightIndex].arrivalDate[0] = ArrDay;
    flightsList[flightIndex].arrivalDate[1] = ArrMonth;
    flightsList[flightIndex].arrivalDate[2] = ArrYear;
    flightsList[flightIndex].arrivalTime[0] = ArrHour;
    flightsList[flightIndex].arrivalTime[1] = ArrMinute;
}


/*
Name: ArrangeArrivalNumers
Entry: arrival day, month, year, hour and minute, and index of the flight
        in the list of all flights
Return: void
Description: arranges de numbers  after summing the flight's duration time
            to match the real intervals
*/
void  ArrangeArrivalNumers(int ArrDay, int ArrMonth, int ArrYear, int ArrHour,
int ArrMinute, int flightIndex){
    if(ArrMinute >= 60){
        ArrHour++;
        ArrMinute -= 60;}

    if(ArrHour >= 24){
        ArrDay++;
        ArrHour -= 24;}

    if(ArrDay > 31){
        ArrMonth++;
        ArrDay -= 31;}

    if((ArrMonth == 4 || ArrMonth == 6 || ArrMonth == 9 || ArrMonth == 11) &&
    ArrDay > 30){
        ArrMonth++;
        ArrDay -= 30;}
        
    if(ArrMonth == 2 && ArrDay > 28){
        ArrMonth++;
        ArrDay -= 28;}

    if(ArrMonth > 12){
        ArrYear++;
        ArrMonth -= 12;}

    AddArrivalTimeToFlightInfo(ArrDay, ArrMonth, ArrYear, ArrHour, ArrMinute,
    flightIndex);
}


/*
Name: calculateArrival
Entry: index ofthe flight inthe list of all flights
Return: void
Description: main function of the process of calculating the arrival date
            and time of a flight
*/
void calculateArrival(int flightIndex){
    int day, month, year, hourDep, minuteDep, hourDur, minuteDur;
    int ArrDay, ArrMonth, ArrYear, ArrHour, ArrMinute;

    day = flightsList[flightIndex].date[0];
    month = flightsList[flightIndex].date[1];
    year = flightsList[flightIndex].date[2];
    hourDep = flightsList[flightIndex].time[0];
    minuteDep = flightsList[flightIndex].time[1];
    hourDur = flightsList[flightIndex].duration[0];
    minuteDur = flightsList[flightIndex].duration[1];

    ArrMinute = minuteDep + minuteDur;
    ArrHour = hourDep + hourDur;
    ArrDay = day;
    ArrMonth = month;
    ArrYear = year;

    ArrangeArrivalNumers(ArrDay,ArrMonth, ArrYear, ArrHour, ArrMinute,
    flightIndex);
}


/*
Name: rightShiftArrivalList
Entry: index of  the comparison flight and of the current flight
Return: void
Description: right shifts all elements to the right of the comparison flight
            (including the comparison flight) and adds the current flight
            to its right place in the arrival flights list
*/
void rightShiftArrivalList(int flightComp, int flightIndex){
    int auxIndex;
    for(auxIndex = totalArrivalFlights - 1; 
    auxIndex >= flightComp; auxIndex--){
        arrivalFlights[auxIndex + 1] = arrivalFlights[auxIndex];
    }
    arrivalFlights[flightComp] = flightsList[flightIndex];
}


/*
Name: FindPlaceInListArrival
Entry: day, month, year, hour, minute, index of the flight in the flights list
Return: void
Description: finds the right place to put the current flight in the list of
            flights arriving to a specific airport and adds it to that place
            of the list
*/
void FindPlaceInListArrival(int day, int month, int year, int hour, int minute,
int flightIndex){
    int dayComp, monthComp, yearComp, hourComp, minuteComp;
    int flightComp, aux = 0;

    for(flightComp = 0; flightComp < totalArrivalFlights; flightComp++){
        dayComp = arrivalFlights[flightComp].arrivalDate[0];
        monthComp = arrivalFlights[flightComp].arrivalDate[1];
        yearComp = arrivalFlights[flightComp].arrivalDate[2];
        hourComp = arrivalFlights[flightComp].arrivalTime[0];
        minuteComp = arrivalFlights[flightComp].arrivalTime[1];

        if(CompareDatesFlights(day, month, year, hour, minute, dayComp,
        monthComp, yearComp, hourComp, minuteComp)){
            rightShiftArrivalList(flightComp, flightIndex);
            totalArrivalFlights++;
            aux = 1;
            break;}
    }
    if(aux == 0){
        arrivalFlights[totalArrivalFlights] = flightsList[flightIndex];
        totalArrivalFlights++;
    }
}


/*
Name: organizeByTimeArrival
Entry: index of a flight in the all flights list
Return: void
Description: main function of organization of the list of flights arriving
            to a specific airport
*/
void organizeByTimeArrival(int flightIndex){
    int day, month, year, hour, minute;

    day = flightsList[flightIndex].arrivalDate[0];
    month = flightsList[flightIndex].arrivalDate[1];
    year = flightsList[flightIndex].arrivalDate[2];
    hour = flightsList[flightIndex].arrivalTime[0];
    minute = flightsList[flightIndex].arrivalTime[1];

    /* checking if its the first flight to be added */
    if(totalArrivalFlights == 0){
        arrivalFlights[0] = flightsList[flightIndex];
        totalArrivalFlights++;
    }

    else{
        FindPlaceInListArrival(day, month,  year, hour, minute, flightIndex);
    }
}

/*
Name: Ccomand
Entry: none
Return: void
Description: main function of the "c" comand, reads the airport from the
            input, checks the airport, finds each flight arriving to that
            airport, calculates its time of arrival, adds it to the list of
            flights arriving to that airport and prints all elements of that
            list
*/
void Ccomand(){
    char id[MAXIDLEN];
    int index;

    scanf("%s", id);
    if(checkAirportExistence(id)){

        for(index = 0; index  < totalFlights; index++){
            if(strcmp(flightsList[index].airportArrival, id) == 0){
                calculateArrival(index);
                organizeByTimeArrival(index);
            }
        }
        for(index = 0; index < totalArrivalFlights; index++){
            printf("%s ", arrivalFlights[index].code);
            printf("%s ", arrivalFlights[index].airportDeparture);
            printf("%02d-%02d-%02d ", arrivalFlights[index].arrivalDate[0], 
                arrivalFlights[index].arrivalDate[1], 
                arrivalFlights[index].arrivalDate[2]);
            printf("%02d:%02d", arrivalFlights[index].arrivalTime[0], 
                arrivalFlights[index].arrivalTime[1]);
            printf("\n");
        }
    }
    /* reseting the list and arrival flight counter for future usage
    of the "c" comand */
    memset(arrivalFlights, 0, sizeof totalArrivalFlights);
    totalArrivalFlights = 0;
}





/*
Name: main
Description: reads the comand form the terminal and redirects to the function
            corresponding to that comand
*/
int main(){
    char input = getchar();

    while(input != 'q'){
        switch (input){
            case 'a': Acomand();
                break;

            case 'l': Lcomand();
                break;

            case 'v': Vcomand();
                break;

            case 'p': Pcomand();
                break;
        
            case 'c': Ccomand();
                break;

            case 't': Tcomand();
                break;
            default: break;
        
        }
        input = getchar();
    }
    return 0;
}

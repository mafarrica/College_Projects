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
#include "lists.h"
#include "globals.h"



/* -----------------------------------------------------------------------------*/



/* -----------------------------------------------------------------------------*/






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
Name: generateAirport
Entry: none
Return: void
Description: main function of the "a" comand, reads the inputs, checks the
            information, adds the airport to the list and prints out the
            wanted result
*/
void generateAirport(){
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
Name: changeTime
Entry: none
Return: void
Description: main function of the "t" comand, read the input, checks the date,
            saves it as the current date and prints it out
*/
void changeTime(){
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
Name: listAirports
Entry: none
Return: void
Description: main function of the "l" comand, checks if the comand is to
            print all airports or just the given ones and redirects to the
            specific functions
*/
void listAirports(){
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
    if(capacity < MINFLIGHTPASSANGERS){
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
    Node *reservations = (Node*) malloc(sizeof(Node));
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


    flightsList[index].reservHead = reservations;

    flightsList[index].reservHead->value = NULL;
    flightsList[index].reservHead->next = NULL;
    flightsList[index].occupiedSeats = 0;


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
Name: flightFunction
Entry: none
Return: void
Description: main function of the "v" comand, checks if the comand is to 
        print all flight or save a flight and redirects to the specific 
        functions
*/
void flightFunction(){
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
Name: printDepartureFlights
Entry: none
Return: void
Description: main function of the "p" comand, reads the airport from the
            input, puts all the flights leaving from that airport in an
            organized list and prints them out one by one
*/
void printDepartureFlights(){
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
Name: printArrivalFlights
Entry: none
Return: void
Description: main function of the "c" comand, reads the airport from the
            input, checks the airport, finds each flight arriving to that
            airport, calculates its time of arrival, adds it to the list of
            flights arriving to that airport and prints all elements of that
            list
*/
void printArrivalFlights(){
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



/* ------------------------------------------------------------------------------------------ */



void freeAllMemory(Node *HashTable){
    /*
    int i;

    for(i = 0; i < totalAirports; i++){
        Node *temp = flightsList[i].reservations;

        while(temp != NULL){
            free(temp->reservInfo);
            free(temp->next);
            free(temp);
            temp = temp->next;
        }
    }

    free(HashTable[0].reservInfo);
    free(HashTable[0].next);
    free(&HashTable[0]);
    for(i = 1; i < HASHTABLESIZE; i++){
        free(HashTable[i].reservInfo->reservCode);
        free(HashTable[i].reservInfo->flightCode);
        free(HashTable[i].reservInfo);
        free(HashTable[i].next);
        free(&HashTable[i]);
    }

    */

    free(HashTable);
}


void fullMemory(Node *HashTable){
    printf("No memory\n");
    freeAllMemory(HashTable);
    exit(0);
}







unsigned long hashFunction(char *key){
    unsigned long i = 0;
    unsigned long aux;
    int a = 0;

    for(aux = 0; aux < strlen(key); aux++){
        i += (key[aux] * (strlen(key) + a));
        a = i*key[aux];
    }

    return i%33;
}


void initializeHashTable(Node *HashTable){
    unsigned long i;
    for(i = 0; i < HASHTABLESIZE; i++){
        Node temp;
        temp.value = NULL;
        temp.next = NULL;
        HashTable[i] = temp;
    }
}





int searchInList(Node *head, Node *item){
    Node *temp = head;

    while(temp->next != NULL){
        temp = temp->next;
        if(strcmp(((Reservation*)temp->value)->reservCode, 
        ((Reservation*)item->value)->reservCode) == 0)
            return 1;
    }

    return 0;
}



int findFlightIndex(char flightCode[], int day, int month, int year){
    int i;
    for(i = 0; i < totalFlights; i++){
        if(strcmp(flightsList[i].code, flightCode) == 0 &&
        flightsList[i].date[0] == day && 
        flightsList[i].date[1] == month &&
        flightsList[i].date[2] == year){
            return i;
        }
    }
     return -1;
}


int checkReservationCode(char code[]){
    int len = strlen(code), i;

    if(len < 10)
        return 0;

    for(i = 0; i < len; i++){
        if(!((code[i] >= 'A' && code[i] <= 'Z') ||
        (code[i] >= '0' && code[i] <= '9')))
            return 0;
    }
    return 1;
}



int checkExistingReservation(Node *HashTable, char *reservCode, Node *reservNode){
    unsigned long index = hashFunction(reservCode);
    int result = searchInList(&HashTable[index], reservNode);

    return result;
}


int checkNumReservations(char flightCode[], int day, int month, int year, 
int reservPassengers){
    int i = findFlightIndex(flightCode, day, month, year);
    
    if(flightsList[i].occupiedSeats + reservPassengers > 
    flightsList[i].passangers){
        return 0;
    }
    return 1;
}



int checkNumPassengers(int num){
    return num > 0;
}



int checkFlightExistence(char code[], int day, int month, int year){
    int check;
    check = findFlightIndex(code, day, month, year);
    return check == -1;
}


int checkReservations(char flightCode[], int day, int month, int year,
char reservCode[], int reservPassengers, Node *HashTable, Node *reservNode){
   
    if(!checkReservationCode(reservCode)){
        printf("invalid reservation code\n");
        return 0;
    }
    
    if(checkFlightExistence(flightCode, day, month, year)){
        printf("%s: flight does not exist\n", flightCode);
        return 0;
    }


    if(checkExistingReservation(HashTable, reservCode, reservNode)){
        printf("%s: flight reservation already used\n", reservCode);
        return 0;
    }


    if(!checkNumReservations(flightCode, day, month, year, reservPassengers)){
        printf("too many reservations\n");
        return 0;
    }

    if(!checkDate(day, month, year)){
        return 0;
    }

    if(!checkNumPassengers(reservPassengers)){
        printf("invalid passenger number\n");
        return 0;
    }
    return 1;
}










Reservation* allocReservation(Node *HashTable, char *reservCode, int day,
int month, int year, int passengerNum, char *flightCode){
    Reservation *reserv = (Reservation*) malloc(sizeof(Reservation));
    char *codeR = (char*) malloc(sizeof(char) * (strlen(reservCode) + 1));
    char *codeF = (char*) malloc(sizeof(char) * (strlen(flightCode) + 1));

    if(reserv == NULL || codeR == NULL || codeF == NULL){
        printf("full memory 1\n");
        fullMemory(HashTable);
    }

    strcpy(codeF, flightCode);
    strcpy(codeR, reservCode);


    strcpy(reserv->flightCode, codeF);
    strcpy(reserv->reservCode, codeR);
    reserv->passengers = passengerNum;
    reserv->date[0] = day;
    reserv->date[1] = month;
    reserv->date[2] = year;

    return reserv;
}



void insertInHashTable(Node *HashTable, Node *reservNode){
    unsigned long index = hashFunction(((Reservation*)reservNode->value)->reservCode);
    Node *head = &HashTable[index];

    insertInList_end(head, reservNode);

}





void insertInPlaceFlightInfo(int index, Node *reservNode){
    Node *previous = flightsList[index].reservHead;
    Node *current = flightsList[index].reservHead->next;

    /* first element of ordered list */
    if(strcmp(((Reservation*)current->value)->reservCode, 
    ((Reservation*)reservNode->value)->reservCode) > 0){
        previous->next = reservNode;
        reservNode->next = current;
        return;
    }

    while(current->next != NULL){
        current = current->next;
        previous = previous->next;
        if(strcmp(((Reservation*)current->value)->reservCode, 
        ((Reservation*)reservNode->value)->reservCode) > 0){
            reservNode->next = current;
            previous->next = reservNode;
            return;
        }
    }

    /* last element of ordered list */
    current->next = reservNode;
    reservNode->next = NULL;
}




void InsertInFlightInfo(Node *reservNode){
    char *flightCode = ((Reservation*)reservNode->value)->flightCode;
    int day = ((Reservation*)reservNode->value)->date[0];
    int month = ((Reservation*)reservNode->value)->date[1];
    int year = ((Reservation*)reservNode->value)->date[2];

    int flightIndex = findFlightIndex(flightCode, day, month, year);
    
    flightsList[flightIndex].occupiedSeats += ((Reservation*)reservNode->value)->passengers;


    /* inserting first reservation in flight info */
    if(flightsList[flightIndex].reservHead->next == NULL){
        flightsList[flightIndex].reservHead->next = reservNode;
        reservNode->next = NULL;
        return;
    }
    else{
        insertInPlaceFlightInfo(flightIndex, reservNode);
    }
}










void createReservation(char flightCode[], int day, int month, int year,
char reservCode[], int reservPassengers, Node *HashTable){
    Reservation *reservation = allocReservation(HashTable, reservCode, 
    day, month, year, reservPassengers, flightCode);

    Node *reservNode = (Node*) malloc(sizeof(Node));

    if(reservNode == NULL){
        printf("full memory 2\n");
        fullMemory(HashTable);
    }

    reservNode->value = (Reservation*)reservation;
    reservNode->next = NULL;

    if(!checkReservations(flightCode, day, month, year, reservCode, 
    reservPassengers, HashTable, reservNode))
        return;

    
    insertInHashTable(HashTable, reservNode);

    InsertInFlightInfo(reservNode);
}




void printReservations(char flightCode[], int day, int month, int year){
    int index = findFlightIndex(flightCode, day, month, year);
    Node *temp = flightsList[index].reservHead;

    if(checkFlightExistence(flightCode, day, month, year)){
        printf("%s: flight does not exist\n", flightCode);
        return;
    }
    if(!checkDate(day, month, year))
        return;


    while(temp->next != NULL){
        temp = temp->next;
        printf("%s %d\n", ((Reservation*)temp->value)->reservCode,
        ((Reservation*)temp->value)->passengers);
    }
}





void reservationFunction(Node *HashTable){
    char reservCode[RESCODESIZE];
    int day, month, year;
    char flightCode[MAXFLIGHTCODE];
    int reservPassengers;

    scanf("%s", flightCode);
    scanf("%d-%d-%d", &day, &month, &year);

    if(getchar() == '\n'){
        printReservations(flightCode, day, month, year);
        return;
    }

    scanf("%s", reservCode);
    scanf("%d", &reservPassengers);
    getchar();
    createReservation(flightCode, day, month, year, 
    reservCode, reservPassengers, HashTable);
}


/* ----------------------------------------------------------------- */


unsigned long checkCodeForReservation(char *code, Node *HashTable){
    unsigned long index = hashFunction(code);
    Node *temp = &HashTable[index];

    if(!checkReservationCode(code))
        return 0;
    
    while(temp->next != NULL){
        temp = temp->next;
        if(strcmp(((Reservation*)temp->value)->reservCode, code) == 0){
            return index;
        }
    }
    return -1;
}

int checkCodeForFlight(char *code){
    int i;
    for(i = 0; i < totalFlights; i++){
        if(strcmp(flightsList[i].code, code) == 0){
            return i;
        }
    }
    return -1;
}


Node* deleteFromHashTable(Node *prev, Node *temp, char* reservCode){
    Node *reservation;
    while(temp != NULL){
        if(strcmp(((Reservation*)temp->value)->reservCode, reservCode) == 0){
            deleteFromList(prev, temp);
            reservation = temp;
            break;
        }
        prev = prev->next;
        temp = temp->next;
    }
    
    return reservation;
}


void deleteFromFlight(Node *prev, Node *temp, char* reservCode){
    while(temp != NULL){
        if(strcmp(((Reservation*)temp->value)->reservCode, reservCode) == 0){
            deleteFromList(prev, temp);
            break;
        }
        prev = prev->next;
        temp = temp->next;
    }
}



void deleteReservation(Node *HashTable, char *reservCode, 
unsigned long HTindex, int FLTindex){
    Node *prevHT = &HashTable[HTindex];
    Node *tempHT = prevHT->next;

    Node *prevFLT = flightsList[FLTindex].reservHead;
    Node *tempFLT = prevFLT->next;

    Node *reservation;

    reservation = deleteFromHashTable(prevHT, tempHT, reservCode);    

    deleteFromFlight(prevFLT, tempFLT, reservCode);
    
    /* free reservation memory */
    free(((Reservation*)reservation->value)->reservCode);
    free(((Reservation*)reservation->value)->flightCode);
    free((Reservation*)reservation->value);
    free(reservation);

}





void deleteFlightOrReservation(Node *HashTable){
    char code[RESCODESIZE];
    unsigned long check1;
    int  check2;

    scanf("%s", code);

    check1 = checkCodeForReservation(code, HashTable);
    check2 = checkCodeForFlight(code);

    if(check1 == -1 && check2 == -1){
        printf("not found\n");
        return;
    }
    else if(check1 != -1){
        /* é uma reserva */
    }
    
    /* é um voo */
    
}

































void readInput(Node *HashTable){
    char input = getchar();

    while(input != 'q'){
        switch (input){
            case 'a': generateAirport();
                break;

            case 'l': listAirports();
                break;

            case 'v': flightFunction();
                break;

            case 'p': printDepartureFlights();
                break;
        
            case 'c': printArrivalFlights();
                break;

            case 't': changeTime();
                break;
            case 'r': reservationFunction(HashTable);
                break;
            case 'e': deleteFlightOrReservation(HashTable);
                break;
            default: break;
        
        }
        input = getchar();
    }
    return;
}

/*
Name: main
Description: reads the comand form the terminal and redirects to the function
            corresponding to that comand
*/
int main(){
    Node *HashTable = (Node*)malloc(sizeof(Node) * HASHTABLESIZE);

    if(HashTable == NULL){
        fullMemory(HashTable);
        return 0;
    }

    initializeHashTable(HashTable);

    readInput(HashTable);

    freeAllMemory(HashTable);

    return 0;
}

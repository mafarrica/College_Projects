#ifndef GLOBALS_H
#define GLOBALS_H

#define MAXFLIGHTS 30000
#define MAXAIRPORTS 40

#define MAXIDLEN 4
#define MAXCOUNTRYCHAR 31
#define MAXCITYCHAR 51
#define MAXFLIGHTDURATION 12
#define MINFLIGHTPASSANGERS 10
#define MAXFLIGHTCODECHAR 2
#define MAXFLIGHTCODENUM 4
#define MAXFLIGHTCODE 7

#define RESCODESIZE 65535
#define HASHTABLESIZE 1000


typedef struct {
    char flightCode[MAXFLIGHTCODE];
    char reservCode[RESCODESIZE];
    int passengers;
    int date[3];
} Reservation;






/* airport structure */

typedef struct {
    char id[MAXIDLEN];
    char country[MAXCOUNTRYCHAR];
    char city[MAXCITYCHAR];
    int numflights;
}Airport;

/* flight structure */

typedef struct {
    char code[MAXFLIGHTCODE];
    char airportDeparture[MAXIDLEN];
    char airportArrival[MAXIDLEN];
    int date[3];
    int time[2];
    int duration[2];
    int passangers;
    int arrivalDate[3];
    int arrivalTime[2];

    Node *reservHead;
    int occupiedSeats;
}Flight;










/* global variables and arrays */

Airport airportsList[MAXAIRPORTS];

Flight flightsList[MAXFLIGHTS];

Flight departFlights[MAXFLIGHTS];

Flight arrivalFlights[MAXFLIGHTS];

int currentDate[3] = {1, 1, 2022};

int totalAirports = 0;

int totalFlights = 0;

int totalDepartFlights = 0;

int totalArrivalFlights = 0;



#endif
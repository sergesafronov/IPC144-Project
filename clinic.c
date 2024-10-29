#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>


// include the user library "core" so we can use those functions
#include "core.h"
// include the user library "clinic" where the function prototypes are declared
#include "clinic.h"


//////////////////////////////////////
// DISPLAY FUNCTIONS
//////////////////////////////////////

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display's the patient table header (table format)
void displayPatientTableHeader(void)
{
    printf("Pat.# Name            Phone#\n"
           "----- --------------- --------------------\n");
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Displays a single patient record in FMT_FORM | FMT_TABLE format
void displayPatientData(const struct Patient* patient, int fmt)
{
    if (fmt == FMT_FORM)
    {
        printf("Name  : %s\n"
               "Number: %05d\n"
               "Phone : ", patient->name, patient->patientNumber);
        displayFormattedPhone(patient->phone.number);
        printf(" (%s)\n", patient->phone.description);
    }
    else
    {
        printf("%05d %-15s ", patient->patientNumber,
               patient->name);
        displayFormattedPhone(patient->phone.number);
        printf(" (%s)\n", patient->phone.description);
    }
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display's appointment schedule headers (date-specific or all records)
void displayScheduleTableHeader(const struct Date* date, int isAllRecords)
{
    printf("Clinic Appointments for the Date: ");

    if (isAllRecords)
    {
        printf("<ALL>\n\n");
        printf("Date       Time  Pat.# Name            Phone#\n"
               "---------- ----- ----- --------------- --------------------\n");
    }
    else
    {
        printf("%04d-%02d-%02d\n\n", date->year, date->month, date->day);
        printf("Time  Pat.# Name            Phone#\n"
               "----- ----- --------------- --------------------\n");
    }
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display a single appointment record with patient info. in tabular format
void displayScheduleData(const struct Patient* patient,
                         const struct Appointment* appoint,
                         int includeDateField)
{
    if (includeDateField)
    {
        printf("%04d-%02d-%02d ", appoint->date.year, appoint->date.month,
               appoint->date.day);
    }
    printf("%02d:%02d %05d %-15s ", appoint->time.hour, appoint->time.min,
           patient->patientNumber, patient->name);

    displayFormattedPhone(patient->phone.number);

    printf(" (%s)\n", patient->phone.description);
}


//////////////////////////////////////
// MENU & ITEM SELECTION FUNCTIONS
//////////////////////////////////////

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// main menu
void menuMain(struct ClinicData* data)
{
    int selection;

    do {
        printf("Veterinary Clinic System\n"
               "=========================\n"
               "1) PATIENT     Management\n"
               "2) APPOINTMENT Management\n"
               "-------------------------\n"
               "0) Exit System\n"
               "-------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 2);
        putchar('\n');
        switch (selection)
        {
        case 0:
            printf("Are you sure you want to exit? (y|n): ");
            selection = !(inputCharOption("yn") == 'y');
            putchar('\n');
            if (!selection)
            {
                printf("Exiting system... Goodbye.\n\n");
            }
            break;
        case 1:
            menuPatient(data->patients, data->maxPatient);
            break;
        case 2:
            menuAppointment(data);
            break;
        }
    } while (selection);
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Patient Management
void menuPatient(struct Patient patient[], int max)
{
    int selection;

    do {
        printf("Patient Management\n"
               "=========================\n"
               "1) VIEW   Patient Data\n"
               "2) SEARCH Patients\n"
               "3) ADD    Patient\n"
               "4) EDIT   Patient\n"
               "5) REMOVE Patient\n"
               "-------------------------\n"
               "0) Previous menu\n"
               "-------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 5);
        putchar('\n');
        switch (selection)
        {
        case 1:
            displayAllPatients(patient, max, FMT_TABLE);
            suspend();
            break;
        case 2:
            searchPatientData(patient, max);
            break;
        case 3:
            addPatient(patient, max);
            suspend();
            break;
        case 4:
            editPatient(patient, max);
            break;
        case 5:
            removePatient(patient, max);
            suspend();
            break;
        }
    } while (selection);
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Patient edit
void menuPatientEdit(struct Patient* patient)
{
    int selection;

    do {
        printf("Edit Patient (%05d)\n"
               "=========================\n"
               "1) NAME : %s\n"
               "2) PHONE: ", patient->patientNumber, patient->name);
        
        displayFormattedPhone(patient->phone.number);
        
        printf("\n"
               "-------------------------\n"
               "0) Previous menu\n"
               "-------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 2);
       
        if (selection == 1)
        {
            printf("\nName  : ");
            inputCString(patient->name, 1, NAME_LEN);
            putchar('\n');
            printf("Patient record updated!\n\n");
        }
        else if (selection == 2)
        {
            inputPhoneData(&patient->phone);
            putchar('\n');
            printf("Patient record updated!\n\n");
        }

    } while (selection);
    putchar('\n');
}


// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Appointment Management
void menuAppointment(struct ClinicData* data)
{
    int selection;

    do {
        printf("Appointment Management\n"
               "==============================\n"
               "1) VIEW   ALL Appointments\n"
               "2) VIEW   Appointments by DATE\n"
               "3) ADD    Appointment\n"
               "4) REMOVE Appointment\n"
               "------------------------------\n"
               "0) Previous menu\n"
               "------------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 4);
        putchar('\n');
        switch (selection)
        {
        case 1:
            viewAllAppointments(data);  
            suspend();
            break;
        case 2:
            viewAppointmentSchedule(data);  
            suspend();
            break;
        case 3:
            addAppointment(data->appointments, data->maxAppointments,
                           data->patients, data->maxPatient);  
            suspend();
            break;
        case 4:
            removeAppointment(data->appointments, data->maxAppointments,
                              data->patients, data->maxPatient); 
            suspend();
            break;
        }
    } while (selection);
}


// ---------------------------------------------------------------------------
// !!! INSERT/COPY YOUR MS#2 FUNCTION DEFINITIONS BELOW... !!!
// Note: Maintain the same order/sequence as it is listed in the header file
//       Properly organize/categorize any new functions accordingly
// ---------------------------------------------------------------------------


// Display's all patient data in the FMT_FORM | FMT_TABLE format
// (Copy your code from MS#2)
void displayAllPatients(const struct Patient patient[], int max, int fmt) {
    if (max == 0) {
        printf("*** No records found ***\n");
        return;

    }
    if (fmt == FMT_TABLE) {
        displayPatientTableHeader();
    }
    int i;
    for (i = 0; i < max; i++) {
        if (patient[i].patientNumber == 0) {
            continue;
        }
        displayPatientData(&patient[i], fmt);
    }
}


// Search for a patient record based on patient number or phone number
// (Copy your code from MS#2)
void searchPatientData(const struct Patient patient[], int max) {
    int selection;
    do {
        printf("Search Options\n"
            "==========================\n"
            "1) By patient number\n"
            "2) By phone number\n"
            "..........................\n"
            "0) Previous menu\n"
            "..........................\n"
            "Selection: ");
        selection = inputIntRange(0, 2);
        putchar('\n');
        switch (selection)
        {
        case 1:
            searchPatientByPatientNumber(patient, max);
            suspend();
            break;
        case 2:
            searchPatientByPhoneNumber(patient, max);
            suspend();
            break;
        }
    } while (selection);
}


// Add a new patient record to the patient array
// (Copy your code from MS#2)
void addPatient(struct Patient patient[], int max) {
    int i;
    for (i = 0; i < max; i++) {
        if (patient[i].patientNumber == 0) {
            break;
        }
    }
    if (i < max) {
        int id = nextPatientNumber(patient, max);
        patient[i].patientNumber = id;
        inputPatient(&patient[i]);
        printf("\n*** New patient record added ***\n");
    }
    else {
        printf("ERROR: Patient listing is FULL!\n");
    }

}


// Edit a patient record from the patient array
// (Copy your code from MS#2)
void editPatient(struct Patient patient[], int max) {
    printf("Enter the patient number: ");
    int id = inputIntPositive();
    int i = findPatientIndexByPatientNum(id, patient, max);
    putchar('\n');
    if (i == -1) {
        printf("ERROR: Patient record not found!\n");
        return;
    }
    menuPatientEdit(&patient[i]);
}


// Remove a patient record from the patient array
// (Copy your code from MS#2)
void removePatient(struct Patient patient[], int max) {
    printf("Enter the patient number: ");
    int id = inputIntPositive();
    int i = findPatientIndexByPatientNum(id, patient, max);
    putchar('\n');
    if (i == -1) {
        printf("ERROR: Patient record not found!\n");
        return;
    }
    displayPatientData(&patient[i], FMT_FORM);
    printf("\nAre you sure you want to remove this patient record? (y/n): ");
    if (inputCharOption("yn") == 'y') {
        patient[i].name[0] = '\0';
        patient[i].patientNumber = 0;
        patient[i].phone.description[0] = '\0';
        patient[i].phone.number[0] = 0;
        printf("Patient record has been removed!\n");
    }
    else {
        printf("Operation aborted.\n");
    }
}


// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// Milestone #3 mandatory functions...
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

// View ALL scheduled appointments
void viewAllAppointments(struct ClinicData *data) {
    displayScheduleTableHeader(NULL, 1);
    int i;
    for (i = 0; i < data->maxAppointments; i++) {
        int patient = findPatientIndexByPatientNum(data->appointments[i].patientNumber,
data->patients, data->maxPatient);
        if (patient == -1) {
            continue;
        }
        displayScheduleData(&data->patients[patient], &data->appointments[i], 1);
    }
 }


void inputDate(struct Date* date) {
    int months[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    printf("Year        : ");
    date->year = inputIntPositive();
    if (date->year % 4 == 0) {
        months[1]++;
    }
    printf("Month (1-12): ");
    date->month = inputIntRange(1, 12);
    printf("Day (1-%d)  : ", months[date->month - 1]);
    date->day = inputIntRange(1, months[date->month - 1]);
}


// View appointment schedule for the user input date
void viewAppointmentSchedule(struct ClinicData* data) {
    struct Date date;
    inputDate(&date);
    printf("\n");
    displayScheduleTableHeader(&date, 0);
    int i;
    for (i = 0; i < data->maxAppointments; i++) {
        int patient = findPatientIndexByPatientNum(data->appointments[i].patientNumber,
            data->patients, data->maxPatient);
        if (patient == -1) {
            continue;
        }
        if (data->appointments[i].date.year == date.year &&
            data->appointments[i].date.month == date.month &&
            data->appointments[i].date.day == date.day) {
            displayScheduleData(&data->patients[patient], &data->appointments[i], 0);
        }
        
    }
}

// Add an appointment record to the appointment array
void addAppointment(struct Appointment apps[], int maxApps,
    struct Patient patients[], int maxPatient) {
    
    int i;
    for (i = 0; i < maxApps; i++) {
        if (apps[i].patientNumber < 1) {
            break;
        }
    }
    if (i >= maxApps) {
        printf("\nERROR: Appointment timeslot is not available!\n");
        return;
    }
    printf("Patient Number: ");
    int patientNumber = inputIntPositive();
    int patientIndex = findPatientIndexByPatientNum(patientNumber, patients, maxPatient);
    if (patientIndex == -1) {
        printf("ERROR: Patient record not found!\n");
        return;
    }
    struct Date date;
    int hour, minute;
    int available = 0;
    do {
        inputDate(&date);
        do {
            printf("Hour (0-23)  : ");
            hour = inputIntRange(0, 23);
            printf("Minute (0-59): ");
            minute = inputIntRange(0, 59);
            float time = hour + minute / 100.0;
            if (time < START_APPT_TIME_HOUR || time > END_APPT_TIME_HOUR || minute % 30 != 0) {
                printf("ERROR: Time must be between %02d:00 and %02d:00 in 30 minute intervals.\n",
                    START_APPT_TIME_HOUR, END_APPT_TIME_HOUR);
                putchar('\n');
            }
            else {
                break;
            }
        } while (1);
        int k;
        available = 0;
        for (k = 0; k < maxApps; k++) {
            if (apps[k].date.year == date.year &&
                apps[k].date.month == date.month &&
                apps[k].date.day == date.day &&
                apps[k].time.hour == hour &&
                apps[k].time.min == minute) {
                printf("\nERROR: Appointment timeslot is not available!\n");
                putchar('\n');
                available = 1;
                break;
            }            
        }
    } while (available);

    apps[i].patientNumber = patientNumber;
    apps[i].date.year = date.year;
    apps[i].date.month = date.month;
    apps[i].date.day = date.day;
    apps[i].time.hour = hour;
    apps[i].time.min = minute;
    printf("\n*** Appointment scheduled! ***\n");
    sortAppointments(apps, maxApps);
}

// Remove an appointment record from the appointment array
void removeAppointment(struct Appointment apps[], int maxApps,
    struct Patient patients[], int maxPatient) {

        printf("Patient Number: ");
        int patientNumber = inputIntPositive();
        int patientIndex = findPatientIndexByPatientNum(patientNumber, patients, maxPatient);
        if (patientIndex == -1) {
            printf("ERROR: Patient record not found!\n");
            return;
        }
        struct Date date;
        inputDate(&date);
        
        int i;
        for (i = 0; i < maxApps; i++) {
            if (apps[i].patientNumber == patientNumber &&
                apps[i].date.year == date.year &&
                apps[i].date.month == date.month &&
                apps[i].date.day == date.day) {
                putchar('\n');
                displayPatientData(&patients[patientIndex], FMT_FORM);
                printf("Are you sure you want to remove this appointment (y,n): ");
                if (inputCharOption("yn") == 'y') {
                    apps[i].patientNumber = 0;
                    apps[i].date.year = 0;
                    apps[i].date.month = 0;
                    apps[i].date.day = 0;
                    apps[i].time.hour = 0;
                    apps[i].time.min = 0;
                    printf("\nAppointment record has been removed!\n");
                    sortAppointments(apps, maxApps);
                }
                else {
                    printf("Operation aborted.\n");
                }
            }
        }       
}

//////////////////////////////////////
// UTILITY FUNCTIONS
//////////////////////////////////////

// Search and display patient record by patient number (form)
void searchPatientByPatientNumber(const struct Patient patient[], int max) {
    printf("Search by patient number: ");
    int id = inputIntPositive();
    int i = findPatientIndexByPatientNum(id, patient, max);
    if (i == -1) {
        printf("\n*** No records found ***\n");
        return;
    }
    putchar('\n');
    displayPatientData(&patient[i], FMT_FORM);

}

// Search and display patient records by phone number (tabular)
void searchPatientByPhoneNumber(const struct Patient patient[], int max) {
    printf("Search by phone number: ");
    char phone[PHONE_LEN + 1];
    inputCString(phone, PHONE_LEN, PHONE_LEN);
    int i, found = 0;
    putchar('\n');
    displayPatientTableHeader();
    for (i = 0; i < max; i++) {
        if (strlen(patient[i].phone.number) != 10) {
            continue;
        }
        if (strcmp(patient[i].phone.number, phone) == 0) {
            displayPatientData(&patient[i], FMT_TABLE);
            found++;
        }
    }

    if (found == 0) {
        printf("\n*** No records found ***\n");
        return;
    }
}

// Get the next highest patient number
int nextPatientNumber(const struct Patient patient[], int max) {
    int i, maxId = 0;
    for (i = 0; i < max; i++) {
        if (patient[i].patientNumber > maxId) {
            maxId = patient[i].patientNumber;
        }
    }
    return maxId + 1;
}

// Find the patient array index by patient number (returns -1 if not found) Edit Patient
int findPatientIndexByPatientNum(int id, const struct Patient patient[], int max) {
    int i;
    for (i = 0; i < max; i++) {
        if (patient[i].patientNumber == id) {
            return i;
        }
    }
    return -1;
}


//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

// Get user input for a new patient record
void inputPatient(struct Patient* patient) {
    printf("Patient Data Input\n"
        "------------------\n"
        "Number: %05d\n"
        "Name  : ", patient->patientNumber);
    inputCString(patient->name, 1, NAME_LEN);
    inputPhoneData(&patient->phone);
}

// Get user input for phone contact information
void inputPhoneData(struct Phone* phone) {
    int selection;
    printf("\nPhone Information\n"
        "-----------------\n"
        "How will the patient like to be contacted?\n"
        "1. Cell\n"
        "2. Home\n"
        "3. Work\n"
        "4. TBD\n"
        "Selection: ");
    selection = inputIntRange(1, 4);
    putchar('\n');
    switch (selection) {
    case 1:
        strcpy(phone->description, "CELL");
        break;
    case 2:
        strcpy(phone->description, "HOME");
        break;
    case 3:
        strcpy(phone->description, "WORK");
        break;
    case 4:
        strcpy(phone->description, "TBD");
        return;
    }
    printf("Contact: %s\n", phone->description);
    printf("Number : ");
    inputCString(phone->number, PHONE_LEN, PHONE_LEN);


}


//////////////////////////////////////
// FILE FUNCTIONS
//////////////////////////////////////

// Import patient data from file into a Patient array (returns # of records read)
int importPatients(const char* datafile, struct Patient patients[], int max) {
    FILE* f;
    int numPets = 0, nread;
    f = fopen(datafile, "r");
    if (f == NULL) {
        return 0;
    }
    while (max-- && !feof(f)) {
       nread = fscanf(f, "%d|%[^|]|%[^|]|%[^\n]", &patients[numPets].patientNumber,
            patients[numPets].name, patients[numPets].phone.description,
            patients[numPets].phone.number);
        if (nread > 0) {
            numPets++;
        }
    }
    fclose(f);

    return numPets;
}

// Import appointment data from file into an Appointment array (returns # of records read)
int importAppointments(const char* datafile, struct Appointment appoints[], int max) {
    FILE* f;
    int numApps = 0, nread;
    f = fopen(datafile, "r");
    if (f == NULL) {
        return 0;
    }
    while (max-- && !feof(f)) {
        nread = fscanf(f, "%d,%d,%d,%d,%d,%d", &appoints[numApps].patientNumber,
            &appoints[numApps].date.year, &appoints[numApps].date.month,
            &appoints[numApps].date.day, &appoints[numApps].time.hour,
            &appoints[numApps].time.min);
        if (nread > 0) {
            numApps++;
        }
    }
    fclose(f);

    sortAppointments(appoints, max);

    return numApps;

}

// Sort appointments
void sortAppointments(struct Appointment* appointments, int size) {
    int i;
    int k;
    struct Appointment temp;
    for (i = size - 1; i > 0; i--) {
        for (k = 0; k < i; k++) {            
            //Sort by year
            if (appointments[k].date.year > appointments[k + 1].date.year) {
                
                temp = appointments[k];
                appointments[k] = appointments[k + 1];
                appointments[k + 1] = temp;
            }
            //Sort by day
            else if (appointments[k].date.year == appointments[k + 1].date.year
                     && appointments[k].date.day > appointments[k + 1].date.day) {
                
                    temp = appointments[k];
                    appointments[k] = appointments[k + 1];
                    appointments[k + 1] = temp;
                 }
            //Sort by hour
            else if (appointments[k].date.year == appointments[k + 1].date.year 
                    && appointments[k].date.day == appointments[k + 1].date.day
                    && appointments[k].time.hour > appointments[k + 1].time.hour) {
                
                    temp = appointments[k];
                    appointments[k] = appointments[k + 1];
                    appointments[k + 1] = temp;
                 }
            //Sort by minutes
            else if (appointments[k].date.year == appointments[k + 1].date.year
                    && appointments[k].date.day == appointments[k + 1].date.day
                    && appointments[k].time.hour == appointments[k + 1].time.hour
                    && appointments[k].time.min > appointments[k + 1].time.min) {
                
                    temp = appointments[k];
                    appointments[k] = appointments[k + 1];
                    appointments[k + 1] = temp;
                 }
        }
    }
}
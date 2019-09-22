#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <inttypes.h>
#include <time.h>

///< test parameters
#define SPEEDTEST_NUM_ITERATIONS (100)
#define SPEEDTEST_NUM_RECORDS (1000000)

///< struct, no pack and no alignment
typedef struct
{
    char Name[40];
    char Surname[40];
    uint32_t EmployeeNumber;
    uint8_t Age;
    uint32_t Salary;
    uint8_t Gender;
    char PhoneNumber[20];
} Employee;

///< struct, packed using __attribute__ ((packed)) (GCC only)
typedef struct __attribute__((packed))
{
    char Name[40];
    char Surname[40];
    uint32_t EmployeeNumber;
    uint8_t Age;
    uint32_t Salary;
    uint8_t Gender;
    char PhoneNumber[20];
} Employee_packed1;

///< struct, packed using #pragma pack(push, 1), compatible with VS C++  compiler
#pragma pack(push, 1)
typedef struct
{
    char Name[40];
    char Surname[40];
    uint32_t EmployeeNumber;
    uint8_t Age;
    uint32_t Salary;
    uint8_t Gender;
    char PhoneNumber[20];
} Employee_packed2;
#pragma pack(pop)

/********************************************//**
 * \brief Macro show_struct_size to show structure size
 *
 * \param astruct : structure to show
 * \return Nothing
 *
 ***********************************************/
#define show_struct_size(astruct) printf("size of " # astruct " struct = %zu\n",sizeof(astruct));

/********************************************//**
 * \brief Macro show_offset_of to show offset of
 *        member in struct
 *
 * \param astruct : structure to show
 * \param member : member for which offset is to be shown
 * \return Nothing
 *
 ***********************************************/
#define show_offset_of(astruct,member) printf("Offset of " # astruct "." # member " = %zu\n",offsetof(astruct,member))

/********************************************//**
 * \brief Macro show_offsets to show offsets of
 *        all members in struct
 *
 * \param astruct : structure for which to show offsets
 * \return Nothing
 *
 ***********************************************/
#define show_offsets(astruct) \
    show_offset_of(astruct,Name); \
    show_offset_of(astruct,Surname); \
    show_offset_of(astruct,EmployeeNumber); \
    show_offset_of(astruct,Age); \
    show_offset_of(astruct,Salary); \
    show_offset_of(astruct,Gender); \
    show_offset_of(astruct,PhoneNumber); \
    printf("\n");

/********************************************//**
 * \brief Macro speed_test do a speed test by populating
 *        all the records in an array
 *
 * \param astruct : structure for which to populate data
 * \return Nothing
 *
 ***********************************************/
#define speed_test(astruct) \
    do { \
        uint32_t i,j; \
        char startstr[30]; \
        char endstr[30]; \
        time (&start_t); \
        printf("Speed test: " #astruct "\n"); \
        for(j=0; j<SPEEDTEST_NUM_ITERATIONS; j++) \
        { \
            for(i=0; i<SPEEDTEST_NUM_RECORDS; i++) \
            { \
                strcpy(astruct[i].Name,"John"); \
                strcpy(astruct[i].Surname,"Doe"); \
                astruct[i].EmployeeNumber = i; \
                astruct[i].Age = (uint8_t)(20 + (i % 20)); \
                astruct[i].Salary = 20000 + (i % 20000); \
                astruct[i].Gender = (uint8_t)(i & 0x01); \
                sprintf(astruct[i].PhoneNumber,"%" PRIu32, 10000000u + i); \
            } \
            printf("Speed test: %d/%d\n",j+1,SPEEDTEST_NUM_ITERATIONS); \
        } \
        time (&end_t); \
        dif = difftime (end_t,start_t); \
        memcpy(&start_tm,localtime ( &start_t ),sizeof(struct tm)); \
        memcpy(&end_tm,localtime ( &end_t ),sizeof(struct tm)); \
        strftime(startstr, sizeof(startstr), "%A %c", &start_tm); \
        strftime(endstr, sizeof(endstr), "%A %c", &end_tm); \
        printf ("Test " #astruct " %.2f seconds to run (%s : %s)\n", dif, startstr,endstr ); \
    } while(0);

/********************************************//**
 * \brief main function
 *
 * \param None
 * \return int (0)
 *
 ***********************************************/
int main()
{
    time_t start_t,end_t;
    struct tm start_tm,end_tm;
    double dif;

    Employee *Employees;
    Employee_packed1 *Employees_packed1;
    Employee_packed2 *Employees_packed2;

    Employees = malloc(sizeof(Employee) * SPEEDTEST_NUM_RECORDS);
    Employees_packed1 = malloc(sizeof(Employee_packed1) * SPEEDTEST_NUM_RECORDS);
    Employees_packed2 = malloc(sizeof(Employee_packed2) * SPEEDTEST_NUM_RECORDS);

    show_struct_size(Employee);
    show_struct_size(Employee_packed1);
    show_struct_size(Employee_packed2);
    printf("\n");

    show_offsets(Employee);
    show_offsets(Employee_packed1);
    show_offsets(Employee_packed2);
    printf("\n");

    speed_test(Employees);
    speed_test(Employees_packed1);
    speed_test(Employees_packed2);

    free(Employees);
    free(Employees_packed1);
    free(Employees_packed2);

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>

// struct, no pack and no alignment
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
CASSERT()

// struct, packed using __attribute__ ((packed)) (GCC only)
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

// struct, packed using #pragma pack(push, 1), compatible with VS C++  compiler
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

#define show_struct_size(astruct) printf("size of " # astruct " struct = %zu\n",sizeof(astruct));

#define show_offset_of(astruct,member) printf("Offset of " # astruct "." # member " = %zu\n",offsetof(astruct,member))

#define show_offsets(astruct) \
    show_offset_of(astruct,Name); \
    show_offset_of(astruct,Surname); \
    show_offset_of(astruct,EmployeeNumber); \
    show_offset_of(astruct,Age); \
    show_offset_of(astruct,Salary); \
    show_offset_of(astruct,Gender); \
    show_offset_of(astruct,PhoneNumber); \
    printf("\n");

int main()
{
    show_struct_size(Employee);
    show_struct_size(Employee_packed1);
    show_struct_size(Employee_packed2);
    printf("\n");

    show_offsets(Employee);
    show_offsets(Employee_packed1);
    show_offsets(Employee_packed2);
    printf("\n");

    return 0;
}
